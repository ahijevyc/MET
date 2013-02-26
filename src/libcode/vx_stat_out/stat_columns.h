// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2012
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

////////////////////////////////////////////////////////////////////////

#ifndef  __STAT_COLUMNS_H__
#define  __STAT_COLUMNS_H__

////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

#include "stat_hdr_columns.h"

#include "vx_statistics.h"

////////////////////////////////////////////////////////////////////////

static const char * hdr_columns [] = {
   "VERSION",        "MODEL",
   "FCST_LEAD",      "FCST_VALID_BEG",
   "FCST_VALID_END", "OBS_LEAD",
   "OBS_VALID_BEG",  "OBS_VALID_END",
   "FCST_VAR",       "FCST_LEV",
   "OBS_VAR",        "OBS_LEV",
   "OBTYPE",         "VX_MASK",
   "INTERP_MTHD",    "INTERP_PNTS",
   "FCST_THRESH",    "OBS_THRESH",
   "COV_THRESH",     "ALPHA",
   "LINE_TYPE"
};

static const char * fho_columns [] = {
   "TOTAL",       "F_RATE",      "H_RATE",
   "O_RATE"
};

static const char * ctc_columns [] = {
   "TOTAL",       "FY_OY",       "FY_ON",
   "FN_OY",       "FN_ON"
};

static const char * ctp_columns [] = {
   "TOTAL",       "FY_OY_TP",    "FY_ON_TP",
   "FN_OY_TP",    "FN_ON_TP",    "FY_TP",
   "FN_TP",       "OY_TP",       "ON_TP"
};

static const char * cfp_columns [] = {
   "TOTAL",       "FY_OY_FP",    "FY_ON_FP",
   "FN_OY_FP",    "FN_ON_FP",    "FY",
   "FN"
};

static const char * cop_columns [] = {
   "TOTAL",       "FY_OY_OP",    "FY_ON_OP",
   "FN_OY_OP",    "FN_ON_OP",    "OY",
   "ON"
};

static const char * cts_columns [] = {
   "TOTAL",
   "BASER",       "BASER_NCL",   "BASER_NCU",   "BASER_BCL",   "BASER_BCU",
   "FMEAN",       "FMEAN_NCL",   "FMEAN_NCU",   "FMEAN_BCL",   "FMEAN_BCU",
   "ACC",         "ACC_NCL",     "ACC_NCU",     "ACC_BCL",     "ACC_BCU",
   "FBIAS",       "FBIAS_BCL",   "FBIAS_BCU",
   "PODY",        "PODY_NCL",    "PODY_NCU",    "PODY_BCL",    "PODY_BCU",
   "PODN",        "PODN_NCL",    "PODN_NCU",    "PODN_BCL",    "PODN_BCU",
   "POFD",        "POFD_NCL",    "POFD_NCU",    "POFD_BCL",    "POFD_BCU",
   "FAR",         "FAR_NCL",     "FAR_NCU",     "FAR_BCL",     "FAR_BCU",
   "CSI",         "CSI_NCL",     "CSI_NCU",     "CSI_BCL",     "CSI_BCU",
   "GSS",         "GSS_BCL",     "GSS_BCU",
   "HK",          "HK_NCL",      "HK_NCU",      "HK_BCL",      "HK_BCU",
   "HSS",         "HSS_BCL",     "HSS_BCU",
   "ODDS",        "ODDS_NCL",    "ODDS_NCU",    "ODDS_BCL",    "ODDS_BCU"
};

static const char * mctc_columns [] = {
   "TOTAL",       "N_CAT"
};

static const char * mcts_columns [] = {
   "TOTAL",       "N_CAT",
   "ACC",         "ACC_NCL",     "ACC_NCU",     "ACC_BCL",     "ACC_BCU",
   "HK",          "HK_BCL",      "HK_BCU",
   "HSS",         "HSS_BCL",     "HSS_BCU",
   "GER",         "GER_BCL",     "GER_BCU"
};

static const char * cnt_columns [] = {
   "TOTAL",
   "FBAR",        "FBAR_NCL",    "FBAR_NCU",    "FBAR_BCL",    "FBAR_BCU",
   "FSTDEV",      "FSTDEV_NCL",  "FSTDEV_NCU",  "FSTDEV_BCL",  "FSTDEV_BCU",
   "OBAR",        "OBAR_NCL",    "OBAR_NCU",    "OBAR_BCL",    "OBAR_BCU",
   "OSTDEV",      "OSTDEV_NCL",  "OSTDEV_NCU",  "OSTDEV_BCL",  "OSTDEV_BCU",
   "PR_CORR",     "PR_CORR_NCL", "PR_CORR_NCU", "PR_CORR_BCL", "PR_CORR_BCU",
   "SP_CORR",
   "KT_CORR",
   "RANKS",
   "FRANK_TIES",
   "ORANK_TIES",
   "ME",          "ME_NCL",      "ME_NCU",      "ME_BCL",      "ME_BCU",
   "ESTDEV",      "ESTDEV_NCL",  "ESTDEV_NCU",  "ESTDEV_BCL",  "ESTDEV_BCU",
   "MBIAS",       "MBIAS_BCL",   "MBIAS_BCU",
   "MAE",         "MAE_BCL",     "MAE_BCU",
   "MSE",         "MSE_BCL",     "MSE_BCU",
   "BCMSE",       "BCMSE_BCL",   "BCMSE_BCU",
   "RMSE",        "RMSE_BCL",    "RMSE_BCU",
   "E10",         "E10_BCL",     "E10_BCU",
   "E25",         "E25_BCL",     "E25_BCU",
   "E50",         "E50_BCL",     "E50_BCU",
   "E75",         "E75_BCL",     "E75_BCU",
   "E90",         "E90_BCL",     "E90_BCU"
};

static const char * sl1l2_columns [] = {
   "TOTAL",       "FBAR",        "OBAR",
   "FOBAR",       "FFBAR",       "OOBAR"
};

static const char * sal1l2_columns [] = {
   "TOTAL",       "FABAR",       "OABAR",
   "FOABAR",      "FFABAR",      "OOABAR"
};

static const char * vl1l2_columns [] = {
   "TOTAL",       "UFBAR",       "VFBAR",
   "UOBAR",       "VOBAR",       "UVFOBAR",
   "UVFFBAR",     "UVOOBAR"
};

static const char * val1l2_columns [] = {
   "TOTAL",       "UFABAR",      "VFABAR",
   "UOABAR",      "VOABAR",      "UVFOABAR",
   "UVFFABAR",    "UVOOABAR"
};

static const char * pct_columns [] = {
   "TOTAL",       "N_THRESH",    "THRESH_",
   "OY_",         "ON_"
};

static const char * pstd_columns [] = {
   "TOTAL",       "N_THRESH",    "BASER",
   "BASER_NCL",   "BASER_NCU",   "RELIABILITY",
   "RESOLUTION",  "UNCERTAINTY", "ROC_AUC",
   "BRIER",       "BRIER_NCL",   "BRIER_NCU",
   "THRESH_"
};

static const char * pjc_columns [] = {
   "TOTAL",       "N_THRESH",    "THRESH_",
   "OY_TP_",      "ON_TP_",      "CALIBRATION_",
   "REFINEMENT_", "LIKELIHOOD_", "BASER_"
};

static const char * prc_columns [] = {
   "TOTAL",       "N_THRESH",    "THRESH_",
   "PODY_",       "POFD_"
};

static const char * mpr_columns [] = {
   "TOTAL",       "INDEX",       "OBS_SID",
   "OBS_LAT",     "OBS_LON",     "OBS_LVL",
   "OBS_ELV",     "FCST",        "OBS",
   "CLIMO"
};

static const char * nbrctc_columns [] = {
   "TOTAL",       "FY_OY",       "FY_ON",
   "FN_OY",       "FN_ON"
};

static const char * nbrcts_columns [] = {
   "TOTAL",
   "BASER",       "BASER_NCL",   "BASER_NCU",   "BASER_BCL",   "BASER_BCU",
   "FMEAN",       "FMEAN_NCL",   "FMEAN_NCU",   "FMEAN_BCL",   "FMEAN_BCU",
   "ACC",         "ACC_NCL",     "ACC_NCU",     "ACC_BCL",     "ACC_BCU",
   "FBIAS",       "FBIAS_BCL",   "FBIAS_BCU",
   "PODY",        "PODY_NCL",    "PODY_NCU",    "PODY_BCL",    "PODY_BCU",
   "PODN",        "PODN_NCL",    "PODN_NCU",    "PODN_BCL",    "PODN_BCU",
   "POFD",        "POFD_NCL",    "POFD_NCU",    "POFD_BCL",    "POFD_BCU",
   "FAR",         "FAR_NCL",     "FAR_NCU",     "FAR_BCL",     "FAR_BCU",
   "CSI",         "CSI_NCL",     "CSI_NCU",     "CSI_BCL",     "CSI_BCU",
   "GSS",         "GSS_BCL",     "GSS_BCU",
   "HK",          "HK_NCL",      "HK_NCU",      "HK_BCL",      "HK_BCU",
   "HSS",         "HSS_BCL",     "HSS_BCU",
   "ODDS",        "ODDS_NCL",    "ODDS_NCU",    "ODDS_BCL",    "ODDS_BCU"
};

static const char * nbrcnt_columns [] = {
   "TOTAL",
   "FBS",         "FBS_BCL",     "FBS_BCU",
   "FSS",         "FSS_BCL",     "FSS_BCU"
};

static const char * isc_columns [] = {
   "TOTAL",
   "TILE_DIM",    "TILE_XLL",    "TILE_YLL",
   "NSCALE",      "ISCALE",      "MSE",
   "ISC",         "FENERGY2",    "OENERGY2",
   "BASER",       "FBIAS"
};

static const char * rhist_columns [] = {
   "TOTAL",       "CRPS",        "IGN",
   "N_RANK",      "RANK_"
};

static const char * orank_columns [] = {
   "TOTAL",       "INDEX",       "OBS_SID",
   "OBS_LAT",     "OBS_LON",     "OBS_LVL",
   "OBS_ELV",     "OBS",         "PIT",
   "RANK",        "N_ENS_VLD",   "N_ENS",
   "ENS_"
};

static const char * ssvar_columns [] = {
   "TOTAL",       "N_BIN",       "BIN_i",
   "BIN_N",       "VAR_MIN",     "VAR_MAX",
   "VAR_MEAN",    "FBAR",        "OBAR",
   "FOBAR",       "FFBAR",       "OOBAR"
};

static const char * job_sum_columns [] = {
   "TOTAL",
   "MEAN",        "MEAN_NCL",    "MEAN_NCU",     "MEAN_BCL",    "MEAN_BCU",
   "STDEV",       "STDEV_BCL",   "STDEV_BCU",
   "MIN",
   "P10",         "P25",         "P50",          "P75",         "P90",
   "MAX"
};

static const char * job_go_columns [] = {
   "GO_INDEX"
};

static const char * job_ss_columns [] = {
   "SS_INDEX"
};

static const char * job_wdir_columns [] = {
   "TOTAL",
   "FBAR",        "OBAR",        "ME",           "MAE"
};

////////////////////////////////////////////////////////////////////////

static const int max_stat_col       = 73;
static const int stat_col_len       = 32;

static const int n_header_columns   = sizeof(hdr_columns)/sizeof(*hdr_columns);
static const int n_fho_columns      = sizeof(fho_columns)/sizeof(*fho_columns);
static const int n_ctc_columns      = sizeof(ctc_columns)/sizeof(*ctc_columns);
static const int n_ctp_columns      = sizeof(ctp_columns)/sizeof(*ctp_columns);
static const int n_cfp_columns      = sizeof(cfp_columns)/sizeof(*cfp_columns);
static const int n_cop_columns      = sizeof(cop_columns)/sizeof(*cop_columns);
static const int n_cts_columns      = sizeof(cts_columns)/sizeof(*cts_columns);
static const int n_mctc_columns     = sizeof(mctc_columns)/sizeof(*mctc_columns);
static const int n_mcts_columns     = sizeof(mcts_columns)/sizeof(*mcts_columns);
static const int n_cnt_columns      = sizeof(cnt_columns)/sizeof(*cnt_columns);
static const int n_sl1l2_columns    = sizeof(sl1l2_columns)/sizeof(*sl1l2_columns);
static const int n_sal1l2_columns   = sizeof(sal1l2_columns)/sizeof(*sal1l2_columns);
static const int n_vl1l2_columns    = sizeof(vl1l2_columns)/sizeof(*vl1l2_columns);
static const int n_val1l2_columns   = sizeof(val1l2_columns)/sizeof(*val1l2_columns);

static const int n_pct_columns      = sizeof(pct_columns)/sizeof(*pct_columns);
static const int n_pstd_columns     = sizeof(pstd_columns)/sizeof(*pstd_columns);
static const int n_pjc_columns      = sizeof(pjc_columns)/sizeof(*pjc_columns);
static const int n_prc_columns      = sizeof(prc_columns)/sizeof(*prc_columns);

static const int n_mpr_columns      = sizeof(mpr_columns)/sizeof(*mpr_columns);
static const int n_nbrctc_columns   = sizeof(nbrctc_columns)/sizeof(*nbrctc_columns);
static const int n_nbrcts_columns   = sizeof(nbrcts_columns)/sizeof(*nbrcts_columns);
static const int n_nbrcnt_columns   = sizeof(nbrcnt_columns)/sizeof(*nbrcnt_columns);
static const int n_isc_columns      = sizeof(isc_columns)/sizeof(*isc_columns);
static const int n_job_sum_columns  = sizeof(job_sum_columns)/sizeof(*job_sum_columns);
static const int n_job_go_columns   = sizeof(job_go_columns)/sizeof(*job_go_columns);
static const int n_job_ss_columns   = sizeof(job_ss_columns)/sizeof(*job_ss_columns);
static const int n_job_wdir_columns = sizeof(job_wdir_columns)/sizeof(*job_wdir_columns);

static const int n_rhist_columns    = sizeof(rhist_columns)/sizeof(*rhist_columns);
static const int n_orank_columns    = sizeof(orank_columns)/sizeof(*orank_columns);
static const int n_ssvar_columns    = sizeof(ssvar_columns)/sizeof(*ssvar_columns);

////////////////////////////////////////////////////////////////////////

inline int get_n_mctc_columns  (int n) { return(2  + n*n); }
inline int get_n_pct_columns   (int n) { return(3  + 3*(max(1, n)-1)); }
inline int get_n_pstd_columns  (int n) { return(12 +    max(1, n)   ); }
inline int get_n_pjc_columns   (int n) { return(3  + 7*(max(1, n)-1)); }
inline int get_n_prc_columns   (int n) { return(3  + 3*(max(1, n)-1)); }
inline int get_n_rhist_columns (int n) { return(4  + n);               } // n = N_RANK
inline int get_n_orank_columns (int n) { return(12 + n);               } // n = N_ENS

////////////////////////////////////////////////////////////////////////

extern int get_column_offset      (const char **, int, const char *);
extern int get_mctc_column_offset (const char *, int);
extern int get_pct_column_offset  (const char *);
extern int get_pstd_column_offset (const char *);
extern int get_pjc_column_offset  (const char *);
extern int get_prc_column_offset  (const char *);
extern int get_rhist_column_offset(const char *);
extern int get_orank_column_offset(const char *);

////////////////////////////////////////////////////////////////////////

extern int  parse_thresh_index(const char *);
extern void parse_row_col(const char *, int &, int &);

////////////////////////////////////////////////////////////////////////

extern void open_txt_file (ofstream *&,  const char *);
extern void close_txt_file(ofstream *&,  const char *);

////////////////////////////////////////////////////////////////////////

// Write out the header row for fixed length line types
extern void write_header_row(const char **, int, int, AsciiTable &, int, int);

// Write out the header row for variable length line types
extern void write_mctc_header_row  (int, int, AsciiTable &, int, int);
extern void write_pct_header_row   (int, int, AsciiTable &, int, int);
extern void write_pstd_header_row  (int, int, AsciiTable &, int, int);
extern void write_pjc_header_row   (int, int, AsciiTable &, int, int);
extern void write_prc_header_row   (int, int, AsciiTable &, int, int);
extern void write_rhist_header_row (int, int, AsciiTable &, int, int);
extern void write_orank_header_row (int, int, AsciiTable &, int, int);

extern void write_fho_row   (StatHdrColumns &, const CTSInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_ctc_row   (StatHdrColumns &, const CTSInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_cts_row   (StatHdrColumns &, const CTSInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_mctc_row  (StatHdrColumns &, const MCTSInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_mcts_row  (StatHdrColumns &, const MCTSInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_cnt_row   (StatHdrColumns &, const CNTInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_sl1l2_row (StatHdrColumns &, const CNTInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_sl1l2_row (StatHdrColumns &, const SL1L2Info &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_sal1l2_row(StatHdrColumns &, const SL1L2Info &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_vl1l2_row (StatHdrColumns &, const VL1L2Info &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_val1l2_row(StatHdrColumns &, const VL1L2Info &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_pct_row   (StatHdrColumns &, const PCTInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_pstd_row  (StatHdrColumns &, const PCTInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_pjc_row   (StatHdrColumns &, const PCTInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_prc_row   (StatHdrColumns &, const PCTInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_nbrctc_row(StatHdrColumns &, const NBRCTSInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_nbrcts_row(StatHdrColumns &, const NBRCTSInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_nbrcnt_row(StatHdrColumns &, const NBRCNTInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_mpr_row   (StatHdrColumns &, const PairDataPoint *, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_isc_row   (StatHdrColumns &, const ISCInfo &, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_rhist_row (StatHdrColumns &, const PairDataEnsemble *, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_orank_row (StatHdrColumns &, const PairDataEnsemble *, bool,
                             AsciiTable &, int &, AsciiTable &, int &);
extern void write_ssvar_row (StatHdrColumns &, const PairDataEnsemble *, bool,
                             AsciiTable &, int &, AsciiTable &, int &);

////////////////////////////////////////////////////////////////////////

// Write out the column headers
extern void write_header_cols(const StatHdrColumns &,  AsciiTable &, int);

// Write out the columns of data specific to each line type
extern void write_fho_cols   (const CTSInfo &,          AsciiTable &, int, int);
extern void write_ctc_cols   (const CTSInfo &,          AsciiTable &, int, int);
extern void write_cts_cols   (const CTSInfo &,     int, AsciiTable &, int, int);
extern void write_mctc_cols  (const MCTSInfo &,         AsciiTable &, int, int);
extern void write_mcts_cols  (const MCTSInfo &,    int, AsciiTable &, int, int);
extern void write_cnt_cols   (const CNTInfo &,     int, AsciiTable &, int, int);
extern void write_sl1l2_cols (const CNTInfo &,          AsciiTable &, int, int);
extern void write_sl1l2_cols (const SL1L2Info &,        AsciiTable &, int, int);
extern void write_sal1l2_cols(const SL1L2Info &,        AsciiTable &, int, int);
extern void write_vl1l2_cols (const VL1L2Info &,        AsciiTable &, int, int);
extern void write_val1l2_cols(const VL1L2Info &,        AsciiTable &, int, int);
extern void write_pct_cols   (const PCTInfo &,          AsciiTable &, int, int);
extern void write_pstd_cols  (const PCTInfo &,     int, AsciiTable &, int, int);
extern void write_pjc_cols   (const PCTInfo &,          AsciiTable &, int, int);
extern void write_prc_cols   (const PCTInfo &,          AsciiTable &, int, int);
extern void write_nbrctc_cols(const NBRCTSInfo &,       AsciiTable &, int, int);
extern void write_nbrcts_cols(const NBRCTSInfo &,  int, AsciiTable &, int, int);
extern void write_nbrcnt_cols(const NBRCNTInfo &,  int, AsciiTable &, int, int);
extern void write_nbrcnt_cols(const NBRCNTInfo &,  int, AsciiTable &, int, int);
extern void write_mpr_cols   (const PairDataPoint *,    int, AsciiTable &, int, int);
extern void write_isc_cols   (const ISCInfo &,     int, AsciiTable &, int, int);
extern void write_rhist_cols (const PairDataEnsemble *,      AsciiTable &, int, int);
extern void write_orank_cols (const PairDataEnsemble *, int, AsciiTable &, int, int);
extern void write_ssvar_cols (const PairDataEnsemble *, int, AsciiTable &, int, int);

////////////////////////////////////////////////////////////////////////

#endif   /*  __STAT_COLUMNS_H__  */

////////////////////////////////////////////////////////////////////////
