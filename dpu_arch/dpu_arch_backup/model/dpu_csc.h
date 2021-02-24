#ifndef _DPU_CSC_H
#define _DPU_CSC_H

#include <string>
#include <unordered_map>

/**
 * @class csc_mat_dpu
 * @brief Class for storing CSC matrix according to the mode parameters.
 */
class csc_mat_dpu
{
public:
    /**
     * @brief Constructor.
     *
     * @param is_src_rgb         Whether the source is R'G'B' or Y'CbCr surface.
     * @param is_dst_rgb         Whether the dest is R'G'B' or Y'CbCr surface.
     * @param is_src_range_full  Whether the source has full or limited range.
     * @param is_dst_range_full  Whether the dest has full or limited range.
     * @param str_gamut          Gamut name in a std::string.
     */
    csc_mat_dpu(bool is_src_rgb, bool is_dst_rgb,
                bool is_src_range_full, bool is_dst_range_full,
                std::string str_gamut);
    /**
     * @brief Overloaded constructor.
     *
     * Format indices:
     * - 0: full RGB.
     * - 1: limited RGB.
     * - 2: full YCbCr (BT.601).
     * - 3: full YCbCr (BT.709).
     * - 4: limited YCbCr (BT.601).
     * - 5: limited YCbCr (BT.709).
     * - 6: limited YCbCr (BT.2020).
     * - 7: full YCbCr (BT.2020).
     *
     * @param infmt   Input data format.
     * @param outfmt  Output data format.
     */
    csc_mat_dpu(unsigned infmt, unsigned outfmt);
    /** 
     * @brief Overloaded function call operator to get matrix data.
     *
     * @param r  Row index of the matrix.
     * @param c  Column index of the matrix.
     */
    double operator()(int r, int c) const { return m_csc_mat[r][c]; }
    /** 
     * @brief Get DPU's CSC source format index.
     * 0: full RGB.
     * 1: limited RGB.
     * 2: full YCbCr (BT.601).
     * 3: full YCbCr (BT.709).
     * 4: limited YCbCr (BT.601).
     * 5: limited YCbCr (BT.709).
     * 6: limited YCbCr (BT.2020).
     * 7: full YCbCr (BT.2020).
     */
    unsigned infmt() const { return m_infmt; }
    /// Get DPU's CSC destination format index.
    unsigned outfmt() const { return m_outfmt; }
    /// Whether the source is RGB or not.
    bool is_src_rgb() const { return m_is_src_rgb; }
    /// Whether the destination is RGB or not.
    bool is_dst_rgb() const { return m_is_dst_rgb; }
    /// Whether the source is full range signal or not.
    bool is_src_range_full() const { return m_is_src_range_full; }
    /// Whether the source is full range signal or not.
    bool is_dst_range_full() const { return m_is_dst_range_full; }
private:
    /// CSC operation mode (12*n+1 distinct cases for n gamuts).
    enum class Mode {
        // BT.601-525/BT.601-625 (4+4 = 8 cases)
        YCBCR2RGB_F2L_BT601,
        YCBCR2RGB_F2F_BT601,
        YCBCR2RGB_L2L_BT601,
        YCBCR2RGB_L2F_BT601,
        RGB2YCBCR_F2L_BT601,
        RGB2YCBCR_F2F_BT601,
        RGB2YCBCR_L2L_BT601,
        RGB2YCBCR_L2F_BT601,
        // BT.709 (8 cases)
        YCBCR2RGB_F2L_BT709,
        YCBCR2RGB_F2F_BT709,
        YCBCR2RGB_L2L_BT709,
        YCBCR2RGB_L2F_BT709,
        RGB2YCBCR_F2L_BT709,
        RGB2YCBCR_F2F_BT709,
        RGB2YCBCR_L2L_BT709,
        RGB2YCBCR_L2F_BT709,
        // BT.2020 (8 cases)
        YCBCR2RGB_F2L_BT2020,
        YCBCR2RGB_F2F_BT2020,
        YCBCR2RGB_L2L_BT2020,
        YCBCR2RGB_L2F_BT2020,
        RGB2YCBCR_F2L_BT2020,
        RGB2YCBCR_F2F_BT2020,
        RGB2YCBCR_L2L_BT2020,
        RGB2YCBCR_L2F_BT2020,
        // Range scaling matrices (4 cases for all gamuts)
        YCBCR2YCBCR_F2L,
        YCBCR2YCBCR_L2F,
        RGB2RGB_F2L,
        RGB2RGB_L2F,
        // no operations (4 redundant cases for each gamut)
        BYPASS,
    };
    /// CSC operation mode table for converting std::string to the mode enum.
    static const std::unordered_map<std::string, Mode> MODE_TABLE;
    /// Whether the source surface is R'G'B' or Y'CbCr.
    bool m_is_src_rgb{};
    /// Whether the destination surface is R'G'B' or Y'CbCr.
    bool m_is_dst_rgb{};
    /// Whether the source range is full or limited.
    bool m_is_src_range_full{};
    /// Whether the destination range is full or limited.
    bool m_is_dst_range_full{};
    /// Gamut of the source surface.
    std::string m_str_gamut{};
    /// Input format index.
    unsigned m_infmt{};
    /// Output format index.
    unsigned m_outfmt{};
    /// CSC operation mode string.
    std::string m_str_mode{};
    /// 3x3 CSC matrix.
    double m_csc_mat[3][3]{};
    /// Set CSC module's operational mode.
    void set_csc_mode();
    /// Set 3x4 CSC matrix according to the CSC parameters.
    void set_csc_matrix();
    /// Generate CSC mode string.
    std::string gen_mode_str() const;
    /** 
     * Convert CSC mode string to the mode enum.
     *
     * @param mode_str  CSC mode string.
     *
     * @return enum value representing the CSC mode.
     */
    Mode mode_str_to_enum(const std::string& mode_str) const;
    /// Get DPU's CSC format index.
    unsigned fmt(bool rgb, bool range_full, const std::string& gamut) const;
    /// Get gamut string via format index.
    std::string get_gamut(unsigned fmt_idx) const;
};

#endif // _DPU_CSC_H
