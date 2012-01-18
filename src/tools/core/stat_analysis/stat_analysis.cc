// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2012
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

////////////////////////////////////////////////////////////////////////
//
//   Filename:   stat_analysis.cc
//
//   Description:
//      Based on user specified options, this tool performs a variety
//      of analysis jobs on the STAT output of the Grid-Stat,
//      Point-Stat, and Wavelet-Stat tools.
//
//   Mod#   Date      Name            Description
//   ----   ----      ----            -----------
//   000    09/05/07  Halley Gotway   New
//   001    07/01/08  Halley Gotway   Add the rank_corr_flag to the
//                    config file to disable computing rank
//                    correlations.
//   002    06/21/10  Halley Gotway   Add the vif_flag to correct normal
//                    CI's for time series aggregations.
//   003    08/15/11  Oldenburg       Fix a bug related to parsing the
//                    config file alpha value list
//   004    08/16/11  Halley Gotway   Reimplementation of GO Index job
//                    with addition of generalized Skill Score Index
//   005    10/26/11  Holmes          Added use of command line class to
//                                    parse the command line arguments.
//   006    11/14/11  Holmes          Added code to enable reading of
//                                    multiple config files.
//
////////////////////////////////////////////////////////////////////////

using namespace std;

#include <cmath>
#include <cstdio>
#include <dirent.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "vx_log.h"

#include "stat_analysis.h"
#include "parse_stat_line.h"
#include "aggr_stat_line.h"
#include "stat_analysis_job.h"

////////////////////////////////////////////////////////////////////////

static void parse_command_line(int &argc, char **argv);
static void sanity_check();
static void usage();
static void set_lookin_path(const StringArray &);
static void set_out_filename(const StringArray &);
static void set_tmp_dir(const StringArray &);
static void set_logfile(const StringArray &);
static void set_verbosity_level(const StringArray &);
static void set_config_file(const StringArray &);
static void process_search_dirs();
static void process_stat_file(const char *, const STATAnalysisJob &,
                              int &, int &);
static void process_job(const char *, int);
static void clean_up();

//
// Routines for command-line switches
//
static void set_config(const char *);
static void set_search_dir(const char *);
static void set_out_file(const char *);
static void set_verbosity(int);

////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv []) {
   int i, n;
   Result r;
   char default_conf_file[PATH_MAX];

   //
   // Set handler to be called for memory allocation error
   //
   set_new_handler(oom);

   //
   // Parse the command line
   //
   parse_command_line(argc, argv);

   //
   // If a config file was specified, set up the default job using the
   // config file.
   //
   if(config_file.length() != 0) {

      //
      // Read the default config file first and then read the user's
      //
      replace_string(met_base_str, MET_BASE, default_config_filename, default_conf_file);
      mlog << Debug(1) << "Reading Default Config: " << default_conf_file << "\n";
      conf.read(default_conf_file);
      mlog << Debug(1) << "Reading User Config: " << config_file << "\n";
      conf.read(config_file);

      //
      // Sanity check the command line and config file options
      //
      sanity_check();

      //
      // Setup the default job using the options specified in the config
      // file
      //
      default_job.clear();
      set_job_from_config(conf, default_job);
   }

   //
   // Enclose within a try block to catch any run time errors, and
   // delete the temp file before exiting.
   //
   try {

      //
      // Process the STAT files found in the search directories.
      //
      process_search_dirs();

      //
      // If a config file was specified, process the jobs in the config
      // file.
      //
      if(config_file.length() != 0) {

         n = conf.n_jobs_elements();

         for(i=0; i<n; i++) {
            r = conf.jobs(i);
            process_job(r.sval(), i+1);
         }
      }
      //
      // Otherwise, process the job specified on the command line.
      //
      else {
         process_job(command_line_job, 1);
      }

   }
   catch(int j) { // Catch an error

      mlog << Error << "\n  main() -> "
           << "encountered an error value of " << j
           << ".  Calling clean_up() and usage() before exiting.\n\n";

      clean_up();
      usage();
   }

   //
   // Deallocate memory and clean up
   //
   clean_up();

   return(0);
}

////////////////////////////////////////////////////////////////////////

void parse_command_line(int &argc, char **argv) {
   CommandLine cline;
   ConcatString cmd_line_job;
   int i;

   //
   // check for zero arguments
   //
   if (argc == 1)
      usage();

   config_file.erase();

   //
   // parse the command line into tokens
   //
   cline.set(argc, argv);

   //
   // Allow for unrecognized command line switches.
   // This must be called after set above since set calls
   // clear which would reset this to false.
   // This allows us to be able to handle single jobs on
   // the command line.
   //
   cline.allow_unrecognized_switches();

   //
   // set the usage function
   //
   cline.set_usage(usage);

   //
   // add the options function calls
   //
   cline.add(set_lookin_path, "-lookin", -1);
   cline.add(set_out_filename, "-out", 1);
   cline.add(set_tmp_dir, "-tmp_dir", 1);
   cline.add(set_logfile, "-log", 1);
   cline.add(set_verbosity_level, "-v", 1);
   cline.add(set_config_file, "-config", 1);

   //
   // parse the command line
   //
   cline.parse();

   //
   // If no config file was specified, parse out the STAT Analysis job
   // command from the command line.
   //
   if(config_file.length() == 0) {

      cmd_line_job.erase();

      for(i=0; i<cline.n(); i++) {

         //
         // build the command line back up from the leftover arguments
         //
         cmd_line_job << cline[i];

         //
         // add a space between arguments, except for the last argument
         //
         if (i + 1 != cline.n())
            cmd_line_job << ' ';
      } // end for

      //
      // Store the remaining options as the STAT Command Line job
      //
      if (cmd_line_job.length() > 0)
         strcpy(command_line_job, cmd_line_job);
   } // end if

   //
   // Check for at least one search file or directory
   //
   if(search_dirs.n_elements() == 0) {
      mlog << Error << "\n  parse_command_line() -> "
           << "no STAT search files or directories specified!\n\n";

      exit(1);
   }

   return;
}

////////////////////////////////////////////////////////////////////////

void sanity_check() {
   unixtime ut_beg, ut_end;

   //
   // Conf: version
   //

   check_met_version(conf.version().sval());

   //
   // Check for fcst_valid_beg > fcst_valid_end
   //
   ut_beg = timestring_to_unix(conf.fcst_valid_beg().sval());
   ut_end = timestring_to_unix(conf.fcst_valid_end().sval());

   if((ut_beg > 0) && (ut_end > 0) && (ut_beg > ut_end)) {
      mlog << Error << "\n  sanity_check() -> "
           << "fcst_valid_beg is after fcst_valid_end: "
           << conf.fcst_valid_beg().sval() << " > "
           << conf.fcst_valid_end().sval() << "!\n\n";

      exit(1);
   }

   //
   // Check for obs_valid_beg > obs_valid_end
   //
   ut_beg = timestring_to_unix(conf.obs_valid_beg().sval());
   ut_end = timestring_to_unix(conf.obs_valid_end().sval());

   if((ut_beg > 0) && (ut_end > 0) && (ut_beg > ut_end)) {
      mlog << Error << "\n  sanity_check() -> "
           << "obs_valid_beg is after obs_valid_end: "
           << conf.obs_valid_beg().sval() << " > "
           << conf.obs_valid_end().sval() << "!\n\n";

      exit(1);
   }

   //
   // Check for fcst_init_beg > fcst_init_end
   //
   ut_beg = timestring_to_unix(conf.fcst_init_beg().sval());
   ut_end = timestring_to_unix(conf.fcst_init_end().sval());

   if((ut_beg > 0) && (ut_end > 0) && (ut_beg > ut_end)) {
      mlog << Error << "\n  sanity_check() -> "
           << "fcst_init_beg is after fcst_init_end: "
           << conf.fcst_init_beg().sval() << " > "
           << conf.fcst_init_end().sval() << "!\n\n";

      exit(1);
   }

   //
   // Check for obs_init_beg > obs_init_end
   //
   ut_beg = timestring_to_unix(conf.obs_init_beg().sval());
   ut_end = timestring_to_unix(conf.obs_init_end().sval());

   if((ut_beg > 0) && (ut_end > 0) && (ut_beg > ut_end)) {
      mlog << Error << "\n  sanity_check() -> "
           << "obs_init_beg is after obs_init_end: "
           << conf.obs_init_beg().sval() << " > "
           << conf.obs_init_end().sval() << "!\n\n";

      exit(1);
   }

   //
   // Conf: rank_corr_flag
   //
   if(conf.rank_corr_flag().ival() != 0 &&
      conf.rank_corr_flag().ival() != 1) {
      mlog << Error << "\n  sanity_check() -> "
           << "The rank_corr_flag (" << conf.rank_corr_flag().ival()
           << ") must be set to 0 or 1.\n\n";
      exit(1);
   }

   //
   // Conf: vif_flag
   //
   if(conf.vif_flag().ival() != 0 &&
      conf.vif_flag().ival() != 1) {
      mlog << Error << "\n  sanity_check() -> "
           << "The vif_flag (" << conf.vif_flag().ival()
           << ") must be set to 0 or 1.\n\n";
      exit(1);
   }

   //
   // Conf: tmp_dir
   //
   if(opendir(conf.tmp_dir().sval()) == NULL ) {
      mlog << Error << "\n  sanity_check() -> "
           << "Cannot access the tmp_dir temporary directory: "
           << conf.tmp_dir().sval() << "\n\n";
      exit(1);
   }

   return;
}

////////////////////////////////////////////////////////////////////////

void set_config(const char *path) {

   config_file = path;

   return;
}

////////////////////////////////////////////////////////////////////////

void set_search_dir(const char *path) {

   search_dirs.add(path);

   return;
}

////////////////////////////////////////////////////////////////////////

void set_out_file(const char *path) {

   out_file = path;

   //
   // Create an output file and set the sa_out ofstream to it.
   //
   sa_out = new ofstream;
   sa_out->open(out_file);

   if(!(*sa_out)) {
      mlog << Error << "\n  set_out_file()-> "
           << "can't open the output file \"" << out_file
           << "\" for writing!\n\n";
      exit(1);
   }

   mlog << Debug(1) << "Creating STAT-Analysis output file \""
        << out_file << "\"\n";

   return;
}

////////////////////////////////////////////////////////////////////////

void set_verbosity(int i) {

   mlog.set_verbosity_level(i);

   return;
}

////////////////////////////////////////////////////////////////////////

void process_search_dirs() {
   int n, i, j, max_len, n_read, n_keep;
   STATAnalysisJob filter_job;
   stat_analysis_Conf go_conf;
   char go_conf_file[PATH_MAX];

   //
   // Initialize
   //
   n_read = n_keep = 0;

   //
   // Get the list of stat files in the search directories
   //
   files = get_stat_filenames(search_dirs);

   n = files.n_elements();

   if(n == 0) {
      mlog << Error << "\n  process_search_dirs() -> "
           << "no STAT files found in the directories specified!\n\n";

      throw(1);
   }

   //
   // Set the file searching job to the default job.
   //
   filter_job = default_job;

   //
   // For command line jobs parse the filtering criteria to be used.
   //
   if(config_file.length() == 0) {

      //
      // Parse the command line job options.
      //
      filter_job.parse_job_command(command_line_job);

      //
      // If this is a GO Index job use the GO Index filtering criteria.
      //
      if(filter_job.job_type == stat_job_go_index) {

         //
         // Read in the STATAnalysis config file which defines
         // the GO Index.
         //
         replace_string(met_base_str, MET_BASE,
                        go_index_config_file, go_conf_file);
         go_conf.read(go_conf_file);

         //
         // Parse the contents of the GO Index config file into the
         // search job.
         //
         set_job_from_config(go_conf, filter_job);

      } // end if go_index
   } // end if config_file

   //
   // Open up the temp file for storing the intermediate STAT line data
   //

   //
   // If the tmp_dir has not already been set on the command line,
   // use the config file setting or default setting.
   //
   if(tmp_dir.length() == 0) {
      if(config_file.length() != 0) tmp_dir = conf.tmp_dir().sval();
      else                          tmp_dir = default_tmp_dir;
   }

   //
   // Build the temp file name
   //
   tmp_file << tmp_dir << "/" << "tmp_stat_analysis";
   tmp_path = make_temp_file_name(tmp_file, '\0');

   //
   // Open the temp file
   //
   tmp_out.open(tmp_path);
   if(!tmp_out) {
      mlog << Error << "\n  process_search_dirs() -> "
           << "can't open the temporary file \"" << tmp_path
           << "\" for writing!\n\n";

      throw(1);
   }

   //
   // Go through each input file
   //
   max_len = 0;

   for(i=0; i<n; i++)  {
      j = strlen(files[i]);
      if(j > max_len) max_len = j;
   }
   max_len += 3;

   for(i=0; i<n; i++) {
      if(mlog.verbosity_level() > 2) {

         mlog << Debug(3) << "Processing STAT file \"" << files[i] << "\" ";

         for(j=strlen(files[i]); j<max_len; j++) mlog << '.';

         mlog << " " << i+1 << " of " << n << "\n";

         if((j%5) == 4) mlog << '\n';

      }

      process_stat_file(files[i], filter_job, n_read, n_keep);
   }

   mlog << Debug(2) << "STAT Lines read     = " << n_read << "\n";
   mlog << Debug(2) << "STAT Lines retained = " << n_keep << "\n";

   tmp_out.close();

   return;
}

////////////////////////////////////////////////////////////////////////

void process_stat_file(const char *filename, const STATAnalysisJob &j,
                       int &n_read, int &n_keep) {
   LineDataFile f;
   STATLine line;

   if(!(f.open(filename))) {
      mlog << Error << "\n  process_stat_file() -> "
           << "unable to open input stat file \""
           << filename << "\"\n\n";

      throw(1);
   }

   while(f >> line) {

      //
      // Continue if the line is not a valid STAT line type.
      //
      if(line.type() == no_stat_line_type)
         continue;

      n_read++;

      if(j.is_keeper(line)) {

         n_keep++;

         tmp_out << line;
      }
   } // end while

   f.close();

   return;
}

////////////////////////////////////////////////////////////////////////

void process_job(const char * jobstring, int n_job) {
   STATAnalysisJob job;
   ConcatString full_jobstring;

   //
   // Initialize to the default job
   //
   job = default_job;

   //
   // Parse the job command line options
   //
   job.parse_job_command(jobstring);

   //
   // Get the full jobstring
   //
   job.get_jobstring(full_jobstring);

   //
   // Do the job
   //
   do_job(full_jobstring, job, n_job, tmp_dir, tmp_path,
          sa_out);

   return;
}

////////////////////////////////////////////////////////////////////////

void clean_up() {

   //
   // Delete the temp file if it exists
   //
   if(tmp_path) remove_temp_file(tmp_path);

   return;
}

////////////////////////////////////////////////////////////////////////

void usage() {

   cout << "\n*** Model Evaluation Tools (MET" << met_version
        << ") ***\n\n"

        << "Usage: " << program_name << "\n"
        << "\t-lookin path\n"
        << "\t[-out filename]\n"
        << "\t[-tmp_dir path]\n"
        << "\t[-log file]\n"
        << "\t[-v level]\n"
        << "\t[-config config_file] | [JOB COMMAND LINE]\n\n"

        << "\twhere\t\"-lookin path\" specifies a STAT file or "
        << "top-level directory containing STAT files.  It allows the "
        << "use of wildcards (at least one required).\n"

        << "\t\t\"-out filename\" specifies a file name to which "
        << "output should be written rather than the screen (optional).\n"

        << "\t\t\"-tmp_dir path\" specifies the directory into which "
        << "temporary files should be written (optional).\n"

        << "\t\t\"-log file\" outputs log messages to the specified "
        << "file (optional).\n"

        << "\t\t\"-v level\" overrides the default level of logging ("
        << mlog.verbosity_level() << ") (optional).\n"

        << "\t\t\"-config config_file\" specifies a STATAnalysis "
        << "config file containing STATAnalysis jobs to be run.\n"

        << "\t\t\"JOB COMMAND LINE\" specifies all the arguments "
        << "necessary to perform a single STATAnalysis job.\n\n"

        << "\tNOTE: Refer to a STATAnalysis config file for details "
        << "on how to specify the JOB COMMAND LINE.\n\n"

        << flush;

   exit (1);
}

////////////////////////////////////////////////////////////////////////

void set_lookin_path(const StringArray & a)
{
   for (int i = 0; i < a.n_elements(); i++)
      set_search_dir(a[i]);
}

////////////////////////////////////////////////////////////////////////

void set_out_filename(const StringArray & a)
{
   set_out_file(a[0]);
}

////////////////////////////////////////////////////////////////////////

void set_tmp_dir(const StringArray & a)
{
   tmp_dir << a[0];
   if(opendir(tmp_dir) == NULL ) {
      mlog << Error << "\n  parse_command_line() -> "
           << "Cannot access the tmp_dir temporary directory: "
           << tmp_dir << "\n\n";
      exit(1);
   }
}

////////////////////////////////////////////////////////////////////////

void set_logfile(const StringArray & a)
{
   ConcatString filename;

   filename = a[0];

   mlog.open_log_file(filename);
}

////////////////////////////////////////////////////////////////////////

void set_verbosity_level(const StringArray & a)
{
   set_verbosity(atoi(a[0]));
}

////////////////////////////////////////////////////////////////////////

void set_config_file(const StringArray & a)
{
   set_config(a[0]);
}

////////////////////////////////////////////////////////////////////////


