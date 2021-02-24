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

const std::string FILE_NAME[CK_NUM] =
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

class spl_win_vld_tag : public tag_base
{
public:
    spl_win_vld_tag() : tag_base(CK_ID::SPL_WIN_VLD) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(spl_win_vld_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned long long spl_unpack_dat : 38;
}
;
class sups_vwin_vld_tag : public tag_base
{
public:
    sups_vwin_vld_tag() : tag_base(CK_ID::SUPS_VWIN_VLD) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(sups_vwin_vld_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned long long sups_vpxl_nxt : 38;
    unsigned long long sups_vpxl_cur : 38;
    unsigned int sups_vacc : 21;
    unsigned int sups_vfct : 8;
    unsigned int sups_vcoef1 : 9;
    unsigned int sups_vcoef2 : 9;
}
;
class sups_hwin_vld_tag : public tag_base
{
public:
    sups_hwin_vld_tag() : tag_base(CK_ID::SUPS_HWIN_VLD) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(sups_hwin_vld_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned long long sups_hpxl : 40;
    unsigned int sups_hacc : 21;
    unsigned int sups_hfct : 8;
    unsigned int sups_hcoef1 : 9;
    unsigned int sups_hcoef2 : 9;
    unsigned int sups_out_dat : 30;
    unsigned int sups_out_alpha : 8;
    unsigned int sups_color_key : 1;
    unsigned int sups_alpha_key : 1;
}
;
class sups_config_done_tag : public tag_base
{
public:
    sups_config_done_tag() : tag_base(CK_ID::SUPS_CONFIG_DONE) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(sups_config_done_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int spl_src_w : 14;
    unsigned int spl_src_h : 13;
    unsigned int spl_dst_w : 14;
    unsigned int spl_dst_h : 13;
    unsigned int spl_hacc : 21;
    unsigned int spl_vacc : 21;
    unsigned int spl_htap : 1;
    unsigned int spl_vtap : 1;
    unsigned int spl_vdup : 1;
    unsigned int spl_alpha_ups : 1;
    unsigned int spl_keyl : 30;
    unsigned int spl_keyh : 30;
    unsigned int key_mode : 3;
}
;
class cur_vld_tag : public tag_base
{
public:
    cur_vld_tag() : tag_base(CK_ID::CUR_VLD) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(cur_vld_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int cur_dat : 32;
}
;
class cur_csc_vld_tag : public tag_base
{
public:
    cur_csc_vld_tag() : tag_base(CK_ID::CUR_CSC_VLD) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(cur_csc_vld_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int csc_in_dat : 32;
    unsigned int ry_sum : 18;
    unsigned int gu_sum : 18;
    unsigned int bv_sum : 18;
    unsigned int ry_bright : 18;
    unsigned int gu_bright : 18;
    unsigned int bv_bright : 18;
    unsigned int cur_ycbcr : 1;
    unsigned int csc_out_dat : 32;
}
;
class scsc_in_win_vld_tag : public tag_base
{
public:
    scsc_in_win_vld_tag() : tag_base(CK_ID::SCSC_IN_WIN_VLD) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(scsc_in_win_vld_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int scsc_in_pxl : 30;
    unsigned int scsc_r_f1 : 25;
    unsigned int scsc_g_f2 : 25;
    unsigned int scsc_b_f3 : 25;
    unsigned int scsc_r_f4 : 25;
    unsigned int scsc_g_f5 : 25;
    unsigned int scsc_b_f6 : 25;
    unsigned int scsc_r_f7 : 25;
    unsigned int scsc_g_f8 : 25;
    unsigned int scsc_b_f9 : 25;
    unsigned int scsc_sum_r : 25;
    unsigned int scsc_sum_g : 25;
    unsigned int scsc_sum_b : 25;
    unsigned int scsc_bright_r : 25;
    unsigned int scsc_bright_g : 25;
    unsigned int scsc_bright_b : 25;
    unsigned int scsc_out_pxl : 30;
}
;
class scsc_config_done_tag : public tag_base
{
public:
    scsc_config_done_tag() : tag_base(CK_ID::SCSC_CONFIG_DONE) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(scsc_config_done_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int scsc_in_fmt : 3;
    unsigned int scsc_out_fmt : 3;
    unsigned int scsc_bright : 9;
    unsigned int scsc_program : 1;
    unsigned int scsc_coef1 : 14;
    unsigned int scsc_coef2 : 14;
    unsigned int scsc_coef3 : 14;
    unsigned int scsc_coef4 : 14;
    unsigned int scsc_coef5 : 14;
    unsigned int scsc_coef6 : 14;
    unsigned int scsc_coef7 : 14;
    unsigned int scsc_coef8 : 14;
    unsigned int scsc_coef9 : 14;
}
;
class ovl_in_de_tag : public tag_base
{
public:
    ovl_in_de_tag() : tag_base(CK_ID::OVL_IN_DE) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(ovl_in_de_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int spl0_ovl_pxl : 30;
    unsigned int spl0_ovl_window : 1;
    unsigned int spl0_ovl_alpha : 8;
    unsigned int spl0_ovl_color_key : 1;
    unsigned int spl0_ovl_alpha_key : 1;
    unsigned int spl0_ovl_ycbcr : 1;
    unsigned int ovl0_pla_fct : 4;
    unsigned int ovl0_plb_fct : 4;
    unsigned int ovl0_alpha : 9;
    unsigned int ovl0_ycbcr : 1;
    unsigned int ovl0_dout : 30;
    unsigned int ovl1_a_alpha : 8;
    unsigned int ovl1_a_window : 1;
    unsigned int ovl1_a_alpha_key : 1;
    unsigned int ovl1_a_color_key : 1;
    unsigned int spl1_ovl_pxl : 30;
    unsigned int spl1_ovl_window : 1;
    unsigned int spl1_ovl_alpha : 8;
    unsigned int spl1_ovl_color_key : 1;
    unsigned int spl1_ovl_alpha_key : 1;
    unsigned int spl1_ovl_ycbcr : 1;
    unsigned int ovl1_pla_fct : 4;
    unsigned int ovl1_plb_fct : 4;
    unsigned int ovl1_alpha : 9;
    unsigned int ovl1_ycbcr : 1;
    unsigned int ovl1_dout : 30;
    unsigned int cur_ovl_type : 2;
    unsigned int cur_ovl_window : 1;
    unsigned int cur_ovl_data : 32;
    unsigned int cur_ovl_ycbcr : 1;
    unsigned int ovl_pus_pxl : 30;
}
;
class ovl_config_tag : public tag_base
{
public:
    ovl_config_tag() : tag_base(CK_ID::OVL_CONFIG) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(ovl_config_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int reg_bg_color : 30;
    unsigned int reg_bg_ycbcr : 1;
    unsigned int reg_ovl0_key_mode : 4;
    unsigned int reg_ovl0_pla_fct : 4;
    unsigned int reg_ovl0_plb_fct : 4;
    unsigned int reg_ovl0_alpha_blend_mode : 1;
    unsigned int reg_ovl0_inv_alpha : 1;
    unsigned int reg_ovl0_plane_alpha : 8;
    unsigned int reg_ovl0_alpha_key_sel : 2;
    unsigned int reg_ovl0_color_key_sel : 2;
    unsigned int reg_ovl0_alpha_rang : 1;
    unsigned int reg_ovl1_key_mode : 4;
    unsigned int reg_ovl1_pla_fct : 4;
    unsigned int reg_ovl1_plb_fct : 4;
    unsigned int reg_ovl1_alpha_blend_mode : 1;
    unsigned int reg_ovl1_inv_alpha : 1;
    unsigned int reg_ovl1_plane_alpha : 8;
    unsigned int reg_ovl1_alpha_key_sel : 2;
    unsigned int reg_ovl1_color_key_sel : 2;
    unsigned int reg_ovl1_alpha_rang : 1;
}
;
class pus_in_de_tag : public tag_base
{
public:
    pus_in_de_tag() : tag_base(CK_ID::PUS_IN_DE) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(pus_in_de_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int ovl_pus_pxl : 30;
    unsigned int h_acc : 21;
    unsigned int v_acc : 21;
    unsigned int hfct_tmp : 8;
    unsigned int vfct_tmp : 8;
    unsigned int hfct : 8;
    unsigned int vfct : 8;
    unsigned int r_next_v : 8;
    unsigned int r_current_v : 8;
    unsigned int g_next_v : 8;
    unsigned int g_current_v : 8;
    unsigned int b_next_v : 8;
    unsigned int b_current_v : 8;
    unsigned int r_next_h : 10;
    unsigned int r_current_h : 10;
    unsigned int g_next_h : 10;
    unsigned int g_current_h : 10;
    unsigned int b_next_h : 10;
    unsigned int b_current_h : 10;
    unsigned int h_r : 10;
    unsigned int h_g : 10;
    unsigned int h_b : 10;
    unsigned int pus_lut_pxl : 30;
}
;
class pus_config_tag : public tag_base
{
public:
    pus_config_tag() : tag_base(CK_ID::PUS_CONFIG) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(pus_config_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int reg_pus_en : 1;
    unsigned int reg_pus_hen : 1;
    unsigned int reg_pus_ven : 1;
    unsigned int reg_pus_width_dst : 13;
    unsigned int reg_pus_height_dst : 12;
    unsigned int reg_pus_ratio_mode : 1;
    unsigned int reg_pus_ratio_plus : 1;
    unsigned int reg_pus_ratio_h : 20;
    unsigned int reg_pus_ratio_v : 20;
    unsigned int reg_pus_cos2tap : 1;
    unsigned int reg_pus_bg_color : 30;
    unsigned int ratio_h : 20;
    unsigned int ratio_v : 20;
}
;
class lut_if_tag : public tag_base
{
public:
    lut_if_tag() : tag_base(CK_ID::LUT_IF) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(lut_if_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int pus_lut_pxl : 30;
    unsigned int lut_csc_pxl : 30;
}
;
class lut_config_tag : public tag_base
{
public:
    lut_config_tag() : tag_base(CK_ID::LUT_CONFIG) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(lut_config_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int reg_lut_lut_en : 1;
    unsigned int reg_lut_intp_on : 1;
    unsigned int reg_lut_bitwidth : 2;
}
;
class dihter_in_de_tag : public tag_base
{
public:
    dihter_in_de_tag() : tag_base(CK_ID::DIHTER_IN_DE) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(dihter_in_de_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int r_pxl_in : 10;
    unsigned int g_pxl_in : 10;
    unsigned int b_pxl_in : 10;
    unsigned int dith_row_r : 2;
    unsigned int dith_row_g : 2;
    unsigned int dith_row_b : 2;
    unsigned int dith_col_r : 2;
    unsigned int dith_col_g : 2;
    unsigned int dith_col_b : 2;
    unsigned int r_pre_dither : 10;
    unsigned int r_add_detc : 9;
    unsigned int r_avail_bits_2dither : 4;
    unsigned int r_value_2add_fm_pre_dither : 6;
    unsigned int r_reg16by16_out : 16;
    unsigned int r_reg16by16_out_sel : 4;
    unsigned int r_seld_reg16by16_out_bit : 1;
    unsigned int g_pre_dither : 10;
    unsigned int g_add_detc : 9;
    unsigned int g_avail_bits_2dither : 4;
    unsigned int g_value_2add_fm_pre_dither : 6;
    unsigned int g_reg16by16_out : 16;
    unsigned int g_reg16by16_out_sel : 4;
    unsigned int g_seld_reg16by16_out_bit : 1;
    unsigned int b_pre_dither : 10;
    unsigned int b_add_detc : 9;
    unsigned int b_avail_bits_2dither : 4;
    unsigned int b_value_2add_fm_pre_dither : 6;
    unsigned int b_reg16by16_out : 16;
    unsigned int b_reg16by16_out_sel : 4;
    unsigned int b_seld_reg16by16_out_bit : 1;
    unsigned int r_dith_out : 10;
    unsigned int g_dith_out : 10;
    unsigned int b_dith_out : 10;
}
;
class dither_config_tag : public tag_base
{
public:
    dither_config_tag() : tag_base(CK_ID::DITHER_CONFIG) 
    {
        reset();
    };
    void reset(unsigned char b = 0)
    {
        char* start = reinterpret_cast<char*>(&(this->m__marker)) + sizeof(this->m__marker);
        auto sz = sizeof(dither_config_tag) - sizeof(tag_base);
        std::memset(start, b, sz);
    }
    unsigned int reg_dither_en : 1;
    unsigned int reg_dither_base : 3;
    unsigned int reg_dither_bitsel : 1;
    unsigned int reg_dither_dist_en : 1;
}
;