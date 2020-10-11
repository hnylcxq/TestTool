#ifndef _DPU_H_
#define _DPU_H_



#define 	DPU_TRUE  		1
#define 	DPU_FALSE 		0 


typedef		unsigned char       bool_t;

typedef     unsigned char       u8_t;
typedef     unsigned short      u16_t;
typedef     unsigned int        u32_t;
typedef     unsigned long long  u64_t;
typedef     char                i8_t;
typedef     short               i16_t;
typedef     int                 i32_t;
typedef     long long           i64_t;


typedef enum _DPU_PORT_TYPE
{
    DPU_PORT_0 = 0x1,
    DPU_PORT_1 = 0x2,
    DPU_PORT_2 = 0x4,
    DPU_PORT_NUM = 3,
}DPU_PORT_TYPE;


typedef  enum _DPU_STATUS
{
    DPU_OK = 0,
    DPU_EINVAL,

}DPU_STATUS;

typedef enum _DPU_DEVICE_POWER_STATE
{
    DPU_POWER_ON = 0,
    DPU_POWER_STANDBY,
    DPU_POWER_SUSPEND,
    DPU_POWER_OFF,
}DPU_DEVICE_POWER_STATE;

typedef enum _DPU_PLANE_TYPE
{
    DPU_PRIMARY_PLANE = 0,
    DPU_OVERLAY_PLANE,
    DPU_CURSOR_PLANE,
}DPU_PLANE_TYPE;

typedef enum _DPU_CRTC_TYPE
{
    DPU_CRTC_0 = 0,
    DPU_CRTC_1,
    DPU_CRTC_2,
    DPU_MAX_CRTC_NUM,
}DPU_CRTC_TYPE;

struct dpu_cb_funs_t
{
    void*   cb_print;
    void*   cb_delay_us;
    void*   cb_read_u8;
    void*   cb_read_u16;
    void*   cb_read_u32;
    void*   cb_write_u8;
    void*   cb_write_u16;
    void*   cb_write_u32;
    void*   cb_alloc_mem;
    void*   cb_free_mem;
    void*   cb_spin_lock;
    void*   cb_spin_unlock;
    void*   cb_mutex_lock;
    void*   cb_mutex_unlock;
    
    void*   cb_strcmp;
    void*   cb_strcpy;
    void*   cb_strncmp;
    void*   cb_memset;
    void*   cb_memcpy;
    void*   cb_memcmp;
    void*   cb_do_div;
    void*   cb_vsprintf;
    void*   cb_vsnprintf;
};


struct dpu_manager_t
{
    void *what;
};


typedef enum _DPU_FLIP_FLAG
{
    DPU_PAGE_FLIP_ONLY = 0,
    DPU_ENABLE_FLIP,
    DPU_DISABLE_FLIP,
}DPU_FLIP_FLAG;

typedef enum _DPU_OVERLAY_MODE
{
    DPU_INVALID_OVERLAY_MODE = 0x00,
    DPU_SOP_WINDOW_KEY = 0x01,
    DPU_SOP_ALPHA_KEY = 0x02,
    DPU_SOP_COLOR_KEY = 0x03,
    DPU_POS_WINDOW_KEY = 0x04,
    DPU_POS_ALPHA_KEY = 0x05,
    DPU_POS_COLOR_KEY = 0x06,
    DPU_PS_ALPHA_BLENDING =0x08,
    DPU_CONSTANT_ALPHA = 0x09,
    DPU_SS_ALPHA_BLENDING = 0xA,
    DPU_CHROMA_KEY   = 0x0B,
}DPU_OVERLAY_MODE;

struct dpu_overlay_t 
{
    DPU_OVERLAY_MODE mode;

    union
    {
        struct 
        {
            u8_t  kp;
            u8_t  ks;
        }window_key;

        struct 
        {
            u8_t  kp;
            u8_t  ks;
        }alpha_key;

        struct 
        {
            u8_t  type;
            struct 
            {
                u8_t  _10bit_color: 1;  //?
                u8_t  reserved :7;
            };
        }color_key;

        struct 
        {
            u8_t  constant_alpha;
            u8_t  plane_value;
            struct 
            {
                u8_t  invert  :1;
                u8_t  plane_blending  :1;
                u8_t  reserved    :6;
                
            };
        }constant_alpha_blending;


        struct
        {   
            u8_t  plane_value;

            struct
            {
                u8_t   plane_blending:1;
                u8_t   use_ps_alpha :1;
                u8_t   premul_blend :1;
                u8_t   invert_alpha :1;
                u8_t   reserved     :4;
            };
        }alpha_blending;

        struct
        {
            u32_t lower_bound;
            u32_t upper_bound;
            
        }chroma_key;
    };
};



typedef enum _DPU_SURFACE_FORMAT_T
{
    DPU_FORMAT_INVALID =0,
    DPU_FORMAT_MONO,
    DPU_FORMAT_P8,
    DPU_FORMAT_R5G6B5,
    DPU_FORMAT_A1R5G5B5,
    DPU_FORMAT_A8R8G8B8,
    DPU_FORMAT_A8B8G8R8,
    DPU_FORMAT_X8R8G8B8,
    DPU_FORMAT_X8B8G8R8,
    DPU_FORMAT_A2R10G10B10,
    DPU_FORMAT_A2B10G10R10,
    DPU_FORMAT_CRYCBY422_16,
    DPU_FORMAT_YCRYCB422_16,
    DPU_FORMAT_CRYCBY422_32,
    DPU_FORMAT_YCRYCB422_32,
    DPU_FORMAT_YCBCR8888_32,
    DPU_FORMAT_CRYCB8888_32,
    DPU_FORMAT_YCBCR2101010_32,
    DPU_FORMAT_CRYCB2101010_32,
    DPU_FORMAT_NUM,
}DPU_SURFACE_FORMAT;


struct dpu_surface_t
{
    u32_t   addr;
    u32_t   bit_cnt;
    u32_t   pitch;
    u32_t   width;
    u32_t   height;
    u32_t   aligned_width;
    u32_t   size;

    u32_t    range_type;
    DPU_SURFACE_FORMAT  format;

    struct
    {
        u32_t    compressed :1;
        u32_t    reserved   :31;
    };

};


struct dpu_plane_t
{
    DPU_CRTC_TYPE   crtc;
    DPU_PLANE_TYPE  plane;

    u32_t   src_x;
    u32_t   src_y;
    u32_t   src_w;
    u32_t   src_h;
    u32_t   dst_x;
    u32_t   dst_y;
    u32_t   dst_w;
    u32_t   dst_h;

    struct dpu_surface_t  surface;
    struct dpu_overlay_t  overlay;

    DPU_FLIP_FLAG  flag;
};

typedef enum _DPU_OUTPUT_SIGNAL_
{
    DPU_INVALID_SIGNAL= 0,
    DPU_RGB_SIGNAL,
    DPU_YCBCR444_SIGNAL,
    DPU_YCBCR422_SIGNAL,
    DPU_YCBCR420_SIGNAL,
    DPU_MAX_SIGNAL_NAM,
}DPU_OUTPUT_SIGNAL;



//timing info ?
struct base_mode_info_t
{
    u32_t  x_res;
    u32_t  y_res;
    
    u32_t  refresh_rate;

    u32_t  aspect_ratio;
    u32_t  hv_polarity;
    u32_t  htotal;
    u32_t  hblank_start;
    u32_t  hblank_end;
    u32_t  hsync_start;
    u32_t  hsync_end;
    u32_t  vtotal;
    u32_t  vblank_start;
    u32_t  vblank_end;
    u32_t  vsync_start;
    u32_t  vsync_end;

    u32_t  pixel_clock;
    u32_t  bit_per_commonent;

    DPU_OUTPUT_SIGNAL  output_signal;
};


struct dpu_virt_mode_t
{

    DPU_CRTC_TYPE  crtc;
    struct base_mode_info_t mode;
};

struct dpu_real_mode_t
{
    DPU_PORT_TYPE device;
    struct base_mode_info_t mode;
};


struct dpu_device_set_t
{
    DPU_PORT_TYPE  device;
    DPU_DEVICE_POWER_STATE  state;

    //some para for cts
    struct 
    {
        u32_t     link_rate;  
        u32_t     lane_count; 
        u32_t     async_clk;        //0: sync clock; 1: async clock. default: async clock
        u32_t     enhanced_frame_mode;  //1: normal frame mode; 0: enhanced frame mode.
        u32_t     bit_depth;     // 6, 8, 10, 12 or 16. default: BitDepth = bpc
        u32_t     color_format; //1: RGB, 2: YUV422, 4: YUV444.
        u32_t     cea;          //use CEA Color Dynamic Range
        u32_t     coef;         //1: ITU601, 2: ITU709 
    };
};

struct dpu_i2c_para_t
{
    u8_t    group;
    u8_t    addr;
    u8_t    offset;
    u8_t*   buffer;
    u32_t     length;
    u8_t      op;      //0: read   1: write
};


struct dpu_aux_para_t
{
    u32_t  device;
    u32_t  offset;
    u32_t  length;
    u8_t*  buffer;
    u8_t   op;     //0: read   1: write

};


typedef enum _DPU_CURSOR_TYPE
{
    DPU_CURSOR_INVALID_TYPE = 0,
    DPU_MONO,
    DPU_COLOR,
    DPU_PREMULT,
    DPU_COVERAGE,
}DPU_CURSOR_TYPE;

typedef enum _DPU_CURSOR_MODE
{
    DPU_CURSOR_MODE_INVALID = 0,
    DPU_CURSOR_64_64,
    DPU_CURSOR_128_128,
}DPU_CURSOR_MODE;

struct dpu_cursor_para_t
{
   
    DPU_CRTC_TYPE           crtc;
    DPU_CURSOR_TYPE         type;
    DPU_CURSOR_MODE         mode;
    i32_t                   pos_x;
    i32_t                   pos_y;
    u32_t                   addr;

    u32_t                   vsync_off;   //1: vsync off  2:vsync on

    DPU_FLIP_FLAG           flag;
 };


DPU_STATUS dpu_set_virt_mode(struct dpu_manager_t* dpu_manager, struct dpu_virt_mode_t * mode);

DPU_STATUS dpu_set_real_mode(struct dpu_manager_t* dpu_manager, struct dpu_real_mode_t * mode);

DPU_STATUS dpu_update_plane(struct dpu_manager_t* dpu_manager, struct dpu_plane_t* plane_info);

DPU_STATUS dpu_set_device(struct dpu_manager_t *dpu_manager ,struct dpu_device_set_t* device_set);

DPU_STATUS dpu_set_i2c(struct dpu_manager_t *dpu_manager, struct dpu_i2c_para_t *i2c_para);

DPU_STATUS dpu_set_aux(struct dpu_manager_t *dpu_manager, struct dpu_aux_para_t *aux_para);

DPU_STATUS dpu_set_cursor(struct dpu_manager_t *dpu_manager, struct dpu_cursor_para_t  *cursor_para);



#endif
