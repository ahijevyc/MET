// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2007
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

////////////////////////////////////////////////////////////////////////

#ifndef  __VX_MET_UTIL_CONSTANTS_H__
#define  __VX_MET_UTIL_CONSTANTS_H__

////////////////////////////////////////////////////////////////////////

static const char met_version[]     = "V2.0";
static const char met_base_str[]    = "MET_BASE";
static const char txt_file_ext[]    = ".txt";
static const char stat_file_ext[]   = ".stat";
static const char full_domain_str[] = "FULL";

static const char * const proj_type[4] = {
   "LatLon", 
   "Mercator", 
   "Lambert Conformal",
   "Polar Stereographic"
};

// String containing all valid PrepBufr message types
static const char all_msg_typ_str[] = 
"ADPUPA AIRCAR AIRCFT ADPSFC ERS1DA GOESND GPSIPW MSONET PROFLR QKSWND RASSDA SATEMP SATWND SFCBOG SFCSHP SPSSMI SYNDAT VADWND ANYAIR ANYSFC ONLYSF";

// Special PrepBufr message types
static const char anyair_str[]         = "ANYAIR";
static const char anyair_msg_typ_str[] = "AIRCAR AIRCFT";
static const char anysfc_str[]         = "ANYSFC";
static const char anysfc_msg_typ_str[] = "ADPSFC SFCSHP ADPUPA PROFLR";
static const char onlysf_str[]         = "ONLYSF";
static const char onlysf_msg_typ_str[] = "ADPSFC SFCSHP";

// String containing all interpolation methods
static const char all_interp_mthd_str[] = 
   "MIN MAX MEDIAN UW_MEAN DW_MEAN LS_FIT";

// Commonly used regular expressions
static const char yyyymmdd_hhmmss_reg_exp[] =
   "[0-9]\\{8,8\\}_[0-9]\\{6,6\\}";
static const char non_ws_reg_exp[] = "[a-zA-Z0-9]";

// Bootstrap methods
static const int boot_bca_flag  = 0;
static const int boot_perc_flag = 1;

////////////////////////////////////////////////////////////////////////

static const int max_str_len  = 512;
static const int max_line_len = 2048;
static const double grib_earth_radius_km = 6367.47;
static const int default_precision = 5;

////////////////////////////////////////////////////////////////////////

// Constants used in deriving observation values
static const double const_a     = 1.0/273.15;
static const double const_b     = 2500000.0/461.5;
static const double const_c     = 6.11;

// Constants used in deriving PRMSL
static const double const_tmb   = 288.15;  // kelvin
static const double const_gop   = 9.80616; // from The Ceaseless Wind
static const double const_rd    = 287.0;   // kg/k dry gas constant

////////////////////////////////////////////////////////////////////////

#endif   //  __VX_MET_UTIL_CONSTANTS_H__

////////////////////////////////////////////////////////////////////////
