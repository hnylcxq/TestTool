#include <algorithm>
#include "dpu_ref.h"
#include "dpu_cmodel.h"
#define _USE_MATH_DEFINES
#include "math.h"

float get_weight(float off, float ratio, bool is_duplicate, bool is_cos)
{
    float weight = 1.0f;
    if (ratio > 1.0f)
    {
        if (is_duplicate)
        {
            weight = off > 0.5 ? 0 : 1.0f;
        }
        else
        {
            weight = is_cos ? float(cos(M_PI * off) / 2 + 0.5f) : 1.0f - off;
        }
    }

    return weight;
}


int ref_get_ch(uint16_t* pbase, int x, int y, int w, int h, int ch)
{
    if (x >= w)
        x = w - 1;
    if (y >= h)
        y = h - 1;
    return pbase[(x + y * w) * 4 + ch];
}
void scl_stream_ref(int src_w, int src_h, int dst_w, int dst_h, bool is_cos_h, bool is_cos_v,
    bool is_alpha_ups, bool is_color_key, bool is_v_duplicate, unsigned int key_val, unsigned short* psrc, unsigned short* pdst)
{

    float ratio_h = dst_w * 1.0f / src_w;
    float ratio_v = dst_h * 1.0f / src_h;
    float src_x = 0, src_y = 0, sdratio_h = 1 / ratio_h, sdratio_v = 1 / ratio_v;
    for (int y = 0; y < dst_h; y++)
    {
        int src_y_i = (int)src_y;
        float nxt_src_y = src_y + sdratio_v;
        src_x = 0;
        for (int x = 0; x < dst_w; x++)
        {
            float weight_x = 1.0f, weight_y = 1.0f;
            float sum[4] = { 0 };
            float nxt_src_x = src_x + sdratio_h;
            int src_x_i = (int)src_x;
            float off_h = src_x - src_x_i, off_v = src_y - src_y_i;
            unsigned short* pdst_pix = pdst + (y * dst_w + x) * 4;//TODO;
            weight_x = get_weight(off_h, ratio_h, false, is_cos_h);
            weight_y = get_weight(off_v, ratio_v, is_v_duplicate, is_cos_v);
            for (int ch = 0; ch < 4; ch++)
            {
                float sum_v[2] = { 0 };
                int src[4];
                src[0] = ref_get_ch(psrc, src_x_i, src_y_i, src_w, src_h, ch);
                src[1] = ref_get_ch(psrc, src_x_i, src_y_i + 1, src_w, src_h, ch);
                src[2] = ref_get_ch(psrc, src_x_i + 1, src_y_i, src_w, src_h, ch);
                src[3] = ref_get_ch(psrc, src_x_i + 1, src_y_i + 1, src_w, src_h, ch);
                sum_v[0] = weight_y * src[0] + (1 - weight_y) * src[1];
                sum_v[1] = weight_y * src[2] + (1 - weight_y) * src[3];
                sum[ch] = weight_x * sum_v[0] + (1 - weight_x) * sum_v[1];
                int max_val = ch == 3 ? 255 : 1023;
                pdst_pix[ch] = std::clamp(int32_t(sum[ch] + 0.5), 0, max_val);
                //if (x <= 2 && y <= 2)
                //{
                //    printf("(%d,%d)ch%d: srcx,y: %d,%d; weight x,y: %f,%f; sumv0,v1: %f,%f, sum: %f res:%0x\n,", x, y, ch, src_x_i, src_y_i, weight_x, weight_y, sum_v[0], sum_v[1], sum[ch], pdst_pix[ch]);
                //}

            }


            src_x = nxt_src_x;
        }
        src_y = nxt_src_y;
    }
}