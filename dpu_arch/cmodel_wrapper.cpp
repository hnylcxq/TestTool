#include"dpu_cmodel.h"
#include"cmodel_wrapper.h"


enum CK_ID
{
    SPL_WIN_VLD,
    SUPS_VWIN_VLD,
    SUPS_HWIN_VLD,
    SUPS_CONFIG_DONE,
    CUR_VLD,
    CUR_CSC_VLD,
    SCSC_IN_WIN_VLD,
    SCSC_CONFIG_DONE,
    OVL_IN_DE,
    OVL_CONFIG,
    PUS_IN_DE,
    PUS_CONFIG,
    LUT_IF,
    LUT_CONFIG,
    DIHTER_IN_DE,
    DITHER_CONFIG,
    CK_NUM
};

const static std::string FILE_NAME[CK_NUM] =
{
    "spl_win_vld",
    "sups_vwin_vld",
    "sups_hwin_vld",
    "sups_config_done",
    "cur_vld",
    "cur_csc_vld",
    "scsc_in_win_vld",
    "scsc_config_done",
    "ovl_in_de",
    "ovl_config",
    "pus_in_de",
    "pus_config",
    "lut_if",
    "lut_config",
    "dihter_in_de",
    "dither_config",
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


bool m_is_chk_en = false;
bool m_is_ref_chk_en = false;


void scl_stream_wrapper(struct scl_stream_para_t *para)
{
    //set parameters here
    //assign parameters to function
    //input fmt must be bus format
    int src_w = para->src_w;
    int src_h = para->src_h;
    int dst_w = para->dst_w;
    int dst_h = para->dst_h;
    bool is_cos_h = para->is_cos_h;
    bool is_cos_v = para->is_cos_v;
    bool is_alpha_ups = para->is_alpha_ups;
    //bool is_color_key =1;// m_dp.scl.key_mode > 0;
    bool is_v_duplicate = para->is_v_duplicate;
    unsigned int keyl = para->keyl;
    unsigned int keyh = para->keyh;
    unsigned int key_mode = para->key_mode;
    unsigned int h_acc_ = para->h_acc;
    unsigned int v_acc_ = para->v_acc;

	if(!para->src  || !para->dst)
	{
		printf("%s: Error surface is null src %p dst %p\n", __func__, para->src, para->dst);
	}
    scl_stream_c(src_w, src_h, dst_w, dst_h, is_cos_h, is_cos_v,
            is_alpha_ups, key_mode, is_v_duplicate, keyl, keyh,
            (uint16_t*)para->src, (uint16_t*)para->dst, h_acc_, v_acc_,
            FILE_NAME[SUPS_VWIN_VLD], FILE_NAME[SUPS_HWIN_VLD], FILE_NAME[SUPS_CONFIG_DONE]);
    
}


void scl_panel_wrapper(struct scl_panel_para_t *para)
{
    //set parameters here
    //assign parameters to function
    //input fmt must be bus format
    int src_w = para->src_w;
    int src_h = para->src_h;
    int dst_w = para->dst_w;
    int dst_h = para->dst_h;
    int buf_w = para->panel_width;
    int buf_h = para->panel_height;
    bool h_en = para->h_en;
    bool v_en = para->v_en;
    bool is_cos = para->is_cos;
    bool is_hw_ratio = para->is_hw_ratio;
    bool ratio_plus = para->ratio_plus;
    unsigned int bg_color = para->bg_color;
    unsigned int h_acc_ = para->h_acc;
    unsigned int v_acc_ = para->v_acc;

	
	if(!para->src  || !para->dst)
	{
		printf("%s: Error surface is null src %p dst %p\n", __func__, para->src, para->dst);
	}

    scl_panel_c(src_w, src_h, dst_w, dst_h, buf_w, buf_h,
			para->start_x, para->start_y,
            is_cos, h_en || v_en, h_en, v_en, is_hw_ratio,
            ratio_plus, bg_color, (uint16_t*)para->src, (uint16_t*)para->dst,
            h_acc_, v_acc_,
            FILE_NAME[PUS_IN_DE], FILE_NAME[PUS_CONFIG]);
}

#if 0
win_c update_win(image_tag tag, int stx, int sty, bool is_ref_st) {
    win_c win_res;
    win_res.x = tag.rect.lft + 1;
    win_res.w = tag.rect.wid();
    win_res.y = tag.rect.top + 1;
    win_res.h = tag.rect.het();
    if (win_res.w < 0)
        win_res.w = 0;
    if (win_res.h < 0)
        win_res.h = 0;
    if (is_ref_st)
    {
        win_res.x -= stx;
        win_res.y -= sty;
    }
    return win_res;
}
#endif



void overlay_wrapper(struct overlay_para_t *para)
{
    ovl_stream reg0, reg1;
    bool is_curs_ycbcr = para->is_curs_ycbcr;

    reg0.key_mode = para->ovl0_key_mode;
    reg0.pla_fct = para->ovl0_pla_fct;
    reg0.plb_fct = para->ovl0_plb_fct;
    reg0.bld_mode = para->ovl0_bld_mode;
    reg0.is_inv_alpha = para->ovl0_is_inv_alpha;
    reg0.plane_alpha_val = para->ovl0_plane_alpha_val;
    reg0.alpha_key_sel = para->ovl0_alpha_key_sel;
    reg0.color_key_sel = para->ovl0_color_key_sel;
    reg0.is_alpha_rang = para->ovl0_is_alpha_rang;
    reg0.is_mdi_sec = para->ovl0_is_mdi_sec;
    reg0.is_ref_int = para->ovl0_is_ref_int;
    reg0.is_ycbcr = para->ovl0_is_ycbcr;

    reg1.key_mode = para->ovl1_key_mode;
    reg1.pla_fct = para->ovl1_pla_fct;
    reg1.plb_fct = para->ovl1_plb_fct;
    reg1.bld_mode = para->ovl1_bld_mode;
    reg1.is_inv_alpha = para->ovl1_is_inv_alpha;
    reg1.plane_alpha_val = para->ovl1_plane_alpha_val;
    reg1.alpha_key_sel = para->ovl1_alpha_key_sel;
    reg1.color_key_sel = para->ovl1_color_key_sel;
    reg1.is_alpha_rang = para->ovl1_is_alpha_rang;
    reg1.is_mdi_sec = para->ovl1_is_mdi_sec;
    reg1.is_ref_int = para->ovl1_is_ref_int;
    reg1.is_ycbcr = para->ovl1_is_ycbcr;

    bool is_cur_ref_int = para->is_curs_ref_int;
    win_c win0, win1, win_cur;

    int int_stx = para->iwin_start_x;
    int int_sty = para->iwin_start_y;
    //win0 = update_win(m_dp.s0_tag, int_stx, int_sty, reg0.is_ref_int);
    //win1 = update_win(m_dp.s1_tag, int_stx, int_sty, reg1.is_ref_int);
   // win_cur = update_win(m_dp.cur_tag, int_stx, int_sty, is_cur_ref_int);

	win0.x = para->win_0_start_x;
	win0.y = para->win_0_start_y;
	win0.w = para->win_0_width;
	win0.h = para->win_0_height;

	win1.x = para->win_1_start_x;
	win1.y = para->win_1_start_y;
	win1.w = para->win_1_width;
	win1.h = para->win_1_height;

	win_cur.x = para->win_cur_start_x;//read from reg ?
	win_cur.y = para->win_cur_start_y;
	win_cur.w = para->win_cur_width;
	win_cur.h = para->win_cur_height;
	

	if(!para->dst)
	{
		printf("%s: Error surface is null dst %p\n", __func__, para->dst);
	}

    if (!m_is_ref_chk_en)
        overlay_c(true, para->dst_width, para->dst_height,
            para->bg_color, para->bg_ycbcr, reg0, reg1, para->cur_type,
            para->is_curs_ycbcr, is_cur_ref_int, (uint16_t*)para->win0_src, (uint16_t*)para->win1_src,
            (uint32_t*)para->cur_src, (uint16_t*)para->dst,
            win0, win1, win_cur, int_stx, int_sty,
            FILE_NAME[OVL_IN_DE], FILE_NAME[OVL_CONFIG]);

    return;
}




unsigned long long signature_wrapper(struct signature_para_t  *para)
{
    int width = para->width;
    int height = para->height;
    const unsigned short* psrc = reinterpret_cast<unsigned short*>(para->src);
    //unsigned short* pdst = reinterpret_cast<unsigned short*>(para->dst);
    return signature_drv_c(width, height, psrc);
}



void csc_plane_wrapper(struct csc_plane_para_t *para)
{
    int width = para->width;
    int height = para->height;
    unsigned infmt = para->infmt;
    unsigned outfmt = para->outfmt;
    unsigned bright = para->bright;
    bool prog = para->prog;
    unsigned coef1 = para->coef1;
    unsigned coef2 = para->coef2;
    unsigned coef3 = para->coef3;
    unsigned coef4 = para->coef4;
    unsigned coef5 = para->coef5;
    unsigned coef6 = para->coef6;
    unsigned coef7 = para->coef7;
    unsigned coef8 = para->coef8;
    unsigned coef9 = para->coef9;
    const unsigned short* psrc = para->src;
    unsigned short* pdst = para->dst;


	if(!para->src  || !para->dst)
	{
		printf("%s: Error surface is null src %p dst %p\n", __func__, para->src, para->dst);
	}

    // perform plane CSC
    csc_plane_c(width, height,
        infmt, outfmt, bright, prog,
        coef1, coef2, coef3,
        coef4, coef5, coef6,
        coef7, coef8, coef9,
        psrc, pdst,
        FILE_NAME[SCSC_CONFIG_DONE], FILE_NAME[SCSC_IN_WIN_VLD]);
}



void csc_cursor_wrapper(struct csc_cursor_para_t *para)
{
    int width = para->width;
    int height = para->height;
    unsigned outfmt = para->fmt;
    const unsigned char* psrc = (unsigned char*)para->src;
    unsigned char* pdst = (unsigned char*)para->dst;


	if(!para->src  || !para->dst)
	{
		printf("%s: Error surface is null src %p dst %p\n", __func__, para->src, para->dst);
	}

    // perform cursor CSC
    csc_cursor_c(width, height, outfmt, psrc, pdst, FILE_NAME[CUR_CSC_VLD]);
}


void cursor_wrapper(struct cursor_para_t *para, int *out_w, int *out_h)
{

    uint16_t* psrc = para->src;
    uint16_t* pdst = para->dst;
    cur_para p{};
    //int32_t out_w{}, out_h{};  //need this ?
    p.panel_width = para->panel_width;
    p.panel_height = para->panel_height;
    p.x_start = para->x_start;
    p.y_start = para->y_start;
    p.cur_mono_fg = para->cur_mono_fg;
	p.cur_mono_bg = para->cur_mono_bg;
    p.cur_type = para->cur_mono_bg;
	p.cur_size = para->cur_size;

	p.x_off = para->x_off;
	p.y_off = para->y_off;

	
	if(!para->src  || !para->dst)
	{
		printf("%s: Error surface is null src %p dst %p\n", __func__, para->src, para->dst);
	}

    cursor_c(psrc, p, pdst, out_w, out_h, FILE_NAME[CUR_VLD]);
}



uint32_t LUT_DATA[256] =
{
    0, 82, 113, 136, 155, 171, 186, 200, 212, 224, 235, 245, 255,
    264, 274, 282, 291, 299, 307, 314, 322, 329, 336, 343, 349, 356,
    362, 369, 375, 381, 387, 393, 398, 404, 409, 415, 420, 425, 431,
    436, 441, 446, 451, 455, 460, 465, 470, 474, 479, 483, 488, 492,
    497, 501, 505, 509, 514, 518, 522, 526, 530, 534, 538, 542, 546,
    550, 553, 557, 561, 565, 568, 572, 576, 579, 583, 587, 590, 594,
    597, 601, 604, 607, 611, 614, 618, 621, 624, 627, 631, 634, 637,
    640, 644, 647, 650, 653, 656, 659, 662, 665, 668, 672, 675, 678,
    680, 683, 686, 689, 692, 695, 698, 701, 704, 707, 709, 712, 715,
    718, 721, 723, 726, 729, 732, 734, 737, 740, 743, 745, 748, 751,
    753, 756, 758, 761, 764, 766, 769, 771, 774, 776, 779, 781, 784,
    786, 789, 791, 794, 796, 799, 801, 804, 806, 809, 811, 813, 816,
    818, 821, 823, 825, 828, 830, 832, 835, 837, 839, 842, 844, 846,
    849, 851, 853, 855, 858, 860, 862, 864, 867, 869, 871, 873, 875,
    878, 880, 882, 884, 886, 888, 891, 893, 895, 897, 899, 901, 903,
    906, 908, 910, 912, 914, 916, 918, 920, 922, 924, 926, 928, 930,
    933, 935, 937, 939, 941, 943, 945, 947, 949, 951, 953, 955, 957,
    959, 961, 963, 964, 966, 968, 970, 972, 974, 976, 978, 980, 982,
    984, 986, 988, 990, 991, 993, 995, 997, 999, 1001, 1003, 1005,
    1006, 1008, 1010, 1012, 1014, 1016, 1018, 1019, 1021, 1023
};




void lut_wrapper(struct lut_para_t *para)
{
    int width = para->width;
    int height = para->height;
    uint16_t* psrc = para->src;
    uint16_t* pdst = para->dst;
    lut_para p{};

	p.lut_en = para->lut_en;
	p.lut_intp_on = para->lut_intp_on;
	p.lut_bitwidth = para->lut_bitwidth;


	if(!para->src  || !para->dst)
	{
		printf("%s: Error surface is null src %p dst %p\n", __func__, para->src, para->dst);
	}

    lut_c(psrc, pdst, width, height, p, para->lut_data, FILE_NAME[LUT_IF], FILE_NAME[LUT_CONFIG]);
}


void dither_wrapper(struct dither_para_t *para)
{
    int width = para->width;
    int height = para->height;
    uint16_t* psrc = para->src;
    uint16_t* pdst = para->dst;
    dither_para p{};

	p.dither_en = para->dither_en;
	p.base = para->base;
	p.bitsel = para->bitsel;
	p.dist_en = para->dist_en;


	if(!para->src  || !para->dst)
	{
		printf("%s: Error surface is null src %p dst %p\n", __func__, para->src, para->dst);
	}

    dither_c(psrc, pdst, width, height, p, FILE_NAME[DIHTER_IN_DE], FILE_NAME[DITHER_CONFIG]);
}



void input_wrapper(struct input_para_t *input_para)
{
	unsigned short *psrc = input_para->src;
    unsigned short *pdst = input_para->dst;

	inp_para p = {0};

	p.stride_num = input_para->stride;
	p.spl_abgr = input_para->spl_abgr;
	p.spl_crycb = input_para->spl_crycb;
	p.spl_cbycry = input_para->spl_cbycry;
	p.pix_off = input_para->pix_off;

	
	if(!input_para->src  || !input_para->dst)
	{
		printf("%s: Error surface is null src %p dst %p\n", __func__, input_para->src, input_para->dst);
	}

    input_c(psrc, pdst, input_para->width, input_para->height, input_para->spl_fmt, p,
        FILE_NAME[SPL_WIN_VLD]);
}

