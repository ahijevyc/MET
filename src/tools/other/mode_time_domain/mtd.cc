

////////////////////////////////////////////////////////////////////////


static const char mtd_config_filename    [] = "../../../../data/config/MTDConfigDefault";

static const char local_config_filename  [] = "test_config";


static const char fcst_filename [] = "/scratch/bullock/files/arw_20100517_00I.nc";
// static const char  obs_filename [] = "/scratch/bullock/files/obs_20100517_01L.nc";
static const char  obs_filename [] = "/scratch/bullock/files/arw_20100517_00I.nc";

static const int min_object_size = 2000;


////////////////////////////////////////////////////////////////////////


using namespace std;

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cmath>

#include "mtd_config_info.h"
#include "mtd_file.h"
#include "interest_calc.h"
#include "3d_att_single_array.h"
#include "mtd_txt_output.h"


////////////////////////////////////////////////////////////////////////


static ConcatString program_name;


////////////////////////////////////////////////////////////////////////


int main(int argc, char * argv [])

{

program_name = get_short_name(argv[0]);

MtdConfigInfo config;

config.read_config(mtd_config_filename, local_config_filename);

// config.process_config(FileType_General_Netcdf, FileType_General_Netcdf);
config.process_config(FileType_NcMet, FileType_NcMet);

int j, k;
MtdFloatFile fcst_raw, obs_raw;
MtdFloatFile fcst_conv, obs_conv;
MtdIntFile fcst_mask, obs_mask;
MtdIntFile fcst_obj, obs_obj;
InterestCalculator calc;


if ( ! fcst_raw.read(fcst_filename) )  {

   cerr << "\n\n  " << program_name << ": unable to read fcst file \"" << fcst_filename << "\"\n\n";

   exit ( 1 );

}

if ( ! obs_raw.read(obs_filename) )  {

   cerr << "\n\n  " << program_name << ": unable to read obs file \"" << obs_filename << "\"\n\n";

   exit ( 1 );

}


calc.add(config.space_centroid_dist_wt, config.space_centroid_dist_if, &PairAtt3D::SpaceCentroidDist);
calc.add(config.time_centroid_delta_wt, config.time_centroid_delta_if, &PairAtt3D::TimeCentroidDelta);
calc.add(config.speed_delta_wt,         config.speed_delta_if,         &PairAtt3D::SpeedDelta);
calc.add(config.direction_diff_wt,      config.direction_diff_if,      &PairAtt3D::DirectionDifference);
calc.add(config.volume_ratio_wt,        config.volume_ratio_if,        &PairAtt3D::VolumeRatio);
calc.add(config.axis_angle_diff_wt,     config.axis_angle_diff_if,     &PairAtt3D::AxisDiff);
calc.add(config.start_time_delta_wt,    config.start_time_delta_if,    &PairAtt3D::StartTimeDelta);
calc.add(config.end_time_delta_wt,      config.end_time_delta_if,      &PairAtt3D::EndTimeDelta);

calc.check();



cout << "\n  fcst conv radius = " << (config.fcst_conv_radius) << "\n";
cout << "\n   obs conv radius = " << (config.obs_conv_radius) << "\n";


fcst_conv = fcst_raw.convolve(config.fcst_conv_radius);
 obs_conv =  obs_raw.convolve(config.obs_conv_radius);

fcst_mask = fcst_conv.threshold(config.fcst_conv_thresh);
 obs_mask =  obs_conv.threshold(config.obs_conv_thresh);

fcst_obj = fcst_mask;
 obs_obj =  obs_mask;

cout << "Start split\n" << flush;
fcst_obj.split();
cout << "mid split\n" << flush;
 obs_obj.split();
cout << "End split\n" << flush;


fcst_conv.write("fcst_conv.nc");
 obs_conv.write("obs_conv.nc");

fcst_mask.write("fcst_mask.nc");
 obs_mask.write("obs_mask.nc");

fcst_obj.write("fcst_obj_notoss.nc");
 obs_obj.write("obs_obj_notoss.nc");

fcst_obj.toss_small_objects(min_object_size);
 obs_obj.toss_small_objects(min_object_size);

fcst_obj.write("fcst_obj_toss.nc");
 obs_obj.write("obs_obj_toss.nc");

cout << "\n\n  fcst threshold:\n";
config.fcst_conv_thresh.dump(cout);

cout << "\n\n  obs threshold:\n";
config.obs_conv_thresh.dump(cout);


cout << "\n\n   n_header_3d_cols = " << n_header_3d_cols << '\n';
cout << "\n\n   n_3d_single_cols = " << n_3d_single_cols << '\n';

   //
   // get single attributes
   //

SingleAtt3D att;
SingleAtt3DArray fcst_att, obs_att;
// MtdIntFile s;

cout << "calculating fcst atts\n" << flush;

for (j=0; j<(fcst_obj.n_objects()); ++j)  {

   att = calc_3d_single_atts(fcst_obj, fcst_raw, config.model, j);

   att.set_fcst();

   att.set_simple();

   fcst_att.add(att);

}

cout << "calculating obs atts\n" << flush;

for (j=0; j<(obs_obj.n_objects()); ++j)  {

   att = calc_3d_single_atts(obs_obj, obs_raw, config.model, j);

   att.set_obs();

   att.set_simple();

   obs_att.add(att);

}

// s = obs_obj.select(1);
// 
// s.write("obs_1_select.nc");

// cout << "\n\n  Obs single atts:\n\n";

// obs_att.dump(cout);

do_3d_single_txt_output(fcst_att, obs_att, config, "a.txt");

PairAtt3DArray a;
PairAtt3D p;
MtdIntFile fo, oo;

cout << "\n\n  calculating pair atts\n\n";

for (j=0; j<(fcst_obj.n_objects()); ++j)  {

   fo = fcst_obj.select(j + 1);

   for (k=0; k<(obs_obj.n_objects()); ++k)  {

      oo = obs_obj.select(k + 1);

      cout << "   (" << j << ", " << k << ")\n" << flush;

      if ( (j == 4) && (k == 4) )  {

         cout << "stop\n";

      }

      p = calc_3d_pair_atts(fo, oo, fcst_att[j], obs_att[k]);

      p.set_total_interest(calc(p));

      a.add(p);

   }

}


a.dump(cout);





   //
   //  done
   //

return ( 0 );

}


////////////////////////////////////////////////////////////////////////



