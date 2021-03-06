#ifndef _TYPES_H_
#define _TYPES_H_

#include"config.h"
#include"list.h"
#include "dpu.h"

#define     STR(s)     #s
#define     ARRAY_SIZE(A)   (sizeof(A)/sizeof(A[0]))


#define 	TRUE  		1
#define 	FALSE 		0 

typedef		unsigned char       BOOL;

typedef     unsigned char       u8;
typedef     unsigned short      u16;
typedef     unsigned int        u32;
typedef     unsigned long long  u64;

typedef     char                i8;
typedef     short               i16;
typedef     int                 i32;
typedef     long long           i64;


typedef enum _MISC_OP_TYPE
{
    OP_READ = 0,
    OP_WRITE,
}MISC_OP_TYPE;


#define KEY_ESC                     (0x1B)

//#define KEY_ENTER                   (0xD)
#define KEY_SPACE                   (32)
#define KEY_UP                      (72)
#define KEY_DOWN                    (80)
#define KEY_LEFT                    (75)
#define KEY_RIGHT                   (77)
#define KEY_BACKSPACE               (0x08)



#ifdef __DPU_LINUX_KERNEL__
#define   KEY_ENTER   				0x0A
#define   KEY_UP_DOWN_PRE			27

#else
#define   KEY_ENTER 				0x0D
#define KEY_UP_DOWN_PRE         	(0)

#endif




typedef enum _TT_STATUS_
{
    TT_PASS = 0,
    TT_FAIL = 1,
    TT_INVALID_PARAM,
}TT_STATUS;


struct rect_t
{
    u32 pos_x;
    u32 pos_y;
    u32 width;
    u32 height;
};


struct options_table 
{
    u8  *options_name;
    u8  *options_help;

    u8  options_num;

    struct 
    { 
        u8    base;
        u32*  value;
        u32*  valid_flag;
    
    }para[3];
};

struct support_cmd
{
    u8 *cmd_name;
    TT_STATUS (*func)();
    struct options_table *table;
    u32    options_item_num;
    
    void*   cmd;
    u32  cmd_size;
};


//color value is RGB101010 data, consider the 10bit color test.

#define CHANNEL_BIT   10
#define R_CHANNEL(x)   ((x >>(CHANNEL_BIT * 2))&0x3ff)
#define G_CHANNEL(x)   ((x >>(CHANNEL_BIT))&0x3ff)
#define B_CHANNEL(x)   (x & 0x3ff)

#define WHITE_COLOR   (0x3fffffff)
#define BLACK_COLOR   (0x00000000)
#define RED_COLOR     (0x3ff00000)
#define BLUE_COLOR    (0x000003ff)
#define GREEN_COLOR   (0x000ffC00)


//ITU:601 with gamma correction
/*
Y’ = 0.257*R' + 0.504*G' + 0.098*B' + 16

Cb' = -0.148*R' - 0.291*G' + 0.439*B' + 128

Cr' = 0.439*R' - 0.368*G' - 0.071*B' + 128
*/
#define RGB2YCBCR_FACTOR 10000

#define RGB2Y(R, G, B)  ((0.257 * RGB2YCBCR_FACTOR * (R)  + 0.504 * RGB2YCBCR_FACTOR * (G) + 0.098 * RGB2YCBCR_FACTOR * (B))/RGB2YCBCR_FACTOR + 16)
#define RGB2CB(R, G, B) ((-0.148 * RGB2YCBCR_FACTOR * (R)  - 0.291 * RGB2YCBCR_FACTOR * (G) + 0.439 * RGB2YCBCR_FACTOR * (B))/RGB2YCBCR_FACTOR + 128)
#define RGB2CR(R, G, B) ((0.439 * RGB2YCBCR_FACTOR * (R)  - 0.368 * RGB2YCBCR_FACTOR * (G) - 0.071 * RGB2YCBCR_FACTOR * (B))/RGB2YCBCR_FACTOR + 128)






typedef enum _SURFACE_PATTERN_
{
    PATTERN_INVALID = 0,
    PATTERN_COLOR_BAR,
    PATTERN_COLOR_1,
    PATTERN_COLOR_2,
    PATTERN_CIRCLE,    //for cursor 
    PATTERN_NUM,
}SURFACE_PATTERN;






typedef enum _PORT_TYPE
{
    PORT_0 = 0x1,
    PORT_1 = 0x2,
    PORT_2 = 0x3,
    PORT_NUM = 3,   // 枚举的定义中值是可以重复的，名字不能重复， 还是相当于宏定义一样，完成多个的宏定义的一起定义
}PORT_TYPE;


typedef enum _CRTC_TYPE
{
    CRTC_0 = 0,
    CRTC_1 = 0x1,
    CRTC_2 = 0x2,
    CRTC_NUM = 3,
}CRTC_TYPE;

struct mode_info_t
{
    u32  x_res;  //change to hdisplay later ?
    u32  y_res;
    
    u32  refresh_rate;

    u32  aspect_ratio;
    u32  hv_polarity;
    u32  htotal;
    u32  hblank_start;
    u32  hblank_end;
    u32  hsync_start;
    u32  hsync_end;
    u32  vtotal;
    u32  vblank_start;
    u32  vblank_end;
    u32  vsync_start;
    u32  vsync_end;

    u32  pixel_clock;
    u32  bit_per_commonent;

    u32_t output_signal;
};

struct crtc_info_t
{
    u8      index;

    u32     output;
    struct dpu_display_mode_t hw_mode;
    struct dpu_display_mode_t adjust_mode;
};

typedef enum _PLANE_TYPE_
{
    PRIMARY_PLANE    = 0,
    OVERLAY_PLANE   = 1,
    PLANE_NUM,
}PLANE_TYPE;

typedef enum _OVERLAY_MODE_
{
    CONSTANT_ALPHA = 0,
    PS_ALPHA_BLENDING,
    SOP_COLOR_KEY,
    POS_COLOR_KEY,
    SOP_WINDOW_KEY,
    SOP_ALPHA_KEY,
    POS_WINDOW_KEY,
    POS_ALPHA_KEY,
    SS_ALPHA_BLENDING,
    CHROMA_KEY,
    MAX_KEY_MODE,
}OVERLAY_MODE;

struct overlay_info_t 
{
    OVERLAY_MODE mode;

    struct
    {
      
        u8  kp;
        u8  ks;

        struct 
        {
            u8  constant_alpha;
            u8  plane_value;
            struct 
            {
                u8  invert  :1;
                u8  plane_blending  :1;
                u8  reserved    :6;
                
            };
        }constant_alpha_blending;

        struct
        {   
            u8  plane_value;

            struct
            {
                u8   plane_blending:1;
                u8   use_ps_alpha :1;
                u8   premul_blend :1;
                u8   invert_alpha :1;
                u8   reserved     :4;
            };
        }alpha_blending;

        u32 key_low;
        u32 key_high;  
    };
};


typedef enum _SURFACE_FORMAT_T
{
    FORMAT_INVALID =0,
    FORMAT_P8,
    FORMAT_R5G6B5,
    FORMAT_A1R5G5B5,
    FORMAT_A8R8G8B8,
    FORMAT_A8B8G8R8,
    FORMAT_X8R8G8B8,
    FORMAT_X8B8G8R8,
    FORMAT_A2R10G10B10,
    FORMAT_A2B10G10R10,
    FORMAT_CRYCBY422_16,
    FORMAT_YCRYCB422_16,
    FORMAT_CRYCBY422_32,
    FORMAT_YCRYCB422_32,
    FORMAT_CRYCB8888_32,
    FORMAT_YCBCR2101010_32,
    FORMAT_NUM,
}SURFACE_FORMAT;

struct format_info_t
{
    u32  bit_cnt;
    u8   format_name[FORMAT_NAME_LENGTH];
};

struct surface_info_t
{
    u32    index;
    u32    bit_cnt;
    u32    pitch;
    u32    width;
    u32    height;
    u32    aligned_width;
    //u32    aligned_hight;
    u32    size;  //bytes num

    SURFACE_FORMAT  format;
    u32    range_type;         //TODO
    SURFACE_PATTERN   pattern;

    u32      gpu_addr;
    void*    cpu_addr;

    u8     alpha;
 
    u8     format_name[FORMAT_NAME_LENGTH];

    struct
    {
        u32    compressed :1;
        u32    need_premult:1;
        u32    reserved   :30;
    };

};


typedef enum _PLANE_STATE
{
    PLANE_ENABLED = 0,
    PLANE_DISABLED,
}PLANE_STATE;


struct  csc_para_t
{
   u32 op; //0 : enable 1: disable

   i32    brightness;
   i32    hue;
   i32    contrast;
   i32    saturation;
};


struct plane_info_t
{
    u32  crtc_index;
    PLANE_TYPE  plane_type;
    
    u32  src_x;
    u32  src_y;
    u32  src_w;
    u32  src_h;

    u32  dst_x;
    u32  dst_y;
    u32  dst_w;
    u32  dst_h;

    struct  csc_para_t  csc_para;  //need do validation ?

    struct surface_info_t  *surface;

    struct overlay_info_t  overlay_info;

    PLANE_STATE  plane_state;
    
};

typedef enum _OUTPUT_CONNECTE_STATUS_T
{
    CONNECTED = 0,
    DISCONNECTED,
    UNKNOW_STATUS,
}OUTPUT_CONNECT_STATUS;

typedef enum _OUTPUT_POWER_STATUS_T
{
    POWER_ON = 0,
    POWER_OFF,
}OUTPUT_POWER_STATUS;

struct output_info_t
{
    u32   device;
    u8    edid[256];

    struct dpu_display_mode_list_t mode_list;
	struct dpu_display_info_t display_caps;
    struct crtc_info_t *crtc;


    u32     link_rate;
    u32     lane_count;

    u32     async_clk;        //0: sync clock; 1: async clock. default: async clock
    u32     enhanced_frame_mode;  //1: normal frame mode; 0: enhanced frame mode.
    u32     bit_depth;     // 6, 8, 10, 12 or 16. default: BitDepth = bpc
    u32     color_format; //1: RGB, 2: YUV422, 4: YUV444.
    u32     cea;          //use CEA Color Dynamic Range
    u32     coef;         //1: ITU601, 2: ITU709


    struct  csc_para_t  csc_para;

    OUTPUT_CONNECT_STATUS       connect_status;
    OUTPUT_POWER_STATUS         power_status;

};


typedef enum _CURSOR_TYPE
{
    CURSOR_INVALID_TYPE = 0,
    CURSOR_MONO,
    CURSOR_COLOR,
    CURSOR_PREMULT,
    CURSOR_COVERAGE,
    CURSOR_TYPE_NUM,
}CURSOR_TYPE;


typedef enum _CURSOR_MODE
{
    CURSOR_INVALID_MODE = 0,
    CURSOR_MODE_64_64,
    CURSOR_MODE_128_128,
    CURSOR_MODE_NUM,
}CURSOR_MODE;


struct  cursor_info_t
{
    u32  crtc_index;
    
    CURSOR_TYPE  type;
    CURSOR_MODE  mode;  

    u32 pos_x;
    u32 pos_y;

    struct surface_info_t  *surface;

    PLANE_STATE  plane_state;
};


struct list_block
{
    u32   size;
    u32   offset;           //the node's real offset,
    u32   aligned_offset;   //surface's aligned offset

    struct list_head list_item;
};

struct list_header
{
    struct list_head list;
    unsigned int size;
    unsigned int num;
};


struct mem_segment_t 
{
    u8     segment_id;   
    u32    available_size;   
    u32    mem_size;
    u32    offset;
    u32    reserved_mem_size;   //used for flag buffer, ring buffer ,need refine later
    u32    init_done;

    struct list_header  free;
    struct list_header  busy;
};

typedef enum  _SEGMENT_TYPE
{
    LOCAL_SEGMENT = 0,

    SEGMENT_NUM,

}SEGMENT_TYPE;

struct vidmm_mgr_t
{
    struct mem_segment_t  mem_segments[SEGMENT_NUM];
};


struct surface_manager_t 
{
    u32   num;

    struct 
    {
        u8      valid;
        struct surface_info_t  surface;
    }surfaces[MAX_SURFACE_NUM];

};

typedef enum _CMD_TYPE_
{
    MODE_CMD = 0,
    PLANE_CMD,
    DEVICE_CMD,
    SURFACE_CMD,
    CURSOR_CMD,
    MAX_CMD_NUM,
}CMD_TYPE;

struct mode_cmd_t
{
    u32  crtc_index;
    u32  crtc_valid;

    u32  output;

//add these in one structure
    u32  src_xres;
    u32  src_yres;
    u32  dst_xres;
    u32  dst_yres;
    u32  rr;
    u32 output_signal;
	u32 bpc;


    u32  list_cmd;
    u32  info_cmd;
    u32  help_cmd;

    u32  cmd_index; // used for cached modes
    u32  cmd_valid;
};

struct overlay_cmd_t
{
    u32 mode;
    u32 m_valid;
    u32 kp;
    u32 ks;
    u32 kps_valid;
	u32 key_low;
	u32 key_high;
	u32 key_valid;
};

struct plane_cmd_t
{
    u32   crtc_index;
    u32   ci_valid;
    u32   surface_index;
    u32   si_valid;
    
    u32  plane_type;  //PLANE_TYPE
    u32   pt_valid;         //plane_type_valid

    u32   src_x;
    u32   src_y;

    u32   srcxy_valid;
    
    u32   src_w;
    u32   src_h;
    

    u32   dst_x;
    u32   dst_y;
    u32   dstxy_valid;
    u32   dst_w;
    u32   dst_h;

    u32    disable_plane;    //1:disable plane   0；enable plane
    u32    dp_valid;

    struct overlay_cmd_t  overlay_cmd;


    u32   info_cmd;
    u32   list_cmd;
    u32   help_cmd;

    u32   cmd_index;
    u32   cmd_valid;

};


struct device_cmd_t
{
    u32     output;
    u32     disable;      // 1: turn off device   0 : turn on device

    
    u32     link_rate;       //the maximum link rate used by DP. 1: 5.4Gbps, 2: 2.7Gbps, 3: 1.62Gbps. default:3 1.62Gbps
    u32     lane_count;      //the maximum lane count used by DP. Can be 4, 2, 1. default: 4\n");
    u32     async_clk;        //1: sync clock; 2: async clock. default:2 async clock
    u32     enhanced_frame_mode;  //1: normal frame mode; 2: enhanced frame mode. default 2
    u32     bit_depth;     // 6, 8, 10, 12 or 16. default: BitDepth = bpc
    u32     color_format; //1: RGB, 2: YUV422, 4: YUV444.
    u32     cea;          //use CEA Color Dynamic Range
    u32     coef;         //1: ITU601, 2: ITU709


    u32     modelist_cmd;
    u32     config_cmd;
    u32     list_cmd;
    u32     help_cmd;
	u32     info_cmd;


    
    u32     cmd_index;
    u32     cmd_valid;
};

struct surface_cmd_t
{
    u32     surface_index;  //used for free surface
    u32     si_valid;       //if surface index valid ,means free this surface

    u32     width;
    u32     height;

    u32     alpha;
    u32     alpha_valid;
    u32     pattern; //SURFACE_PATTERN

    u32      format; //SURFACE_FORMAT


    u32     no_draw;
    u32     premult;
    
    u32     compressed;

    u32     list_cmd;
    u32     info_cmd;
    u32     help_cmd;

    u32     cmd_index;
    u32     cmd_valid;
};

struct cursor_cmd_t
{
    u32 op;     //0:disable 1: enable
    u32 op_valid;

    u32 crtc;
    u32 crtc_valid;

    u32 type;   //1:MONO   2 COLOR  3: PREMULT  4: COVERAGE

    u32 mode;  //1: 64x64  2:128x128

    u32 surface_index;
    u32 si_valid;

    u32 pos_x;
    u32 pos_y;
    u32 pos_valid;


    u32 list_cmd;
    u32 info_cmd;
    u32 help_cmd;

    u32 cmd_index;
    u32 cmd_valid;
};


struct  cached_cmd_t
{
    u8      valid;
    union
    {
        struct mode_cmd_t   mode_cmd;
        struct plane_cmd_t  plane_cmd;
        struct device_cmd_t device_cmd;
        struct surface_cmd_t surface_cmd;
        struct cursor_cmd_t  cursor_cmd;
    };
};

struct base_adapter_t
{
	u16  	vender_id;
	u16  	device_id;
	u16  	revision_id;
	
	u8 	    bus_num;
	u8 	    dev_num;
	u8  	func_num;

	u64   	mmio_phy;
	u64   	fb_phy;
	void* 	mmio_base;
	u32		mmio_size;
	void* 	fb_base;
    u32     fb_size;
	u32	    hda_base;
	
	struct  
	{
		u8   bus_num;
		u8   dev_num;
		u8   func_num;
	}bridge_info;


	struct 
	{
		u32 is_primary :1;
		u32 reserved   :31;
	}flags;

};


#define TEST_WITHOUT_DE     		0x1
#define TEST_DE             		0x2
#define TEST_DE_WITH_REAL_CHIP     	0x4

struct dpu_adapter_t
{
	struct base_adapter_t  base;
	
	struct dpu_crtc_caps_t crtc_caps;

    u32     test_domain;   //TEST_DE, TEST_WITHOUT_DE, TEST_DE_WITH_REAL_CHIP
    
    u32 	num_output;
	u32 	support_device;
	u32     active_output[CRTC_NUM];



    u32     width_alignment;    //surface width aligment, in bytes
    u32     offset_alignment;   //surface gpu address aligment 


    struct  vidmm_mgr_t   vidmm_mgr;


    struct  crtc_info_t     current_crtc_info[CRTC_NUM];
    struct  plane_info_t    current_plane_info[CRTC_NUM][PLANE_NUM];
    struct  output_info_t   current_output_info[PORT_NUM];
    struct  cursor_info_t   current_cursor_info[CRTC_NUM];

    struct  surface_manager_t  surface_manager;

    void*    dpu_manager;


    struct  cached_cmd_t  cached_cmd[MAX_CMD_NUM][MAX_CACHED_CMD_NUM];

    u8      cmd_history[MAX_INPUT_HISTORY_NUM][MAX_CMD_STRING_NUM];

    u32     cmd_num;
    
    u32     log_level; //control log output

	u8	*	script_name;
    
	union
	{
		u32  value;
		struct
		{
			u32 run_on_qt	:1;
			u32 reserved   :31;
		};
	}flags;

};






struct dither_t
{
    BOOL 	en;
    u32 	rgb_src;
    u32 	rgb_dst;
    u32 	rgb_op;
    u32 	alpha_src;
    u32 	alpha_dst;
    u32 	alpha_op;
    u32 	bld_color;
};
struct cursor_t
{
    BOOL 	en;
    BOOL	is_cbcr;
    
};
struct scaler_t
{
    BOOL 	en;
    BOOL 	h_en, v_en;
    BOOL 	is_cos_h;
    BOOL 	is_cos_v;
    BOOL 	is_alpha_ups;
    BOOL 	is_color_key;
    BOOL 	is_v_duplicate;
    u32 	keyl;
    u32 	keyh;
    u32 	key_mode;
    u32 	h_acc;
    u32 	v_acc;

    BOOL 	is_cos;
    BOOL 	is_hw_ratio;
    BOOL 	ratio_plus;
};
struct overlay_t
{
    BOOL 	en;
    BOOL 	efuse_sec;
    BOOL 	itg_hden;
    BOOL 	itg_vden;
    u32 	key_mode_0;
    u32 	pla_fct_0;
    u32 	plb_fct_0;
    u32 	bld_mode_0;
    BOOL 	is_inv_alpha_0;
    u32 	plane_alpha_val_0;
    u32 	alpha_key_sel_0;
    u32 	color_key_sel_0;
    BOOL 	is_alpha_rang_0;
    u32 	key_mode_1;
    u32 	pla_fct_1;
    u32 	plb_fct_1;
    u32 	bld_mode_1;
    BOOL 	is_inv_alpha_1;
    u32 	plane_alpha_val_1;
    u32 	alpha_key_sel_1;
    u32 	color_key_sel_1;
    BOOL 	is_alpha_rang_1;
    BOOL 	is_mdi_sec_0;
    BOOL 	is_ycbcr_0;
    BOOL 	is_mdi_sec_1;
    BOOL 	is_ycbcr_1;
    u32 	curs_ovl_tp;
    BOOL 	curs_ycbcr;
    BOOL 	is_ref_int_c;
    BOOL 	is_ref_int_0;
    BOOL 	is_ref_int_1;
};
struct csc_t
{
    BOOL 	src_rgb; ///< RGB or YCbCr source.
    BOOL 	dst_rgb; ///< RGB or YCbCr destination.
    BOOL 	src_range_full; ///< Full or limited range for source.
    BOOL 	dst_range_full; ///< Full or limited range for destination.
    u8      gamut[20]; ///< Gamut name.
    i32 	bright_drv; ///< Programmable brightness offset (actual value).
    u32 	infmt; ///< Input format index.
    u32 	outfmt; ///< Output format index.
    u32 	bright; ///< Programmable brightness offset (fixed point value).
    BOOL 	prog; ///< Programmable matrix and brightness offset.
    u32 	coefs[3][3]; ///< 3x3 matrix coefficients.
};
struct dpu_drv_para_t
{
	struct cursor_t cursor;
    struct scaler_t scl;
    struct overlay_t ovl;
    struct dither_t dither;
    struct csc_t csc_plane;
    struct csc_t csc_cursor;
    u32 	bg_color;
    BOOL 	bg_ycbcr;
};


struct bus_1010108 
{
    u64		 BV : 10;
    u64 	GU : 10;
    u64 	RY : 10;
    u64 	A : 8;
    u64 	is_color_key : 1;
    u64 	is_alpha_key : 1;
    u64 	is_ycbcr : 1; 
    u64 	is_valid : 1; //internal usage
};

struct cmodel_args_t
{
	u32_t   crtc;

	struct  plane_info_t    *plane_info[2];
	struct  cursor_info_t   *cursor_info;
	u8 		*iwin;
	u32_t	iwin_size; //in bytes
	u8 		*background;
	u32_t 	bg_size;

	u8 		*spl_input_src[2];
	u32_t 	spl_input_src_size[2];
	u8 		*spl_input_dst[2];
	u32_t   spl_input_dst_size[2];
	

	u8 		*spl_scl_dst[2];
	u32_t    spl_scl_dst_size[2];


	u8 		*cur_input_src;
	u8 		*cur_input_dst;


	u8 		*spl_csc_dst[2];
	u8 		*cur_csc_dst;

	u8 		*pipe_pu_dst;
	u8 		*pipe_lut_dst;
	u8 		*pipe_csc_dst;
	u8 		*pipe_dither_dst;

	u32  	dest_win_w;
	u32	 	dest_win_h;
};


#endif
