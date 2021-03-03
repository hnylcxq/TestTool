#ifndef _CMODEL_WRAPPER_H_
#define _CMODEL_WRAPPER_H_


#ifdef __cplusplus
extern "C"{
#endif


struct input_para_t 
{
	unsigned int stride;
	unsigned int spl_abgr;
	unsigned int spl_crycb;
	unsigned int spl_cbycry;
	unsigned int pix_off;

	unsigned short * src;   //need get first 256bit algin addr
	unsigned short * dst;

	unsigned int width;
	unsigned int height;

	unsigned int spl_fmt;
};


struct dither_para_t 
{
	unsigned int width;
	unsigned int height;

	unsigned short *src;
	unsigned short *dst;

	
    unsigned int dither_en;
    unsigned int base;
    unsigned int bitsel;
    unsigned int dist_en;
};

struct lut_para_t
{
	unsigned int 	width;
	unsigned int 	height;

	unsigned short *src;
	unsigned short *dst;

	unsigned int lut_en;
    unsigned int lut_intp_on;
    unsigned int lut_bitwidth;
	unsigned int lut_data[256];
};


struct csc_cursor_para_t 
{
	unsigned int width;
	unsigned int height;

	unsigned int fmt;

	unsigned short *src;
	unsigned short *dst;
};

struct cursor_para_t 
{
	unsigned short* src;
	unsigned short* dst;

	unsigned int panel_width;   //should be panel size(iwin size)
	unsigned int panel_height;

	unsigned int x_start;
	unsigned int y_start;

	unsigned int x_off;
	unsigned int y_off;
	unsigned int cur_size;
	unsigned int cur_type;
	unsigned int cur_mono_bg : 24;
	unsigned int cur_mono_fg : 24;

};

struct csc_plane_para_t
{
	unsigned int width;
	unsigned int height;

	unsigned int infmt;
	unsigned int outfmt;
	unsigned int bright;

	unsigned int prog;

	unsigned int coef1;
	unsigned int coef2;
	unsigned int coef3;
	unsigned int coef4;
	unsigned int coef5;
	unsigned int coef6;
	unsigned int coef7;
	unsigned int coef8;
	unsigned int coef9;

	unsigned short *src;
	unsigned short *dst;
	
};

struct signature_para_t 
{
	unsigned int width;
	unsigned int height;

	unsigned short *src;
};


struct scl_stream_para_t 
{
	unsigned int src_w;
	unsigned int src_h;
	unsigned int dst_w;
	unsigned int dst_h;

    unsigned int is_cos_h;
    unsigned int is_cos_v;
    unsigned int is_alpha_ups;
    unsigned int is_v_duplicate;
    unsigned int keyl;
    unsigned int keyh;
    unsigned int key_mode;
    unsigned int h_acc;
    unsigned int v_acc;

	unsigned short 	*src;
	unsigned short 	*dst;

};



struct scl_panel_para_t 
{
	unsigned int src_w;
	unsigned int src_h;
	unsigned int dst_w;
	unsigned int dst_h;

	unsigned int start_x;  //start from 1
	unsigned int start_y;

	unsigned int panel_width;
	unsigned int panel_height;

	unsigned int en;
    unsigned int h_en, v_en;

    unsigned int h_acc;
    unsigned int v_acc;

    unsigned int is_cos;
    unsigned int is_hw_ratio;
    unsigned int ratio_plus;

	unsigned int bg_color;

	unsigned short 	*src;
	unsigned short 	*dst;

};

struct overlay_para_t
{
	unsigned int ovl0_key_mode;
	unsigned int ovl0_pla_fct;
	unsigned int ovl0_plb_fct;
	unsigned int ovl0_bld_mode;
	unsigned int ovl0_is_inv_alpha;
	unsigned int ovl0_plane_alpha_val;
	unsigned int ovl0_alpha_key_sel;
	unsigned int ovl0_color_key_sel;
	unsigned int ovl0_is_alpha_rang;
	unsigned int ovl0_is_mdi_sec;
	unsigned int ovl0_is_ref_int;
	unsigned int ovl0_is_ycbcr;
	
	unsigned int ovl1_key_mode;
	unsigned int ovl1_pla_fct;
	unsigned int ovl1_plb_fct;
	unsigned int ovl1_bld_mode;
	unsigned int ovl1_is_inv_alpha;
	unsigned int ovl1_plane_alpha_val;
	unsigned int ovl1_alpha_key_sel;
	unsigned int ovl1_color_key_sel;
	unsigned int ovl1_is_alpha_rang;
	unsigned int ovl1_is_mdi_sec;
	unsigned int ovl1_is_ref_int;
	unsigned int ovl1_is_ycbcr;

	unsigned int win_0_start_x;  //reg value ,start from 1
	unsigned int win_0_start_y;
	unsigned int win_0_width;
	unsigned int win_0_height;

	unsigned int win_1_start_x;
	unsigned int win_1_start_y;
	unsigned int win_1_width;
	unsigned int win_1_height;

	unsigned int win_cur_start_x;
	unsigned int win_cur_start_y;
	unsigned int win_cur_width;
	unsigned int win_cur_height;

	unsigned int bg_color;
	unsigned int bg_ycbcr;

	unsigned short *win0_src;
	unsigned short *win1_src;
	unsigned short *cur_src;

	unsigned int cur_type;
	unsigned int is_curs_ycbcr;
	unsigned int is_curs_ref_int;


	unsigned int pu_en;

	unsigned int iwin_start_x;
	unsigned int iwin_start_y;
	unsigned int iwin_width;
	unsigned int iwin_height;

	unsigned int dst_width;
	unsigned int dst_height;

	unsigned short *dst;
	
};

void scl_stream_wrapper(struct scl_stream_para_t *para);
void scl_panel_wrapper(struct scl_panel_para_t *para);
void overlay_wrapper(struct overlay_para_t *para);
unsigned long long  signature_wrapper(struct signature_para_t  *para);
void csc_plane_wrapper(struct csc_plane_para_t* para);
void csc_cursor_wrapper(struct csc_cursor_para_t *para);
void cursor_wrapper(struct cursor_para_t *para, int *out_w, int *out_h);
void lut_wrapper(struct lut_para_t *para);
void dither_wrapper(struct dither_para_t *dither_para);
void input_wrapper(struct input_para_t *input_para);

#ifdef __cplusplus
}
#endif

#endif
