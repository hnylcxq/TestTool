#ifndef _DPU_DRIVER_H
#define _DPU_DRIVER_H
#include "driver.h"
#include "dpu_drv_para.h"
#include "image.h"
#include "cmodel_if.h"
using dpu_bus_t = struct _dbt
{
    unsigned short ch[4];
    bool is_line_end;
    bool is_last_line;
    bool is_line_st;
};


class dpu_drv_c : public driver_c
{
public:
    dpu_drv_c() 
    {
        func_p[DPUF_INP] = &dpu_drv_c::input;
        func_p[DPUF_STR_UPSCL] = &dpu_drv_c::scl_stream;
        func_p[DPUF_PAN_UPSCL] = &dpu_drv_c::scl_panel;
        func_p[DPUF_OVERLAY] = &dpu_drv_c::overlay;
        func_p[DPUF_CSC_PLANE] = &dpu_drv_c::csc_plane;
        func_p[DPUF_CSC_CURSOR] = &dpu_drv_c::csc_cursor;
		func_p[DPUF_CURSOR] = &dpu_drv_c::cursor;
        func_p[DPUF_LUT] = &dpu_drv_c::lut;
        func_p[DPUF_DITHER] = &dpu_drv_c::dither;
        func_p[DPUF_OUT] = &dpu_drv_c::output;
        func_p[DPUF_SIGNATURE] = &dpu_drv_c::signature;
    };
    ~dpu_drv_c() {};

    void initial(const env_args_t& _args);
    void process(const uint32_t& frm_idx);
    void initial_modules();
    void destroy_modules();
    enum img_e {
        S0 = 0,
        S1 = 1,
        CURS = 2,
        D = 3,
        IMG_NUM = 4

    };
private:

    void load_paras();
    void adjust_paras();
    void config_surface();
    void kick_off();
    void dump_compare(const uint32_t& frm_idx);
    void release_surface();
    void set_stream(int id, bool is_preparedata, dpu_fmt_c fmt, bool is_rect = true);
    void get_stream(bool is_rect = true);
    void get_scl_ratio(scl_t &scl,bool is_panel);
    bool m_is_chk_en = false;
    bool m_is_ref_chk_en = false;
    std::string* m_res_dir_list{};
    std::string m_out_dir{};
    std::string m_ref_dir{};
    frame_para_c m_frame{};
    uint32_t m_frm_idx{};

    dpu_drv_para_t m_dp{};
    image_c m_img[IMG_NUM]{};
    //if we have our own image_c ,could put it in image_c, however, now , put in 
    uint8_t* buf_ptr[IMG_NUM] = {nullptr};
    //void dither(const dpu_drv_para_t &para, bool is_ref,image_c *sf);
    void input();
    void scl_stream();
    void scl_panel();
    void overlay();
    void csc_plane();
    void signature();
    void csc_cursor();
    void cursor();
    void lut();
    void dither();
    void output();
    void (dpu_drv_c::*func_p[DPUF_FUNC_NUM])();
    
};


#endif // !_CE_DRIVER_H
