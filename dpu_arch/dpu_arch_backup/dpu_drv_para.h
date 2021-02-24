#ifndef _DPU_DRV_PARA_H
#define _DPU_DRV_PARA_H
#include "dpu_fmt.h"

#include <string>

using namespace ck;
enum func_mode_e
{
    DPUF_INP,
    DPUF_STR_UPSCL,
    DPUF_PAN_UPSCL,
    DPUF_CSC_PLANE,
    DPUF_CSC_CURSOR,
    DPUF_CURSOR,
    DPUF_OVERLAY,
    DPUF_LUT,
    DPUF_DITHER,
    DPUF_OUT,
    DPUF_SIGNATURE,
    DPUF_FUNC_NUM
};
using input_arg_t = struct _inpat
{
    uint32_t spl_abgr{};
    uint32_t spl_cbycry{};
    uint32_t spl_crycb{};
};
using dither_t = struct _ditt
{
    bool en{};
    uint32_t rgb_src{};
    uint32_t rgb_dst{};
    uint32_t rgb_op{};
    uint32_t alpha_src{};
    uint32_t alpha_dst{};
    uint32_t alpha_op{};
    uint32_t bld_color{};
};
using cursor_t = struct _curt
{
    bool en{};
    bool is_cbcr{};
    
};
using scl_t = struct _sclt
{
    bool en{};
    bool h_en, v_en;
    bool is_cos_h{};
    bool is_cos_v{};
    bool is_alpha_ups{};
    bool is_color_key{};
    bool is_v_duplicate{};
    uint32_t keyl{};
    uint32_t keyh{};
    uint32_t key_mode{};
    uint32_t h_acc{};
    uint32_t v_acc{};

    bool is_cos{};
    bool is_hw_ratio;
    bool ratio_plus;
};
using ovl_t = struct _ovlt
{
    bool en{};
    bool efuse_sec{};
    bool itg_hden{};
    bool itg_vden{};
    uint32_t key_mode_0;
    uint32_t pla_fct_0;
    uint32_t plb_fct_0;
    uint32_t bld_mode_0;
    bool is_inv_alpha_0;
    uint32_t plane_alpha_val_0;
    uint32_t alpha_key_sel_0;
    uint32_t color_key_sel_0;
    bool is_alpha_rang_0;
    uint32_t key_mode_1;
    uint32_t pla_fct_1;
    uint32_t plb_fct_1;
    uint32_t bld_mode_1;
    bool is_inv_alpha_1;
    uint32_t plane_alpha_val_1;
    uint32_t alpha_key_sel_1;
    uint32_t color_key_sel_1;
    bool is_alpha_rang_1;
    bool is_mdi_sec_0;
    bool is_ycbcr_0;
    bool is_mdi_sec_1;
    bool is_ycbcr_1;
    uint32_t curs_ovl_tp;
    bool curs_ycbcr;
    bool is_ref_int_c;
    bool is_ref_int_0;
    bool is_ref_int_1;
};
using csc_t = struct _csct
{
    bool src_rgb{}; ///< RGB or YCbCr source.
    bool dst_rgb{}; ///< RGB or YCbCr destination.
    bool src_range_full{}; ///< Full or limited range for source.
    bool dst_range_full{}; ///< Full or limited range for destination.
    std::string gamut{}; ///< Gamut name.
    int32_t bright_drv{}; ///< Programmable brightness offset (actual value).
    uint32_t infmt{}; ///< Input format index.
    uint32_t outfmt{}; ///< Output format index.
    uint32_t bright{}; ///< Programmable brightness offset (fixed point value).
    bool prog{}; ///< Programmable matrix and brightness offset.
    uint32_t coefs[3][3]{}; ///< 3x3 matrix coefficients.
};
using dpu_drv_para_t = struct _ddpt
{
    image_tag s0_tag{};
    image_tag s1_tag{};
    image_tag cur_tag{};
    image_tag d_tag{};
    dpu_fmt_c s0fmt,s1fmt,cfmt,dfmt;
    cursor_t cursor{};
    input_arg_t inp{};
    scl_t scl{};
    ovl_t ovl{};
    func_mode_e work_mode{};
    dither_t dither{};
    csc_t csc_plane{};
    csc_t csc_cursor{};
    uint32_t bg_color;
    bool bg_ycbcr;
    //this structure have all parameters 
};
#endif // !_DPU_DRV_PARA_H

