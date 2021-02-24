#include "dpu_csc.h"
#ifdef WIN32
#include "itb_assert.h"
#else
#include <cassert>
#define ASSERT_ITB(A, B, ...) assert(A)
#endif

#include <algorithm> // std::copy()

// csc mode table
const std::unordered_map<
    std::string, csc_mat_dpu::Mode> csc_mat_dpu::MODE_TABLE = {
    // BT.601-525/BT.601-625 (4+4 = 8 cases)
    {"YCBCR2RGB_F2L_BT601"      , Mode::YCBCR2RGB_F2L_BT601      },
    {"YCBCR2RGB_F2F_BT601"      , Mode::YCBCR2RGB_F2F_BT601      },
    {"YCBCR2RGB_L2L_BT601"      , Mode::YCBCR2RGB_L2L_BT601      },
    {"YCBCR2RGB_L2F_BT601"      , Mode::YCBCR2RGB_L2F_BT601      },
    {"RGB2YCBCR_F2L_BT601"      , Mode::RGB2YCBCR_F2L_BT601      },
    {"RGB2YCBCR_F2F_BT601"      , Mode::RGB2YCBCR_F2F_BT601      },
    {"RGB2YCBCR_L2L_BT601"      , Mode::RGB2YCBCR_L2L_BT601      },
    {"RGB2YCBCR_L2F_BT601"      , Mode::RGB2YCBCR_L2F_BT601      },
    // BT.709 (8 cases)
    {"YCBCR2RGB_F2L_BT709"      , Mode::YCBCR2RGB_F2L_BT709      },
    {"YCBCR2RGB_F2F_BT709"      , Mode::YCBCR2RGB_F2F_BT709      },
    {"YCBCR2RGB_L2L_BT709"      , Mode::YCBCR2RGB_L2L_BT709      },
    {"YCBCR2RGB_L2F_BT709"      , Mode::YCBCR2RGB_L2F_BT709      },
    {"RGB2YCBCR_F2L_BT709"      , Mode::RGB2YCBCR_F2L_BT709      },
    {"RGB2YCBCR_F2F_BT709"      , Mode::RGB2YCBCR_F2F_BT709      },
    {"RGB2YCBCR_L2L_BT709"      , Mode::RGB2YCBCR_L2L_BT709      },
    {"RGB2YCBCR_L2F_BT709"      , Mode::RGB2YCBCR_L2F_BT709      },
    // BT.2020 (8 cases)
    {"YCBCR2RGB_F2L_BT2020"     , Mode::YCBCR2RGB_F2L_BT2020     },
    {"YCBCR2RGB_F2F_BT2020"     , Mode::YCBCR2RGB_F2F_BT2020     },
    {"YCBCR2RGB_L2L_BT2020"     , Mode::YCBCR2RGB_L2L_BT2020     },
    {"YCBCR2RGB_L2F_BT2020"     , Mode::YCBCR2RGB_L2F_BT2020     },
    {"RGB2YCBCR_F2L_BT2020"     , Mode::RGB2YCBCR_F2L_BT2020     },
    {"RGB2YCBCR_F2F_BT2020"     , Mode::RGB2YCBCR_F2F_BT2020     },
    {"RGB2YCBCR_L2L_BT2020"     , Mode::RGB2YCBCR_L2L_BT2020     },
    {"RGB2YCBCR_L2F_BT2020"     , Mode::RGB2YCBCR_L2F_BT2020     },
    // Range scaling matrices (4 cases for all gamuts)
    {"YCBCR2YCBCR_F2L"          , Mode::YCBCR2YCBCR_F2L          },
    {"YCBCR2YCBCR_L2F"          , Mode::YCBCR2YCBCR_L2F          },
    {"RGB2RGB_F2L"              , Mode::RGB2RGB_F2L              },
    {"RGB2RGB_L2F"              , Mode::RGB2RGB_L2F              },
    // no operations (4 redundant cases for each gamut)
    {"BYPASS"                   , Mode::BYPASS                   },
};


// class csc_mat_dpu

csc_mat_dpu::csc_mat_dpu(bool is_src_rgb, bool is_dst_rgb,
                         bool is_src_range_full, bool is_dst_range_full,
                         std::string str_gamut) :
    m_is_src_rgb(is_src_rgb), m_is_dst_rgb(is_dst_rgb),
    m_is_src_range_full(is_src_range_full),
    m_is_dst_range_full(is_dst_range_full),
    m_str_gamut(str_gamut),
    m_infmt(fmt(is_src_rgb, is_src_range_full, str_gamut)),
    m_outfmt(fmt(is_dst_rgb, is_dst_range_full, str_gamut))
{
    set_csc_matrix();
}

csc_mat_dpu::csc_mat_dpu(unsigned infmt, unsigned outfmt) :
    m_infmt(infmt), m_outfmt(outfmt)
{
    ASSERT_ITB(infmt <= 7 && outfmt <= 7, "[DPU CSC] Unknown data format!");
    m_is_src_rgb = (infmt == 0 || infmt == 1) ? true : false;
    m_is_dst_rgb = (outfmt == 0 || outfmt == 1) ? true : false;
    m_is_src_range_full = (infmt == 0 || infmt == 2 || \
                           infmt == 3 || infmt == 7) ? true : false;
    m_is_dst_range_full = (outfmt == 0 || outfmt == 2 || \
                           outfmt == 3 || outfmt == 7) ? true : false;
    // gamut: just arbitrarily choose a gamut for RGB->RGB conversion
    if (infmt <= 1 && outfmt <= 1) // RGB->RGB
    {
        m_str_gamut = "bt709";
    }
    else
    {
        std::string str_gamut_in = get_gamut(infmt);
        std::string str_gamut_out = get_gamut(outfmt);
        // str_gamut_in == str_gamut_out, or one of them is non-empty
        m_str_gamut = !str_gamut_in.empty() ? str_gamut_in : str_gamut_out;
    }
    set_csc_matrix();
}

void csc_mat_dpu::set_csc_matrix()
{
    // generate CSC mode string
    m_str_mode = gen_mode_str();
    // get CSC mode enum
    Mode e_mode = mode_str_to_enum(m_str_mode);
    // set CSC matrix
    switch(e_mode)
    {
        // BT.601-525/BT.601-625
    case Mode::YCBCR2RGB_F2L_BT601:
    {
        double mat[3][3] = {
            { 0.859375000,  0.000000000,  1.203125000}, 
            { 0.859375000, -0.294921875, -0.613281250}, 
            { 0.859375000,  1.521484375,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2RGB_F2F_BT601:
    {
        double mat[3][3] = {
            { 1.000000000,  0.000000000,  1.402343750}, 
            { 1.000000000, -0.343750000, -0.714843750}, 
            { 1.000000000,  1.771484375,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2RGB_L2L_BT601:
    {
        double mat[3][3] = {
            { 1.000000000,  0.000000000,  1.371093750}, 
            { 1.000000000, -0.335937500, -0.697265625}, 
            { 1.000000000,  1.732421875,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2RGB_L2F_BT601:
    {
        double mat[3][3] = {
            { 1.164062500,  0.000000000,  1.595703125}, 
            { 1.164062500, -0.392578125, -0.812500000}, 
            { 1.164062500,  2.017578125,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_F2L_BT601:
    {
        double mat[3][3] = {
            { 0.255859375,  0.503906250,  0.097656250}, 
            {-0.148437500, -0.291015625,  0.439453125}, 
            { 0.439453125, -0.367187500, -0.072265625}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_F2F_BT601:
    {
        double mat[3][3] = {
            { 0.298828125,  0.587890625,  0.113281250}, 
            {-0.167968750, -0.332031250,  0.500000000}, 
            { 0.500000000, -0.417968750, -0.082031250}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_L2L_BT601:
    {
        double mat[3][3] = {
            { 0.298828125,  0.587890625,  0.113281250}, 
            {-0.171875000, -0.337890625,  0.511718750}, 
            { 0.511718750, -0.427734375, -0.083984375}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_L2F_BT601:
    {
        double mat[3][3] = {
            { 0.347656250,  0.683593750,  0.132812500}, 
            {-0.197265625, -0.384765625,  0.582031250}, 
            { 0.582031250, -0.488281250, -0.093750000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    // BT.709
    case Mode::YCBCR2RGB_F2L_BT709:
    {
        double mat[3][3] = {
            { 0.859375000,  0.000000000,  1.351562500}, 
            { 0.859375000, -0.160156250, -0.402343750}, 
            { 0.859375000,  1.593750000,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2RGB_F2F_BT709:
    {
        double mat[3][3] = {
            { 1.000000000,  0.000000000,  1.574218750}, 
            { 1.000000000, -0.187500000, -0.468750000}, 
            { 1.000000000,  1.855468750,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2RGB_L2L_BT709:
    {
        double mat[3][3] = {
            { 1.000000000,  0.000000000,  1.539062500}, 
            { 1.000000000, -0.183593750, -0.457031250}, 
            { 1.000000000,  1.814453125,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2RGB_L2F_BT709:
    {
        double mat[3][3] = {
            { 1.164062500,  0.000000000,  1.792968750}, 
            { 1.164062500, -0.212890625, -0.533203125}, 
            { 1.164062500,  2.113281250,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_F2L_BT709:
    {
        double mat[3][3] = {
            { 0.183593750,  0.613281250,  0.062500000}, 
            {-0.101562500, -0.337890625,  0.439453125}, 
            { 0.439453125, -0.398437500, -0.041015625}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_F2F_BT709:
    {
        double mat[3][3] = {
            { 0.212890625,  0.714843750,  0.072265625}, 
            {-0.115234375, -0.384765625,  0.500000000}, 
            { 0.500000000, -0.455078125, -0.044921875}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_L2L_BT709:
    {
        double mat[3][3] = {
            { 0.212890625,  0.714843750,  0.072265625}, 
            {-0.117187500, -0.394531250,  0.511718750}, 
            { 0.511718750, -0.464843750, -0.046875000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_L2F_BT709:
    {
        double mat[3][3] = {
            { 0.248046875,  0.832031250,  0.083984375}, 
            {-0.132812500, -0.449218750,  0.582031250}, 
            { 0.582031250, -0.529296875, -0.052734375}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    // BT.2020
    case Mode::YCBCR2RGB_F2L_BT2020:
    {
        double mat[3][3] = {
            { 0.859375000,  0.000000000,  1.265625000}, 
            { 0.859375000, -0.140625000, -0.490234375}, 
            { 0.859375000,  1.615234375,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2RGB_F2F_BT2020:
    {
        double mat[3][3] = {
            { 1.000000000,  0.000000000,  1.474609375}, 
            { 1.000000000, -0.164062500, -0.572265625}, 
            { 1.000000000,  1.880859375,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2RGB_L2L_BT2020:
    {
        double mat[3][3] = {
            { 1.000000000,  0.000000000,  1.441406250}, 
            { 1.000000000, -0.160156250, -0.558593750}, 
            { 1.000000000,  1.839843750,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2RGB_L2F_BT2020:
    {
        double mat[3][3] = {
            { 1.164062500,  0.000000000,  1.677734375}, 
            { 1.164062500, -0.187500000, -0.650390625}, 
            { 1.164062500,  2.142578125,  0.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_F2L_BT2020:
    {
        double mat[3][3] = {
            { 0.226562500,  0.582031250,  0.050781250}, 
            {-0.123046875, -0.316406250,  0.439453125}, 
            { 0.439453125, -0.404296875, -0.035156250}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_F2F_BT2020:
    {
        double mat[3][3] = {
            { 0.263671875,  0.677734375,  0.058593750}, 
            {-0.138671875, -0.361328125,  0.500000000}, 
            { 0.500000000, -0.458984375, -0.041015625}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_L2L_BT2020:
    {
        double mat[3][3] = {
            { 0.263671875,  0.677734375,  0.058593750}, 
            {-0.142578125, -0.369140625,  0.511718750}, 
            { 0.511718750, -0.470703125, -0.041015625}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2YCBCR_L2F_BT2020:
    {
        double mat[3][3] = {
            { 0.306640625,  0.789062500,  0.068359375}, 
            {-0.162109375, -0.419921875,  0.582031250}, 
            { 0.582031250, -0.535156250, -0.046875000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    // range scaling cases
    case Mode::YCBCR2YCBCR_F2L:
    {
        double mat[3][3] = {
            { 0.859375000,  0.000000000,  0.000000000}, 
            { 0.000000000,  0.878906250,  0.000000000}, 
            { 0.000000000,  0.000000000,  0.878906250}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::YCBCR2YCBCR_L2F:
    {
        double mat[3][3] = {
            { 1.164062500,  0.000000000,  0.000000000}, 
            { 0.000000000,  1.138671875,  0.000000000}, 
            { 0.000000000,  0.000000000,  1.138671875}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2RGB_F2L:
    {
        double mat[3][3] = {
            { 0.859375000,  0.000000000,  0.000000000}, 
            { 0.000000000,  0.859375000,  0.000000000}, 
            { 0.000000000,  0.000000000,  0.859375000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
    case Mode::RGB2RGB_L2F:
    {
        double mat[3][3] = {
            { 1.164062500,  0.000000000,  0.000000000}, 
            { 0.000000000,  1.164062500,  0.000000000}, 
            { 0.000000000,  0.000000000,  1.164062500}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }    
    // no operations
    case Mode::BYPASS:
    {
        double mat[3][3] = {
            { 1.000000000,  0.000000000,  0.000000000}, 
            { 0.000000000,  1.000000000,  0.000000000}, 
            { 0.000000000,  0.000000000,  1.000000000}, 
        };
        std::copy(&mat[0][0], &mat[0][0]+3*3, &m_csc_mat[0][0]);
        break;
    }
} // switch end
}

std::string csc_mat_dpu::gen_mode_str() const
{
    // mode string
    std::string str_mode{};

    if (m_is_src_rgb == m_is_dst_rgb &&
        m_is_src_range_full == m_is_dst_range_full) // no operation
    {
        str_mode = "BYPASS";
    }
    else // meaningful modes
    {
        // check gamut
        ASSERT_ITB(m_str_gamut == "bt601" || m_str_gamut == "bt709" ||
                   m_str_gamut == "bt2020",
                   "[VPE CSC]: Only support BT.601/BT.709/BT.2020 gamut!");
        // src space
        std::string str_src_space = m_is_src_rgb ? "RGB" : "YCBCR";
        // dst space
        std::string str_dst_space = m_is_dst_rgb ? "RGB" : "YCBCR";
        // src range
        std::string str_src_range = m_is_src_range_full ? "F" : "L";
        // dst range
        std::string str_dst_range = m_is_dst_range_full ? "F" : "L";
        // gamut
        std::string str_gamut{};
        if (m_str_gamut == "bt601")
        {
            str_gamut = "BT601";
        }
        else if (m_str_gamut == "bt709")
        {
            str_gamut = "BT709";
        }
        else if (m_str_gamut == "bt2020")
        {
            str_gamut = "BT2020";
        }
        // generate mode string
        // no suffix for range scaling modes
        std::string str_gamut_suffix = (str_src_space == str_dst_space) ?
            "" : ("_" + str_gamut);
        str_mode = str_src_space + "2" + str_dst_space + "_" + \
            str_src_range + "2" + str_dst_range + \
            str_gamut_suffix;
    }
    return str_mode;
}

csc_mat_dpu::Mode csc_mat_dpu::mode_str_to_enum(const std::string& mode_str)
    const
{
    auto it = MODE_TABLE.find(mode_str);
    ASSERT_ITB(it != MODE_TABLE.end(), "Unknown CSC mode string!");
    return it->second;
}

unsigned csc_mat_dpu::fmt(bool rgb, bool range_full, const std::string& gamut)
    const
{
    unsigned idx{};
    if (rgb)
    {
        idx = range_full ? 0 : 1;
    }
    else
    {
        if (gamut == "bt601")
        {
            idx = range_full ? 2 : 4;
        }
        else if (gamut == "bt709")
        {
            idx = range_full ? 3 : 5;
        }
        else if (gamut == "bt2020")
        {
            idx = range_full ? 7 : 6;
        }
    }
    return idx;
}

std::string csc_mat_dpu::get_gamut(unsigned fmt_idx) const
{
    std::string str_gamut(""); // default empty gamut for RGB cases
    if (fmt_idx == 2 || fmt_idx == 4)
    {
        str_gamut = "bt601";
    }
    else if (fmt_idx == 3 || fmt_idx == 5)
    {
        str_gamut = "bt709";
    }
    else if (fmt_idx == 6 || fmt_idx == 7)
    {
        str_gamut = "bt2020";
    }
    return str_gamut;
}
