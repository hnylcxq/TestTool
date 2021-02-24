#ifndef _DPU_FMT_H
#define _DPU_FMT_H

#include "HGF.h"
#include "str.h"
#include "itb_assert.h"
using namespace ck;
//0010: rgb565, 16bpp
//0011: ycbcr422, 16bpp, 8bpc
//1000: argb8888, 32bpp, 8bpc
//1001: aycbcr444, 32bpp, 8bpc
//1010: argb2101010, 32bpp 10bpc
//1011: ycbcr2101010, 32bpp, 10bpc
//1101: ycbcr422, 32bpp, 10/12/16bpc
//Spl_abgr 0:argb, 1: abgr 
//Spl_cbycry 422 data format, 0: ycbycr, 1: cbycry 
//Spl_crycb 444 data format, 0: ycbcr, 1: crycb 
enum dpu_fmt_e
{
    DPU_RGB565 = 2,
    DPU_YUYV = 3,
    DPU_ARGB8888 = 8,
    DPU_AYUV8888 = 9,
    DPU_ARGB2101010 = 10,
    DPU_Y410 = 11,
    DPU_Y210 = 13,
    DPU_NV12 = 16, //only for output 
    DPU_P010 = 17,
    DPU_BUS_AYUV = 32, //bus data format //TODO add definition later
    DPU_BUS_ARGB = 33,
    DPU_BUS_CURS = 34

};
class dpu_fmt_c
{
public:
    dpu_fmt_c() {};
    ~dpu_fmt_c() {};

    void set(const std::string& _fmt_str)
    {
        std::string fmt_str;
        bool is_tile = false;
        if (str::has(_fmt_str, "_"))
        {
            str::vs_t s = str::split(_fmt_str, '_');
            if (str::lower(s.at(s.size() - 1)) == "t")
            {
                is_tile = true;
                s.pop_back();
            }
            fmt_str = str::join(s, "_");
        }
        else
        {
            fmt_str = str::lower(_fmt_str);
        }

        if (fmt_str == "rgb565")
        {
            m_fmt = DPU_RGB565;
        }
        else if (fmt_str == "yuyv")
        {
            m_fmt = DPU_YUYV;
        }
        else if (fmt_str == "argb8888")
        {
            m_fmt = DPU_ARGB8888;
        }
        else if (fmt_str == "ayuv8888")
        {
            m_fmt = DPU_AYUV8888;
        }
        else if (fmt_str == "argb2101010")
        {
            m_fmt = DPU_ARGB2101010;
        }
        else if (fmt_str == "y410")
        {
            m_fmt = DPU_Y410;
        }
        else if (fmt_str == "y210")
        {
            m_fmt = DPU_Y210;
        }
        else if (fmt_str == "nv12")
        {
            m_fmt = DPU_NV12;
        }
        else if (fmt_str == "p010")
        {
            m_fmt = DPU_P010;
        }
        else if (fmt_str == "bus_argb")
        {
            m_fmt = DPU_BUS_ARGB;
        }
        else if (fmt_str == "bus_curs")
        {
            m_fmt = DPU_BUS_CURS;
        }
        else if (fmt_str == "bus_ayuv")
        {
            m_fmt = DPU_BUS_AYUV;
        }
        else
        {
            ASSERT_ITB(0, "UNKNOWN DPU FORMAT!");
        };

    }

    HW_Graph_Fmt toHGF(bool is_dpu_swz)
    {
        switch (m_fmt)
        {
        case DPU_RGB565:
            return HGF_R5G6B5_UNORM;
            break;
        case DPU_YUYV:
            if (is_dpu_swz)
                return HGF_UYVY_VIDEO;
            else
                return HGF_YUYV_VIDEO;
            break;
        case DPU_ARGB8888:
            if (is_dpu_swz)
                return HGF_R8G8B8A8_UNORM;
            else
                return HGF_B8G8R8A8_UNORM;
            break;
        case DPU_AYUV8888:
            ASSERT_ITB(is_dpu_swz == false, "Not support channel swizzle!");
            return HGF_VUYA_VIDEO;
            break;
        case DPU_ARGB2101010:
            if (is_dpu_swz)
                return HGF_R10G10B10A2_UNORM;
            else
                return HGF_B10G10R10A2_UNORM;
            break;
        case DPU_Y410:
            ASSERT_ITB(is_dpu_swz == false, "Not support channel swizzle!");
            return HGF_U10Y10V10A2;
            break;
        case DPU_Y210:
            return HGF_Y210_VIDEO;
            break;
        case DPU_NV12:
            return HGF_NV12_VIDEO_PLANAR;
            break;
        case DPU_P010:
            return HGF_P010_VIDEO_PLANAR;
            break;
        case DPU_BUS_ARGB:
        case DPU_BUS_CURS:
            return HGF_B8G8R8A8_UNORM;
            break;
        case DPU_BUS_AYUV:
            return HGF_VUYA_VIDEO;
            break;
        default:
            ASSERT_ITB(0, "UNKNOWN CE FORMAT!");
            return HGF_UNKNOWN;
            break;
        }
    }


    dpu_fmt_c& operator=(const dpu_fmt_e& rhs)
    {
        this->m_fmt = rhs;
        return *this;
    }
    operator int() const
    {
        return (int)m_fmt;
    }

    uint32_t get_bpp() const
    {
        switch (m_fmt)
        {
        case DPU_RGB565:
        case DPU_YUYV:
        case DPU_P010:
            return 2;
            break;
        case DPU_BUS_ARGB:
        case DPU_BUS_AYUV:
        case DPU_BUS_CURS:
        case DPU_ARGB8888:
        case DPU_AYUV8888:
        case DPU_ARGB2101010:
        case DPU_Y410:
        case DPU_Y210:
            return 4;
            break;
        case DPU_NV12:
            return 1;
            break;
        default:
            ASSERT_ITB(0, "Unsuppoted format!");

            break;
        }
        return 0;
    }
    void get_ch_bits(uint32_t& R, uint32_t& G, uint32_t& B, uint32_t& A)
    {
        switch (m_fmt)
        {
        case DPU_RGB565:
            R = B = 5;
            G = 6;
            break;
        case DPU_YUYV:
            R = G = 8;
            break;
        case DPU_P010:
            R = 10;
            break;
        case DPU_ARGB8888:
        case DPU_AYUV8888:
        case DPU_BUS_ARGB:  //only for image dump
        case DPU_BUS_AYUV://only for image dump
        case DPU_BUS_CURS:
            R = G = B = A = 8;
            break;
        case DPU_ARGB2101010:
        case DPU_Y410:
            R = G = B = 10;
            A = 2;
            break;
        case DPU_Y210:
            R = G = 10;
            break;
        case DPU_NV12:
            R = 8;
            break;
        default:
            break;
        }
        return;
    }


    dpu_fmt_e m_fmt{};
};



#endif // !_DPU_FMT_H
