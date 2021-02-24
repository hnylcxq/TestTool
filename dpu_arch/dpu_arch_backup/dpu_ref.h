#ifndef _DPU_REF_H
#define _DPU_REF_H

void scl_stream_ref(int src_w, int src_h, int dst_w, int dst_h, bool is_cos_h, bool is_cos_v,
    bool is_alpha_ups, bool is_color_key, bool is_v_duplicate, unsigned int key_val, unsigned short* psrc, unsigned short* pdst);
#endif //_DPU_REF_H