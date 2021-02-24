#include "dpu_drv.h"
#include "dir.h"
#include "dpu_ref.h"
#include "dpu_cmodel.h"
#include "itb_log.h"
#include "fixed_num.hpp"
#include "dpu_csc.h"
#include "dpu_ckp.h"

void dpu_drv_c::initial(const env_args_t& _args)
{
    m_is_chk_en = _args.is_chk_en;
    m_is_ref_chk_en = _args.is_ref_en;
    m_res_dir_list = _args.res_dir;
    m_out_dir = _args.out_dir;
    m_ref_dir = _args.ref_dir;
    m_frame = _args.frame;
}
void dpu_drv_c::initial_modules()
{
    ;
}

void dpu_drv_c::destroy_modules()
{

}
void dpu_drv_c::process(const uint32_t& frm_idx)
{
    m_frm_idx = frm_idx; // mainly for ckp dump use

    load_paras();

    adjust_paras();

    config_surface();

    kick_off();

    dump_compare(frm_idx);

    release_surface();

    for (int i = 0; i < IMG_NUM; i++)
    {
        if (buf_ptr[i] != nullptr) {
            delete[] buf_ptr[i];
            buf_ptr[i] = nullptr;
        }
    }
}

void dpu_drv_c::load_paras()
{
    m_dp.s0_tag.wid = m_frame.get_vt("s0_sf", "width");
    m_dp.s0_tag.het = m_frame.get_vt("s0_sf", "height");
    m_dp.s0_tag.file = std::string(m_frame.get_vt("s0_sf", "file"));
    m_dp.s0fmt.set(std::string(m_frame.get_vt("s0_sf", "format")));
    m_dp.s0_tag.rect.lft = m_frame.get_vt("s0_sf", "rect", 0, 0);
    m_dp.s0_tag.rect.rht = m_frame.get_vt("s0_sf", "rect", int(m_dp.s0_tag.wid - 1), 1);
    m_dp.s0_tag.rect.top = m_frame.get_vt("s0_sf", "rect", 0, 2);
    m_dp.s0_tag.rect.bot = m_frame.get_vt("s0_sf", "rect", int(m_dp.s0_tag.het - 1), 3);
    if (m_frame.para["s0_sf"].find("sf_start_pos") != m_frame.para["s0_sf"].end())
    {
        m_dp.s0_tag.rd_st_x = m_frame.get_vt("s0_sf", "sf_start_pos", 0, 0);
        m_dp.s0_tag.rd_st_y = m_frame.get_vt("s0_sf", "sf_start_pos", 0, 1);
    }
    //for s1_tag the format is argb or ayuv 10 bit bus data
    m_dp.s1_tag.wid = m_frame.get_vt("s1_sf", "width", 0);
    if (m_dp.s1_tag.wid > 0)
    {
        m_dp.s1_tag.het = m_frame.get_vt("s1_sf", "height", 0);
        m_dp.s1_tag.file = std::string(m_frame.get_vt("s1_sf", "file", 0));
        m_dp.s1fmt.set(std::string(m_frame.get_vt("s0_sf", "format")));
        m_dp.s1_tag.rect.lft = m_frame.get_vt("s1_sf", "rect", 0, 0);
        m_dp.s1_tag.rect.rht = m_frame.get_vt("s1_sf", "rect", int(m_dp.s1_tag.wid - 1), 1);
        m_dp.s1_tag.rect.top = m_frame.get_vt("s1_sf", "rect", 0, 2);
        m_dp.s1_tag.rect.bot = m_frame.get_vt("s1_sf", "rect", int(m_dp.s1_tag.het - 1), 3);
        if (m_frame.para["s1_sf"].find("sf_start_pos") != m_frame.para["s1_sf"].end())
        {
            m_dp.s1_tag.rd_st_x = m_frame.get_vt("s1_sf", "sf_start_pos", 0, 0);
            m_dp.s1_tag.rd_st_y = m_frame.get_vt("s1_sf", "sf_start_pos", 0, 1);
        }
    }

    m_dp.cur_tag.wid = m_frame.get_vt("curs_sf", "width", 0);
    if (m_dp.cur_tag.wid > 0)
    {
        m_dp.cur_tag.het = m_frame.get_vt("curs_sf", "height", 0);
        m_dp.cur_tag.file = std::string(m_frame.get_vt("curs_sf", "file", 0));
        m_dp.cfmt.set(std::string(m_frame.get_vt("curs_sf", "format")));
        m_dp.cur_tag.rect.lft = m_frame.get_vt("curs_sf", "rect", 0, 0);
        m_dp.cur_tag.rect.rht = m_frame.get_vt("curs_sf", "rect", int(m_dp.cur_tag.wid - 1), 1);
        m_dp.cur_tag.rect.top = m_frame.get_vt("curs_sf", "rect", 0, 2);
        m_dp.cur_tag.rect.bot = m_frame.get_vt("curs_sf", "rect", int(m_dp.cur_tag.het - 1), 3);
        if (m_frame.para["curs_sf"].find("sf_start_pos") != m_frame.para["curs_sf"].end())
        {
            m_dp.cur_tag.rd_st_x = m_frame.get_vt("curs_sf", "sf_start_pos", 0, 0);
            m_dp.cur_tag.rd_st_y = m_frame.get_vt("curs_sf", "sf_start_pos", 0, 1);
        }

    }


    m_dp.d_tag.wid = m_frame.get_vt("dst_sf", "width");
    m_dp.d_tag.het = m_frame.get_vt("dst_sf", "height");
    m_dp.d_tag.file = std::string(m_frame.get_vt("dst_sf", "file", 0));
    m_dp.dfmt.set(std::string(m_frame.get_vt("dst_sf", "format")));
    m_dp.d_tag.rect.lft = m_frame.get_vt("dst_sf", "rect", 0, 0);
    m_dp.d_tag.rect.rht = m_frame.get_vt("dst_sf", "rect", int(m_dp.d_tag.wid - 1), 1);
    m_dp.d_tag.rect.top = m_frame.get_vt("dst_sf", "rect", 0, 2);
    m_dp.d_tag.rect.bot = m_frame.get_vt("dst_sf", "rect", int(m_dp.d_tag.het - 1), 3);

    m_dp.bg_color = m_frame.get_vt("misc", "bg_color", 0x20280a02, 30);
    m_dp.bg_ycbcr = m_frame.get_vt("misc", "bg_ycbcr", 0, 1);
    std::string t = m_frame.get_vt("func_mode", "type");
    //for different module, we use different intial methods to get window signals.
    //generate signals and set in driver parameters

    if (t == "input")
    {
        m_dp.work_mode = DPUF_INP;
        m_dp.inp.spl_abgr = m_frame.get_vt("input", "spl_abgr", 0);
        m_dp.inp.spl_cbycry = m_frame.get_vt("input", "spl_cbycry", 0);
        m_dp.inp.spl_crycb = m_frame.get_vt("input", "spl_crycb", 0);
        if (m_dp.inp.spl_abgr == 1 && m_dp.s0fmt != DPU_ARGB8888)
            m_dp.inp.spl_abgr = 0;
        if (m_dp.inp.spl_cbycry == 1 && m_dp.s0fmt != DPU_YUYV)
            m_dp.inp.spl_cbycry = 0;
    }
    else if (t == "stream_upscl")
    {
        m_dp.work_mode = DPUF_STR_UPSCL;
        m_dp.scl.is_cos_h = m_frame.get_vt("scl", "cos_h", 0, 1);
        m_dp.scl.is_cos_v = m_frame.get_vt("scl", "cos_v", 0, 1);
        m_dp.scl.is_color_key = m_frame.get_vt("scl", "col_key_en", 0, 1);
        m_dp.scl.is_alpha_ups = m_frame.get_vt("scl", "alpha_ups", 0, 1);
        m_dp.scl.is_v_duplicate = m_frame.get_vt("scl", "v_dupli", 0, 1);
        m_dp.scl.keyl = m_frame.get_vt("scl", "keyl", 0, 30);
        m_dp.scl.keyh = m_frame.get_vt("scl", "keyh", 0, 30);
        m_dp.scl.key_mode = m_frame.get_vt("scl", "key_mode", 0, 3);
        get_scl_ratio(m_dp.scl, false);
    }
    else if (t == "panel_upscl")
    {
        m_dp.work_mode = DPUF_PAN_UPSCL;
        m_dp.scl.is_cos = m_frame.get_vt("scl", "cos", 0, 1);
        m_dp.scl.is_hw_ratio = m_frame.get_vt("scl", "hw_ratio", 0, 1);
        m_dp.scl.ratio_plus = m_frame.get_vt("scl", "ratio_plus", 0, 1);
        get_scl_ratio(m_dp.scl, true);
        ASSERT_ITB(m_dp.d_tag.rect.lft == m_dp.s0_tag.rect.lft && m_dp.d_tag.rect.top == m_dp.d_tag.rect.top, "src and dst should have same st");
    }
    else if (t == "csc_plane")
    {
        m_dp.work_mode = DPUF_CSC_PLANE;
        m_dp.csc_plane.src_rgb = m_frame.get_vt("csc_plane", "src_rgb", 0, 1);
        m_dp.csc_plane.dst_rgb = m_frame.get_vt("csc_plane", "dst_rgb", 0, 1);
        m_dp.csc_plane.src_range_full = m_frame.get_vt(
            "csc_plane", "src_range_full", 0, 1);
        m_dp.csc_plane.dst_range_full = m_frame.get_vt(
            "csc_plane", "dst_range_full", 0, 1);
        m_dp.csc_plane.gamut = std::string(m_frame.get_vt("csc_plane", "gamut", 0, 1));
        m_dp.csc_plane.bright_drv = m_frame.get_vt("csc_plane", "bright", 0, 1);
        m_dp.csc_plane.prog = m_frame.get_vt("csc_plane", "prog", 0, 1);
        if (m_dp.csc_plane.prog)
        {
            auto coefs = m_dp.csc_plane.coefs;
            coefs[0][0] = m_frame.get_vt("csc_plane", "coefs", 0, 0);
            coefs[0][1] = m_frame.get_vt("csc_plane", "coefs", 0, 1);
            coefs[0][2] = m_frame.get_vt("csc_plane", "coefs", 0, 2);
            coefs[1][0] = m_frame.get_vt("csc_plane", "coefs", 0, 3);
            coefs[1][1] = m_frame.get_vt("csc_plane", "coefs", 0, 4);
            coefs[1][2] = m_frame.get_vt("csc_plane", "coefs", 0, 5);
            coefs[2][0] = m_frame.get_vt("csc_plane", "coefs", 0, 6);
            coefs[2][1] = m_frame.get_vt("csc_plane", "coefs", 0, 7);
            coefs[2][2] = m_frame.get_vt("csc_plane", "coefs", 0, 8);
        }
    }
    else if (t == "csc_cursor")
    {
        m_dp.work_mode = DPUF_CSC_CURSOR;
        m_dp.csc_cursor.src_rgb = m_frame.get_vt("csc_cursor", "src_rgb", 0, 1);
        m_dp.csc_cursor.dst_rgb = m_frame.get_vt("csc_cursor", "dst_rgb", 0, 1);
        m_dp.csc_cursor.src_range_full = \
            m_frame.get_vt("csc_cursor", "src_range_full", 0, 1);
        m_dp.csc_cursor.dst_range_full = \
            m_frame.get_vt("csc_cursor", "dst_range_full", 0, 1);
        m_dp.csc_cursor.gamut = std::string(m_frame.get_vt("csc_cursor", "gamut", 0, 1));
    }
    else if (t == "cursor")
    {
        m_dp.work_mode = DPUF_CURSOR;
    }
    else if (t == "overlay")
    {
        m_dp.work_mode = DPUF_OVERLAY;
        m_dp.ovl.efuse_sec = m_frame.get_vt("ovl", "efuse_sec", 0, 1);
        m_dp.ovl.key_mode_0 = m_frame.get_vt("ovl", "key_mode_0", 0, 4);
        m_dp.ovl.pla_fct_0 = m_frame.get_vt("ovl", "pla_fct_0", 0, 4);
        m_dp.ovl.plb_fct_0 = m_frame.get_vt("ovl", "plb_fct_0", 0, 4);
        m_dp.ovl.bld_mode_0 = m_frame.get_vt("ovl", "bld_mode_0", 0, 1);
        m_dp.ovl.is_inv_alpha_0 = m_frame.get_vt("ovl", "is_inv_alpha_0", 0, 1);
        m_dp.ovl.plane_alpha_val_0 = m_frame.get_vt("ovl", "plane_alpha_val_0", 0, 8);
        m_dp.ovl.alpha_key_sel_0 = m_frame.get_vt("ovl", "alpha_key_sel_0", 0, 2);
        m_dp.ovl.color_key_sel_0 = m_frame.get_vt("ovl", "color_key_sel_0", 0, 2);
        m_dp.ovl.is_alpha_rang_0 = m_frame.get_vt("ovl", "is_alpha_rang_0", 0, 1);
        m_dp.ovl.key_mode_1 = m_frame.get_vt("ovl", "key_mode_1", 0, 4);
        m_dp.ovl.pla_fct_1 = m_frame.get_vt("ovl", "pla_fct_1", 0, 4);
        m_dp.ovl.plb_fct_1 = m_frame.get_vt("ovl", "plb_fct_1", 0, 4);
        m_dp.ovl.bld_mode_1 = m_frame.get_vt("ovl", "bld_mode_1", 0, 1);
        m_dp.ovl.is_inv_alpha_1 = m_frame.get_vt("ovl", "is_inv_alpha_1", 0, 1);
        m_dp.ovl.plane_alpha_val_1 = m_frame.get_vt("ovl", "plane_alpha_val_1", 0, 8);
        m_dp.ovl.alpha_key_sel_1 = m_frame.get_vt("ovl", "alpha_key_sel_1", 0, 2);
        m_dp.ovl.color_key_sel_1 = m_frame.get_vt("ovl", "color_key_sel_1", 0, 2);
        m_dp.ovl.is_alpha_rang_1 = m_frame.get_vt("ovl", "is_alpha_rang_1", 0, 1);
        m_dp.ovl.curs_ovl_tp = m_frame.get_vt("ovl", "curs_ovl_tp", 0, 2);
        m_dp.ovl.is_mdi_sec_0 = m_frame.get_vt("ovl", "is_mdi_sec_0", 0, 1);
        m_dp.ovl.is_ycbcr_0 = m_frame.get_vt("ovl", "is_ycbcr_0", 0, 1);
        m_dp.ovl.is_mdi_sec_1 = m_frame.get_vt("ovl", "is_mdi_sec_1", 0, 1);
        m_dp.ovl.is_ycbcr_1 = m_frame.get_vt("ovl", "is_ycbcr_1", 0, 1);
        m_dp.ovl.curs_ycbcr = m_frame.get_vt("ovl", "curs_ycbcr", 0, 1);
        m_dp.ovl.is_ref_int_0 = m_frame.get_vt("ovl", "is_ref_int_1", 0, 1);
        m_dp.ovl.is_ref_int_1 = m_frame.get_vt("ovl", "is_ref_int_0", 0, 1);
        m_dp.ovl.is_ref_int_c = m_frame.get_vt("ovl", "curs_is_int", 0, 1);
    }
    else if (t == "lut")
    {
        m_dp.work_mode = DPUF_LUT;
    }
    else if (t == "dither")
    {
        m_dp.work_mode = DPUF_DITHER;
    }
    else if (t == "out")
    {
        m_dp.work_mode = DPUF_OUT;
    }
    else if (t == "signature")
    {
        m_dp.work_mode = DPUF_SIGNATURE;
    }
    else
    {
        ASSERT_ITB(0, "Unsupported function!");
    }

}

void dpu_drv_c::adjust_paras()
{
    //set limitation here
    //if do not enable ld engine, the src format is only bus format
    if (m_dp.work_mode == DPUF_INP)
    {
        ASSERT_ITB(m_dp.s0fmt < DPU_NV12, "Unsupported src fmt!");
    }
    else if (m_dp.work_mode == DPUF_OUT)
    {
        ASSERT_ITB(m_dp.dfmt <= DPU_NV12, "Unsupported dst fmt!");
    }
    else
    {
        ASSERT_ITB(m_dp.dfmt >= DPU_BUS_AYUV, "Unsupported pipe fmt!");
        ASSERT_ITB(m_dp.s0fmt >= DPU_BUS_AYUV, "Unsupported pipe fmt!");
    }

    if (m_dp.work_mode == DPUF_CSC_PLANE)
    {
        csc_t& csc_data = m_dp.csc_plane;
        // check if input gamut is supported
        std::string gamut(csc_data.gamut);
        ASSERT_ITB(gamut == "bt601" || gamut == "bt709" || gamut == "bt2020",
            "[DPU CSC]: Only support BT.601/BT.709/BT.2020 gamut!");
        // necessary data
        constexpr int PREC_BRIGHT[2] = { 8, 0 };
        constexpr int PREC_COEFS[2] = { 4, 9 };
        csc_mat_dpu cm(csc_data.src_rgb, csc_data.dst_rgb,
            csc_data.src_range_full, csc_data.dst_range_full,
            gamut);
        // get format indices
        csc_data.infmt = cm.infmt();
        csc_data.outfmt = cm.outfmt();
        // get brightness offset
        fixed_num fx_bright = fixed_num(PREC_BRIGHT[0], PREC_BRIGHT[1], true,
            csc_data.bright_drv);
        csc_data.bright = fx_bright.get_raw_dw();
        // get matrix coefficients (non-programmable cases)
        if (!csc_data.prog)
        {
            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    // double -> Q4.9 -> unsigned int
                    fixed_num fx_coef(PREC_COEFS[0], PREC_COEFS[1], true,
                        cm(row, col));
                    csc_data.coefs[row][col] = fx_coef.get_raw_dw();
                }
            }
        }
    }
    if (m_dp.work_mode == DPUF_CSC_CURSOR)
    {
        csc_t& csc_data = m_dp.csc_cursor;
        // check if input gamut is supported
        std::string gamut(csc_data.gamut);
        ASSERT_ITB(gamut == "bt601" || gamut == "bt709" || gamut == "bt2020",
            "[DPU CSC]: Only support BT.601/BT.709/BT.2020 gamut!");
        // necessary data
        csc_mat_dpu cm(csc_data.src_rgb, csc_data.dst_rgb,
            csc_data.src_range_full, csc_data.dst_range_full,
            gamut);
        // get format index
        csc_data.outfmt = cm.outfmt();
    }
}

void dpu_drv_c::config_surface()
{
    //get fmt and set fmt related information
    //set bpp, fmt_info , update
    m_dp.s0_tag.is_tile = false;
    m_dp.s0_tag.bpp = m_dp.s0fmt.get_bpp();
    if (m_dp.s0fmt == DPU_BUS_ARGB || (m_dp.work_mode == DPUF_CSC_CURSOR && m_dp.dfmt == DPU_BUS_CURS))
    {
        m_dp.s0_tag.fmt_info.is_swz_rb = true;
    }
    m_dp.s0_tag.fmt = m_dp.s0fmt.toHGF(m_dp.inp.spl_abgr || m_dp.inp.spl_cbycry || m_dp.inp.spl_crycb);
    m_dp.s0fmt.get_ch_bits(m_dp.s0_tag.fmt_info.r_bits,
        m_dp.s0_tag.fmt_info.g_bits,
        m_dp.s0_tag.fmt_info.b_bits,
        m_dp.s0_tag.fmt_info.a_bits);

    m_dp.s0_tag.update();
    m_img[S0].setup(m_dp.s0_tag);
    m_img[S0].alloc();
    m_img[S0].load_img_data(res_file(m_res_dir_list, m_dp.s0_tag.file));
    set_stream(S0, true, m_dp.s0fmt, m_dp.work_mode != DPUF_PAN_UPSCL);
    if (m_dp.work_mode == DPUF_OVERLAY)
    {
        //allocate cursor and s1 with bus format
        m_dp.cur_tag.bpp = m_dp.s1_tag.bpp = m_dp.s0_tag.bpp;
        m_dp.cur_tag.fmt = m_dp.s1_tag.fmt = m_dp.s0_tag.fmt;
        m_dp.cur_tag.fmt_info = m_dp.s1_tag.fmt_info = m_dp.s0_tag.fmt_info;
        m_dp.s1_tag.update();

        m_img[S1].setup(m_dp.s1_tag);
        m_img[S1].alloc();
        m_img[S1].load_img_data(res_file(m_res_dir_list, m_dp.s1_tag.file));
        set_stream(S1, true, m_dp.s1fmt);

    }
    if (m_dp.work_mode == DPUF_CURSOR || m_dp.work_mode == DPUF_OVERLAY)
    {
        //set cursor fmt and alloc
         //for overlay, curs should be bus format
         //for cursor surface is cur input format
        // m_img[CURS].alloc();
        m_dp.cur_tag.bpp = m_dp.cfmt.get_bpp();
        m_dp.cur_tag.update();
        m_img[CURS].setup(m_dp.cur_tag);
        m_img[CURS].alloc();
        m_img[CURS].load_img_data(res_file(m_res_dir_list, m_dp.cur_tag.file));
        set_stream(CURS, true, m_dp.cfmt);
    }

    m_dp.d_tag.is_tile = false;
    m_dp.d_tag.bpp = m_dp.dfmt.get_bpp();
    if (m_dp.dfmt == DPU_BUS_ARGB || (m_dp.work_mode == DPUF_CSC_CURSOR && m_dp.dfmt == DPU_BUS_CURS))
    {
        m_dp.d_tag.fmt_info.is_swz_rb = true;
    }
    m_dp.d_tag.fmt = m_dp.dfmt.toHGF(false); // todo
    m_dp.dfmt.get_ch_bits(m_dp.d_tag.fmt_info.r_bits,
        m_dp.d_tag.fmt_info.g_bits,
        m_dp.d_tag.fmt_info.b_bits,
        m_dp.d_tag.fmt_info.a_bits);

    m_dp.d_tag.update();
    m_img[D].setup(m_dp.d_tag);
    m_img[D].alloc();
    set_stream(D, false, m_dp.dfmt, m_dp.work_mode != DPUF_PAN_UPSCL && m_dp.work_mode != DPUF_OVERLAY);
    uint32_t size = (m_dp.d_tag.wid * m_dp.d_tag.het + 7) >> 3;

}


void dpu_drv_c::kick_off()
{
    //we always only test one function only if we want to test more, need add dst as src mechanism as different frame
    bool is_check_with_ref = 0;
    (this->*func_p[m_dp.work_mode])();
}

void dpu_drv_c::input()
{
    unsigned short* psrc = reinterpret_cast<unsigned short*>(buf_ptr[S0]);
    unsigned short* pdst = reinterpret_cast<unsigned short*>(buf_ptr[D]);
    if (EQUAL_OR(m_dp.s0fmt, DPU_RGB565, DPU_ARGB8888, DPU_ARGB2101010))
    {
        ASSERT_ITB(m_dp.dfmt == DPU_BUS_ARGB || m_dp.dfmt == DPU_BUS_CURS, "");
    }
    if (EQUAL_OR(m_dp.s0fmt, DPU_YUYV, DPU_AYUV8888, DPU_Y410, DPU_Y210))
    {
        ASSERT_ITB(m_dp.dfmt == DPU_BUS_AYUV || m_dp.dfmt == DPU_BUS_CURS, "");
    }

    inp_para p{};
    p.stride_num = m_dp.s0_tag.pitch >> 5;
    p.spl_abgr = m_dp.inp.spl_abgr;
    p.spl_crycb = m_dp.inp.spl_crycb;
    p.spl_cbycry = m_dp.inp.spl_cbycry;
    input_c(psrc, pdst, m_dp.d_tag.rect.wid(), m_dp.d_tag.rect.het(), m_dp.s0fmt, p,
        FILE_NAME[SPL_WIN_VLD]);
}

void dpu_drv_c::scl_stream()
{
    //set parameters here
    //assign parameters to function
    //input fmt must be bus format
    int src_w = m_dp.s0_tag.rect.wid();
    int src_h = m_dp.s0_tag.rect.het();
    int dst_w = m_dp.d_tag.rect.wid();
    int dst_h = m_dp.d_tag.rect.het();
    bool is_cos_h = m_dp.scl.is_cos_h;
    bool is_cos_v = m_dp.scl.is_cos_v;
    bool is_alpha_ups = m_dp.scl.is_alpha_ups;
    bool is_color_key = m_dp.scl.key_mode > 0;
    bool is_v_duplicate = m_dp.scl.is_v_duplicate;
    unsigned int keyl = m_dp.scl.keyl;
    unsigned int keyh = m_dp.scl.keyh;
    unsigned int key_mode = m_dp.scl.key_mode;
    unsigned int h_acc_ = m_dp.scl.h_acc;
    unsigned int v_acc_ = m_dp.scl.v_acc;
    if (m_is_ref_chk_en)
    {
        scl_stream_ref(src_w, src_h, dst_w, dst_h, is_cos_h, is_cos_v, is_alpha_ups, is_color_key, is_v_duplicate, keyl, (uint16_t*)buf_ptr[S0], (uint16_t*)buf_ptr[D]);
    }
    else
    {
        scl_stream_c(src_w, src_h, dst_w, dst_h, is_cos_h, is_cos_v,
            is_alpha_ups, key_mode, is_v_duplicate, keyl, keyh,
            (uint16_t*)buf_ptr[S0], (uint16_t*)buf_ptr[D], h_acc_, v_acc_,
            FILE_NAME[SUPS_VWIN_VLD], FILE_NAME[SUPS_HWIN_VLD], FILE_NAME[SUPS_CONFIG_DONE]);
    }
}
void dpu_drv_c::scl_panel()
{
    //set parameters here
    //assign parameters to function
    //input fmt must be bus format
    int src_w = m_dp.s0_tag.rect.wid();
    int src_h = m_dp.s0_tag.rect.het();
    int dst_w = m_dp.d_tag.rect.wid();
    int dst_h = m_dp.d_tag.rect.het();
    int buf_w = m_dp.d_tag.wid;
    int buf_h = m_dp.d_tag.het;
    bool h_en = m_dp.scl.h_en;
    bool v_en = m_dp.scl.v_en;
    bool is_cos = m_dp.scl.is_cos;
    bool is_hw_ratio = m_dp.scl.is_hw_ratio;
    bool ratio_plus = m_dp.scl.ratio_plus;
    unsigned int bg_color = m_dp.bg_color;
    unsigned int h_acc_ = m_dp.scl.h_acc;
    unsigned int v_acc_ = m_dp.scl.v_acc;
    if (m_is_ref_chk_en)
    {
        scl_stream_ref(src_w, src_h, dst_w, dst_h, is_cos, is_cos, false, false, false, 0, (uint16_t*)buf_ptr[S0], (uint16_t*)buf_ptr[D]);
    }
    else
    {
        scl_panel_c(src_w, src_h, dst_w, dst_h, buf_w, buf_h,
            m_dp.d_tag.rect.lft + 1, m_dp.d_tag.rect.top + 1,
            is_cos, h_en || v_en, h_en, v_en, is_hw_ratio,
            ratio_plus, bg_color, (uint16_t*)buf_ptr[S0], (uint16_t*)buf_ptr[D],
            h_acc_, v_acc_,
            FILE_NAME[PUS_IN_DE], FILE_NAME[PUS_CONFIG]);
    }
}

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
void dpu_drv_c::overlay()
{
    ovl_t* ppr = &m_dp.ovl;
    ovl_stream reg0, reg1;
    bool is_curs_ycbcr = m_dp.cursor.is_cbcr;
    reg0.key_mode = ppr->key_mode_0;
    reg0.pla_fct = ppr->pla_fct_0;
    reg0.plb_fct = ppr->plb_fct_0;
    reg0.bld_mode = ppr->bld_mode_0;
    reg0.is_inv_alpha = ppr->is_inv_alpha_0;
    reg0.plane_alpha_val = ppr->plane_alpha_val_0;
    reg0.alpha_key_sel = ppr->alpha_key_sel_0;
    reg0.color_key_sel = ppr->color_key_sel_0;
    reg0.is_alpha_rang = ppr->is_alpha_rang_0;
    reg0.is_mdi_sec = ppr->is_mdi_sec_0;
    reg0.is_ref_int = ppr->is_ref_int_0;
    reg0.is_ycbcr = ppr->is_ycbcr_0;
    reg1.key_mode = ppr->key_mode_1;
    reg1.pla_fct = ppr->pla_fct_1;
    reg1.plb_fct = ppr->plb_fct_1;
    reg1.bld_mode = ppr->bld_mode_1;
    reg1.is_inv_alpha = ppr->is_inv_alpha_1;
    reg1.plane_alpha_val = ppr->plane_alpha_val_1;
    reg1.alpha_key_sel = ppr->alpha_key_sel_1;
    reg1.color_key_sel = ppr->color_key_sel_1;
    reg1.is_alpha_rang = ppr->is_alpha_rang_1;
    reg1.is_mdi_sec = ppr->is_mdi_sec_1;
    reg1.is_ref_int = ppr->is_ref_int_1;
    reg1.is_ycbcr = ppr->is_ycbcr_1;
    win_c win0, win1, win_cur;
    bool is_cur_ref_int = ppr->is_ref_int_c;
    int int_stx = m_dp.d_tag.rect.lft, int_sty = m_dp.d_tag.rect.top;
    win0 = update_win(m_dp.s0_tag, int_stx, int_sty, reg0.is_ref_int);
    win1 = update_win(m_dp.s1_tag, int_stx, int_sty, reg1.is_ref_int);
    win_cur = update_win(m_dp.cur_tag, int_stx, int_sty, is_cur_ref_int);

    if (!m_is_ref_chk_en)
        overlay_c(ppr->efuse_sec, m_dp.d_tag.wid, m_dp.d_tag.het,
            m_dp.bg_color, m_dp.bg_ycbcr, reg0, reg1, ppr->curs_ovl_tp,
            ppr->curs_ycbcr, is_cur_ref_int, (uint16_t*)buf_ptr[S0], (uint16_t*)buf_ptr[S1],
            (uint32_t*)buf_ptr[CURS], (uint16_t*)buf_ptr[D],
            win0, win1, win_cur, int_stx, int_sty,
            FILE_NAME[OVL_IN_DE], FILE_NAME[OVL_CONFIG]);

    return;
}
void dpu_drv_c::signature()
{
    int width = m_dp.d_tag.rect.wid();
    int height = m_dp.d_tag.rect.het();
    const unsigned short* psrc = reinterpret_cast<unsigned short*>(buf_ptr[S0]);
    unsigned short* pdst = reinterpret_cast<unsigned short*>(buf_ptr[D]);
    signature_c(width, height, psrc, pdst);
}
void dpu_drv_c::csc_plane()
{
    int width = m_dp.d_tag.rect.wid();
    int height = m_dp.d_tag.rect.het();
    csc_t& csc_data = m_dp.csc_plane;
    unsigned infmt = csc_data.infmt;
    unsigned outfmt = csc_data.outfmt;
    unsigned bright = csc_data.bright;
    bool prog = csc_data.prog;
    unsigned coef1 = csc_data.coefs[0][0];
    unsigned coef2 = csc_data.coefs[0][1];
    unsigned coef3 = csc_data.coefs[0][2];
    unsigned coef4 = csc_data.coefs[1][0];
    unsigned coef5 = csc_data.coefs[1][1];
    unsigned coef6 = csc_data.coefs[1][2];
    unsigned coef7 = csc_data.coefs[2][0];
    unsigned coef8 = csc_data.coefs[2][1];
    unsigned coef9 = csc_data.coefs[2][2];
    const unsigned short* psrc = reinterpret_cast<unsigned short*>(buf_ptr[S0]);
    unsigned short* pdst = reinterpret_cast<unsigned short*>(buf_ptr[D]);

    // perform plane CSC
    csc_plane_c(width, height,
        infmt, outfmt, bright, prog,
        coef1, coef2, coef3,
        coef4, coef5, coef6,
        coef7, coef8, coef9,
        psrc, pdst,
        FILE_NAME[SCSC_CONFIG_DONE], FILE_NAME[SCSC_IN_WIN_VLD]);
}

void dpu_drv_c::csc_cursor()
{
    int width = m_dp.d_tag.rect.wid();
    int height = m_dp.d_tag.rect.het();
    csc_t& csc_data = m_dp.csc_cursor;
    unsigned outfmt = csc_data.outfmt;
    const unsigned char* psrc = reinterpret_cast<unsigned char*>(buf_ptr[S0]);
    unsigned char* pdst = reinterpret_cast<unsigned char*>(buf_ptr[D]);

    // perform cursor CSC
    csc_cursor_c(width, height, outfmt, psrc, pdst, FILE_NAME[CUR_CSC_VLD]);
}

void dpu_drv_c::cursor()
{
    int width = m_dp.d_tag.rect.wid();
    int height = m_dp.d_tag.rect.het();
    uint16_t* psrc = reinterpret_cast<uint16_t*>(buf_ptr[S0]);
    uint16_t* pdst = reinterpret_cast<uint16_t*>(buf_ptr[D]);
    cur_para p{};
    int32_t out_w{}, out_h{};
    p.panel_width = 200;
    p.panel_height = 200;
    p.x_start = 1;
    p.y_start = 200;
    p.cur_mono_fg = 0xffff;
    p.cur_type = 3;
    cursor_c(psrc, p, pdst, &out_w, &out_h, FILE_NAME[CUR_VLD]);
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
void dpu_drv_c::lut()
{
    int width = m_dp.d_tag.rect.wid();
    int height = m_dp.d_tag.rect.het();
    uint16_t* psrc = reinterpret_cast<uint16_t*>(buf_ptr[S0]);
    uint16_t* pdst = reinterpret_cast<uint16_t*>(buf_ptr[D]);
    lut_para p{};
    lut_c(psrc, pdst, width, height, p, LUT_DATA, FILE_NAME[LUT_IF], FILE_NAME[LUT_CONFIG]);
}

void dpu_drv_c::dither()
{
    int width = m_dp.d_tag.rect.wid();
    int height = m_dp.d_tag.rect.het();
    uint16_t* psrc = reinterpret_cast<uint16_t*>(buf_ptr[S0]);
    uint16_t* pdst = reinterpret_cast<uint16_t*>(buf_ptr[D]);
    dither_para p{};
    dither_c(psrc, pdst, width, height, p, FILE_NAME[DIHTER_IN_DE], FILE_NAME[DITHER_CONFIG]);
}

void dpu_drv_c::output()
{
    unsigned short* psrc = reinterpret_cast<unsigned short*>(buf_ptr[S0]);
    unsigned short* pdst = reinterpret_cast<unsigned short*>(buf_ptr[D]);
    if (EQUAL_OR(m_dp.s0fmt, DPU_RGB565, DPU_ARGB8888, DPU_ARGB2101010))
    {
        ASSERT_ITB(m_dp.dfmt == DPU_BUS_ARGB || m_dp.dfmt == DPU_BUS_CURS, "");
    }
    if (EQUAL_OR(m_dp.s0fmt, DPU_YUYV, DPU_AYUV8888, DPU_Y410, DPU_Y210))
    {
        ASSERT_ITB(m_dp.dfmt == DPU_BUS_AYUV || m_dp.dfmt == DPU_BUS_CURS, "");
    }

    uint32_t hw_info_id = 0 & 0xffff;
    uint32_t hw_info_frm = m_frm_idx & 0xffff;
    uint32_t hw_info = (hw_info_id << 4) | hw_info_frm;

    inp_para p{};
    p.stride_num = m_dp.s0_tag.pitch >> 5;
    p.spl_abgr = m_dp.inp.spl_abgr;
    p.spl_crycb = m_dp.inp.spl_crycb;
    p.spl_cbycry = m_dp.inp.spl_cbycry;
    //input_c(psrc, pdst, m_dp.d_tag.rect.wid(), m_dp.d_tag.rect.het(), m_dp.s0fmt, p, hw_info);
}

void dpu_drv_c::get_scl_ratio(scl_t& scl, bool is_panel)
{
    float hr = m_dp.s0_tag.rect.wid() * 1.0f / m_dp.d_tag.rect.wid(), vr = m_dp.s0_tag.rect.het() * 1.0f / m_dp.d_tag.rect.het();
    fixed_num hr_fix = fixed_num(1, 20, false, hr), vr_fix = fixed_num(1, 20, false, vr);
    scl.h_acc = hr_fix.get_raw_dw();
    scl.v_acc = vr_fix.get_raw_dw();
    if (is_panel)
    {
        scl.h_en = scl.v_en = true;
        if (hr == 1) {
            scl.h_acc = 0; scl.h_en = false;
        }
        if (vr == 1) {
            scl.v_acc = 0; scl.v_en = false;
        }

    }
    return;
}
void dpu_drv_c::set_stream(int id, bool is_preparedata, dpu_fmt_c fmt, bool is_rect)
{
    image_tag tag = m_img[id].get_tag();
    int buf_w, buf_h, rect_l, rect_t;
    if (is_rect)
    {
        buf_w = tag.rect.wid(); buf_h = tag.rect.het();
        //if out, crop, notice, all surface's surface size should be the same
        if (buf_w + tag.rect.lft > tag.wid)
        {
            buf_w = tag.wid - tag.rect.lft;
            ASSERT_ITB(id == CURS, "only cursor can set window out of dst surface");
        }

        if (buf_h + tag.rect.top > tag.het)
        {
            buf_h = tag.het - tag.rect.top;
            ASSERT_ITB(id == CURS, "only cursor can set window out of dst surface");
        }


        rect_l = tag.rect.lft; rect_t = tag.rect.top;
    }
    else
    {
        buf_w = tag.wid; buf_h = tag.het;
        rect_l = rect_t = 0;
    }
    uint32_t pitch = buf_w * tag.bpp;
    uint32_t size = buf_w * buf_h;
    bool is_bus_1010108 = false, is_bus_8bit = false;
    switch (fmt)
    {
    case DPU_BUS_AYUV:
    case DPU_BUS_ARGB:
        size = size * 8;//5 bytes
        is_bus_1010108 = true;
        break;
    case DPU_BUS_CURS:
        //8888
        size = size * 4;
        is_bus_8bit = true;
        break;
    case DPU_NV12: //never prepare data for 420 just allocate
    case DPU_P010:
        size = size * tag.bpp * 3 / 2;//5 bytes
        break;
    default:
        size *= tag.bpp;

        break;
    }
    if (buf_ptr[id] != nullptr)
    {
        delete[] buf_ptr[id];
        buf_ptr[id] = nullptr;
    }
    buf_ptr[id] = new uint8_t[size];
    memset(buf_ptr[id], 0, size);
    if (is_preparedata)
    {
        uint8_t* psrc_base = (uint8_t*)m_img[id].get_img_addr_full() + rect_t * tag.pitch, * psrc;
        uint16_t* pdst_base = (uint16_t*)buf_ptr[id];
        bus_1010108* pdst_bus;
        for (int y = rect_t; y <= rect_t + buf_h - 1; y++)
        {
            //copy by format request
            //basic case, just copy source data
            //for bus data we need convert
            if (is_bus_1010108)
            {

                for (int x = rect_l, x_w = 0; x_w <= buf_w - 1; x++, x_w++)
                {
                    psrc = psrc_base + (x << 2);
                    pdst_bus = (bus_1010108*)(pdst_base + (x_w << 2));
                    bool is_alpha_key = (psrc[1] + psrc[2] + psrc[0]) > 512;
                    bool is_color_key = !is_alpha_key && x_w > buf_w / 2 && y >= (rect_t + buf_h / 3) && y <= (rect_t + buf_h * 2 / 3);
                    //D[39]: alpha_key, D[38]: color_key, D[37:30]: alpha channel, D[29:20]: R/Y, D[19:10]: G/U, D[9:0]: B/V ....
                    pdst_bus->BV = (psrc[0] << 2) | (psrc[0] >> 6);
                    pdst_bus->GU = (psrc[1] << 2) | (psrc[1] >> 6);
                    pdst_bus->RY = (psrc[2] << 2) | (psrc[2] >> 6);
                    pdst_bus->A = (psrc[3] << 2) | (psrc[3] >> 6);
                    pdst_bus->is_color_key = is_color_key;
                    pdst_bus->is_alpha_key = is_alpha_key;
                    pdst_bus->is_ycbcr = fmt == DPU_BUS_AYUV;
                    pdst_bus->is_valid = true;
                }
                pdst_base += pitch;//surface
            }
            else
            {
                //TODO no 420 input //For is_bus_8bit also use copy
                memcpy(pdst_base, psrc_base + rect_l * tag.bpp, pitch);
                pdst_base += (pitch / 2);//short pointersurface
            }
            psrc_base += tag.pitch;//stream

        }


    }
    return; //need return continuous valid window data instead //TODO
}
void dpu_drv_c::get_stream(bool is_rect)
{
    image_tag tag = m_img[D].get_tag();
    int buf_w, buf_h, rect_l, rect_t;
    if (is_rect)
    {
        buf_w = tag.rect.wid(); buf_h = tag.rect.het();
        rect_l = tag.rect.lft; rect_t = tag.rect.top;
    }
    else
    {
        buf_w = tag.wid; buf_h = tag.het;
        rect_l = rect_t = 0;
    }
    uint32_t pitch = buf_w * tag.bpp;
    bool is_bus_1010108 = m_dp.dfmt == DPU_BUS_AYUV || m_dp.dfmt == DPU_BUS_ARGB;
    bool is_420 = m_dp.dfmt == DPU_NV12 || m_dp.dfmt == DPU_P010;
    bool is_bus_curs = m_dp.dfmt == DPU_BUS_CURS;

    uint8_t* pdst_base = (uint8_t*)m_img[D].get_img_addr_full(), * pdst;
    uint16_t* psrc_base = (uint16_t*)buf_ptr[D];
    bus_1010108* psrc;
    uint32_t uvoff = tag.wid * tag.het;
    ASSERT_ITB(!is_420 || (is_420 && (tag.wid & 1) || (tag.het & 1)), "nv12 surface wrong");
    pdst_base += rect_t * tag.pitch * tag.bpp;
    for (int y = rect_t; y <= rect_t + buf_h - 1; y++)
    {
        if (is_bus_1010108)
        {
            for (int x = rect_l, x_w = 0; x_w <= buf_w - 1; x++, x_w++)
            {
                psrc = (bus_1010108*)(psrc_base + (x_w << 2));//stream
                pdst = pdst_base + (x << 2); //surface
                if (m_dp.inp.spl_abgr)
                {
                    pdst[0] = (psrc->RY >> 2) & 0xff;
                    pdst[1] = (psrc->GU >> 2) & 0xff;
                    pdst[2] = (psrc->BV >> 2) & 0xff;
                }
                else
                {
                    pdst[0] = (psrc->BV >> 2) & 0xff;
                    pdst[1] = (psrc->GU >> 2) & 0xff;
                    pdst[2] = (psrc->RY >> 2) & 0xff;
                }
                pdst[3] = psrc->A;
            }
        }
        else
        {

            if (is_420)
            {
                //TODO by according interfacememcpy(pdst_base+ uvoff, psrc_base, buf_w * ptag.bpp/2);
            }
            else
            {
                memcpy(pdst_base, psrc_base, buf_w * tag.bpp);
            }
        }
        pdst_base += tag.pitch; //32bpp
        psrc_base += is_bus_curs ? pitch / 2 : pitch; //4 channels

    }

    return; //need return continuous valid window data instead //TODO
}

template<typename T>
T* make_ptr(uint64_t val)
{
    return reinterpret_cast<T*>(val);
}

void dpu_drv_c::dump_compare(const uint32_t& frm_idx)
{
    get_stream(m_dp.work_mode != DPUF_PAN_UPSCL && m_dp.work_mode != DPUF_OVERLAY);
    std::string out_file = m_img[D].dump_to_file(m_out_dir, frm_idx);
    std::string ref_file = str::replace(out_file, m_out_dir, m_ref_dir);
    int status = 3;

    uint32_t fail_x{}, fail_y{};
    if (!fs::exists(m_ref_dir) || !fs::exists(ref_file)) status = 0;
    else
    {
        auto [out_data, out_info] = file::read(out_file);
        auto [ref_data, ref_info] = file::read(ref_file);
        uint64_t out_ptr = (uint64_t)out_data.get();
        uint64_t ref_ptr = (uint64_t)ref_data.get();
        if (out_info.file_size != ref_info.file_size)
        {
            status = 1;
        }
        else
        {
            uint32_t bpp = m_img[D].get_tag().bpp;
            uint32_t width = m_img[D].get_tag().wid;
            uint32_t height = m_img[D].get_tag().het;
            uint32_t pitch = width * bpp;
            for (uint32_t y = 0; y < height; y++)
            {
                for (uint32_t x = 0; x < width; x++)
                {
                    uint32_t offset = y * pitch + x * bpp;
                    if (bpp == 1)
                    {
                        if (*make_ptr<uint8_t>(ref_ptr + offset) !=
                            *make_ptr<uint8_t>(out_ptr + offset))
                        {
                            fail_x = x;
                            fail_y = y;
                            status = 2;
                            break;
                        }
                    }
                    else if (bpp == 2)
                    {
                        if (*make_ptr<uint16_t>(ref_ptr + offset) !=
                            *make_ptr<uint16_t>(out_ptr + offset))
                        {
                            fail_x = x;
                            fail_y = y;
                            status = 2;
                            break;
                        }
                    }
                    else if (bpp == 4)
                    {
                        if (*make_ptr<uint32_t>(ref_ptr + offset) !=
                            *make_ptr<uint32_t>(out_ptr + offset))
                        {
                            fail_x = x;
                            fail_y = y;
                            status = 2;
                            break;
                        }
                    }
                    else if (bpp == 8)
                    {
                        if (*make_ptr<uint64_t>(ref_ptr + offset) !=
                            *make_ptr<uint64_t>(out_ptr + offset))
                        {
                            fail_x = x;
                            fail_y = y;
                            status = 2;
                            break;
                        }
                    }
                    else if (bpp == 16)
                    {
                    }
                }
                if (status == 2) break;
            }
        }
    }

    m_run_stutas.status.push_back(status);
    m_run_stutas.fail_coord.push_back(std::make_pair(fail_x, fail_y));
}

void dpu_drv_c::release_surface()
{
    for (int i = IMG_NUM - 1; i >= 0; i--)
    {
        m_img[i].free();
    }
}
