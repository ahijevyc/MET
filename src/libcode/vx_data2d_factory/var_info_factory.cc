// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2007
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

///////////////////////////////////////////////////////////////////////////////
//
//   Filename:   var_info.cc
//
//   Description:
//
//   Mod#   Date      Name           Description
//   ----   ----      ----           -----------
//
///////////////////////////////////////////////////////////////////////////////

using namespace std;

#include <map>
#include <stdlib.h>
#include <strings.h>

#include "var_info_factory.h"
#include "grdfiletype_to_string.h"
#include "var_info_grib.h"
#include "var_info_nc_met.h"
#include "var_info_nc_pinterp.h"

#ifdef WITH_GRIB2
   #include "var_info_grib2.h"
#endif

#include "vx_cal.h"
#include "vx_log.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Code for class VarInfoFactory
//
///////////////////////////////////////////////////////////////////////////////

VarInfo * VarInfoFactory::new_var_info(GrdFileType t) {
   VarInfo *vi = (VarInfo *) 0;

   //
   // Switch on file type and instantiate the appropriate class.
   // The VarInfo object is allocated and needs to be deleted by caller.
   //

   switch(t) {

      case FileType_Gb1:
         vi = new VarInfoGrib;
         break;

      case FileType_Gb2:
#ifdef WITH_GRIB2
         vi = new VarInfoGrib2;
#else
         mlog << Error << "\n\n  VarInfoFactory::new_var_info() -> "
              << "Support for GRIB2 has not been compiled!\n\n";
         exit(1);
#endif
         break;

      case FileType_NcMet:
         vi = new VarInfoNcMet;
         break;

      case FileType_NcPinterp:
         vi = new VarInfoNcPinterp;
         break;

      case FileType_NcCF:
      case FileType_HdfEos:

         mlog << Error << "\n\n  VarInfoFactory::new_var_info() -> "
              << "Support for GrdFileType = " << grdfiletype_to_string(t)
              << " not yet implemented!\n\n";
         exit(1);
         break;

      default:
         mlog << Error << "\n\n  VarInfoFactory::new_var_info() -> "
              << "unsupported gridded data file type \"" << t
              << "\"\n\n";
         exit(1);
         break;
   } // end switch

   return(vi);
}

///////////////////////////////////////////////////////////////////////////////

VarInfo * VarInfoFactory::new_var_info(ConcatString s) {
   GrdFileType type;

   // Convert the string to a gridded data file type
   string_to_grdfiletype(s, type);

   return(new_var_info(type));
}

///////////////////////////////////////////////////////////////////////////////
