#include "dpu_cmodel.h"
#include "dpu_csc.h"
#include "dpu_fixed_num.hpp"
#include "dpu_ckp.h"
#define STREAM_DBGMODE 0 //1, dump file, 2, load file
#ifndef __VCS__
#define prt_onscr printf
#else
#include <cassert>
#include <vcsuser.h>
#define prt_onscr io_printf
#endif
#define MSK38 0x3fffffffffull
#define MSK30 0x3fffffffull
const unsigned int scl_cos_t[256] =
{ 0x100,0x100,0x100,0x100,0x100,0x100,0x100,0x100,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfe,
0xfe,0xfd,0xfd,0xfd,0xfc,0xfc,0xfb,0xfb,0xfa,0xfa,0xf9,0xf9,0xf8,0xf8,0xf7,0xf7,
0xf6,0xf6,0xf5,0xf4,0xf4,0xf3,0xf2,0xf2,0xf1,0xf0,0xef,0xee,0xee,0xed,0xec,0xeb,
0xea,0xe9,0xe8,0xe8,0xe7,0xe6,0xe5,0xe4,0xe3,0xe2,0xe1,0xe0,0xdf,0xde,0xdc,0xdb,
0xda,0xd9,0xd8,0xd7,0xd6,0xd4,0xd3,0xd2,0xd1,0xd0,0xce,0xcd,0xcc,0xcb,0xc9,0xc8,
0xc7,0xc5,0xc4,0xc3,0xc1,0xc0,0xbf,0xbd,0xbc,0xba,0xb9,0xb8,0xb6,0xb5,0xb3,0xb2,
0xb0,0xaf,0xae,0xac,0xab,0xa9,0xa8,0xa6,0xa5,0xa3,0xa2,0xa0,0x9e,0x9d,0x9b,0x9a,
0x98,0x97,0x95,0x94,0x92,0x91,0x8f,0x8d,0x8c,0x8a,0x89,0x87,0x86,0x84,0x82,0x81,
0x7f,0x7e,0x7c,0x7a,0x79,0x77,0x76,0x74,0x73,0x71,0x6f,0x6e,0x6c,0x6b,0x69,0x68,
0x66,0x65,0x63,0x62,0x60,0x5e,0x5d,0x5b,0x5a,0x58,0x57,0x55,0x54,0x52,0x51,0x50,
0x4e,0x4d,0x4b,0x4a,0x48,0x47,0x46,0x44,0x43,0x41,0x40,0x3f,0x3d,0x3c,0x3b,0x39,
0x38,0x37,0x35,0x34,0x33,0x32,0x30,0x2f,0x2e,0x2d,0x2c,0x2a,0x29,0x28,0x27,0x26,
0x25,0x24,0x22,0x21,0x20,0x1f,0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18,0x18,0x17,0x16,
0x15,0x14,0x13,0x12,0x12,0x11,0x10,0xf,0xe,0xe,0xd,0xc,0xc,0xb,0xa,0xa,
0x9,0x9,0x8,0x8,0x7,0x7,0x6,0x6,0x5,0x5,0x4,0x4,0x3,0x3,0x3,0x2,
0x2,0x2,0x2,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0 };
const unsigned int panel_scl_cos_t[256] = { 
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x2,0x2,0x2,
0x2,0x3,0x3,0x3,0x4,0x4,0x5,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x9,0x9,
0xa,0xa,0xb,0xc,0xc,0xd,0xe,0xe,0xf,0x10,0x11,0x11,0x12,0x13,0x14,0x15,
0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,
0x25,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2f,0x30,0x31,0x32,0x34,0x35,0x36,0x37,
0x39,0x3a,0x3b,0x3d,0x3e,0x3f,0x41,0x42,0x44,0x45,0x46,0x48,0x49,0x4b,0x4c,0x4d,
0x4f,0x50,0x52,0x53,0x55,0x56,0x58,0x59,0x5b,0x5c,0x5e,0x5f,0x61,0x62,0x64,0x65,
0x67,0x68,0x6a,0x6c,0x6d,0x6f,0x70,0x72,0x73,0x75,0x76,0x78,0x7a,0x7b,0x7d,0x7e,
0x80,0x81,0x83,0x85,0x86,0x88,0x89,0x8b,0x8c,0x8e,0x90,0x91,0x93,0x94,0x96,0x97,
0x99,0x9a,0x9c,0x9d,0x9f,0xa1,0xa2,0xa4,0xa5,0xa7,0xa8,0xaa,0xab,0xad,0xae,0xaf,
0xb1,0xb2,0xb4,0xb5,0xb7,0xb8,0xb9,0xbb,0xbc,0xbe,0xbf,0xc0,0xc2,0xc3,0xc4,0xc6,
0xc7,0xc8,0xca,0xcb,0xcc,0xcd,0xcf,0xd0,0xd1,0xd2,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,
0xda,0xdc,0xdd,0xde,0xdf,0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,
0xea,0xeb,0xec,0xed,0xee,0xef,0xef,0xf0,0xf1,0xf2,0xf2,0xf3,0xf4,0xf5,0xf6,0xf6,
0xf7,0xf7,0xf7,0xf8,0xf9,0xf9,0xfa,0xfa,0xfa,0xfb,0xfb,0xfc,0xfc,0xfd,0xfd,0xfd,
0xfe,0xfe,0xfe,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };

bool get_valid_sig(win_c win, int x, int y)
{
    return x >= 0 && x < win.w && y >= 0 && y <win.h;
}

inline bool get_valid_sig_pos(win_c win, int x, int y, int& pos)
{
    bool valid_bit = false;
    pos = -1;
    x = x - win.x;
    y = y - win.y;
    if (get_valid_sig(win, x , y))
    {
        valid_bit = true;
        pos = x + y * win.w;
    }
    return valid_bit;
}

void get_pix_from_bus(const bus_1010108* pbus, uint16_t* pres, unsigned long long* buscolor = nullptr, bool is_get_alpha = true)
{
    pres[0] = pbus->BV;
    pres[1] = pbus->GU;
    pres[2] = pbus->RY;
    if(is_get_alpha)
        pres[3] = pbus->A;
    if (buscolor != nullptr)
    {
        if(is_get_alpha)
            *buscolor = *((unsigned long long*)pbus) & MSK38;
        else
            *buscolor = *((unsigned long long*)pbus) & MSK30;
    }
    return;
}
unsigned long long get_pix(uint16_t* psrc, uint16_t* pres, int x, int y, int w, int h)
{
    if (x >= w)
        x = w - 1;
    if (y >= h)
        y = h - 1;
    psrc += (x + y * w) * 4;
    unsigned long long buscolor;
    get_pix_from_bus((bus_1010108*)psrc, pres, &buscolor);
    return buscolor;
}
unsigned long long get_pix_int(uint16_t* psrc, uint16_t* pres, int x, int y, int w, int x0, int y0, int sw , int sh)
{
    if (x >= sw)
        x = sw - 1;
    if (y >= sh)
        y = sh - 1;
    psrc += (x + x0  + (y + y0)* w) * 4;
    unsigned long long buscolor;
    get_pix_from_bus((bus_1010108*)psrc, pres, &buscolor);
    return buscolor;
}
uint16_t get_ch(uint16_t* pbase, int x, int y, int w, int h, int ch)
{
    if (x >= w)
        x = w - 1;
    if (y >= h)
        y = h - 1;
    bus_1010108* bus = (bus_1010108*)(pbase + (x + y * w) * 4);
    switch (ch)
    {
    case 0:
        return bus->BV;
    case 1:
        return bus->GU;
    case 2:
        return bus->RY;
    case 3:
        return bus->A;
    default:
        assert(0);
        break;
    }
    return 0;
}
void set_color_to_bus(unsigned short* pbus_, unsigned short* pcolor, 
    bool* is_color_key = nullptr, bool* is_alpha_key = nullptr, uint32_t is_ycbcr = 0)
{
    bus_1010108* pbus = (bus_1010108*)pbus_;
    pbus->BV = pcolor[0];
    pbus->GU = pcolor[1];
    pbus->RY = pcolor[2];
    pbus->A = pcolor[3];
    if (is_color_key != nullptr)
        pbus->is_color_key= *is_color_key;
    if (is_alpha_key != nullptr)
        pbus->is_alpha_key = *is_alpha_key;
    pbus->is_ycbcr = is_ycbcr;
    return;
}
void get_weight(fixed_num off, bool is_scl, bool is_duplicate, bool is_cos, fixed_num& res)
{
    res = 1;
    if (is_scl)
    {
        if (is_duplicate)
        {
            res = 1;//off > 0.5 ? 0 : 1;
        }
        else
        {
            int ind = (off.get_raw_dw() >> 12) & 0xff;
            if (is_cos)
            {
                int val = scl_cos_t[ind];
                res.set_raw(val);
            }
            else
            {
                if (ind == 0xff)
                {
                    res.set_raw(0); 
                }
                else
                    res.set_raw(0x100 - ind); //res 's ini is 1

            }
               
        }
    }

    return;
}
//key_mode 
//alpha key: always calculate and send to next module
//color key: always calculate and return value as key result for scaling 
//chroma key: when keymode is 3, send chromakey as color key to next stage, however, do not use it in scaling 
bool check_color_key(uint16_t* pick_col, unsigned int dst_w, unsigned int keyl, unsigned int keyh, unsigned int key_mode, bool &is_color_key, bool &is_alpha_key)
{
    bool is_key_hit;
    is_alpha_key = (pick_col[3] & 0xff) == (keyl & 0xff);
    is_color_key = (pick_col[0] | (pick_col[1] << 10) | (pick_col[2] << 20)) == keyl;

    is_key_hit = key_mode == 0x6 ? is_color_key:false;
    
    if ((key_mode & 3) == 3)
    {
        is_color_key = true;
        for (int i = 0, shift = 0;i < 3;i++, shift += 10)
        {
            is_color_key = is_color_key && pick_col[i] >= ((keyl >> shift) & 0x3ff) && pick_col[i] <= ((keyh >> shift) & 0x3ff);
        }
    }
    
    return is_key_hit;
}
void dump_stream_set_tag(int src_w, int src_h, int dst_w, int dst_h, bool is_cos_h, bool is_cos_v,
    bool is_alpha_ups, int key_mode, bool is_v_duplicate, unsigned int keyl, unsigned int keyh,    unsigned int h_acc_, unsigned int v_acc_)
{
    sups_config_done_tag tag;
    tag.spl_src_w = src_w;
    tag.spl_src_h = src_h;
    tag.spl_dst_w = dst_w;
    tag.spl_dst_h = dst_h;
    tag.spl_hacc = h_acc_;
    tag.spl_vacc = v_acc_;
    tag.spl_htap = is_cos_h;
    tag.spl_vtap = is_cos_v;
    tag.spl_vdup = is_v_duplicate;
    tag.spl_alpha_ups = is_alpha_ups;
    tag.spl_keyl = keyl;
    tag.spl_keyh = keyh;
    tag.key_mode = key_mode;
    ck_dump(&tag);
    return;
}
void scl_stream_c(int src_w, int src_h, int dst_w, int dst_h, 
    bool is_cos_h, bool is_cos_v, bool is_alpha_ups, int key_mode, 
    bool is_v_duplicate, unsigned int keyl, unsigned int keyh, 
    unsigned short* psrc, unsigned short* pdst,
    unsigned int h_acc_, unsigned int v_acc_, 
    std::string svv_ckp_fn, std::string shv_ckp_fn, std::string scd_ckp_fn)
{
    unsigned short* prefdst;
    if (STREAM_DBGMODE == 1)
    {
        FILE* pfile = fopen("dbg_strscl_in.bin", "wb");
        fwrite(psrc, sizeof(bus_1010108), src_w* src_h, pfile);
        fclose(pfile);
    }
    else if (STREAM_DBGMODE == 2)
    {
        FILE* pfile = fopen("dbg_strscl_in.bin", "rb");
        fread(psrc, sizeof(bus_1010108), src_w * src_h, pfile);
        fclose(pfile);
        prefdst = new unsigned short[dst_w * dst_h * 4];
        pfile = fopen("dbg_strscl_out.bin", "rb");
        fread(prefdst, sizeof(bus_1010108), dst_w * dst_h, pfile);
        fclose(pfile);
    }
    ckp_c::inst()->initial(true, svv_ckp_fn, SUPS_VWIN_VLD);
    ckp_c::inst()->initial(true, shv_ckp_fn, SUPS_HWIN_VLD);
    ckp_c::inst()->initial(true, scd_ckp_fn, SUPS_CONFIG_DONE);
    //define fixed_num vars
    fixed_num acc_h_base = fixed_num(1, 20, false);
    fixed_num acc_v_base = fixed_num(1, 20, false);
    acc_h_base.set_raw(h_acc_);
    acc_v_base.set_raw(v_acc_);

    fixed_num acc_h = fixed_num(1, 20, false, 0);
    fixed_num acc_v = fixed_num(1, 20, false, 0);

    fixed_num coef_h = fixed_num(1, 8, false, 0);
    fixed_num coef_v = fixed_num(1, 8, false, 0);
    fixed_num coef_v1 = coef_v;
    fixed_num coef_h1 = coef_h;
    fixed_num mul_res = fixed_num(9, 8, false, 0);
    fixed_num sum = fixed_num(9, 9, false, 0);
    fixed_num sum_v_0 = fixed_num(9, 1, false, 0);
    fixed_num sum_v_1 = sum_v_0;
    fixed_num src_0 = fixed_num(8, 0, false, 0), src_1 = src_0;
    fixed_num half = fixed_num(1, 20, false, 0.5f);
    fixed_num one = fixed_num(1, 8, false, 1);
    fixed_num quarter_98 = fixed_num(9, 8, false, 0.25f);
    fixed_num okta_99 = fixed_num(9, 9, false, 0.125f);
    int src_x = 0, src_y = 0;
    bool is_h = src_w < dst_w;
    bool is_v = src_h < dst_h;
    //bypass
    bool is_bypass = !is_h && !is_v;//should never hit
    int shft[4] = { 2,2,2,0 };
    unsigned short pdst_pix[4], pick_col[4], v_key_sel_0[4], v_key_sel_1[4],*pdst_cur;
    bool is_color_key, is_alpha_key;
    acc_v = 0;
    sups_vwin_vld_tag vtag;
    sups_hwin_vld_tag htag;
    dump_stream_set_tag(src_w, src_h, dst_w, dst_h, is_cos_h, is_cos_v, is_alpha_ups, key_mode, is_v_duplicate, keyl, keyh, h_acc_, v_acc_);
    int is_key_hit_v[16]{};
    bool is_ycbcr = ((bus_1010108*)psrc)->is_ycbcr;//all pixels in one frame has same value

    for (int y = 0;y < dst_h;y++)
    {
        acc_h = 0;//reset acc_h
        src_x = 0;
        if (acc_h == 1)
        {
            acc_h = 0;
        }
        
        int v_off = acc_v >= half && !is_bypass && !is_v_duplicate? 1 : 0;
        get_weight(acc_v, is_v, is_v_duplicate, is_cos_v, coef_v);
        coef_v1.assign(one - coef_v);
        vtag.sups_vacc = acc_v.get_raw_dw();
        vtag.sups_vfct = (vtag.sups_vacc >> 12) & 0xff;
        vtag.sups_vcoef1 = coef_v.get_raw_dw();
        vtag.sups_vcoef2 = coef_v1.get_raw_dw();
        //printf("y = %d, acc_v = %f,  %f\n", y, float(acc_v), float(coef_v));
        for (int x = 0;x < dst_w;x++)
        {
            //get_color_from_bus(pdst + (y * dst_w + x) * 4, pdst_pix);
            int h_off = acc_h >= half && !is_bypass ? 1 : 0;
            get_weight(acc_h, is_h, false, is_cos_h, coef_h);
            coef_h1.assign(one - coef_h);
            htag.sups_hpxl = 0;
            htag.sups_hacc = acc_h.get_raw_dw();
            htag.sups_hfct = (htag.sups_hacc >> 12) & 0xff;
            htag.sups_hcoef1 = coef_h.get_raw_dw();
            htag.sups_hcoef2 = coef_h1.get_raw_dw();

            unsigned short x_y[4], x1_y[4], x_y1[4], x1_y1[4];
            if (is_v)
            {
                vtag.sups_vpxl_cur = get_pix(psrc, x_y, src_x, src_y, src_w, src_h);
                vtag.sups_vpxl_nxt = get_pix(psrc, x_y1, src_x, src_y + 1, src_w, src_h);
            }
            else
            {
                vtag.sups_vpxl_cur = 0;
                vtag.sups_vpxl_nxt = get_pix(psrc, x_y, src_x, src_y, src_w, src_h);
            }
            get_pix(psrc, x1_y, src_x + 1, src_y, src_w, src_h);
            get_pix(psrc, x1_y1, src_x + 1, src_y + 1, src_w, src_h);
            get_pix(psrc, v_key_sel_0, src_x, src_y + v_off, src_w, src_h);
            is_key_hit_v[(src_x & 0xf)] = check_color_key(v_key_sel_0, dst_w, keyl, keyh, key_mode, is_color_key, is_alpha_key); //colorkey alphakey useless here
            get_pix(psrc, v_key_sel_1, src_x + 1, src_y + v_off, src_w, src_h);
            is_key_hit_v[((src_x + 1) & 0xf)] = check_color_key(v_key_sel_1, dst_w, keyl, keyh, key_mode, is_color_key, is_alpha_key); //colorkey alphakey useless here
            
            get_pix(psrc, pick_col, src_x + h_off, src_y + v_off, src_w, src_h);
            bool is_key_hit = check_color_key(pick_col, dst_w, keyl, keyh, key_mode, is_color_key, is_alpha_key);


            //if (x == 0 && y <=1)
            //{
            //    float acc_h_float = acc_h;
            //    float acc_v_float = acc_v;
            //    prt_onscr("acc_h = %f, acc_v = %f, pick = (%d,%d), pick_col = %x,%x,%x,%x, colkey = %1d, a_key = %1d, keyl = %x\n",\
            //        acc_h_float, acc_v_float, src_x + h_off, src_y + v_off, pick_col[0], pick_col[1],pick_col[2],pick_col[3],is_color_key, is_alpha_key, keyl);
            //}
            unsigned long long dump_ch = 0;
            if (!is_key_hit && !is_bypass)
            {
                for (int ch = 0;ch < 4;ch++)
                {
                    
                    if (is_v)
                    {
                        src_0 = x_y[ch] >> shft[ch];
                        src_1 = x_y1[ch] >> shft[ch];
                        mul_res.assign(coef_v * src_0 + coef_v1 * src_1 + quarter_98);
                        if (is_key_hit_v[src_x & 0xf])
                            sum_v_0 = v_key_sel_0[ch] >> shft[ch];
                        else
                            sum_v_0.assign(mul_res, true, false);
                        //sum_v_0.assign(coef_v * psrc_pix[ch] + (one - coef_v) * psrc_pix[ch + 4 * dst_w]);
                        src_0 = x1_y[ch] >> shft[ch];
                        src_1 = x1_y1[ch] >> shft[ch];
                        mul_res.assign(coef_v * src_0 + coef_v1 * src_1 + quarter_98);
                        if (is_key_hit_v[(src_x + 1) & 0xf])
                            sum_v_1 = v_key_sel_1[ch] >> shft[ch];
                        else
                            sum_v_1.assign(mul_res, true, false);
                        dump_ch = sum_v_0.get_raw_dw();
                        if (is_v_duplicate)
                        {
                            dump_ch = x_y[ch];
                            if (ch == 3)
                                dump_ch = dump_ch << 2;
                        }
                        
                    }
                    else
                    {
                        sum_v_0 = x_y[ch] >> shft[ch];
                        sum_v_1 = x1_y[ch] >> shft[ch]; //8.0
                        vtag.sups_vacc = 1 << 20;
                        vtag.sups_vfct = 0xff;
                        vtag.sups_vcoef1 = 0;
                        vtag.sups_vcoef2 = 1<<8;
                        dump_ch = x_y[ch];     
                        if (ch == 3)
                            dump_ch = dump_ch << 2;
                    }
                   
                    htag.sups_hpxl = htag.sups_hpxl | (dump_ch << (ch * 10));
                    unsigned short res;
                    if (is_v_duplicate || !is_v)
                    {
                        sum.assign(coef_h * sum_v_0 + coef_h1 * sum_v_1 + quarter_98);
                        if (ch < 3)
                            res = (sum.get_raw_dw() >> (10 - shft[ch])) << 1;
                        else
                            res = sum.get_raw_dw() >> 9;
                    }
                    else
                    {
                        sum.assign(coef_h * sum_v_0 + coef_h1 * sum_v_1 + okta_99);
                        res = sum.get_raw_dw() >> (9 - shft[ch]);
                    }
                    
                    if (res >= (1 << (8 + shft[ch])))
                        res = (1 << (8 + shft[ch])) - 1;
                    pdst_pix[ch] = res;
                    if (ch == 3 && !is_alpha_ups) //always do v and choose at last
                    {
                        pdst_pix[3] = pick_col[3];
                    }
                }

            }
            else
            {
               memcpy(pdst_pix, pick_col, 4 * sizeof(unsigned short));
            }
            pdst_cur = pdst + (y * dst_w + x) * 4;
            set_color_to_bus(pdst_cur, pdst_pix, &is_color_key, &is_alpha_key);
            ((bus_1010108*)pdst_cur)->is_ycbcr = is_ycbcr;
            htag.sups_out_dat = *((unsigned long long*)pdst_cur) & MSK30;
            htag.sups_out_alpha = ((bus_1010108*)pdst_cur)->A;
            htag.sups_color_key = is_color_key;
            htag.sups_alpha_key = is_alpha_key;
            if (is_key_hit || is_bypass)
            {
                vtag.sups_vfct = 0xff;
                vtag.sups_vcoef1 = 0;
                vtag.sups_vcoef2 = 1 << 8;
                htag.sups_hpxl = htag.sups_out_alpha;
                htag.sups_hpxl = htag.sups_out_dat | (htag.sups_hpxl << 32ull);
            }
            ck_dump(&vtag);
            ck_dump(&htag);
            acc_h = acc_h + acc_h_base;
            if (acc_h >= 1)
            {
                acc_h = acc_h.create_by_frac();
                src_x++;
            }
        }
        acc_v = acc_v + acc_v_base;
        if (acc_v >= 1)
        {
            acc_v = acc_v.create_by_frac();
            src_y++;
        }
    }
    if (STREAM_DBGMODE == 1)
    {
        FILE* pfile = fopen("dbg_strscl_out.bin", "wb");
        fwrite(pdst, sizeof(bus_1010108), src_w * src_h, pfile);
    }
    else if (STREAM_DBGMODE == 2)
    {
        delete[] prefdst;
    }
    ckp_c::inst()->close(SUPS_VWIN_VLD);
    ckp_c::inst()->close(SUPS_HWIN_VLD);
    ckp_c::inst()->close(SUPS_CONFIG_DONE);
}

void get_weight_panel(fixed_num off, bool is_scl, bool is_cos, fixed_num& res, uint32_t & fct_tmp, uint32_t & fct)
{
    res = 1;
    if (is_scl)
    {
        int ind = (off.get_raw_dw() >> 12) & 0xff;
        int val;
        fct_tmp = ind;
        if (is_cos)
        {
            val = panel_scl_cos_t[ind];
        }
        else
            val = ind;
        fct = val;
        val = (val >> 1) + (val & 1);
        res.set_raw(val);
    }
    return;
}

//for panel upscaling, the input surface only have 3 channels
void scl_panel_c(int src_w, int src_h, int dst_w, int dst_h, 
    int surf_w, int surf_h, int rect_l, int rect_t, 
    bool is_cos, bool is_pus_en, bool is_h, bool is_v, bool is_hw_ratio, 
    bool ratio_plus, unsigned int bg_color_, unsigned short* psrc, unsigned short* pdst, 
    unsigned int h_acc_, unsigned int v_acc_, 
    std::string pid_ckp_fn, std::string pc_ckp_fn)
{
    if (!is_pus_en)
    {
        memcpy(pdst, psrc, sizeof(bus_1010108) * surf_w * surf_h);
        return;
    }
    ckp_c::inst()->initial(true, pid_ckp_fn, PUS_IN_DE);
    ckp_c::inst()->initial(true, pc_ckp_fn, PUS_CONFIG);
    //define fixed_num vars
    fixed_num acc_h_base = fixed_num(1, 20, false);
    fixed_num acc_v_base = fixed_num(1, 20, false);
    acc_h_base.set_raw(h_acc_);
    acc_v_base.set_raw(v_acc_);

    fixed_num acc_h = fixed_num(1, 20, false, 0);
    fixed_num acc_v = fixed_num(1, 20, false, 0);

    fixed_num coef_h = fixed_num(1, 7, false, 0);
    fixed_num coef_v = fixed_num(1, 7, false, 0);
    fixed_num sum = fixed_num(11, 7, false, 0);

    fixed_num sum_v_0 = fixed_num(8, 1, false, 0);
    fixed_num sum_v_1 = fixed_num(8, 1, false, 0);

    fixed_num half = fixed_num(1, 20, false, 0.5f);
    fixed_num one = fixed_num(1, 20, false, 1);
    fixed_num quarter_7 = fixed_num(0, 7, false, 0.25f);
    fixed_num okta_7 = fixed_num(0, 7, false, 0.125f);


    fixed_num src_0 = fixed_num(8, 0, false, 0), src_1 = src_0;
    unsigned long long het = src_h, wid = src_w;
    unsigned short dst_pix[4]{};
    pus_in_de_tag sig_tag{}, sig_tag_bypass{};
    pus_config_tag reg_tag{};
    reg_tag.reg_pus_en = is_pus_en;
    reg_tag.reg_pus_hen = is_h;
    reg_tag.reg_pus_ven = is_v;
    reg_tag.reg_pus_width_dst = dst_w;
    reg_tag.reg_pus_height_dst = dst_h;
    reg_tag.reg_pus_ratio_mode = is_hw_ratio;
    reg_tag.reg_pus_ratio_plus = ratio_plus;
    reg_tag.reg_pus_ratio_h = h_acc_;
    reg_tag.reg_pus_ratio_v = v_acc_;
    reg_tag.reg_pus_cos2tap = is_cos;
    reg_tag.reg_pus_bg_color = bg_color_;
    rect_l = rect_l - 1;
    rect_t = rect_t - 1;

    if (is_hw_ratio)
    {
        if (ratio_plus)
        {
            het = ((het + 1) << 20) / dst_h;
            wid = ((wid + 1) << 20) / dst_w;
        }
        else
        {
            het = (het << 20) / dst_h;
            wid = (wid << 20) / dst_w;
        }
        acc_h_base.set_raw(wid & 0x1fffff);
        acc_v_base.set_raw(het & 0x1fffff);
    }
    else
    {
        acc_h_base.set_raw(h_acc_);
        acc_v_base.set_raw(v_acc_);
    }
    reg_tag.ratio_h = acc_h_base.get_raw_dw() & 0xfffff;
    reg_tag.ratio_v = acc_v_base.get_raw_dw() & 0xfffff;
    ck_dump(&reg_tag);
    bus_1010108 bg_bus{};
    *((unsigned int*)&bg_bus) = bg_color_;
    bg_bus.is_ycbcr = ((bus_1010108*)psrc)[0].is_ycbcr;
    sig_tag_bypass.pus_lut_pxl = bg_color_;
    int src_x = 0, src_y = 0;
    fixed_num tmp = fixed_num(11, 0, false, 0);
    int rect_r = rect_l + dst_w - 1, rect_b = rect_t + dst_h - 1;
    for (int y = 0;y < surf_h;y++)
    {
        if (y < rect_t || y > rect_b)
        {
            for (int k = 0;k < surf_w;k++)
            {
                memcpy(pdst + (y * surf_w + k)* 4, &bg_bus, 8);
                sig_tag_bypass.pus_lut_pxl = bg_color_;
                ck_dump(&sig_tag_bypass);
            }
            continue;
        }
        acc_h = 0;//acc_h_base.create_by_frac();//reset acc_h
        src_x = 0;
        uint32_t h_fact_tmp, v_fact_tmp, h_fact, v_fact;
        get_weight_panel(acc_v, is_v, is_cos, coef_v, v_fact_tmp,v_fact);
        if (y == rect_t)
        {
            sig_tag.vfct_tmp = 0xff; sig_tag.vfct = 0xff;
        }
        else
        {
           sig_tag.vfct_tmp = v_fact_tmp;sig_tag.vfct = v_fact;
        }
        //printf("y = %d, acc_v = %f,  %f\n", y, float(acc_v), 1 - float(coef_v));
        for (int x = 0;x < surf_w;x++)
        {
            unsigned short x_y[4], x1_y[4], x_y1[4], x1_y1[4];
            sig_tag.h_acc = acc_h.get_raw_dw();
            sig_tag.v_acc = acc_v.get_raw_dw();
            sig_tag.ovl_pus_pxl = get_pix_int(psrc, x_y, src_x, src_y, surf_w, rect_l, rect_t, src_w, src_h);
            get_weight_panel(acc_h, is_h, is_cos, coef_h, h_fact_tmp, h_fact);
            get_pix_int(psrc, x1_y, src_x  + 1, src_y, surf_w, rect_l, rect_t, src_w, src_h);
            get_pix_int(psrc, x_y1, src_x, src_y + 1, surf_w, rect_l, rect_t, src_w, src_h);
            get_pix_int(psrc, x1_y1, src_x + 1, src_y + 1, surf_w, rect_l, rect_t, src_w, src_h);
            sig_tag.hfct_tmp = h_fact_tmp;sig_tag.hfct = h_fact;
            if (y == rect_t)
            {
                sig_tag.r_next_v = x_y[2] >> 2; sig_tag.r_current_v = 0;
                sig_tag.g_next_v = x_y[1] >> 2; sig_tag.g_current_v = 0;
                sig_tag.b_next_v = x_y[0] >> 2; sig_tag.b_current_v = 0;
            }
            else
            {
                sig_tag.r_current_v = x_y[2] >> 2; sig_tag.r_next_v = x_y1[2] >> 2;
                sig_tag.g_current_v = x_y[1] >> 2; sig_tag.g_next_v = x_y1[1] >> 2;
                sig_tag.b_current_v = x_y[0] >> 2; sig_tag.b_next_v = x_y1[0] >> 2;
            }
            
            unsigned short* pdst_pos = pdst + (y * surf_w + x) * 4;
            if (x<rect_l || x> rect_r)
            {
                memcpy(pdst_pos, &bg_bus, 8);
                sig_tag_bypass.pus_lut_pxl = bg_color_;
                ck_dump(&sig_tag_bypass);
                continue;
            }
            int dumpv0[3] = { 0 }, dumpv1[3] = { 0 };

            for (int ch = 0;ch < 3;ch++)
            {
                sum_v_0 = sum_v_1 = 0;
                src_0 = x_y[ch] >> 2;
                src_1 = x_y1[ch] >> 2;
                sum.assign((one - coef_v) * src_0 + coef_v * src_1);
                sum_v_0.assign(sum, true, true); //convert to 9.0
                dumpv0[ch] = sum_v_0.get_raw_dw() << 1;
                src_0 = x1_y[ch] >> 2;
                src_1 = x1_y1[ch] >> 2;
                sum.assign((one - coef_v) * src_0 + coef_v * src_1);
                sum_v_1.assign(sum, true, true); //
                dumpv1[ch] = sum_v_1.get_raw_dw() << 1;
                sum.assign((one - coef_h) * sum_v_0 + coef_h * sum_v_1 + okta_7); //9.0*1.7 get 12.14 ,store to 10.7 directly

                unsigned short res = sum.get_raw_dw() >> 5;
                if (res > 1023)
                    res = 1023;
                dst_pix[ch] = res;
            }

            acc_h = is_h ? acc_h + acc_h_base : acc_h + 1;
            if (acc_h >= 1)
            {
                acc_h = acc_h.create_by_frac();
                src_x++;
            }

            sig_tag.r_current_h = dumpv0[2]; sig_tag.r_next_h = dumpv1[2];
            sig_tag.g_current_h = dumpv0[1]; sig_tag.g_next_h = dumpv1[1];
            sig_tag.b_current_h = dumpv0[0]; sig_tag.b_next_h = dumpv1[0];
            sig_tag.h_r = dst_pix[2];
            sig_tag.h_g = dst_pix[1];
            sig_tag.h_b = dst_pix[0];
            set_color_to_bus(pdst_pos, dst_pix);
            ((bus_1010108*)pdst_pos)->is_ycbcr = bg_bus.is_ycbcr;
            sig_tag.pus_lut_pxl = *((unsigned long long*)pdst_pos) & MSK38;
            ck_dump(&sig_tag);
        }
        acc_v = is_v ? acc_v + acc_v_base : acc_v + 1;
        if (acc_v >= 1)
        {
            acc_v = acc_v.create_by_frac();
            src_y++;
        }
    }
    ckp_c::inst()->close(PUS_IN_DE);
    ckp_c::inst()->close(PUS_CONFIG);
}

bool set_key(uint32_t key_case, bool a_key, bool b_key)
{
    bool key_result = false;
    if (key_case == 0xd || (key_case & 0xc) == 0x8)
        key_result = a_key;
    else if (key_case == 0xe || (key_case & 0xc) == 0x4)
        key_result = b_key;
    else if (key_case == 0xc || key_case == 0xf)
        key_result = a_key || b_key;
    return key_result;
}
int bld_alu(unsigned int a, unsigned int b, int a_fct, int b_fct, bool is_cbcr, bool is_alpha_bld_mode = false, bool bld_mode = false, bool is_swap_ab = false)
{
    int a_s = a;
    int b_s = b;
    int res;
    if (is_cbcr) //do sign convert
    {
        a_s = a_s - 512;
        b_s = b_s - 512;
    }
    if (bld_mode == 0)
    {
        res = a_s * a_fct + b_fct * b_s;// no rounding
    }
    else//bld_mode == 1
    {
        if (is_swap_ab)//in.key_mode == 0x8
        {
            res = a_fct * b_s + b_fct * a_s;
        }
        else //if (in.key_mode == 0xc) 
        {
            res = a_fct * a_s + b_fct * b_s;
        }
    }
    if (is_alpha_bld_mode)
    {
        res = (res + 128) >> 8;
    //    int sign = res >= 0 ? 1 : -1;
    //    res = sign * ((abs(res) + 128) >> 8);//shift use abs or not? --> use simple method now
    }
    else
    {
        res = res >> 8;
    }
    
    if (is_cbcr)
    {
        //convert back
        res = res + 0x200;
        res = res < 1 ? 1 : (res > 0x3ff ? 0x3ff : res);
    }
    else
        res = res < 0 ? 0 : (res > 0x3ff ? 0x3ff : res);
    
    return res;
}
void ovl_base(const ovl_stream& in, const bus_1010108& a, const bus_1010108& b, bus_1010108& out, ovl_in_de_tag& sig_tag, bool is_ovl_0)
{
    //, bool a.is_valid, bool b.is_valid,
    //    unsigned short* a_pix, unsigned short* b_pix, unsigned short* res,
    //    unsigned int& alpha_out,
    unsigned int alpha_a = a.A, alpha_b = b.A, alpha_mix;
    unsigned short a_pix[4],b_pix[4],res[3];
    bool is_k[4] = { 0 };
    for (int i = 0;i < 4;i++)
    {
        is_k[i] = in.key_mode & (1 << i);
    }

    //get key
    bool ovl_a_key, ovl_b_key;
    unsigned int s_pla_fct, s_plb_fct,key_sel;
    if (is_k[1])
    {
        ovl_a_key = a.is_color_key; ovl_b_key = b.is_color_key;
    }
    else
    {
        ovl_a_key = is_k[0] ? a.is_alpha_key : a.is_valid;
        ovl_b_key = is_k[0] ? b.is_alpha_key : b.is_valid;
    }
    key_sel = is_k[2] ? ovl_b_key : ovl_a_key;
    if (key_sel)
    {
        s_pla_fct = in.pla_fct; s_plb_fct = in.plb_fct;
    }
    else
    {
        s_pla_fct = is_k[2]? 0:8; s_plb_fct = 8 - s_pla_fct;
    }

   
    if (is_k[3] || in.is_alpha_rang || (!in.is_alpha_rang && ((!is_k[2] && ovl_a_key) || (is_k[2] && ovl_b_key))))
        alpha_mix = alpha_a == 0xff ? 0xff : ((((0x100 - alpha_a) * alpha_b + 0x80) >> 8) + alpha_a);//alpha_cal_out
    else
        alpha_mix = !is_k[2] ? alpha_a : alpha_b;

    unsigned int alpha_key_case = ((a.is_valid << 3) | (b.is_valid << 2) | (in.alpha_key_sel & 3))&0xffffffff;
    unsigned int col_key_case = ((a.is_valid << 3) | (b.is_valid << 2) | (in.color_key_sel & 3)) & 0xffffffff;
    if (alpha_key_case == 0xd || (alpha_key_case & 0xc) == 0x8)
        out.A = alpha_a;
    else if (alpha_key_case == 0xe || (alpha_key_case & 0xc) == 0x4)
        out.A = alpha_b;
    else if (alpha_key_case == 0xc || alpha_key_case == 0xf)
        out.A = alpha_mix;
    else
        out.A = 0;

    out.is_color_key = set_key(col_key_case, a.is_color_key, b.is_color_key);
    out.is_alpha_key = set_key(alpha_key_case, a.is_alpha_key, b.is_alpha_key);
    
    out.is_ycbcr = (((s_plb_fct & 0xc) > 0) || is_k[3]) ? b.is_ycbcr : a.is_ycbcr;
    unsigned int ovl_alpha, plane_alpha_u, invert_alpha, alpha_u;
    
    //get alpha 
    ovl_alpha = 0;
    if (in.key_mode == 0x8)
        ovl_alpha = alpha_a;
    else if (in.key_mode == 0xc)
        ovl_alpha = alpha_b;
    else if (in.key_mode == 0x9)
        ovl_alpha = (in.pla_fct << 4) | in.plb_fct;

    plane_alpha_u = in.plane_alpha_val == 0xff ? ovl_alpha : (ovl_alpha * in.plane_alpha_val + 0x80) >> 8; //lose precision

    invert_alpha = in.is_inv_alpha ? (~plane_alpha_u) & 0xff : plane_alpha_u;

    //extend 8 bit to 9 bit
    if (invert_alpha == 0xff)
        alpha_u = 0x1ff;
    else if (invert_alpha == 0)
        alpha_u = 0;
    else if (in.is_inv_alpha)
        alpha_u = (invert_alpha << 1) | 1;
    else
        alpha_u = invert_alpha << 1;

    if (a.is_valid ^ b.is_valid)
    {
        const bus_1010108* psrc = a.is_valid ? &a : &b;
        out.BV = psrc->BV;
        out.GU = psrc->GU;
        if (out.is_ycbcr)
        {
            out.BV = out.BV == 0 ? 1 : out.BV;
            out.GU = out.GU == 0 ? 1 : out.GU;
        }
        out.RY = psrc->RY;
        if (is_ovl_0)
        {
            sig_tag.spl0_ovl_pxl = 0;
            sig_tag.spl0_ovl_alpha = 0;
            sig_tag.spl0_ovl_color_key = 0;
            sig_tag.spl0_ovl_alpha_key = 0;
            sig_tag.spl0_ovl_ycbcr = 0;
            sig_tag.ovl0_pla_fct = 8;
            sig_tag.ovl0_plb_fct =  0;
            sig_tag.ovl0_alpha = alpha_u;
            sig_tag.ovl0_ycbcr = out.is_ycbcr;
            sig_tag.ovl0_dout = *((unsigned long long*)(&out)) & MSK30;
            sig_tag.ovl1_a_alpha = out.A;
            sig_tag.ovl1_a_window = true;
            sig_tag.ovl1_a_alpha_key = out.is_alpha_key;
            sig_tag.ovl1_a_color_key = out.is_color_key;
        }
        else
        {
            sig_tag.spl1_ovl_pxl = 0;
            sig_tag.spl1_ovl_alpha = 0;
            sig_tag.spl1_ovl_color_key = 0;
            sig_tag.spl1_ovl_alpha_key = 0;
            sig_tag.spl1_ovl_ycbcr = 0;
            sig_tag.ovl1_alpha = alpha_u;
            sig_tag.ovl1_ycbcr = out.is_ycbcr;
            sig_tag.ovl1_pla_fct = 8;
            sig_tag.ovl1_plb_fct = 0;
            sig_tag.ovl1_dout = *((unsigned long long*)(&out)) & MSK30;
        }

        return;
    }
    int fct_a_bld, fct_b_bld;
    unsigned long long a_3chs, b_3chs;
    get_pix_from_bus(&a, a_pix, &a_3chs, false);
    get_pix_from_bus(&b, b_pix, &b_3chs, false);
   
    
    if (is_k[3])//alpha blending mode, branch 1
    {   
        //ycbcr case

        fct_b_bld = (alpha_u >> 1) + (alpha_u & 1);
        fct_a_bld = 0x100 - fct_b_bld;//1-a
        if (in.bld_mode == 1)
            fct_b_bld = plane_alpha_u == 0xff ? 0x100 : plane_alpha_u;

        for (int ch_id = 0;ch_id < 3;ch_id++)
        {
            res[ch_id] = bld_alu(a_pix[ch_id], b_pix[ch_id], fct_a_bld, fct_b_bld, (ch_id == 0 || ch_id == 1) && out.is_ycbcr, true ,in.bld_mode, in.key_mode == 0x8 || in.key_mode == 0x9);
        }
    }
    else
    {
         
        //do blend with lower precision
        
        for (int ch_id = 0;ch_id < 3;ch_id++)
        {
            fct_a_bld = s_pla_fct == 8 ? 0x100 : ((s_pla_fct & 0x7) << 5);
            fct_b_bld = s_plb_fct == 8 ? 0x100 : ((s_plb_fct & 0x7) << 5);
            res[ch_id] = bld_alu(a_pix[ch_id], b_pix[ch_id], fct_a_bld, fct_b_bld, (ch_id == 0 || ch_id == 1) && out.is_ycbcr);
        }
    }
    out.BV = res[0];
    out.GU = res[1];
    out.RY = res[2];

    if (is_ovl_0)
    {
        sig_tag.spl0_ovl_pxl = b_3chs;
        sig_tag.spl0_ovl_alpha = b.A;
        sig_tag.spl0_ovl_color_key = b.is_color_key;
        sig_tag.spl0_ovl_alpha_key = b.is_alpha_key;
        sig_tag.spl0_ovl_ycbcr = b.is_ycbcr;
        sig_tag.ovl0_pla_fct = s_pla_fct;
        sig_tag.ovl0_plb_fct = s_plb_fct;
        sig_tag.ovl0_alpha = alpha_u;
        sig_tag.ovl0_ycbcr = out.is_ycbcr;
        sig_tag.ovl0_dout = *((unsigned long long*)(&out))&MSK30;
        sig_tag.ovl1_a_alpha = out.A;
        sig_tag.ovl1_a_window = true;
        sig_tag.ovl1_a_alpha_key = out.is_alpha_key;
        sig_tag.ovl1_a_color_key = out.is_color_key;
    }
    else
    {
        sig_tag.spl1_ovl_pxl = b_3chs;
        sig_tag.spl1_ovl_alpha = b.A;
        sig_tag.spl1_ovl_color_key = b.is_color_key;
        sig_tag.spl1_ovl_alpha_key = b.is_alpha_key;
        sig_tag.spl1_ovl_ycbcr = b.is_ycbcr;
        sig_tag.ovl1_ycbcr = out.is_ycbcr;
        sig_tag.ovl1_pla_fct = s_pla_fct;
        sig_tag.ovl1_plb_fct = s_plb_fct;
        sig_tag.ovl1_alpha = alpha_u;
        sig_tag.ovl1_ycbcr = out.is_ycbcr;
        sig_tag.ovl1_dout = *((unsigned long long*)(&out)) & MSK30;
    }
}
enum {
    SEL_A = 0,
    SEL_INV_A,
    SEL_CUR,
    SEL_BLD
};
enum {
    CUR_MONO = 0,
    CUR_COL,
    CUR_BLD_PRE,
    CUR_BLD_NOR
};

//load window later
//input and output is 8 bit?
void ovl_cur(unsigned char* cur_pix, int ovl_type, unsigned short* a_pix, unsigned short* out, bool is_cur_ycbcr, bool is_a_cbcr, bool& is_res_cbcr, bool is_valid)
{
    out[3] = 0xff;
    if (!is_valid)
    {
        memcpy(out, a_pix, sizeof(unsigned short) * 3);
        return;
    }
    int sel_src = SEL_CUR;
    int alpha, bld_rounding, res;
    is_res_cbcr = is_a_cbcr;
    unsigned int mask = cur_pix[3] & 3;
    if (ovl_type == CUR_MONO || ovl_type == CUR_COL)
    {
        if ((mask & 2) == 0)
            sel_src = SEL_CUR;
        else if (mask == 2)
            sel_src = SEL_A;
        else
            sel_src = SEL_INV_A;
    }
    else
    {
        if (cur_pix[3] == 0xff)
            sel_src = SEL_CUR;
        else if (cur_pix[3] == 0x0)
            sel_src = SEL_A;
        else
            sel_src = SEL_BLD;
    }

    //for channel 0, Y/R
    
    for (int ch_id = 0;ch_id < 3;ch_id++)
    {
        switch (sel_src)
        {
        case SEL_A:
            out[ch_id] = a_pix[ch_id];
            break;
        case SEL_INV_A:
            out[ch_id] = (~a_pix[ch_id]) & 0x3ff;
            break;
        case SEL_CUR:
            out[ch_id] = cur_pix[ch_id]<<2;
            break;
        default: //blending ovl_type = CUR_BLD_PRE or CUR_BLD
            int cur_s = cur_pix[ch_id];
            int lsb = ((cur_pix[3] & 0x80) == 0x80) ? 0 : (a_pix[ch_id] & 3);
            int a_s = (a_pix[ch_id] >> 2);
            if (ch_id == 0 || ch_id == 1)
            {
                if (is_cur_ycbcr)
                    cur_s = cur_s - 128;
                if (is_a_cbcr)
                    a_s = a_s - 128;
            }

            int alpha_s_inv = (~cur_pix[3]) & 0xff;
            if (ovl_type == CUR_BLD_PRE)
            {
                alpha = 256;
                bld_rounding = 0;
            }
            else {
                alpha = cur_pix[3];
                bld_rounding = 128;
            }
            res = (cur_s * alpha + (alpha_s_inv + 1) * a_s + bld_rounding)>>8;
            if ((ch_id == 0 || ch_id == 1) && is_res_cbcr)
            {
                res = res + 128;
                out[ch_id] = res > 255 ? 255 : (res < 1 ? 1 : res);
            }
            else 
            {
                out[ch_id] = res > 255 ? 255 : (res < 0 ? 0 : res);
            }
            out[ch_id] = (out[ch_id] << 2) | lsb;
            break;
        }
        
    }

}
void ovl_set_tag(ovl_in_de_tag &sig_tag, ovl_config_tag &reg_tag, bool efuse_sec, unsigned int res_w, unsigned int res_h, unsigned int reg_bg_col, bool reg_bg_ycbcr, \
    const ovl_stream& ovl0, const ovl_stream& ovl1, \
    int curs_ovl_tp, bool is_curs_ycbcr)
{
    reg_tag.reg_bg_color = reg_bg_col;
    reg_tag.reg_bg_ycbcr = reg_bg_ycbcr;
    reg_tag.reg_ovl0_key_mode = ovl0.key_mode;
    reg_tag.reg_ovl0_pla_fct = ovl0.pla_fct;
    reg_tag.reg_ovl0_plb_fct = ovl0.plb_fct;
    reg_tag.reg_ovl0_alpha_blend_mode = ovl0.bld_mode;
    reg_tag.reg_ovl0_inv_alpha = ovl0.is_inv_alpha;
    reg_tag.reg_ovl0_plane_alpha = ovl0.plane_alpha_val;
    reg_tag.reg_ovl0_alpha_key_sel = ovl0.alpha_key_sel;
    reg_tag.reg_ovl0_color_key_sel = ovl0.color_key_sel;
    reg_tag.reg_ovl0_alpha_rang = ovl0.is_alpha_rang;
    reg_tag.reg_ovl1_key_mode = ovl1.key_mode;
    reg_tag.reg_ovl1_pla_fct = ovl1.pla_fct;
    reg_tag.reg_ovl1_plb_fct = ovl1.plb_fct;
    reg_tag.reg_ovl1_alpha_blend_mode = ovl1.bld_mode;
    reg_tag.reg_ovl1_inv_alpha = ovl1.is_inv_alpha;
    reg_tag.reg_ovl1_plane_alpha = ovl1.plane_alpha_val;
    reg_tag.reg_ovl1_alpha_key_sel = ovl1.alpha_key_sel;
    reg_tag.reg_ovl1_color_key_sel = ovl1.color_key_sel;
    reg_tag.reg_ovl1_alpha_rang = ovl1.is_alpha_rang;
    sig_tag.cur_ovl_type = curs_ovl_tp;
    sig_tag.cur_ovl_ycbcr = is_curs_ycbcr;

}

void adjust_win(win_c &win, bool is_ref_int, win_c wi)
{
    win.x = win.x - 1; win.y = win.y - 1;
    if (is_ref_int)
    {
        win.x += wi.x; win.y += wi.y;
    }
    return;
}
//pu_en|| cur_ref_iwin
//all internal data is ARGB,so UV's channel index is 0,1
using ovl_wins = struct _ovlwins
{
    unsigned int res_w;
    unsigned int res_h;
    win_c _0;
    win_c _1;
    win_c _c;
    win_c _i;
    bool pu_en;
    bool is_ref_int_c;
};
void overlay_c(bool efuse_sec, unsigned int res_w, unsigned int res_h, unsigned int reg_bg_col, bool reg_bg_ycbcr, \
    const ovl_stream& ovl0, const ovl_stream& ovl1, \
    int curs_ovl_tp, bool is_curs_ycbcr, unsigned short* psrc_0, unsigned short* psrc_1,
    unsigned int* psrc_curs, unsigned short* pdst, win_c w_0, win_c w_1, win_c w_c, win_c w_i,bool pu_en, bool is_ref_int_c_,
    std::string oid_ckp_fn, std::string oc_ckp_fn)
{
   
   
    ckp_c::inst()->initial(true, oid_ckp_fn, OVL_IN_DE);
    ckp_c::inst()->initial(true, oc_ckp_fn, OVL_CONFIG);
    bus_1010108 sig_a{}, sig_b{}, sig_out{};
    ovl_stream ovl0_loc = ovl0, ovl1_loc = ovl1;
    ovl_in_de_tag sig_tag;
    ovl_config_tag reg_tag;
    int cnt = 0;
    bool is_ref_int_c = pu_en || is_ref_int_c_;
    win_c win_cur_clamp;
    w_i.x--;
    w_i.y--;
    //w_c.w = w_c.h = w_1.w = w_1.h = 0;
    adjust_win(w_0, ovl0.is_ref_int, w_i);
    adjust_win(w_1, ovl1.is_ref_int, w_i);
    adjust_win(w_c, is_ref_int_c, w_i);

    if (is_ref_int_c)
    {
        win_cur_clamp = w_i;
    }
    else
    {
        win_cur_clamp.x = win_cur_clamp.y = 0;
        win_cur_clamp.w = res_w;
        win_cur_clamp.h = res_h;
    }
    //clamp for cursor
    if ((int)win_cur_clamp.w + win_cur_clamp.x < w_c.w + w_c.x)
        w_c.w = win_cur_clamp.w + win_cur_clamp.x - w_c.x;
    if ((int)win_cur_clamp.h + win_cur_clamp.y < w_c.y + w_c.h)
        w_c.h = win_cur_clamp.h + win_cur_clamp.y - w_c.y;
    

    ovl_set_tag(sig_tag, reg_tag, efuse_sec, res_w, res_h, reg_bg_col, reg_bg_ycbcr,ovl0, ovl1,curs_ovl_tp, is_curs_ycbcr);
    ck_dump(&reg_tag);
    //deal with efuse_sec
    if (efuse_sec && ovl0.is_mdi_sec) {
        ovl0_loc.key_mode = 0x4;
        ovl0_loc.pla_fct = 0;
        ovl0_loc.plb_fct = 0x8;
    }
    if (efuse_sec && ovl1.is_mdi_sec) {
        ovl1_loc.key_mode = 0x4;
        ovl1_loc.pla_fct = 0;
        ovl1_loc.plb_fct = 0x8;
    }

    bool sig0_valid, sig1_valid,curs_valid;

    unsigned short polv0_out[4], povl1_out[4],pdst_pix[4];
    unsigned short s0_in[4] = { 0 }, s1_in[4] = { 0 };
    int pos0 = -1, pos1 = -1, pos_curs = -1,pos = 0;
    for (unsigned int y = 0.;y < res_h; y++)
    {
        for (unsigned int x = 0 ;x < res_w;x++)
        {
            memcpy((unsigned int*)(&sig_a), &reg_bg_col, 4); //copy 0~2 channel
            sig_a.A = 0;
            sig_a.is_alpha_key = false;
            sig_a.is_color_key = false;
            sig_a.is_ycbcr = reg_bg_ycbcr;
            sig_a.is_valid = true;

            sig0_valid = get_valid_sig_pos(w_0, x , y, pos0);
            sig1_valid = get_valid_sig_pos(w_1, x , y, pos1);
            curs_valid = get_valid_sig_pos(w_c, x ,y, pos_curs);

            //do background ovl with stream 0
            memset(polv0_out, 0, sizeof(unsigned short) * 4);
            if (sig0_valid)
                sig_b = *(bus_1010108*)(psrc_0 + (pos0 << 2));
            else
                memset(&sig_b, 0, sizeof(sig_b));
            sig_b.is_ycbcr = ovl0.is_ycbcr;
            
            sig_b.is_valid = sig0_valid;

            sig_tag.spl0_ovl_window = sig0_valid;

            ovl_base(ovl0_loc, sig_a, sig_b, sig_out, sig_tag, true);
            

            //ovl with stream1
            sig_a = sig_out;
            sig_a.is_valid = true;
            if (sig1_valid)
                sig_b = *(bus_1010108*)(psrc_1 + (pos1 << 2));
            else
                memset(&sig_b, 0, sizeof(sig_b));
            sig_b.is_ycbcr = ovl1.is_ycbcr;
            
            sig_b.is_valid = (efuse_sec && ovl0.is_mdi_sec) ? (!sig0_valid && sig1_valid) : sig1_valid;
            sig_tag.spl1_ovl_window = sig1_valid;
            ovl_base(ovl1_loc, sig_a, sig_b, sig_out, sig_tag, false);
            

            //ovl with cursor
            get_pix_from_bus(&sig_out, povl1_out);
            bool is_ycbcr_out = sig_out.is_ycbcr;
            ovl_cur((unsigned char*)(psrc_curs + pos_curs), curs_ovl_tp, povl1_out, pdst_pix, is_curs_ycbcr, sig_out.is_ycbcr, is_ycbcr_out, curs_valid);
            sig_tag.cur_ovl_window = curs_valid;
            sig_tag.cur_ovl_data = curs_valid  ? *((unsigned int*)(psrc_curs + pos_curs)) : 0;
            //write to bus
            bus_1010108 *pbusout = (bus_1010108*)(pdst + (pos << 2));
            set_color_to_bus(pdst + (pos << 2), pdst_pix);
            pbusout->is_ycbcr = is_ycbcr_out;
            sig_tag.ovl_pus_pxl = *((unsigned int*)pbusout) & MSK30;
            //prt_onscr("step sig_tag %d\n", cnt++);

            ck_dump(&sig_tag);

            pos++;
        }
    }
    ckp_c::inst()->close(OVL_IN_DE);
    ckp_c::inst()->close(OVL_CONFIG);
   
}
unsigned long long getbit(unsigned long long inp, int pos)
{
    return (inp >> pos) & 1;
}
void signature_c(int width, int height, const unsigned short* psrc, unsigned short* pdst)
{
    unsigned long long inp, out_h = 0x7fffffffff, out_l = 1,out_h_o;
    unsigned long long * psrcbus = (unsigned long long*)psrc;
    unsigned long long* pdstbus = (unsigned long long*)pdst;
    
    for (int y = 0, off =0;y < height;y++)
    {
        for (int x = 0;x < width; x++)
        {
            inp = psrcbus[off]&0x3fffffff;
            out_h_o = out_h;
            out_h = (((out_h << 1) | out_l) & 0x7fffffffff) ^ (inp >> 1);
            out_l = (getbit(out_h_o, 0) ^ getbit(out_h_o, 17)) ^ (getbit(out_h_o, 19) ^ getbit(out_h_o, 38)) ^ getbit(inp, 0);
            pdstbus[off] = (out_h << 1) | out_l;
            off++;
        }
    }
    return ;
}
unsigned long long signature_drv_c(int width, int height, const unsigned short* psrc)
{
    unsigned long long inp, out_h = 0x7fffffffff, out_l = 1, out_h_o;
    unsigned long long* psrcbus = (unsigned long long*)psrc;

    for (int y = 0, off = 0;y < height;y++)
    {
        for (int x = 0;x < width; x++)
        {
            inp = psrcbus[off] & 0x3fffffff;
            out_h_o = out_h;
            out_h = (((out_h << 1) | out_l) & 0x7fffffffff) ^ (inp >> 1);
            out_l = (getbit(out_h_o, 0) ^ getbit(out_h_o, 17)) ^ (getbit(out_h_o, 19) ^ getbit(out_h_o, 38)) ^ getbit(inp, 0);
            off++;
        }
    }
    return (out_h << 1)|out_l;
}
void csc_plane_c(int width, int height,
                 unsigned infmt, unsigned outfmt, unsigned bright, bool prog,
                 unsigned coef1, unsigned coef2, unsigned coef3,
                 unsigned coef4, unsigned coef5, unsigned coef6,
                 unsigned coef7, unsigned coef8, unsigned coef9,
                 const unsigned short* psrc, unsigned short* pdst,
                 std::string scd_ckp_fn, std::string siwv_ckp_fn)
{
    // checkpoint dump initialization
    ckp_c::inst()->initial(true, scd_ckp_fn, SCSC_CONFIG_DONE);
    ckp_c::inst()->initial(true, siwv_ckp_fn, SCSC_IN_WIN_VLD);
    // consts
    constexpr int PREC_DATA_IO[2] = {10, 0};
    constexpr int PREC_DATA_INTER[2] = {15, 9};
    constexpr int PREC_BRIGHT[2] = {8, 0};
    constexpr int PREC_OFF_PARAM[2] = {11, 9}; // final offset parameters
    constexpr int PREC_COEFS[2] = {4, 9};
    // convert params to fixed num
    fixed_num fx_coefs[3][3]{};
    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            fx_coefs[r][c] = fixed_num(PREC_COEFS[0], PREC_COEFS[1], true);
        }
    }
    csc_mat_dpu cm(infmt, outfmt);
    if (prog) // use manually set coefs
    {
        fx_coefs[0][0].set_raw(coef1);
        fx_coefs[0][1].set_raw(coef2);
        fx_coefs[0][2].set_raw(coef3);
        fx_coefs[1][0].set_raw(coef4);
        fx_coefs[1][1].set_raw(coef5);
        fx_coefs[1][2].set_raw(coef6);
        fx_coefs[2][0].set_raw(coef7);
        fx_coefs[2][1].set_raw(coef8);
        fx_coefs[2][2].set_raw(coef9);
    }
    else // use fixed coefs
    {
        for (int r = 0; r < 3; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                fx_coefs[r][c] = cm(r, c);
            }
        }
    }
    //bool src_rgb  = infmt == 0 || infmt == 1;
    //bool src_full = infmt == 0 || infmt == 2 || infmt == 3 || infmt == 7;
    //bool dst_rgb  = outfmt == 0 || outfmt == 1;
    //bool dst_full = outfmt == 0 || outfmt == 2 || outfmt == 3 || outfmt == 7;
    bool src_rgb  = cm.is_src_rgb();
    bool src_full = cm.is_src_range_full();
    bool dst_rgb  = cm.is_dst_rgb();
    bool dst_full = cm.is_dst_range_full();
        
    // dump checkpoint for interface parameters
    scsc_config_done_tag cfg_tag{};
    cfg_tag.scsc_in_fmt   = infmt;
    cfg_tag.scsc_out_fmt  = outfmt;
    cfg_tag.scsc_bright   = bright;
    cfg_tag.scsc_program  = prog;
    cfg_tag.scsc_coef1    = coef1;
    cfg_tag.scsc_coef2    = coef2;
    cfg_tag.scsc_coef3    = coef3;
    cfg_tag.scsc_coef4    = coef4;
    cfg_tag.scsc_coef5    = coef5;
    cfg_tag.scsc_coef6    = coef6;
    cfg_tag.scsc_coef7    = coef7;
    cfg_tag.scsc_coef8    = coef8;
    cfg_tag.scsc_coef9    = coef9;
    ck_dump(&cfg_tag);
    memcpy(pdst, psrc, width * height * sizeof(bus_1010108));
    // traverse all pixels
    unsigned long long src_bus;
    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            // get source data
            uint16_t src[4]; // input data
            src_bus = get_pix(const_cast<uint16_t*>(psrc), src, c, r, width, height);
            fixed_num fx_src[3]{};
            for (int ch = 0; ch < 3; ++ch)
            {
                // signed for scaled YPbPr
                // BGR -> RGB for DPU_BUS_ARGB format
                fx_src[ch] = fixed_num(PREC_DATA_IO[0], PREC_DATA_IO[1], true,
                                       src[2-ch]);
            }
            // step 1: convert input to scaled data
            if (src_rgb)
            {
                if (!src_full)
                {
                    for (int ch = 0; ch < 3; ++ch)
                    {
                        fx_src[ch].assign(fx_src[ch] - 64);
                    }
                }
            }
            else
            {
                if (!src_full)
                {
                    fx_src[0].assign(fx_src[0] - 64);
                }
                // Cb/Cr -> scaled Pb/Pr
                fx_src[1].assign(fx_src[1] - 512);
                fx_src[2].assign(fx_src[2] - 512);
            }
            
            // step 2: CSC matrix operation
            fixed_num fx_csc[3]{}; // the result of CSC matrix operation
            unsigned int inter_csc[3][3]{}; // mat[r][c]*in[c]
            for (int r_mat = 0; r_mat < 3; ++r_mat)
            {
                // sum <- 0
                fx_csc[r_mat] = fixed_num(
                    PREC_DATA_INTER[0], PREC_DATA_INTER[1], true, 0);
                for (int c_mat = 0; c_mat < 3; ++c_mat)
                {
                    // sum <- sum + mat[r][c]*in[c]
                    fixed_num fx_tmp(
                        PREC_DATA_INTER[0], PREC_DATA_INTER[1], true);
                    fx_tmp.assign(fx_coefs[r_mat][c_mat]*fx_src[c_mat]);
                    fx_csc[r_mat].assign(fx_csc[r_mat] + fx_tmp);
                    // for checkpoint dump
                    inter_csc[r_mat][c_mat] = fx_tmp.get_raw_dw();
                }
            }
            
            // step 3: add brightness offset
            // bright_ext[9:0] = {bright[8], bright[8:0]} -> no change in value
            fixed_num fx_bright(PREC_BRIGHT[0]+1, PREC_BRIGHT[1], true, 0);
            if (prog)
            {
                unsigned bright_ext_msb = (bright & 0x100) << 1;
                unsigned bright_ext = bright_ext_msb | bright;
                fx_bright.set_raw(bright_ext);
            }
            // initial offset is 8-bit scale, will be expanded to 10-bit later
            int off_ry = dst_full ? 0 : 16;
            int off_gbuv = (dst_rgb && !dst_full) ? 16 : 0;
            fixed_num fx_off_ry(PREC_DATA_IO[0], PREC_DATA_IO[1], true,
                                off_ry);
            fixed_num fx_off_gbuv(PREC_DATA_IO[0], PREC_DATA_IO[1], true,
                                  off_gbuv);
            fixed_num fx_rnd(0, 1, false, 0.5);
            // the channel sum after brightness processing
            fixed_num fx_bproc[3] = {
                fixed_num(PREC_DATA_INTER[0], PREC_DATA_INTER[1], true),
                fixed_num(PREC_DATA_INTER[0], PREC_DATA_INTER[1], true),
                fixed_num(PREC_DATA_INTER[0], PREC_DATA_INTER[1], true)
            };
            // brightness offset only adds to R/G/B/Y channels
            fx_off_ry.assign(fx_off_ry + fx_bright);
            if (dst_rgb)
            {
                fx_off_gbuv.assign(fx_off_gbuv + fx_bright);
            }
            // final offset parameters: left shift 11 bits (Q9.0 -> Q11.9)
            // new_val = old_val << 2;
            fixed_num fx_adj_ry(PREC_OFF_PARAM[0], PREC_OFF_PARAM[1], true,
                                fx_off_ry * 4);
            fixed_num fx_adj_gbuv(PREC_OFF_PARAM[0], PREC_OFF_PARAM[1], true,
                                  fx_off_gbuv * 4);
                
            fx_bproc[0].assign(fx_csc[0] + fx_adj_ry + fx_rnd);
            fx_bproc[1].assign(fx_csc[1] + fx_adj_gbuv + fx_rnd);
            fx_bproc[2].assign(fx_csc[2] + fx_adj_gbuv + fx_rnd);
            
            // step 4: compute output data
            uint16_t dst[4];// = get_ch(pdst, c, r, width, height, 0);
            // limits
            int rgby_min = 0;
            int rgby_max = (1 << PREC_DATA_IO[0]) - 1;
            fixed_num fx_rgby_min(
                PREC_DATA_IO[0], PREC_DATA_IO[1], false, rgby_min);
            fixed_num fx_rgby_max(
                PREC_DATA_IO[0], PREC_DATA_IO[1], false, rgby_max);
            int cbcr_min = -512;
            int cbcr_max = 511;
            fixed_num fx_cbcr_min(
                PREC_DATA_IO[0], PREC_DATA_IO[1], true, cbcr_min);
            fixed_num fx_cbcr_max(
                PREC_DATA_IO[0], PREC_DATA_IO[1], true, cbcr_max);
            fixed_num fx_dst[3] = {fx_bproc[0], fx_bproc[1], fx_bproc[2]};
            // clamp result
            if (dst_rgb)
            {
                for (int ch = 0; ch < 3; ++ch)
                {
                    fx_dst[ch] = (fx_dst[ch] < fx_rgby_min) ?
                        fx_rgby_min : fx_dst[ch];
                    fx_dst[ch] = (fx_dst[ch] > fx_rgby_max) ?
                        fx_rgby_max : fx_dst[ch];
                }
            }
            else // scaled YPbPr -> YCbCr
            {
                fx_dst[0] = (fx_dst[0] < fx_rgby_min) ?
                    fx_rgby_min : fx_dst[0];
                fx_dst[0] = (fx_dst[0] > fx_rgby_max) ?
                    fx_rgby_max : fx_dst[0];
                for (int ch = 1; ch < 3; ++ch)
                {
                    fx_dst[ch] = (fx_dst[ch] < fx_cbcr_min) ?
                        fx_cbcr_min : fx_dst[ch];
                    fx_dst[ch] = (fx_dst[ch] > fx_cbcr_max) ?
                        fx_cbcr_max : fx_dst[ch];
                    // make result positive
                    fx_dst[ch].assign(fx_dst[ch] + 512);
                }
            }
            // get output
            for (int ch = 0; ch < 3; ++ch)
            {
                double data_out = static_cast<double>(fx_dst[ch]);
                // RGB -> BGR for DPU_BUS_ARGB format
                dst[2-ch] = static_cast<uint16_t>(data_out);
            }
            dst[3] = src[3];//bypass alpha too
            unsigned short *pdst_cur = pdst + (static_cast<std::size_t>(width) * r + c) * 4;
            set_color_to_bus(pdst_cur,dst);
            // set ycbcr flag based on outfmt
            bus_1010108* pbus = reinterpret_cast<bus_1010108*>(pdst_cur);
            pbus->is_ycbcr = !dst_rgb;

            // dump per-pixel checkpoint
            scsc_in_win_vld_tag data_tag{};
            data_tag.scsc_in_pxl   = src_bus & MSK30;
            data_tag.scsc_r_f1     = inter_csc[0][0];
            data_tag.scsc_g_f2     = inter_csc[0][1];
            data_tag.scsc_b_f3     = inter_csc[0][2];
            data_tag.scsc_r_f4     = inter_csc[1][0];
            data_tag.scsc_g_f5     = inter_csc[1][1];
            data_tag.scsc_b_f6     = inter_csc[1][2];
            data_tag.scsc_r_f7     = inter_csc[2][0];
            data_tag.scsc_g_f8     = inter_csc[2][1];
            data_tag.scsc_b_f9     = inter_csc[2][2];
            data_tag.scsc_sum_r    = fx_csc[0].get_raw_dw();
            data_tag.scsc_sum_g    = fx_csc[1].get_raw_dw();
            data_tag.scsc_sum_b    = fx_csc[2].get_raw_dw();
            data_tag.scsc_bright_r = fx_bproc[0].get_raw_dw();
            data_tag.scsc_bright_g = fx_bproc[1].get_raw_dw();
            data_tag.scsc_bright_b = fx_bproc[2].get_raw_dw();
            data_tag.scsc_out_pxl  = *(reinterpret_cast<unsigned long long*>(pdst_cur)) & MSK30;
            ck_dump(&data_tag);
        }
    }
    ckp_c::inst()->close(SCSC_CONFIG_DONE);
    ckp_c::inst()->close(SCSC_IN_WIN_VLD);
}

void csc_cursor_c(int width, int height,
                  unsigned outfmt,
                  const unsigned char* psrc, unsigned char* pdst,
                  std::string ccv_ckp_fn)
{
    // checkpoint dump initialization
    ckp_c::inst()->initial(true, ccv_ckp_fn, CUR_CSC_VLD);
    if (outfmt == 0) // bypass
    {
        // copy 4 channels
        std::memcpy(pdst, psrc, static_cast<std::size_t>(width)*height*4);
        // dump checkpoint
        for (int r = 0; r < height; ++r)
        {
            for (int c = 0; c < width; ++c)
            {
                // get source data (4 channels)
                unsigned idx_ch0 = (c + r*width) * 4;
                uint8_t* src = const_cast<uint8_t*>(&(psrc[idx_ch0]));
                uint8_t* dst = &(pdst[idx_ch0]);
                // dump per-pixel checkpoint
                cur_csc_vld_tag data_tag{};
                data_tag.csc_in_dat  = *(reinterpret_cast<unsigned int*>(src));
                data_tag.ry_sum      = 0;
                data_tag.gu_sum      = 0;
                data_tag.bv_sum      = 0;
                data_tag.ry_bright   = 0;
                data_tag.gu_bright   = 0;
                data_tag.bv_bright   = 0;
                data_tag.cur_ycbcr   = 0;
                data_tag.csc_out_dat = *(reinterpret_cast<unsigned int*>(dst));
                ck_dump(&data_tag);
            }
        }
        ckp_c::inst()->close(CUR_CSC_VLD);
        return;
    }
    // consts
    constexpr int PREC_DATA_IO[2] = {8, 0};
    constexpr int PREC_DATA_INTER[2] = {9, 8};
    constexpr int PREC_COEFS[2] = {0, 8};
    constexpr unsigned INFMT = 0;
    // get matrix coefficients
    csc_mat_dpu cm(INFMT, outfmt);
    // convert params to fixed num
    fixed_num fx_coefs[3][3]{};
    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            fx_coefs[r][c] = fixed_num(PREC_COEFS[0], PREC_COEFS[1], true,
                                       cm(r, c));
        }
    }
    //bool dst_rgb = outfmt == 0 || outfmt == 1;
    //bool dst_full = outfmt == 0 || outfmt == 2 || outfmt == 3 || outfmt == 7;
    bool dst_rgb  = cm.is_dst_rgb();
    bool dst_full = cm.is_dst_range_full();
    // traverse all pixels
    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            // get source data (4 channels)
            unsigned idx_ch0 = (c + r*width) * 4;
            uint8_t* src = const_cast<uint8_t*>(&(psrc[idx_ch0]));
            fixed_num fx_src[3]{};
            for (int ch = 0; ch < 3; ++ch)
            {
                // signed for scaled YPbPr
                // BGR -> RGB for bus data
                fx_src[ch] = fixed_num(PREC_DATA_IO[0], PREC_DATA_IO[1], true,
                                       src[2-ch]);
            }
            // step 1: CSC matrix operationn
            // fx_csc = 0
            fixed_num fx_csc[3]{}; // the result of CSC matrix operation
            for (int r_mat = 0; r_mat < 3; ++r_mat)
            {
                // inter = 0
                fx_csc[r_mat] = fixed_num(
                    PREC_DATA_INTER[0], PREC_DATA_INTER[1], true, 0);
                for (int c_mat = 0; c_mat < 3; ++c_mat)
                {
                    // sum <- sum + mat[r][c]*in[c]
                    fx_csc[r_mat].assign(
                        fx_csc[r_mat] + fx_coefs[r_mat][c_mat]*fx_src[c_mat]);
                }
            }
            
            // step 2: add offset for data of limited range
            int off_ry = dst_full ? 0 : 16;
            int off_gbuv = (dst_rgb && !dst_full) ? 16 : 0;
            fixed_num fx_off_ry(PREC_DATA_IO[0], PREC_DATA_IO[1], true,
                                off_ry);
            fixed_num fx_off_gbuv(PREC_DATA_IO[0], PREC_DATA_IO[1], true,
                                  off_gbuv);
            fixed_num fx_rnd(0, 1, false, 0.5);
            // the channel sum after offset addition
            fixed_num fx_offsum[3] = {
                fixed_num(PREC_DATA_INTER[0], PREC_DATA_INTER[1], true),
                fixed_num(PREC_DATA_INTER[0], PREC_DATA_INTER[1], true),
                fixed_num(PREC_DATA_INTER[0], PREC_DATA_INTER[1], true)
            };
            fx_offsum[0].assign(fx_csc[0] + fx_off_ry + fx_rnd);
            fx_offsum[1].assign(fx_csc[1] + fx_off_gbuv + fx_rnd);
            fx_offsum[2].assign(fx_csc[2] + fx_off_gbuv + fx_rnd);

            // step 3: compute output data
            uint8_t* dst = &(pdst[idx_ch0]);
            // limits
            int rgby_min = 0;
            int rgby_max = (1 << PREC_DATA_IO[0]) - 1;
            fixed_num fx_rgby_min(
                PREC_DATA_IO[0], PREC_DATA_IO[1], false, rgby_min);
            fixed_num fx_rgby_max(
                PREC_DATA_IO[0], PREC_DATA_IO[1], false, rgby_max);
            int cbcr_min = -128;
            int cbcr_max = 127;
            fixed_num fx_cbcr_min(
                PREC_DATA_IO[0], PREC_DATA_IO[1], true, cbcr_min);
            fixed_num fx_cbcr_max(
                PREC_DATA_IO[0], PREC_DATA_IO[1], true, cbcr_max);
            fixed_num fx_dst[3] = {fx_offsum[0], fx_offsum[1], fx_offsum[2]};
            // clamp result
            if (dst_rgb)
            {
                for (int ch = 0; ch < 3; ++ch)
                {
                    fx_dst[ch] = (fx_dst[ch] < fx_rgby_min) ?
                        fx_rgby_min : fx_dst[ch];
                    fx_dst[ch] = (fx_dst[ch] > fx_rgby_max) ?
                        fx_rgby_max : fx_dst[ch];
                }
            }
            else // scaled YPbPr -> YCbCr
            {
                fx_dst[0] = (fx_dst[0] < fx_rgby_min) ?
                    fx_rgby_min : fx_dst[0];
                fx_dst[0] = (fx_dst[0] > fx_rgby_max) ?
                    fx_rgby_max : fx_dst[0];
                for (int ch = 1; ch < 3; ++ch)
                {
                    fx_dst[ch] = (fx_dst[ch] < fx_cbcr_min) ?
                        fx_cbcr_min : fx_dst[ch];
                    fx_dst[ch] = (fx_dst[ch] > fx_cbcr_max) ?
                        fx_cbcr_max : fx_dst[ch];
                    // make result positive
                    fx_dst[ch].assign(fx_dst[ch] + 128);
                }
            }
            // get output
            for (int ch = 0; ch < 3; ++ch)
            {
                double data_out = static_cast<double>(fx_dst[ch]);
                // RGB -> BGR for bus data
                dst[2-ch] = static_cast<uint8_t>(data_out);
            }
            dst[3] = src[3]; // bypass alpha data

            // dump per-pixel checkpoint
            cur_csc_vld_tag data_tag{};
            data_tag.csc_in_dat  = *(reinterpret_cast<unsigned int*>(src));
            data_tag.ry_sum      = fx_csc[0].get_raw_dw();
            data_tag.gu_sum      = fx_csc[1].get_raw_dw();
            data_tag.bv_sum      = fx_csc[2].get_raw_dw();
            data_tag.ry_bright   = fx_offsum[0].get_raw_dw();
            data_tag.gu_bright   = fx_offsum[1].get_raw_dw();
            data_tag.bv_bright   = fx_offsum[2].get_raw_dw();
            data_tag.cur_ycbcr   = dst_rgb ? 0 : 1;
            data_tag.csc_out_dat = *(reinterpret_cast<unsigned int*>(dst));
            ck_dump(&data_tag);
        }
    }
    ckp_c::inst()->close(CUR_CSC_VLD);
}

uint64_t make_bus_data_for_dump(uint16_t* _p_data)
{
    uint64_t t{}, d{};
    for (int i = 0; i < 4; i++)
    {
        d = _p_data[i];
        t |= d << (10 * i);
    }
    return t;
}
void input_c(unsigned short* p_src, unsigned short* p_dst,
    unsigned int w, unsigned int h, unsigned int sfmt, inp_para para,
    std::string swv_ckp_fn)
{
    ckp_c::inst()->initial(true, swv_ckp_fn, SPL_WIN_VLD);
    spl_win_vld_tag dump_tag{};

    uint32_t pitch_word = para.stride_num * 32 / 2;

    uint32_t pix_off = para.pix_off;

    uint16_t* p16_cur_line = p_src;

    uint8_t alhpa = 0xff;

    uint32_t is_ycbcr{};

    if (sfmt == 3 || sfmt == 9 || sfmt == 11 || sfmt == 13)
    {
        is_ycbcr = 1;
    }
    for (uint32_t y = 0; y < h; y++)
    {
        uint32_t x = 0;
        while (x < w)
        {
            uint16_t ch[4]{}, ch1[4]{};
            if (sfmt == 2) // rgb565
            {
                uint16_t sraw = p16_cur_line[pix_off + x];
                ch[0] = (sraw & 0x1f) << 5; // b
                ch[1] = ((sraw >> 5) & 0x3f) << 4; // g
                ch[2] = ((sraw >> 11) & 0x1f) << 5; // r
                ch[3] = alhpa;
            }
            else if (sfmt == 3) // yuyv & uyvy
            {
                uint16_t sraw0 = p16_cur_line[pix_off + x];
                uint16_t sraw1 = p16_cur_line[pix_off + x + 1];
                if (!para.spl_cbycry)
                {
                    ch[2] = (sraw0 & 0xff) << 2;
                    ch1[2] = (sraw1 & 0xff) << 2;
                    ch[1] = ch1[1] = ((sraw0 >> 8) & 0xff) << 2;
                    ch[0] = ch1[0] = ((sraw1 >> 8) & 0xff) << 2;
                    ch[3] = ch1[3] = alhpa;
                }
                else
                {
                    ch[2] = ((sraw0 >> 8) & 0xff) << 2;
                    ch1[2] = ((sraw1 >> 8) & 0xff) << 2;
                    ch[1] = ch1[1] = (sraw0 & 0xff) << 2;
                    ch[0] = ch1[0] = (sraw1 & 0xff) << 2;
                    ch[3] = ch1[3] = alhpa;
                }
                set_color_to_bus(p_dst + y * w * 4 + x * 4, ch, nullptr, nullptr, is_ycbcr);
                dump_tag.spl_unpack_dat = make_bus_data_for_dump(ch);
                ck_dump(&dump_tag);
                set_color_to_bus(p_dst + y * w * 4 + (x + 1) * 4, ch1, nullptr, nullptr, is_ycbcr);
                dump_tag.spl_unpack_dat = make_bus_data_for_dump(ch1);
                ck_dump(&dump_tag);
                x += 2;
                continue;
            }
            else if (sfmt == 8) // argb8888
            {
                uint32_t sraw = ((uint32_t*)p16_cur_line)[pix_off + x];
                uint32_t rsb = para.spl_abgr == 1 ? 0 : 16;
                uint32_t bsb = para.spl_abgr == 1 ? 16 : 0;
                ch[2] = ((sraw >> rsb) & 0xff) << 2;
                ch[1] = ((sraw >> 8) & 0xff) << 2;
                ch[0] = ((sraw >> bsb) & 0xff) << 2;
                ch[3] = ((sraw >> 24) & 0xff);
            }
            else if (sfmt == 9) // ayuv8888
            {
                uint32_t sraw = ((uint32_t*)p16_cur_line)[pix_off + x];
                ch[2] = ((sraw >> 16) & 0xff) << 2;
                ch[1] = ((sraw >> 8) & 0xff) << 2;
                ch[0] = ((sraw >> 0) & 0xff) << 2;
                ch[3] = (sraw >> 24) & 0xff;
            }
            else if (sfmt == 10) // argb1010102
            {
                uint32_t sraw = ((uint32_t*)p16_cur_line)[pix_off + x];
                uint32_t rsb = para.spl_abgr == 1 ? 0 : 20;
                uint32_t bsb = para.spl_abgr == 1 ? 20 : 0;
                ch[2] = (sraw >> rsb) & 0x3ff;
                ch[1] = (sraw >> 10) & 0x3ff;
                ch[0] = (sraw >> bsb) & 0x3ff;
                alhpa = sraw >> 30;
                ch[3] = ((alhpa & 0x3) << 6) | ((alhpa & 0x3) << 4) | ((alhpa & 0x3) << 2) | ((alhpa & 0x3) << 0);
            }
            else if (sfmt == 11) // uyva1010102
            {
                uint32_t sraw = ((uint32_t*)p16_cur_line)[pix_off + x];
                ch[2] = (sraw >> 10) & 0x3ff;
                ch[1] = (sraw >> 0) & 0x3ff;
                ch[0] = (sraw >> 20) & 0x3ff;
                alhpa = sraw >> 30;
                ch[3] = ((alhpa & 0x3) << 6) | ((alhpa & 0x3) << 4) | ((alhpa & 0x3) << 2) | ((alhpa & 0x3) << 0);
            }
            else if (sfmt == 13) // y210
            {
                uint32_t sraw0 = ((uint32_t*)p16_cur_line)[pix_off + x];
                uint32_t sraw1 = ((uint32_t*)p16_cur_line)[pix_off + x + 1];
                ch[2] = (((sraw0 >> 0) >> 6) & 0x3ff);
                ch1[2] = (((sraw1 >> 0) >> 6) & 0x3ff);
                ch[1] = ch1[1] = (((sraw0 >> 16) >> 6) & 0x3ff);
                ch[0] = ch1[0] = (((sraw1 >> 16) >> 6) & 0x3ff);
                ch[3] = ch1[3] = alhpa;
                set_color_to_bus(p_dst + y * w * 4 + x * 4, ch, nullptr, nullptr, is_ycbcr);
                dump_tag.spl_unpack_dat = make_bus_data_for_dump(ch);
                ck_dump(&dump_tag);
                set_color_to_bus(p_dst + y * w * 4 + (x + 1) * 4, ch1, nullptr, nullptr, is_ycbcr);
                dump_tag.spl_unpack_dat = make_bus_data_for_dump(ch1);
                ck_dump(&dump_tag);
                x += 2;
                continue;
            }
            else
            {
                assert(0);
            }
            set_color_to_bus(p_dst + y * w * 4 + x * 4, ch, nullptr, nullptr, is_ycbcr);
            dump_tag.spl_unpack_dat = make_bus_data_for_dump(ch);
            ck_dump(&dump_tag);
            x++;
        }

        p16_cur_line += pitch_word;
    }
    ckp_c::inst()->close(SPL_WIN_VLD);
}

void cursor_c(unsigned short* p_cur, cur_para para, 
    unsigned short* p_cursor_out, int* w_out, int* h_out, 
    std::string cv_ckp_fn)
{
    uint32_t x_off = para.x_off;
    uint32_t y_off = para.y_off;
    uint32_t x_start = para.x_start - 1;
    uint32_t y_start = para.y_start - 1;
    ckp_c::inst()->initial(true, cv_ckp_fn, CUR_VLD);
    cur_vld_tag dump_tag{};

    uint32_t cur_w{};
    uint32_t cur_h{};
    uint32_t* cur_out_p = (uint32_t*)p_cursor_out;
    uint32_t* cur_in_p = (uint32_t*)p_cur;

    if (para.cur_size == 0)
    {
        cur_w = cur_h = 64;
    }
    else if (para.cur_size == 1)
    {
        cur_w = 64;
        cur_h = 128;
    }
    else if (para.cur_size == 2)
    {
        cur_w = 128;
        cur_h = 64;
    }
    else
    {
        cur_w = cur_h = 128;
    }

    uint32_t cur_valid_w = cur_w - x_off;
    uint32_t cur_valid_h = cur_h - y_off;

    // update cursor output width/height
    uint32_t x_off_on_panel = x_start;
    uint32_t y_off_on_panel = y_start;

    if (x_off_on_panel >= para.panel_width ||
        y_off_on_panel >= para.panel_height)
    {
        *w_out = *h_out = 0;
        ckp_c::inst()->close(SPL_WIN_VLD);
        return;
    }

    uint32_t win_width = (para.pu_en || para.cur_ref_iwin) ? para.iwin_width : para.panel_width;
    uint32_t win_height = (para.pu_en || para.cur_ref_iwin) ? para.iwin_height : para.panel_height;

    if (x_off_on_panel + cur_valid_w > win_width)
    {
        *w_out = win_width - x_off_on_panel;
    }
    else
    {
        *w_out = cur_valid_w;
    }
    if (y_off_on_panel + cur_valid_h > win_height)
    {
        *h_out = win_height - y_off_on_panel;
    }
    else
    {
        *h_out = cur_valid_h;
    }

    uint32_t out_dat{};

    for (uint32_t y = 0; y < cur_h; y++)
    {
        if (y < y_off || y >= y_off + *h_out) continue;
        for (uint32_t x = 0; x < cur_w; x++)
        {
            if (x < x_off || x >= x_off + *w_out) continue;
            if (para.cur_type == 0) // mono cursor
            {
                uint32_t d = cur_in_p[(y * cur_w + x) / 16];
                uint32_t off = x % 16;
                off = off <= 7 ? 7 - off : 23 - off;
                uint32_t d_a = ((d & 0xffff) >> off) & 0x1;
                uint32_t d_x = (((d >> 16) & 0xffff) >> off) & 0x1;
                
                out_dat = (d_a << 25) | (d_x << 24);
                if (d_x == 0 && d_a == 0)
                {
                    out_dat |= para.cur_mono_bg;
                }
                else if (d_x == 1 && d_a == 0)
                {
                    out_dat |= para.cur_mono_fg;
                }
                else
                {
                    out_dat = (out_dat >> 24) << 24;
                }
            }
            else
            {
                out_dat = cur_in_p[y * cur_w + x];
            } 
            cur_out_p[(y - y_off) * (*w_out) + (x - x_off)] = out_dat;

            dump_tag.cur_dat = out_dat;
            ck_dump(&dump_tag);
        }
    }

    ckp_c::inst()->close(SPL_WIN_VLD);
}


void lut_c(unsigned short* p_src, unsigned short* p_dst, 
    unsigned int wid, unsigned int het, lut_para para, uint32_t* table, 
    std::string li_ckp_fn, std::string lc_ckp_fn)
{
    ckp_c::inst()->initial(true, li_ckp_fn, LUT_IF);
    ckp_c::inst()->initial(true, lc_ckp_fn, LUT_CONFIG);
    lut_if_tag lut_if_dump{};
    lut_config_tag lut_cfg_dump{};
    lut_cfg_dump.reg_lut_lut_en = para.lut_en;
    lut_cfg_dump.reg_lut_intp_on = para.lut_intp_on;
    lut_cfg_dump.reg_lut_bitwidth = para.lut_bitwidth;
    ck_dump(&lut_cfg_dump);
    bool is_ycbcr = ((bus_1010108*)p_src)->is_ycbcr;
    for (uint32_t y = 0; y < het; y++)
    {
        for (uint32_t x = 0; x < wid; x++)
        {
            uint16_t pdd[4] = { 0 };
            uint32_t pix_in_dump{};
            uint32_t pix_out_dump{};
            for (uint32_t ch = 0; ch < 3; ch++)
            {
                uint16_t sd = get_ch(p_src, x, y, wid, het, ch);
                pix_in_dump |= (sd << (ch * 10));
                if (para.lut_en)
                {
                    uint32_t lut_aa = ((sd >> 2) & 0xff);
                    uint32_t lut_ab = lut_aa == 0xff ? lut_aa : lut_aa + 1;
                    uint32_t fct = ((sd & 0x3) << 1);
                    uint32_t fct_r = 0x8 - fct;
                    uint16_t lut_v_aa = ((table[lut_aa] >> (ch * 10)) & 0x3ff);
                    uint16_t lut_v_ab = ((table[lut_ab] >> (ch * 10)) & 0x3ff);
                    uint16_t lout = (lut_v_aa *fct_r + lut_v_ab * fct) >> 3;
                    if (para.lut_intp_on)
                    {
                        pdd[ch] = lout & 0x3ff;
                        pix_out_dump |= (lout << (ch * 10));
                    }
                    else
                    {
                        pdd[ch] = lut_v_aa & 0x3ff;
                        pix_out_dump |= (lut_v_aa << (ch * 10));
                    }
                }
                else
                {
                    pdd[ch] = sd & 0x3ff;
                    pix_out_dump |= (sd << (ch * 10));
                }
            }
            pdd[3] = 0;
            lut_if_dump.pus_lut_pxl = pix_in_dump;
            lut_if_dump.lut_csc_pxl = pix_out_dump;
            ck_dump(&lut_if_dump);
            set_color_to_bus(p_dst + (x + y * wid) * 4, pdd);
            ((bus_1010108*)(p_dst + (x + y * wid) * 4))->is_ycbcr = is_ycbcr;
        }
    }
    ckp_c::inst()->close(LUT_IF);
    ckp_c::inst()->close(LUT_CONFIG);
}

const uint16_t dither_pattern[16] =
{
    0xFFFE, 0xFE00, 0xFFF8, 0xF800,
    0xE000, 0xFFE0, 0x8000, 0xFF80,
    0xFFF0, 0xF000, 0xFFFC, 0xFC00,
    0x0000, 0xFF00, 0xC000, 0xFFC0
};

void dither_c(unsigned short* p_src, unsigned short* p_dst, 
    unsigned int wid, unsigned int het, dither_para para, 
    std::string did_ckp_fn, std::string dc_ckp_fn)
{
    ckp_c::inst()->initial(true, did_ckp_fn, DIHTER_IN_DE);
    ckp_c::inst()->initial(true, dc_ckp_fn, DITHER_CONFIG);
    dihter_in_de_tag did_dump{};
    dither_config_tag dc_dump{};
    dc_dump.reg_dither_en = true;
    dc_dump.reg_dither_base = para.base;
    dc_dump.reg_dither_bitsel = para.bitsel;
    dc_dump.reg_dither_dist_en = para.dist_en;
    ck_dump(&dc_dump);
    uint16_t pre_dither{}, add_dect{}, avail_bits2dither{}, val2add_fm_pre_dither{}, dis_dither{};
    uint16_t reg16by16_out_sel{}, pat{}, seld_reg16by16_out_bit{}, pat_idx{};
    uint16_t paty{}, patx{};
    uint16_t cd{}, dither_out[4] = { 0 };

    for (uint32_t y = 0; y < het; y++)
    {
        for (uint32_t x = 0; x < wid; x++)
        {
            for (uint32_t ch = 0; ch < 3; ch++)
            {
                cd = get_ch(p_src, x, y, wid, het, ch);
                switch (para.base)
                {
                case 1:
                case 3:
                    pre_dither = cd & ~0x1f;
                    add_dect = ((cd >> 5) << 4) | 0xf;
                    avail_bits2dither = (cd >> 1) & 0xf;
                    val2add_fm_pre_dither = 0x10;
                    dis_dither = 0;
                    break;
                case 4:
                    pre_dither = cd & ~0xf;
                    add_dect = ((cd >> 4) << 3) | 0x7;
                    avail_bits2dither = cd & 0xf;
                    val2add_fm_pre_dither = 0x8;
                    dis_dither = 0;
                    break;
                case 5:
                    pre_dither = cd & ~0x7;
                    add_dect = ((cd >> 3) << 2) | 0x3;
                    avail_bits2dither = (cd & 0x7) << 1;
                    val2add_fm_pre_dither = 0x4;
                    dis_dither = 0;
                    break;
                case 6:
                    pre_dither = cd & ~0x3;
                    add_dect = ((cd >> 2) << 1) | 0x1;
                    avail_bits2dither = (cd & 0x3) << 2;
                    val2add_fm_pre_dither = 0x2;
                    //dis_dither = 0; // todo: no need to set this?
                    break;
                case 7:
                    pre_dither = cd & ~0x1;
                    add_dect = (cd >> 1);
                    avail_bits2dither = (cd & 0x1) << 3;
                    val2add_fm_pre_dither = 0x1;
                    //dis_dither = 0;// todo: no need to set this?
                    break;
                case 0:
                    pre_dither = cd;
                    add_dect = 0x1ff;
                    avail_bits2dither = 0;
                    val2add_fm_pre_dither = 0;
                    //dis_dither = 0;
                    break;
                default:
                    break;
                }

                if (para.bitsel == 0)
                {
                    reg16by16_out_sel = avail_bits2dither & ~0x3;
                }
                else
                {
                    reg16by16_out_sel = avail_bits2dither;
                }
                patx = x & 3;
                paty = y & 3;
                if (para.dist_en)
                {
                    if (ch == 0) // b channel
                    {
                        paty = (paty - 1) & 0x3;
                    }
                    if (ch == 2)
                    {
                        patx = (patx - 1) & 0x3;
                    }
                }
                pat_idx = (paty << 2) | patx;
                pat = dither_pattern[pat_idx];
                seld_reg16by16_out_bit = (pat >> reg16by16_out_sel) & 1;
                if (add_dect != 0x1ff && para.dither_en && para.base != 0 && seld_reg16by16_out_bit == 1)
                {
                    dither_out[ch] = ((pre_dither >> 1) + val2add_fm_pre_dither) << 1;
                }
                else
                {
                    dither_out[ch] = pre_dither;
                }
                dither_out[ch] = (dither_out[ch] >> 10) == 1 ? 0x3ff : (dither_out[ch] & 0x3ff);

                if (ch == 2)
                {
                    did_dump.r_pxl_in = cd;
                    did_dump.dith_row_r = paty;
                    did_dump.dith_col_r = patx;
                    did_dump.r_pre_dither = pre_dither;
                    did_dump.r_add_detc = add_dect;
                    did_dump.r_avail_bits_2dither = avail_bits2dither;
                    did_dump.r_value_2add_fm_pre_dither = val2add_fm_pre_dither;
                    did_dump.r_reg16by16_out = pat;
                    did_dump.r_reg16by16_out_sel = reg16by16_out_sel;
                    did_dump.r_seld_reg16by16_out_bit = seld_reg16by16_out_bit;
                    did_dump.r_dith_out = dither_out[ch];
                }
                else if (ch == 1)
                {
                    did_dump.g_pxl_in = cd;
                    did_dump.dith_row_g = paty;
                    did_dump.dith_col_g = patx;
                    did_dump.g_pre_dither = pre_dither;
                    did_dump.g_add_detc = add_dect;
                    did_dump.g_avail_bits_2dither = avail_bits2dither;
                    did_dump.g_value_2add_fm_pre_dither = val2add_fm_pre_dither;
                    did_dump.g_reg16by16_out = pat;
                    did_dump.g_reg16by16_out_sel = reg16by16_out_sel;
                    did_dump.g_seld_reg16by16_out_bit = seld_reg16by16_out_bit;
                    did_dump.g_dith_out = dither_out[ch];
                }
                else
                {
                    did_dump.b_pxl_in = cd;
                    did_dump.dith_row_b = paty;
                    did_dump.dith_col_b = patx;
                    did_dump.b_pre_dither = pre_dither;
                    did_dump.b_add_detc = add_dect;
                    did_dump.b_avail_bits_2dither = avail_bits2dither;
                    did_dump.b_value_2add_fm_pre_dither = val2add_fm_pre_dither;
                    did_dump.b_reg16by16_out = pat;
                    did_dump.b_reg16by16_out_sel = reg16by16_out_sel;
                    did_dump.b_seld_reg16by16_out_bit = seld_reg16by16_out_bit;
                    did_dump.b_dith_out = dither_out[ch];
                }
            }
            ck_dump(&did_dump);
            dither_out[3] = 0;
            set_color_to_bus(p_dst + (x + y * wid) * 4, dither_out);
        }
    }
    ckp_c::inst()->close(DIHTER_IN_DE);
    ckp_c::inst()->close(DITHER_CONFIG);
}

void output_c(unsigned short* p_src, unsigned short* p_dst,
    unsigned int w, unsigned int h, unsigned int dfmt, out_para para, unsigned int hw_info)
{
    for (uint32_t y = 0; y < h; y++)
    {
        for (uint32_t x = 0; x < w; x++)
        {

        }
    }
}

