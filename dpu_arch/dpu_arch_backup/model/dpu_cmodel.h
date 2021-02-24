#ifndef _DPU_CMODEL_H
#define _DPU_CMODEL_H
#include <string>

using ovl_stream = struct _ovlst
{
    unsigned int key_mode;
    unsigned int pla_fct;
    unsigned int plb_fct;
    unsigned int bld_mode;
    bool is_inv_alpha;
    unsigned int plane_alpha_val;
    unsigned int alpha_key_sel;
    unsigned int color_key_sel;
    bool is_alpha_rang;
    bool is_mdi_sec;
    bool is_ycbcr;
    bool is_ref_int;
};
using win_c = struct _win_c
{
    int x;
    int y;
    int w;
    int h;
};
using bus_1010108 = struct _bus_1010108
{
    unsigned long long BV : 10;
    unsigned long long GU : 10;
    unsigned long long RY : 10;
    unsigned long long A : 8;
    unsigned long long is_color_key : 1;
    unsigned long long is_alpha_key : 1;
    unsigned long long is_ycbcr : 1; 
    unsigned long long is_valid : 1; //internal usage
};

using inp_para = struct _ipt
{
    unsigned int spl_abgr : 1;
    unsigned int spl_cbycry : 1;
    unsigned int spl_crycb : 1;
    unsigned int pix_off : 5;
    unsigned int stride_num : 12;
};

using cur_para = struct _cpt
{
    unsigned int panel_width{};
    unsigned int panel_height{};
    unsigned int x_start{};
    unsigned int y_start{};
    unsigned int x_off{};
    unsigned int y_off{};
    unsigned int cur_size{};
    unsigned int cur_type{};
    unsigned int cur_mono_bg : 24;
    unsigned int cur_mono_fg : 24;
};

using lut_para = struct _lpt
{
    unsigned int lut_en{};
    unsigned int lut_intp_on{};
    unsigned int lut_bitwidth{};
};

using dither_para = struct _dpt
{
    unsigned int dither_en{};
    unsigned int base{};
    unsigned int bitsel{};
    unsigned int dist_en{};
};

using out_para = struct _opt
{
    unsigned int spl_abgr : 1;
    unsigned int spl_cbycry : 1;
    unsigned int spl_crycb : 1;
    unsigned int is_12bpc : 1;
};

void scl_stream_c(int src_w, int src_h, int dst_w, int dst_h, 
    bool is_cos_h, bool is_cos_v, bool is_alpha_ups, int key_mode, 
    bool is_v_duplicate, unsigned int keyl, unsigned int keyh, 
    unsigned short* psrc, unsigned short* pdst,
    unsigned int h_acc_, unsigned int v_acc_, 
    std::string svv_ckp_fn, std::string shv_ckp_fn, std::string scd_ckp_fn);

void scl_panel_c(int src_w, int src_h, int dst_w, int dst_h, 
    int surf_w, int surf_h, int rect_l, int rect_t, 
    bool is_cos, bool is_pus_en, bool is_h, bool is_v, bool is_hw_ratio, 
    bool ratio_plus, unsigned int bg_color_, unsigned short* psrc, unsigned short* pdst, 
    unsigned int h_acc_, unsigned int v_acc_, 
    std::string pid_ckp_fn, std::string pc_ckp_fn);

void overlay_c(bool efuse_sec, unsigned int res_w, unsigned int res_h,
    unsigned int reg_bg_col, bool reg_bg_ycbcr, \
    const ovl_stream& ovl0, const ovl_stream& ovl1, \
    int curs_ovl_tp, bool is_curs_ycbcr, bool is_curs_int, unsigned short* psrc_0, unsigned short* psrc_1,
    unsigned int* psrc_curs, unsigned short* pdst, \
    win_c win_0, win_c win_1, win_c win_cur, int int_st_x, int int_st_y,
    std::string oid_ckp_fn, std::string oc_ckp_fn);
/**
 * @brief Interface of DPU's plane CSC module.
 *
 * @param psrc         Source data from surface S0_SF (bus data).
 * @param pdst         Destination data to surface DST_SF (bus data).
 * @param scd_ckp_fn   Filename of the scsc_config_DONE checkpoint.
 * @param siwv_ckp_fn  Filename of the scsc_in_win_VLD checkpoint.
 *
 * @note
 * - @p psrc & @p pdst hold a surface of BGRA data.
 * - Extending rule for @p bright: bright_ext = {bright[8], bright[8:0]} (10bit)
 * - Inside the function, R/B data is switched for CSC operation.
 */
void csc_plane_c(int width, int height,
                 unsigned infmt, unsigned outfmt, unsigned bright, bool prog,
                 unsigned coef1, unsigned coef2, unsigned coef3,
                 unsigned coef4, unsigned coef5, unsigned coef6,
                 unsigned coef7, unsigned coef8, unsigned coef9,
                 const unsigned short* psrc, unsigned short* pdst,
                 std::string scd_ckp_fn, std::string siwv_ckp_fn);
/**
 * @brief Interface of DPU's cursor CSC module.
 *
 * @param psrc        Source data from cursor surface CURS_SF (bus data).
 * @param pdst        Destination data to surface DST_SF (bus data).
 * @param ccv_ckp_fn  Filename of the cur_csc_VLD checkpoint.
 *
 * @note
 * - @p psrc & @p pdst hold a surface of BGRA data.
 * - Inside the function, R/B data is switched for CSC operation.
 */
void csc_cursor_c(int width, int height,
                  unsigned outfmt,
                  const unsigned char* psrc, unsigned char* pdst,
                  std::string ccv_ckp_fn);

void input_c(unsigned short* p_src, unsigned short* p_dst, 
    unsigned int sf_w, unsigned int sf_h, unsigned int sfmt, inp_para para, 
    std::string swv_ckp_fn);

void cursor_c(unsigned short* p_cur, cur_para para, 
    unsigned short* p_cursor_out, int* w_out, int* h_out, 
    std::string cv_ckp_fn);

void lut_c(unsigned short* p_src, unsigned short* p_dst, 
    unsigned int wid, unsigned int het, lut_para para, uint32_t* table,
    std::string li_ckp_fn, std::string lc_ckp_fn);

void dither_c(unsigned short* p_src, unsigned short* p_dst, 
    unsigned int wid, unsigned int het, dither_para para, 
    std::string did_ckp_fn, std::string dc_ckp_fn);

void signature_c(int width, int height, const unsigned short* psrc, unsigned short* pdst);

void output_c(unsigned short* p_src, unsigned short* p_dst,
    unsigned int sf_w, unsigned int sf_h, unsigned int sfmt, out_para para, unsigned int hw_info);
#endif //_DPU_CMODEL_H
