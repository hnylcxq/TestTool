#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include"types.h"
#include"util.h"
#include"config.h"

#include"dpu.h"

#include "reg/reg.h"


//must sync with OUTPUT_SIGNAL
static u8  *g_output_signal_string[] = {" INVALID"," RGB"," YUV444", " YUV422", "YUV420"};


//must sync with OVERLAY_MODE
static u8  *g_key_mode_string[] = 
{
    "CONSTANT_ALPHA", 
    "PS_ALPHA_BLENDING",
    "SOP_COLOR_KEY",
    "POS_COLOR_KEY",
    "SOP_WINDOW_KEY",
    "SOP_ALPHA_KEY",
    "POS_WINDOW_KEY",
    "POS_ALPHA_KEY",
    "SS_ALPHA_BLENDING",
    "CHROMA_KEY",
};


//mast sync with SURFACE_FORMAT
struct format_info_t g_format_info_string[] = {
        {1, "FORMAT_INVALID"}, //FORMAT_INVALID
        {8, "RGB8"},         //FORMAT_P8
        {16, "RGB565"},      //FORMAT_R5G6B5
        {16, "ARGB1555"},    //FORMAT_A1R5G5B5
        {32, "ARGB8888"},    //FORMAT_A8R8G8B8
        {32, "ABGR8888"},    //FORMAT_A8B8G8R8
        {32, "XRGB8888"},    //FORMAT_X8R8G8B8
        {32, "XBGR8888"},    //FORMAT_X8B8G8R8
        {32, "ARGB2101010"}, //FORMAT_A2R10G10B10
        {32, "ABGR2101010"}, //FORMAT_A2B10G10R10
        {16, "CRYCBY422_16"},//FORMAT_CRYCBY422_16
        {16, "YCRYCB422_16"},//FORMAT_YCRYCB422_16
        {32, "CRYCBY422_32"},//FORMAT_CRYCBY422_32
        {32, "YCRYCB422_32"},//FORMAT_YCRYCB422_32
        {32, "CRYCB8888"},   //FORMAT_CRYCB8888_32
        {32, "YCBCR2101010_32"},//FORMAT_YCBCR2101010_32
};


//mast sync with SURFACE_PATTERN
static u8 *g_color_pattern_string[] = 
{
    "PATTERN_INVALID",
    "PATTERN_COLOR_BAR",
    "PATTERN_COLOR_1",
    "PATTERN_COLOR_2",
    "PATTERN_ARROW"
};


static u8 *g_cursor_type_string[] = 
{
    "INVALID TYPE",
    "MONO TYPE",
    "COLOR TYPE",
    "PREMULT TYPE",
    "COVERAGE TYPE",
};

static struct mode_cmd_t  g_mode_cmd = {0};
static struct plane_cmd_t g_plane_cmd = {0};
static struct surface_cmd_t g_surface_cmd = {0};
static struct device_cmd_t g_device_cmd = {0};
static struct cursor_cmd_t g_cursor_cmd = {0};

static struct options_table mode_options_table[] = 
{
    {"c", "[-c crtc_index]", 1, {10, &g_mode_cmd.crtc_index, &g_mode_cmd.crtc_valid},},
    {"o", "[-o output] eg:0x4", 1, {16, &g_mode_cmd.output,},},
    {"src", "[-src xres yres]", 2, {{10, &g_mode_cmd.src_xres}, {10, &g_mode_cmd.src_yres},}},
    {"dst", "[-dst xres yres]", 2, {{10, &g_mode_cmd.dst_xres}, {10, &g_mode_cmd.dst_yres},}},
    {"rr",  "[-rr refresh rate eg:50]", 1, {{10, &g_mode_cmd.rr},}},
    {"os",  "[-os output signal] 1:RGB 2: YUV444 3: YUV422 4: YUV 420",1, {{10, &g_mode_cmd.output_signal}},},
    {"list",   "[-list] list cached modes", 0, {{0, NULL, &g_mode_cmd.list_cmd}}},
    {"info",   "[-info] current mode info ", 0,{{0, NULL, &g_mode_cmd.info_cmd}}},
    {"help",   "[-help] help", 0, {{0, NULL, &g_mode_cmd.help_cmd},}},
    {"set",   "[-set index], set cached cmd[index]", 1, {{10, &g_mode_cmd.cmd_index, &g_mode_cmd.cmd_valid},}},
};

static struct options_table plane_options_table[] = 
{
    {"c", "[-c crtc_index]", 1, {{10, &g_plane_cmd.crtc_index, &g_plane_cmd.ci_valid}}},
    {"p", "[-p plane_type]", 1, {{10, &g_plane_cmd.plane_type, &g_plane_cmd.pt_valid}}},
    {"s", "[-s surface_index]", 1, {{10, &g_plane_cmd.surface_index, &g_plane_cmd.si_valid}}},
    {"sp", "[-sp src_x src_y]", 2, {{10, &g_plane_cmd.src_x, &g_plane_cmd.srcxy_valid}, {10, &g_plane_cmd.src_y,}}},
    {"dp", "[-dp dst_x dst_y]", 2, {{10, &g_plane_cmd.dst_x, &g_plane_cmd.dstxy_valid}, {10, &g_plane_cmd.dst_y,}}},
    {"sw", "[-sw srx_w src_h]", 2, {{10, &g_plane_cmd.src_w, }, {10, &g_plane_cmd.src_h}}},
    {"dw", "[-dw dst_w dst_h]", 2, {{10, &g_plane_cmd.dst_w}, {10, &g_plane_cmd.dst_h}}},
    {"d", "[-d disable]", 1, {{10, &g_plane_cmd.disable_plane, &g_plane_cmd.dp_valid}}},
    {"km", "[-km keymode] ", 1, {{10, &g_plane_cmd.overlay_cmd.mode, &g_plane_cmd.overlay_cmd.m_valid},}},
    {"kv", "[-kv k0 k1 k2] k0,k1 k2", 3, {{10, &g_plane_cmd.overlay_cmd.k0, &g_plane_cmd.overlay_cmd.k_valid},
                                                                            {10, &g_plane_cmd.overlay_cmd.k1},{16, &g_plane_cmd.overlay_cmd.k2}}},
    {"info", "[-info]  current plane info", 0 ,{{0, NULL, &g_plane_cmd.info_cmd},}},
    {"list", "[-list]  list cached plane config",0, {{0, NULL, &g_plane_cmd.list_cmd}}},
    {"help", "[-help] help ", 0, {{0, NULL, &g_plane_cmd.help_cmd},}},
    {"set", "[-set index] set cached cmd[index]", 1, {{10, &g_plane_cmd.cmd_index, &g_plane_cmd.cmd_valid},}},
};


static struct options_table surface_options_table[] = 
{
   {"c", "[-c ] compressed ", 1, {{10, NULL, &g_surface_cmd.compressed},}},
   {"d", "[-d surface_index] delete surface", 1, {{10, &g_surface_cmd.surface_index, &g_surface_cmd.si_valid},}},
   {"s", "[-s width height], size ", 2, {{10, &g_surface_cmd.width},{10, &g_surface_cmd.height,}}},
   {"f", "[-f format] ",1, {{10, &g_surface_cmd.format},}},
   {"a", "[-a alpha]", 1, {{16, &g_surface_cmd.alpha, &g_surface_cmd.alpha_valid},}},
   {"m", "[-m] need do premult", 0, {{10, NULL, &g_surface_cmd.premult },}},
   {"nd", "[-nd] not draw", 0, {{0, NULL, &g_surface_cmd.no_draw},}},
   {"p", "[-p pattern]", 1, {{10, &g_surface_cmd.pattern,}}},
   {"list", "[-list] list cached surface cmd", 0, {{0, NULL, &g_surface_cmd.list_cmd}}},
   {"info", "[-info] list all surfaces ", 0, {{0, NULL, &g_surface_cmd.info_cmd},}},
   {"help", "[-help] help", 0, {{0, NULL, &g_surface_cmd.help_cmd},}},
   {"set", "[-set index] set cached cmd[index]", 1, {{10, &g_plane_cmd.cmd_index, &g_plane_cmd.cmd_valid},}},
 
};

static struct options_table device_options_table[] = 
{
    {"o", "[-o output]",1, {16,&g_device_cmd.output},},
    {"d", "[-d ] turn off output", 1, {10, NULL, &g_device_cmd.disable},},
    {"lr","[-lr linkrate] 1:5.4G 2:2.7G 3:1.62G default:3", 1, {10, &g_device_cmd.link_rate},},
    {"lc","[-lc linkcount] 1: 4lane 2: 2 lane 3: 1 lane default:1", 1, {10, &g_device_cmd.lane_count},},
    {"as","[-ac async/sync clock] 1:async 2:sync clock default:1", 1, {10, &g_device_cmd.async_clk},},
    {"ef","[-ef enhanced_frame_mode] 1: normal frame mode 2: enhanced frame  default:2", 1, {10, &g_device_cmd.enhanced_frame_mode},},
    {"bd","[-bd bit_depth]  [6,8,10,12 16] default:8",1,{10, &g_device_cmd.bit_depth},},
    {"cf","[-cf color_format] 1:RGB, 2:YUV422 3,YUV444", 1, {10, &g_device_cmd.color_format},},
    {"cea","[-cea] use cea clolor dynamic range", 0,{0, NULL, &g_device_cmd.cea},},
    {"coef","[-coef value], 1:ITU601 2:ITU709",1,{10, &g_device_cmd.coef,},},
    {"ml", "[-ml] list device mode list",0,{0, NULL, &g_device_cmd.modelist_cmd},},
    {"list","[-list] list cached device config",0,{0, NULL, &g_device_cmd.list_cmd},},
    {"info","[-info] current device config",0, {0, NULL, &g_device_cmd.info_cmd}},
    {"help","[-help] list help info",0,{0, NULL, &g_device_cmd.help_cmd}},
    {"set", "[-set index] set cached cmd[index]", 1, {10, &g_device_cmd.cmd_index, &g_device_cmd.cmd_valid},}
};

static struct options_table cursor_options_table[] =
{
    {"op", "[-op  value]  0:disable 1:enable", 1, {10, &g_cursor_cmd.op, &g_cursor_cmd.op_valid}},
    {"c", "[-c  crtc]  ", 1, {10, &g_cursor_cmd.crtc, &g_cursor_cmd.crtc_valid}},
    {"t", "[-t  type] 1:MONO, 2: COLOR  3:PREMULT 4:COVERAGE ", 1, {10, &g_cursor_cmd.type}},
    {"m", "[-m  mode] 1:64x64  2:128x128", 1, {10, &g_cursor_cmd.mode,}},
    {"s", "[-s  surface_index]", 1, {10, &g_cursor_cmd.surface_index, &g_cursor_cmd.si_valid}},
    {"p", "[-p pos_x pox_y]", 2, {{10, &g_cursor_cmd.pos_x, NULL}, {10, &g_cursor_cmd.pos_y, &g_cursor_cmd.pos_valid}}},
    {"list", "[-list] list cached cursor cmd", 0, {0, NULL, &g_cursor_cmd.list_cmd}},
    {"info", "[-info] current cursor config", 0, {0, NULL, &g_cursor_cmd.info_cmd}},
    {"help", "[-help] list help info ", 0, {0, NULL, &g_cursor_cmd.help_cmd},},
    {"set", "[-set index] set cached cmd[index]", 1, {10, &g_cursor_cmd.cmd_index, &g_cursor_cmd.cmd_valid}}

};


static void mode_handle_trace(struct mode_cmd_t *mode_info)
{

    dpu_trace("crtc %d crtc_valid %d, cmd_index %d cmd_index_valid %d, output %d,src(%d,%d) dst(%d,%d),rr %d list %d info %d help %d\n",
            mode_info->crtc_index, mode_info->crtc_valid,
            mode_info->cmd_index,mode_info->cmd_valid,
            mode_info->output,
            mode_info->src_xres,
            mode_info->src_yres,
            mode_info->dst_xres,
            mode_info->dst_yres,
            mode_info->rr,
            mode_info->list_cmd,
            mode_info->info_cmd,
            mode_info->help_cmd);

}

static void mode_handle_list(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct mode_cmd_t *cached_cmd;

    dpu_info("list of cached mode options: \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[MODE_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[MODE_CMD][i].mode_cmd;

            dpu_info("%d: crtc %d output 0x%x, src_mode (%d %d) dst_mode (%d %d), rr %d, output_signal %s\n",
                    i,
                    cached_cmd->crtc_index,
                    cached_cmd->output,
                    cached_cmd->src_xres,
                    cached_cmd->src_yres,
                    cached_cmd->dst_xres,
                    cached_cmd->dst_yres,
                    cached_cmd->rr,
                    g_output_signal_string[cached_cmd->output_signal]);     
            }
    }
}

static void mode_handle_help()
{
    u32 i = 0;
    
    for (i = 0; i < ARRAY_SIZE(mode_options_table); i++)
    {
        dpu_info("%s\n", mode_options_table[i].options_help);
    }

    //add more help info here

}

static void mode_handle_info(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct  crtc_info_t *crtc_info;

    
    for (i = 0; i < CRTC_NUM; i++)
    {
        crtc_info = &dpu_adapter->current_crtc_info[i];

        if (!crtc_info->output)
        {
            dpu_info("crtc_%d: not active\n", i);
        }
        else
        {
            dpu_info("crtc_%d: output 0x%5x, hw mode(%4d %4d) adjust mode(%4d %4d), rr %d, output_signal %s\n",
                    i,
                    crtc_info->output,
                    crtc_info->hw_mode.hactive,
                    crtc_info->hw_mode.vactive,
                    crtc_info->adjust_mode.hactive,
                    crtc_info->adjust_mode.vactive,
                    crtc_info->hw_mode.refresh_rate,
                    g_output_signal_string[crtc_info->hw_mode.output_signal]);
        };
    }


}

static TT_STATUS mode_handle(struct dpu_adapter_t *dpu_adapter, struct mode_cmd_t *mode_info)
{
    i32     i = 0;
    struct mode_cmd_t *cached_cmd;
    struct mode_cmd_t  prepare_cmd = {0};
    struct  crtc_info_t *crtc_info;
    struct  crtc_info_t crtc_set = {0};
    u32 index = 0;

    struct dpu_crtc_mode_set_para_t crtc_mode = {0};
    struct dpu_encoder_mode_set_para_t encoder_mode = {0};

    u32     new_cmd = 0;

    u32     valid = 0;
    u32     temp = 0;
    TT_STATUS ret = TT_PASS;

    mode_handle_trace(mode_info);

    if (dpu_adapter->test_domain | TEST_DOS_ONLY)
    {
        dpu_info("de is not available\n");
        goto end;
    }

    if (mode_info->list_cmd)
    {
        mode_handle_list(dpu_adapter);
        goto end;
    }

    if (mode_info->help_cmd)
    {
        mode_handle_help();
        goto end;
    }

    if (mode_info->info_cmd)
    {
        mode_handle_info(dpu_adapter);
        goto end;
    }

    prepare_cmd.cmd_index = 0;
    prepare_cmd.crtc_index = 0;
    prepare_cmd.output = 0x8000;
    prepare_cmd.src_xres = 1920;
    prepare_cmd.src_yres = 1080;
    prepare_cmd.dst_xres = 1920;
    prepare_cmd.dst_yres = 1080;

    prepare_cmd.rr = 6000;
    prepare_cmd.output_signal = RGB_SIGNAL;
    

    new_cmd = 1;
    if(mode_info->cmd_valid && mode_info->cmd_index < MAX_CACHED_CMD_NUM && dpu_adapter->cached_cmd[MODE_CMD][mode_info->cmd_index].valid)
    {
        cached_cmd = &dpu_adapter->cached_cmd[MODE_CMD][mode_info->cmd_index].mode_cmd;

        memcpy(&prepare_cmd, cached_cmd, sizeof(struct mode_cmd_t)); //all cached cmd value is valid.
        new_cmd = 0;
    }

    if (mode_info->src_xres && mode_info->src_yres)
    {
        prepare_cmd.src_xres = mode_info->src_xres;
        prepare_cmd.src_yres = mode_info->src_yres;
    }

    if (mode_info->dst_xres && mode_info->dst_yres)
    {
        prepare_cmd.dst_xres = mode_info->dst_xres;
        prepare_cmd.dst_yres = mode_info->dst_yres;
    }

    if (mode_info->rr)
    {
        prepare_cmd.rr = mode_info->rr;
        if (prepare_cmd.rr < 100)
        {
            prepare_cmd.rr *= 100;
        }
    }

    if (mode_info->output_signal && mode_info->output_signal < MAX_SIGNAL_NAM)
    {
        prepare_cmd.output_signal = mode_info->output_signal;
    }
 

    if (mode_info->output & dpu_adapter->support_device)
    {
        prepare_cmd.output = tt_get_last_bit(mode_info->output & dpu_adapter->support_device);   
    }

   

    if ((mode_info->crtc_valid)&& (mode_info->crtc_index < CRTC_NUM))
    {
        prepare_cmd.crtc_index = mode_info->crtc_index;
    }


    //check is new cmd or not
    for (i = 0 ;i < MAX_CACHED_CMD_NUM; i++)
    {
        if (!memcmp(&dpu_adapter->cached_cmd[MODE_CMD][i].mode_cmd, &prepare_cmd, sizeof(struct mode_cmd_t)))
        {
            new_cmd = 0;
            break;
        }
    }

    if (new_cmd)
    {
        for (i = MAX_CACHED_CMD_NUM - 2; i >=0; i--)
        {
            memcpy(&dpu_adapter->cached_cmd[MODE_CMD][i+1],
                  &dpu_adapter->cached_cmd[MODE_CMD][i],
                  sizeof(struct cached_cmd_t));
        }

        //update cached cmd
        cached_cmd = &dpu_adapter->cached_cmd[MODE_CMD][prepare_cmd.cmd_index].mode_cmd;
        memcpy(cached_cmd, &prepare_cmd, sizeof(struct mode_cmd_t));
        dpu_adapter->cached_cmd[MODE_CMD][prepare_cmd.cmd_index].valid = 1;
    }



    //update current mode 
    crtc_info = &dpu_adapter->current_crtc_info[prepare_cmd.crtc_index];
    crtc_info->output = prepare_cmd.output;
    crtc_info->hw_mode.hactive = prepare_cmd.src_xres;
    crtc_info->hw_mode.vactive = prepare_cmd.src_yres;
    crtc_info->hw_mode.hactive = prepare_cmd.dst_xres;
    crtc_info->hw_mode.vactive = prepare_cmd.dst_yres;
    crtc_info->hw_mode.refresh_rate = prepare_cmd.rr;
    crtc_info->hw_mode.output_signal = prepare_cmd.output_signal;

    crtc_info->adjust_mode.hactive = prepare_cmd.dst_xres;
    crtc_info->adjust_mode.vactive = prepare_cmd.dst_yres;

    memcpy(&crtc_mode.hw_mode, &crtc_info->hw_mode, sizeof(struct dpu_display_mode_t));
    memcpy(&crtc_mode.adjust_mode, &crtc_info->adjust_mode, sizeof(struct dpu_display_mode_t));
    crtc_mode.crtc = prepare_cmd.crtc_index;
    
    crtc_mode.hw_mode.output_signal = prepare_cmd.output_signal;

    crtc_mode.hw_mode.bpc = 8;

    encoder_mode.crtc = prepare_cmd.crtc_index;
    encoder_mode.encoder = prepare_cmd.crtc_index;
    encoder_mode.conn = prepare_cmd.output;

    dpu_encoder_dpms(dpu_adapter->dpu_manager, prepare_cmd.crtc_index, DPU_POWER_OFF);
    dpu_crtc_dpms(dpu_adapter->dpu_manager, prepare_cmd.crtc_index, DPU_POWER_OFF);

    dpu_crtc_mode_set(dpu_adapter->dpu_manager, &crtc_mode);
    dpu_encoder_mode_set(dpu_adapter->dpu_manager, &encoder_mode);
    

    dpu_crtc_dpms(dpu_adapter->dpu_manager, prepare_cmd.crtc_index, DPU_POWER_OFF);
    dpu_encoder_dpms(dpu_adapter->dpu_manager, prepare_cmd.crtc_index, DPU_POWER_OFF);


    //dpu_info("tt_get_bit_index(prepare_cmd.output) - 1 is %d\n",tt_get_bit_index(prepare_cmd.output) - 1);

//TODO need get correct index here 
    if (prepare_cmd.output & 0x1)
    {
        index = 0;
    }
    else if (prepare_cmd.output & 0x8000)
    {
        index = 1;
    }
    else if (prepare_cmd.output & 0x10000)
    {
        index = 2;
    }

     
    dpu_adapter->current_output_info[index].power_status = POWER_ON;
    dpu_adapter->current_output_info[index].crtc = &dpu_adapter->current_crtc_info[prepare_cmd.crtc_index];

end:
    return ret;
}



static void plane_handle_trace(struct plane_cmd_t *plane_cmd)
{
    dpu_trace("crtc %d, ci_valid %d surface %d surface_valid %d, plane %d, plane_valid %d  info %d list %d help %d \n",
         plane_cmd->crtc_index,
         plane_cmd->ci_valid,
         plane_cmd->surface_index,
         plane_cmd->si_valid,
         plane_cmd->plane_type,
         plane_cmd->pt_valid,
         plane_cmd->info_cmd,
         plane_cmd->list_cmd,
         plane_cmd->help_cmd);
    
    dpu_trace("src_window (%d,%d,%d,%d) src_valid %d dst_window(%d,%d,%d,%d) dst_valid %d cmd_index %d, cmd_valid %d disable %d, d_v %d\n",
         plane_cmd->src_x,
         plane_cmd->src_y,
         plane_cmd->src_w,
         plane_cmd->src_h,
         plane_cmd->srcxy_valid,
         plane_cmd->dst_x,
         plane_cmd->dst_y,
         plane_cmd->dst_w,
         plane_cmd->dst_h,
         plane_cmd->dstxy_valid,
         plane_cmd->cmd_index,
         plane_cmd->cmd_valid,
         plane_cmd->disable_plane,
         plane_cmd->dp_valid);
    
    dpu_debug("overlay key mode %d mode_valid %d k0 %d  k1 %d  k2 %d  k_valid 0x%x\n",
         plane_cmd->overlay_cmd.mode,
         plane_cmd->overlay_cmd.m_valid,
         plane_cmd->overlay_cmd.k0,
         plane_cmd->overlay_cmd.k1,
         plane_cmd->overlay_cmd.k2,
         plane_cmd->overlay_cmd.k_valid);
}

static void plane_handle_list(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct plane_cmd_t *cached_cmd = NULL;

    dpu_info("list of cached plane cmd: \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[PLANE_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[PLANE_CMD][i].plane_cmd;
                 
            dpu_info("index %d: crtc %d, plane %d, surface %d src(%d,%d,%d,%d) dst(%d,%d,%d,%d) disable %d\n",
                i,
                cached_cmd->crtc_index,
                cached_cmd->plane_type,
                cached_cmd->surface_index,
                cached_cmd->src_x,
                cached_cmd->src_y,
                cached_cmd->src_w,
                cached_cmd->src_h,
                cached_cmd->dst_x,
                cached_cmd->dst_y,
                cached_cmd->dst_w,
                cached_cmd->dst_h,
                cached_cmd->disable_plane);
            dpu_info("          overlay: key mode %d k0 %d k1 %d k2 %d \n",
                cached_cmd->overlay_cmd.mode,
                cached_cmd->overlay_cmd.k0,
                cached_cmd->overlay_cmd.k1,
                cached_cmd->overlay_cmd.k2);  
        }
    }
}

static void plane_handle_help()
{
    u32 i = 0;
    for (i = 0; i < ARRAY_SIZE(plane_options_table); i++)
    {
        dpu_info("%s\n", plane_options_table[i].options_help);
    }

    //add more help info here

    dpu_info("--detail info about [-kv k0 k1 k2]\n");
    dpu_info("  0: Constant_Alpha;                 alpha = k0(0x00~0xFF)\n");
    dpu_info("  1: PS Alpha Blending;              alpha blend type = k0(0: coverage; 1: pre-multiplied), plane value = k1(0x00~0xFF)\n");
    dpu_info("  2: SS/TS Over PS    Color Key;     color key type = k0(0:input A.Color_key Or input B.Color_Key,\n");
    dpu_info("                                                         1:input A.Color_key, 2:input B.Color_Key\n");
    dpu_info("  3: PS    Over SS/TS Color Key;     color key = k0(ex. 0xff0000)\n");
    dpu_info("  4: SS/TS Over PS    Window Key;    kp = k0(0~8), ks = k1(0~8)  NOTE: kp + ks = 8\n");
    dpu_info("  5: SS/TS Over PS    Alpha Key;     kp = k0(0~8), ks = k1(0~8), alpha key = k2(0x00~0xFF)  NOTE: kp + ks = 8\n");
    dpu_info("  6: PS    Over SS/TS Window Key;    kp = k0(0~8), ks = k1(0~8)  NOTE: kp + ks = 8\n");
    dpu_info("  7: PS    Over SS/TS Alpha Key;     kp = k0(0~8), ks = k1(0~8), alpha key = k2(0x00~0xFF)  NOTE: kp + ks = 8\n");
    dpu_info("  8: SS/TS Alpha Blending.           alpha blend type = k0(0: coverage; 1: pre-multiplied), plane value = k1\n\n");
    dpu_info("  9: chroma Key(ps over ss, only support ycbcr422_16);     lower key = k0, upper key = k1\n");

}

static void plane_handle_info(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0, j = 0;
    struct plane_info_t *plane_info = NULL;
    
    for (i = 0; i < CRTC_NUM; i++)
    {
        dpu_info("crtc %d \n",i);
        for (j = 0; j < PLANE_NUM; j++)
        {
            plane_info = &dpu_adapter->current_plane_info[i][j];

            if (plane_info->plane_state == PLANE_DISABLED || !plane_info->surface)
            {
                dpu_info("      plane %d is disabled\n",j);
            }
            else
            {
                dpu_info("      plane %d :src(%d,%d,%d,%d) dst(%d,%d,%d,%d) g_addr 0x%08x c_addr 0x%8x size (%d,%d) pitch %d, fmt %s, compress %d si %d\n",
                    plane_info->plane_type,
                    plane_info->src_x,
                    plane_info->src_y,
                    plane_info->src_w,
                    plane_info->src_h,
                    plane_info->dst_x,
                    plane_info->dst_y,
                    plane_info->dst_w,
                    plane_info->dst_h,
                    plane_info->surface->gpu_addr,
                    plane_info->surface->cpu_addr,
                    plane_info->surface->width,
                    plane_info->surface->height,
                    plane_info->surface->pitch,
                    plane_info->surface->format_name,
                    plane_info->surface->compressed,
                    plane_info->surface->index);
        

            if (plane_info->plane_type != PRIMARY_PLANE)
            {
                dpu_info("            overlay info : mode %s \n", g_key_mode_string[plane_info->overlay_info.mode]);
                switch(plane_info->overlay_info.mode)
                {
                    case CONSTANT_ALPHA:
                        dpu_info("            alpha: 0x%x, invert_alpha %d\n",
                        plane_info->overlay_info.constant_alpha_blending.constant_alpha,
                        plane_info->overlay_info.constant_alpha_blending.invert);
                        if (plane_info->overlay_info.constant_alpha_blending.plane_blending)
                        {
                            dpu_info("            with plane bending: 0x%x \n",
                            plane_info->overlay_info.constant_alpha_blending.plane_value);
                        }
                        else
                        {
                            dpu_info("            with no plane bneding\n");
                        }

                        break;
                    case PS_ALPHA_BLENDING:
                    case SS_ALPHA_BLENDING:
                        dpu_info("            %s, use %s alpha, invert_alpha %d\n",
                        plane_info->overlay_info.alpha_blending.premul_blend ? "premult":"coverage",
                        plane_info->overlay_info.alpha_blending.use_ps_alpha ? "PS" : "SS",
                        plane_info->overlay_info.alpha_blending.invert_alpha);
                        if (plane_info->overlay_info.alpha_blending.plane_blending)
                        {
                            dpu_info("            with plane bending: 0x%x\n",
                            plane_info->overlay_info.alpha_blending.plane_value);
                        }
                        else
                        {
                            dpu_info("            with no plane bneding\n");
                        }
                        break;
                    case POS_COLOR_KEY:
                    case SOP_COLOR_KEY:
                    //TODO: type ?
                        dpu_info("            type %d, %s color\n",
                        plane_info->overlay_info.color_key.type,
                        plane_info->overlay_info.color_key._10bit_color ? "10bit": "8bit");
                        break;
                    case SOP_WINDOW_KEY:
                    case POS_WINDOW_KEY:

                        dpu_info("            kp %d, ks %d\n",
                        plane_info->overlay_info.window_key.kp,
                        plane_info->overlay_info.window_key.ks);
                        break;
                    case  SOP_ALPHA_KEY:
                    case  POS_ALPHA_KEY:

                        dpu_info("            kp %d ks %d\n",
                        plane_info->overlay_info.alpha_key.kp,
                        plane_info->overlay_info.alpha_key.ks);
                        break;
                    case  CHROMA_KEY:

                        dpu_info("            lower bound 0x%x, upper bound 0x%x",
                        plane_info->overlay_info.chroma_key.lower_bound,
                        plane_info->overlay_info.chroma_key.upper_bound);
                        break;
                    default:

                        dpu_error("unknow blending mode !!!\n");
                        break;
                    }
                }
            }
        }
    }
}

static TT_STATUS plane_handle(struct dpu_adapter_t *dpu_adapter, struct plane_cmd_t *plane_cmd)
{
    TT_STATUS ret = TT_PASS;
    struct plane_cmd_t *cached_cmd = NULL;
    struct plane_cmd_t prepare_cmd = {0};
    struct plane_info_t *plane_info = NULL;
//    struct dpu_plane_t plane_set ={0};
    struct surface_info_t *surface = NULL;
    u32 new_cmd = 1;
    u32 need_page_flip = 1;
    i32 i = 0, j = 0;

    plane_handle_trace(plane_cmd);

    if (dpu_adapter->test_domain | TEST_DOS_ONLY)
    {
        dpu_info("de is not available\n");
        goto end;
    }

/***
    CBIOS_SURFACE_ATTRIB  stream_attr = {0};
    CBIOS_WINDOW_PARA  src_win = {0};
    CBIOS_WINDOW_PARA  dst_win = {0};
    CBIOS_OVERLAY_INFO   overlay = {0};
    CBIOS_STREAM_PARA   stream_para = {0};
    CBIOS_UPDATE_FRAME_PARA  update_frame = {0};

 
    if (plane_cmd->list_cmd)
    {
        plane_handle_list(dpu_adapter);
        ret = TT_PASS;
        goto end;
    }

    if (plane_cmd->help_cmd)
    {
        plane_handle_help();
        ret = TT_PASS;
        goto end;
        
    }

    if (plane_cmd->info_cmd)
    {
        plane_handle_info(dpu_adapter);
        ret = TT_PASS;
        goto end;
    }

    prepare_cmd.cmd_index = 0;
    prepare_cmd.crtc_index = 0;
    prepare_cmd.surface_index = 0;
    prepare_cmd.plane_type = PRIMARY_PLANE;
    prepare_cmd.src_x = 0;
    prepare_cmd.src_y = 0;
    prepare_cmd.dst_x = 0;
    prepare_cmd.dst_y = 0;

    prepare_cmd.src_w = 640;
    prepare_cmd.src_h = 480;

    prepare_cmd.dst_w = 640;
    prepare_cmd.dst_h = 480;

    prepare_cmd.disable_plane = 0;
    prepare_cmd.overlay_cmd.k_valid = 0;
    prepare_cmd.overlay_cmd.m_valid = 0;

    new_cmd = 1;
    if (plane_cmd->cmd_valid && plane_cmd->cmd_index < MAX_CACHED_CMD_NUM && 
        dpu_adapter->cached_cmd[PLANE_CMD][plane_cmd->cmd_index].valid)
    {
        cached_cmd = &dpu_adapter->cached_cmd[PLANE_CMD][plane_cmd->cmd_index].plane_cmd;

        memcpy(&prepare_cmd, cached_cmd, sizeof(struct plane_cmd_t));

        new_cmd = 0;
    }

    if (plane_cmd->ci_valid )
    {
        if (plane_cmd->crtc_index < CRTC_NUM)
        {
            prepare_cmd.crtc_index = plane_cmd->crtc_index;
        }
        else
        {
            dpu_error("input crtc index is invalid ,please help check\n");
            need_page_flip = 0;
        }
    }

    if (plane_cmd->dp_valid)
    {
        prepare_cmd.disable_plane = plane_cmd->disable_plane ? 1: 0;
    }

    if (plane_cmd->si_valid )
    {
        if (plane_cmd->surface_index < MAX_SURFACE_NUM && dpu_adapter->surface_manager.surfaces[plane_cmd->surface_index].valid)
        {
            prepare_cmd.surface_index = plane_cmd->surface_index;           
        }
        else
        {
            dpu_error("input surface index is invalid ,please help check\n");
            need_page_flip = 0;
        }
    }
    surface = &dpu_adapter->surface_manager.surfaces[prepare_cmd.surface_index].surface; 

    prepare_cmd.src_w = surface->width;
    prepare_cmd.src_h = surface->height;

    prepare_cmd.dst_w = surface->width;
    prepare_cmd.dst_h = surface->height;

    if (plane_cmd->srcxy_valid)
    {
        prepare_cmd.src_x = plane_cmd->src_x;
        prepare_cmd.src_y = plane_cmd->src_y;
    }

    prepare_cmd.src_w = plane_cmd->src_w ?  plane_cmd->src_w : prepare_cmd.src_w;
    prepare_cmd.src_h = plane_cmd->src_h ?  plane_cmd->src_h : prepare_cmd.src_h;

    if (plane_cmd->dstxy_valid)
    {
        prepare_cmd.dst_x = plane_cmd->dst_x;
        prepare_cmd.dst_y = plane_cmd->dst_y;
    }

    prepare_cmd.dst_w = plane_cmd->dst_w ? plane_cmd->dst_w : prepare_cmd.dst_w;
    prepare_cmd.dst_h = plane_cmd->dst_h ? plane_cmd->dst_h : prepare_cmd.dst_h;


    if (plane_cmd->pt_valid)
    {
        if(plane_cmd->plane_type < PLANE_NUM )
        {
            prepare_cmd.plane_type = plane_cmd->plane_type;
        }
        else
        {
            dpu_error("input plane type is invalid ,please help check\n");
            need_page_flip = 0;
        }
    }

    if (plane_cmd->overlay_cmd.m_valid)
    {
        if (plane_cmd->overlay_cmd.mode < MAX_KEY_MODE)
        {
            prepare_cmd.overlay_cmd.m_valid = 1;
            prepare_cmd.overlay_cmd.mode = plane_cmd->overlay_cmd.mode;
        }
        else
        {
            dpu_error("input overlay key mode is invalid ,please help check\n");
            need_page_flip = 0;
        }       
    }

    
    if (plane_cmd->overlay_cmd.k_valid)
    {
        prepare_cmd.overlay_cmd.k0 = plane_cmd->overlay_cmd.k0;
        prepare_cmd.overlay_cmd.k1 = plane_cmd->overlay_cmd.k1;
        prepare_cmd.overlay_cmd.k2 = plane_cmd->overlay_cmd.k2;
        prepare_cmd.overlay_cmd.k_valid = 1;
    }

    //check is new cmd or not
    for (i = 0 ;i < MAX_CACHED_CMD_NUM; i++)
    {
        if (!memcmp(&dpu_adapter->cached_cmd[MODE_CMD][i].plane_cmd, &prepare_cmd, sizeof(struct plane_cmd_t)))
        {
            new_cmd = 0;
            break;
        }
    }

    //update cached cmd
    if (new_cmd && !prepare_cmd.disable_plane)
    {
        for (i = MAX_CACHED_CMD_NUM - 2; i >=0; i--)
        {
            memcpy(&dpu_adapter->cached_cmd[PLANE_CMD][i+1],
                   &dpu_adapter->cached_cmd[PLANE_CMD][i],
                   sizeof(struct cached_cmd_t));
        }

        cached_cmd = &dpu_adapter->cached_cmd[PLANE_CMD][prepare_cmd.cmd_index].plane_cmd;
        memcpy(cached_cmd, &prepare_cmd, sizeof(struct plane_cmd_t));
        dpu_adapter->cached_cmd[PLANE_CMD][prepare_cmd.cmd_index].valid = 1;
    }


    //surface = &dpu_adapter->surface_manager.surfaces[prepare_cmd.surface_index].surface; 
    if (need_page_flip)
    {
        //update current plane info
        plane_info = &dpu_adapter->current_plane_info[prepare_cmd.crtc_index][prepare_cmd.plane_type];
        plane_info->src_x = prepare_cmd.src_x;
        plane_info->src_y = prepare_cmd.src_y;
        plane_info->src_w = prepare_cmd.src_w;
        plane_info->src_h = prepare_cmd.src_h;
        plane_info->dst_x = prepare_cmd.dst_x;
        plane_info->dst_y = prepare_cmd.dst_y;
        plane_info->dst_w = prepare_cmd.dst_w;
        plane_info->dst_h = prepare_cmd.dst_h;

        //plane_info.plane_state = prepare_cmd.disable_plane;
        plane_info->surface = surface;



        update_frame.Size = sizeof(update_frame);
        update_frame.IGAIndex = prepare_cmd.crtc_index;

        if (prepare_cmd.plane_type == CBIOS_STREAM_PS)
        {
            update_frame.pPStreamPara= &stream_para;
        }
        else if (prepare_cmd.plane_type == CBIOS_STREAM_SS)
        {
            update_frame.pSStreamPara= &stream_para;
        }
        else 
        {
            update_frame.pTStreamPara= &stream_para;
        }
            

        stream_para.StreamType = prepare_cmd.plane_type;

        if (plane_info->plane_state == PLANE_ENABLED)
        {
            if (prepare_cmd.disable_plane)
            {
                stream_para.FlipMode = CBIOS_STREAM_FLIP_WITH_DISABLE;
            }
            else
            {
                stream_para.FlipMode = CBIOS_STREAM_FLIP_ONLY;
            }
        }
        else
        {
            if (prepare_cmd.disable_plane)
            {
                stream_para.FlipMode = CBIOS_STREAM_FLIP_WITH_DISABLE;
            }
            else
            {
                stream_para.FlipMode= CBIOS_STREAM_FLIP_WITH_ENABLE;
            }
        }

        stream_para.pSurfaceAttrib = &stream_attr;
        stream_para.pSrcWindowPara = &src_win;
        stream_para.pWindowPara = &dst_win;

        if (stream_para.FlipMode != CBIOS_STREAM_FLIP_WITH_DISABLE)
        {
            stream_attr.StartAddr = surface->gpu_addr;
        }
        else
        {
            stream_attr.StartAddr = 0x12345680;
        }

        stream_attr.SurfaceFmt = surface->format;
        stream_attr.SurfaceWidth = surface->width;
        stream_attr.SurfaceHeight = surface->height;
        stream_attr.BitCount = surface->bit_cnt;
  
        stream_attr.Pitch = surface->pitch;
        stream_attr.bCompress =  0;
        stream_attr.bTiled = 0;

        src_win.PositionX = prepare_cmd.src_x ;
        src_win.PositionY = prepare_cmd.src_y ;
        src_win.WinSizeX = prepare_cmd.src_w;
        src_win.WinSizeY = prepare_cmd.src_h;

        dst_win.PositionX = prepare_cmd.dst_x;
        dst_win.PositionY = prepare_cmd.dst_y;

        dst_win.WinSizeX = prepare_cmd.dst_w;
        dst_win.WinSizeY = prepare_cmd.dst_h;

        if(stream_para.StreamType != CBIOS_STREAM_PS)
        {
            stream_para.pOverlayInfo = &overlay;
            overlay.KeyMode = CBIOS_WINDOW_KEY;
            overlay.WindowKey.Kp_Kmix= 0;
            overlay.WindowKey.Ks_Kt = 8;
        }

        plane_info->plane_state = prepare_cmd.disable_plane;

        ret =  (CBiosUpdateFrame(dpu_adapter->dpu_manager, &update_frame) == CBIOS_OK) ? TT_PASS : TT_FAIL;
    }

end:
    return ret;


        
#if 0
        //get page flip info
        plane_set.crtc = prepare_cmd.crtc_index;
        plane_set.plane = prepare_cmd.plane_type;
        plane_set.src_x = prepare_cmd.src_x;
        plane_set.src_y = prepare_cmd.src_y;
        plane_set.src_w = prepare_cmd.src_w;
        plane_set.src_h = prepare_cmd.src_h;
        plane_set.dst_x = prepare_cmd.dst_x;
        plane_set.dst_y = prepare_cmd.dst_y;
        plane_set.dst_w = prepare_cmd.dst_w;
        plane_set.dst_h = prepare_cmd.dst_h;

     
        plane_set.surface.addr = surface->gpu_addr;
        plane_set.surface.bit_cnt = surface->bit_cnt;
        plane_set.surface.pitch = surface->pitch;
        plane_set.surface.width = surface->width;
        plane_set.surface.height = surface->height;
        plane_set.surface.aligned_width = surface->aligned_width;
        plane_set.surface.size = surface->size;
        plane_set.surface.range_type = surface->range_type;
        plane_set.surface.format = surface->format;  //the define of format is same 
        plane_set.surface.compressed = surface->compressed;


        if (plane_info->plane_state == PLANE_ENABLED)
        {
            if (prepare_cmd.disable_plane)
            {
                plane_set.flag = DPU_DISABLE_FLIP;
            }
            else
            {
                plane_set.flag = DPU_PAGE_FLIP_ONLY;
            }
        }
        else
        {
            if (prepare_cmd.disable_plane)
            {
                plane_set.flag = DPU_DISABLE_FLIP;
            }
            else
            {
                plane_set.flag = DPU_ENABLE_FLIP;
            }
        }
        //update plane state here
        plane_info->plane_state = prepare_cmd.disable_plane;

        //update && get overlay info 
        if (prepare_cmd.overlay_cmd.m_valid)
        {
            switch(prepare_cmd.overlay_cmd.mode)
            {
                case CONSTANT_ALPHA:
                    plane_info->overlay_info.constant_alpha_blending.constant_alpha = prepare_cmd.overlay_cmd.k0;
                    plane_info->overlay_info.mode = CONSTANT_ALPHA;
                    plane_set.overlay.constant_alpha_blending.constant_alpha = prepare_cmd.overlay_cmd.k0;
                    plane_set.overlay.mode = DPU_CONSTANT_ALPHA;
                    break;
                case PS_ALPHA_BLENDING:
                    plane_info->overlay_info.alpha_blending.premul_blend = prepare_cmd.overlay_cmd.k0 ? 1: 0;
                    plane_info->overlay_info.mode = PS_ALPHA_BLENDING;
                    plane_info->overlay_info.alpha_blending.plane_value = prepare_cmd.overlay_cmd.k1 &0xff;
                    plane_set.overlay.alpha_blending.premul_blend = prepare_cmd.overlay_cmd.k0 ? 1: 0;
                    plane_set.overlay.mode = DPU_PS_ALPHA_BLENDING;
                    plane_set.overlay.alpha_blending.plane_value = prepare_cmd.overlay_cmd.k1 &0xff;
                    break;
                case SOP_COLOR_KEY:
                    plane_info->overlay_info.mode = SOP_COLOR_KEY;
                    plane_info->overlay_info.color_key.type = prepare_cmd.overlay_cmd.k0;
                    plane_info->overlay_info.color_key._10bit_color = prepare_cmd.overlay_cmd.k1 ? 1:0;
                    plane_set.overlay.mode = DPU_SOP_COLOR_KEY;
                    plane_set.overlay.color_key.type = prepare_cmd.overlay_cmd.k0;
                    plane_set.overlay.color_key._10bit_color = prepare_cmd.overlay_cmd.k1 ? 1: 0;
                    break;
                case POS_COLOR_KEY:
                    plane_info->overlay_info.mode = POS_COLOR_KEY;
                    plane_info->overlay_info.color_key.type = prepare_cmd.overlay_cmd.k0;
                    plane_info->overlay_info.color_key._10bit_color = prepare_cmd.overlay_cmd.k1 ? 1:0;
                    plane_set.overlay.mode = DPU_POS_COLOR_KEY;
                    plane_set.overlay.color_key.type = prepare_cmd.overlay_cmd.k0;
                    plane_set.overlay.color_key._10bit_color = prepare_cmd.overlay_cmd.k1 ? 1: 0;
                    break;
                case SOP_WINDOW_KEY:
                    plane_info->overlay_info.mode = SOP_WINDOW_KEY;
                    plane_info->overlay_info.window_key.kp = prepare_cmd.overlay_cmd.k0;
                    plane_info->overlay_info.window_key.ks = prepare_cmd.overlay_cmd.k1;
                    plane_set.overlay.mode = DPU_SOP_WINDOW_KEY;
                    plane_set.overlay.window_key.kp = prepare_cmd.overlay_cmd.k0;
                    plane_set.overlay.window_key.ks = prepare_cmd.overlay_cmd.k1;
                    break;
                case SOP_ALPHA_KEY:
                    plane_info->overlay_info.mode = SOP_WINDOW_KEY;
                    plane_info->overlay_info.alpha_key.kp = prepare_cmd.overlay_cmd.k0;
                    plane_info->overlay_info.alpha_key.ks = prepare_cmd.overlay_cmd.k1;
                    plane_set.overlay.mode = DPU_SOP_WINDOW_KEY;
                    plane_set.overlay.alpha_key.kp = prepare_cmd.overlay_cmd.k0;
                    plane_set.overlay.alpha_key.ks = prepare_cmd.overlay_cmd.k1;
                    break;
                case POS_WINDOW_KEY:
                    plane_info->overlay_info.mode = POS_WINDOW_KEY;
                    plane_info->overlay_info.window_key.kp = prepare_cmd.overlay_cmd.k0;
                    plane_info->overlay_info.window_key.ks = prepare_cmd.overlay_cmd.k1;
                    plane_set.overlay.mode = DPU_POS_WINDOW_KEY;
                    plane_set.overlay.window_key.kp = prepare_cmd.overlay_cmd.k0;
                    plane_set.overlay.window_key.ks = prepare_cmd.overlay_cmd.k1;
                    break;
                case POS_ALPHA_KEY:
                    plane_info->overlay_info.mode = POS_ALPHA_KEY;
                    plane_info->overlay_info.alpha_key.kp = prepare_cmd.overlay_cmd.k0;
                    plane_info->overlay_info.alpha_key.ks = prepare_cmd.overlay_cmd.k1;
                    plane_set.overlay.mode = DPU_POS_ALPHA_KEY;
                    plane_set.overlay.alpha_key.kp = prepare_cmd.overlay_cmd.k0;
                    plane_set.overlay.alpha_key.ks = prepare_cmd.overlay_cmd.k1;
                    
                    break;
                case SS_ALPHA_BLENDING:
                    plane_info->overlay_info.alpha_blending.premul_blend = prepare_cmd.overlay_cmd.k0 ? 1: 0;
                    plane_info->overlay_info.mode = SS_ALPHA_BLENDING;
                    plane_info->overlay_info.alpha_blending.plane_value = prepare_cmd.overlay_cmd.k1 &0xff;
                    plane_set.overlay.alpha_blending.premul_blend = prepare_cmd.overlay_cmd.k0 ? 1: 0;
                    plane_set.overlay.mode = DPU_SS_ALPHA_BLENDING;
                    plane_set.overlay.alpha_blending.plane_value = prepare_cmd.overlay_cmd.k1 &0xff;
                    
                    break;
                case CHROMA_KEY:
                    plane_info->overlay_info.chroma_key.lower_bound = prepare_cmd.overlay_cmd.k0;
                    plane_info->overlay_info.chroma_key.upper_bound = prepare_cmd.overlay_cmd.k1;
                    plane_info->overlay_info.mode = CHROMA_KEY;
                    plane_set.overlay.mode = DPU_CHROMA_KEY;
                    plane_set.overlay.chroma_key.lower_bound = prepare_cmd.overlay_cmd.k0;
                    plane_set.overlay.chroma_key.upper_bound = prepare_cmd.overlay_cmd.k1;
                    
                    break;
                default:
                    dpu_info("shouldn't be here , invalid overlay key mode !!!\n");
                    
                    break;
            }
        
        }


        if (DPU_OK != dpu_update_plane(dpu_adapter->dpu_manager, &plane_set))
        {
            dpu_error("update plane failed ,please help check \n");
            ret = TT_FAIL;
            goto end;
        }


    }

    ret = TT_PASS;
#endif
***/
end:
    return ret;
}


static void surface_handle_trace(struct surface_cmd_t *surface_cmd)
{
    dpu_trace("surface_index: %d si_valid %d, width %d height %d, alpha 0x%x, a_valid %d, pattern %d, format %d\n",
        surface_cmd->surface_index,
        surface_cmd->si_valid,
        surface_cmd->width,
        surface_cmd->height,
        surface_cmd->alpha,
        surface_cmd->alpha_valid,
        surface_cmd->pattern,
        surface_cmd->format);
    dpu_trace("no_draw %d, premult %d, compressed %d, list_cmd %d, info_cmd %d help %d, cmd_index %d c_valid %d\n",
        surface_cmd->no_draw,
        surface_cmd->premult,
        surface_cmd->compressed,
        surface_cmd->list_cmd,
        surface_cmd->info_cmd,
        surface_cmd->help_cmd,
        surface_cmd->cmd_index,
        surface_cmd->cmd_valid);

}


static void surface_handle_info(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct surface_info_t *surface = NULL;
    
    dpu_info("\nTotal surface num is %d\n", dpu_adapter->surface_manager.num);


    for (i = 0; i < MAX_SURFACE_NUM; i ++)
    {
        if (dpu_adapter->surface_manager.surfaces[i].valid == 0)
        {
            continue;
        }
        surface = &dpu_adapter->surface_manager.surfaces[i].surface;

        dpu_info("surface %d: w %4d h %4d pitch %4d  %s,  %s, gpu_addr 0x%8x cpu_addr 0x%8x compress %d, do_premult %d\n",
            i,
            surface->width,
            surface->height,
            surface->pitch,
            surface->format_name,
            g_color_pattern_string[surface->pattern],
            surface->gpu_addr,
            surface->cpu_addr,
            surface->compressed,
            surface->need_premult);
    }

     dpu_info("\n");
}

static void surface_handle_help()
{
    u32 i = 0;
    for (i = 0; i < ARRAY_SIZE(surface_options_table); i++)
    {
        dpu_info("%s\n", surface_options_table[i].options_help);
    }

    dpu_info("--format index:\n");
    for (i = 1; i < ARRAY_SIZE(g_format_info_string); i++)
    {
        if (i % 10 == 0)
        {
            dpu_info("\n");
        }

        dpu_info("%d %s,",i,g_format_info_string[i].format_name);
    }

    dpu_info("\n");
}

static void surface_handle_list(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct surface_cmd_t *cached_cmd = NULL;

    dpu_info("list of cached surface cmd (just cache create cmd): \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[SURFACE_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[SURFACE_CMD][i].surface_cmd;
                 
            dpu_info("index %d: width %d height %d aplha %d , pattern %s, format %s, no_draw %d, premult %d, compress %d\n",
                i,
                cached_cmd->width,
                cached_cmd->height,
                cached_cmd->alpha,
                g_color_pattern_string[cached_cmd->pattern],
                g_format_info_string[cached_cmd->format].format_name,
                cached_cmd->no_draw,
                cached_cmd->premult,
                cached_cmd->compressed);

        }
    }
}
#if 0

static struct surface_info_t* alloc_surface(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;

    struct surface_info_t *surface = NULL;


    if (dpu_adapter->surface_manager.num >= MAX_SURFACE_NUM)
    {

        dpu_info("please increase macro MAX_SURFACE_NUM \n");
        surface = NULL;
        return surface;
    }

    for (i = 0; i < MAX_SURFACE_NUM; i ++)
    {
        if (dpu_adapter->surface_manager.surfaces[i].valid == 0)
        {
            surface = &dpu_adapter->surface_manager.surfaces[i].surface;
            dpu_info("create new surface, it's index is %d\n",i);
            break;
        }
    }

    if (i == MAX_SURFACE_NUM)
    {
        dpu_error("No enough surface id, please help check\n");
        surface = NULL;
    }
    else
    {
        dpu_adapter->surface_manager.surfaces[i].valid = 1;
        dpu_adapter->surface_manager.num++;
    }

    return surface;

}

static TT_STATUS free_surface(struct dpu_adapter_t *dpu_adapter, u32 index)
{

    if (index >= MAX_SURFACE_NUM || dpu_adapter->surface_manager.surfaces[index].valid == 0)
    {
        dpu_error("%s:  invalid para \n",__func__);
        return TT_FAIL;
    }

    dpu_adapter->surface_manager.surfaces[index].valid = 0;
    memset(&dpu_adapter->surface_manager.surfaces[index].surface, 0 , sizeof(struct surface_info_t));
    dpu_adapter->surface_manager.num--;
    
    return TT_PASS;
}


TT_STATUS  tt_create_surface(struct dpu_adapter_t *dpu_adapter, struct surface_cmd_t *surface_cmd)
{
    u32  width = 0, aligned_width = 0;
    u32  size = 0;
    TT_STATUS status = TT_PASS;
    struct surface_info_t  *surface = NULL;
    u32 offset = 0;

    if (surface_cmd->width == 0 || surface_cmd->height == 0 || surface_cmd->format >= FORMAT_NUM)
    {
        status = TT_INVALID_PARAM;
        return status;
    }

    surface = alloc_surface(dpu_adapter);

    if (!surface)
    {
        status = TT_FAIL;
        goto end_surface;
    }

    surface->width = surface_cmd->width;
    surface->height = surface_cmd->height;
    surface->format = surface_cmd->format;
    surface->compressed = surface_cmd->compressed;
    surface->need_premult = surface_cmd->premult;
    surface->pattern = surface_cmd->pattern;
    surface->alpha = surface_cmd->alpha;
    surface->aligned_width = tt_align(surface->width, dpu_adapter->width_alignment);


    surface->bit_cnt = g_format_info[surface->format].bit_cnt;
    memcpy(surface->format_name, g_format_info[surface->format].format_name, FORMAT_NAME_LENGTH);
    
    surface->size = surface->aligned_width * surface->height * surface->bit_cnt / 8;
    surface->pitch = surface->aligned_width * surface->bit_cnt / 8;


    return status;

end_video_mem:

    free_surface(dpu_adapter, surface->index);
    
end_surface:
    
    return status;
    
}
#endif

static TT_STATUS surface_handle(struct dpu_adapter_t *dpu_adapter, struct surface_cmd_t *surface_cmd)
{
    TT_STATUS ret = TT_PASS;
    struct surface_cmd_t prepare_cmd = {0};
    struct surface_cmd_t *cached_cmd = NULL;

    u32 new_cmd = 1;
    u32 need_create = 1;
    i32 i = 0;


    surface_handle_trace(surface_cmd);

    if (surface_cmd->info_cmd)
    {
        surface_handle_info(dpu_adapter);
        goto end;
    }

    if (surface_cmd->help_cmd)
    {
        surface_handle_help();
        goto end;
    }

    if (surface_cmd->list_cmd)
    {
        surface_handle_list(dpu_adapter);
        goto end;
    }

    if (surface_cmd->si_valid)
    {
        free_surface(dpu_adapter, surface_cmd->surface_index);
        goto end;
    }

    //create new surface
    //default value
    prepare_cmd.cmd_index = 0;
    prepare_cmd.width = 1920;
    prepare_cmd.height = 1080;
    prepare_cmd.alpha = 0xff;
    prepare_cmd.pattern = PATTERN_COLOR_BAR;
    prepare_cmd.compressed = 0;
    prepare_cmd.no_draw = 0;
    prepare_cmd.premult = 0;
    prepare_cmd.format = FORMAT_A8R8G8B8;
   
    if (surface_cmd->cmd_valid && surface_cmd->cmd_index < MAX_CACHED_CMD_NUM &&
        dpu_adapter->cached_cmd[SURFACE_CMD][surface_cmd->cmd_index].valid)
    {
        new_cmd = 0;
        cached_cmd = &dpu_adapter->cached_cmd[SURFACE_CMD][surface_cmd->cmd_index].surface_cmd;
        memcpy(&prepare_cmd, cached_cmd, sizeof(struct surface_cmd_t));
    }
    
   

    prepare_cmd.width = surface_cmd->width ? surface_cmd->width : prepare_cmd.width;
    prepare_cmd.height = surface_cmd->height ? surface_cmd->height : prepare_cmd.height;

    if (surface_cmd->alpha_valid)
    {
        prepare_cmd.alpha = surface_cmd->alpha & 0xff;
    }

    if (surface_cmd->format !=  FORMAT_INVALID)
    {
        if (surface_cmd->format < FORMAT_NUM)
        {
            prepare_cmd.format = surface_cmd->format;
        }
        else
        {
            dpu_error("invalid surface format, please help check \n");
            need_create = 0;
        }
    }

    if (surface_cmd->pattern != PATTERN_INVALID)
    {
        if (surface_cmd->pattern < PATTERN_NUM)
        {
            prepare_cmd.pattern = surface_cmd->pattern;
        }
        else
        {
            dpu_error("invalid color pattern ,please help check \n");
            need_create = 0;
        }
    }

    prepare_cmd.no_draw = surface_cmd->no_draw ? 1 : 0;
    prepare_cmd.compressed = surface_cmd->compressed ? 1 : 0;



    for (i = 0 ;i < MAX_CACHED_CMD_NUM; i++)
    {
        if (!memcmp(&dpu_adapter->cached_cmd[SURFACE_CMD][i].surface_cmd, &prepare_cmd, sizeof(struct surface_cmd_t)))
        {
            new_cmd = 0;
            break;
        }
    }
 

    if (new_cmd)
    {
        for (i = MAX_CACHED_CMD_NUM - 2; i >=0; i--)
        {
            memcpy(&dpu_adapter->cached_cmd[SURFACE_CMD][i+1],
                  &dpu_adapter->cached_cmd[SURFACE_CMD][i],
                  sizeof(struct cached_cmd_t));
        }

        //update cache cmd
        cached_cmd = &dpu_adapter->cached_cmd[SURFACE_CMD][prepare_cmd.cmd_index].surface_cmd;
        memcpy(cached_cmd, &prepare_cmd, sizeof(struct surface_cmd_t));
        dpu_adapter->cached_cmd[SURFACE_CMD][prepare_cmd.cmd_index].valid = 1;
    }

    if (need_create)
    {

        //create surface

        dpu_info("create surface \n");
        ret = tt_create_surface(dpu_adapter, &prepare_cmd);
    }

end:
    return ret;
    
}

static void device_handle_trace(struct device_cmd_t *device_cmd)
{
    dpu_trace("output 0x%x, disable %d, lr %d lc %d async_clck %d, enhanced_frame_mode %d\n",
        device_cmd->output,
        device_cmd->disable,
        device_cmd->link_rate,
        device_cmd->lane_count,
        device_cmd->async_clk,
        device_cmd->enhanced_frame_mode
        );


    dpu_trace("bit_depth %d, color_fromat %d, cea %d, coef %d, modelist %d, info %d, list %d, help %d, cmd %d cmd valid %d\n",
        device_cmd->bit_depth,
        device_cmd->color_format,
        device_cmd->cea,
        device_cmd->coef,
        device_cmd->modelist_cmd,
        device_cmd->info_cmd,
        device_cmd->list_cmd,
        device_cmd->help_cmd,
        device_cmd->cmd_index,
        device_cmd->cmd_valid);
}

static void device_handle_help()
{
    u32 i = 0;
    for (i = 0; i < ARRAY_SIZE(device_options_table); i++)
    {
        dpu_info("%s\n", device_options_table[i].options_help);
    }

}

static void device_handle_info(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct output_info_t *output = NULL;
    
    dpu_info("support device 0x%x \n", dpu_adapter->support_device);

    for (i = 0; i < PORT_NUM; i++)
    {
        output = &dpu_adapter->current_output_info[i];
        if (output->connect_status == DISCONNECTED_STATUS)
        {
            dpu_info("output 0x%x disconnected\n",output->device);
            continue;
        }

        if (output->power_status == POWER_OFF)
        {
            dpu_info("output 0x%x is power off\n", output->device);
            continue;
        }

        if (output->crtc)
        {
            dpu_info("crtc %d --- output 0x%x num_modes is %d, lr %d lc %d async_clck %d, enhanced_frame_mode %d\n",
                output->crtc->index,
                output->device,
                output->mode_list.num,
                output->link_rate,
                output->lane_count,
                output->async_clk,
                output->enhanced_frame_mode);

            dpu_info("             bit_depth %d, color_fromat %d, cea %d, coef %d\n",
                output->bit_depth,
                output->color_format,
                output->cea,
                output->coef);
        }
        else
        {
            dpu_info("device 0x%x is not active \n",output->device);
        }
    }
}


static void device_handle_list(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct device_cmd_t *cached_cmd = NULL;

    dpu_info("list of cached device cmd: \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[DEVICE_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[DEVICE_CMD][i].device_cmd;
                 
            dpu_info("index %d: output 0x%x, lr %d, lc %d, async_clock %d, frame_mode %d, bit_depth %d color_format %d cea %d coef %d\n",
                    i,
                    cached_cmd->output,
                    cached_cmd->link_rate,
                    cached_cmd->lane_count,
                    cached_cmd->async_clk,
                    cached_cmd->enhanced_frame_mode,
                    cached_cmd->bit_depth,
                    cached_cmd->color_format,
                    cached_cmd->cea,
                    cached_cmd->coef);

        }
    }
}


static void print_mode_list(struct dpu_adapter_t *dpu_adapter, u32 output)
{
    u32 i = 0,j = 0;

    for (i = 0; i < PORT_NUM; i++)
    {
        if (output == dpu_adapter->current_output_info[i].device)
        {
            dpu_info("mode num of 0x%x is %d \n",output,dpu_adapter->current_output_info[i].mode_list.num);

            for (j = 0; j < dpu_adapter->current_output_info[i].mode_list.num; j++)
            {
                dpu_info("%d: %d x %d @ %d\n",
                    j,
                    dpu_adapter->current_output_info[i].mode_list.modes[j].hactive,
                    dpu_adapter->current_output_info[i].mode_list.modes[j].vactive,
                    dpu_adapter->current_output_info[i].mode_list.modes[j].refresh_rate);
            }
        }
    }
}
//Éè¼ÆÒ»¸ö×¨ÃÅµÄdpu º¯ÊýÀ´×ödevice ²ÎÊýµÄ´«µÝ£¬ ºÍdevice on off ²¢ÁÐ´æÔÚ£ ×öcts  test ?
static TT_STATUS device_handle(struct dpu_adapter_t *dpu_adapter, struct device_cmd_t *device_cmd)
{
    TT_STATUS ret = TT_PASS;
    u32 new_cmd = 1;
    u32 need_set_device = 1;

 //   struct dpu_device_set_t  device_set = {0};
    i32 i = 0;

    struct device_cmd_t prepare_cmd = {0};
    struct device_cmd_t *cached_cmd = NULL;

    device_handle_trace(device_cmd);

    if (dpu_adapter->test_domain | TEST_DOS_ONLY)
    {
        dpu_info("de is not available\n");
        goto end;
    }

    if (device_cmd->info_cmd)
    {
        device_handle_info(dpu_adapter);
        goto end;
    }

    if (device_cmd->help_cmd)
    {
        device_handle_help();
        goto end;
    }

    if (device_cmd->list_cmd)
    {
        device_handle_list(dpu_adapter);
        goto end;
    }

    if (device_cmd->modelist_cmd)
    {
        print_mode_list(dpu_adapter, device_cmd->output);
        goto end;
    }

    if (device_cmd->disable)
    {
        if (device_cmd->output & ((1 << PORT_NUM) - 1))
        {
         //   device_set.device = tt_get_last_bit(device_cmd->output);
         //   device_set.state = DPU_POWER_OFF;
          //  dpu_set_device(dpu_adapter->dpu_manager, &device_set);

       //     dpu_adapter->current_output_info[device_set.device].power_status = POWER_OFF;
        }
        else
        {
            dpu_error("invalid device type, please help check \n");
        }
        goto end;
    }

    //default value
    prepare_cmd.async_clk = 2;
    prepare_cmd.cea = 0;
    prepare_cmd.bit_depth = 8;
    prepare_cmd.enhanced_frame_mode = 2;
    prepare_cmd.coef =  1;
    prepare_cmd.color_format = 1;
    prepare_cmd.output = PORT_0;
    prepare_cmd.lane_count = 4;
    prepare_cmd.link_rate = 3;
    prepare_cmd.disable = 0;
        


    if (device_cmd->cmd_valid && device_cmd->cmd_index < MAX_CACHED_CMD_NUM &&
        dpu_adapter->cached_cmd[DEVICE_CMD][device_cmd->cmd_index].valid)
    {
        new_cmd = 0;
        memcpy(&prepare_cmd, &dpu_adapter->cached_cmd[DEVICE_CMD][device_cmd->cmd_index].device_cmd, sizeof(struct device_cmd_t));
    }
    
   
    if (device_cmd->output)
    {
        prepare_cmd.output = tt_get_last_bit(device_cmd->output);
    }

    prepare_cmd.async_clk = device_cmd->async_clk ? device_cmd->async_clk :  prepare_cmd.async_clk;
    prepare_cmd.cea = device_cmd->cea ? device_cmd->cea :  prepare_cmd.cea;
    prepare_cmd.color_format = device_cmd->color_format ? device_cmd->color_format : prepare_cmd.color_format;
    prepare_cmd.enhanced_frame_mode = device_cmd->enhanced_frame_mode ? device_cmd->enhanced_frame_mode : prepare_cmd.enhanced_frame_mode;
    prepare_cmd.lane_count = device_cmd->lane_count ? device_cmd->lane_count : prepare_cmd.lane_count;
    prepare_cmd.link_rate = device_cmd->link_rate ? device_cmd->link_rate : prepare_cmd.link_rate;
    prepare_cmd.bit_depth = device_cmd->bit_depth ? device_cmd->bit_depth : prepare_cmd.bit_depth;
    prepare_cmd.coef = device_cmd->coef ? device_cmd->coef : prepare_cmd.coef;
    


    //check is new cmd or not
    for (i = 0 ;i < MAX_CACHED_CMD_NUM; i++)
    {
       if (!memcmp(&dpu_adapter->cached_cmd[DEVICE_CMD][i].device_cmd, &prepare_cmd, sizeof(struct device_cmd_t)))
       {
           new_cmd = 0;
           break;
       }
    }

    if (new_cmd)
    {
        for (i = MAX_CACHED_CMD_NUM - 2; i >=0; i--)
        {
            memcpy(&dpu_adapter->cached_cmd[DEVICE_CMD][i+1],
                 &dpu_adapter->cached_cmd[DEVICE_CMD][i],
                 sizeof(struct cached_cmd_t));
        }

        //update cached cmd
        cached_cmd = &dpu_adapter->cached_cmd[DEVICE_CMD][prepare_cmd.cmd_index].device_cmd;
        memcpy(cached_cmd, &prepare_cmd, sizeof(struct device_cmd_t));
        dpu_adapter->cached_cmd[DEVICE_CMD][prepare_cmd.cmd_index].valid = 1;

    }


    //TODO: check value valid
    if (prepare_cmd.output)
    {
     //   device_set.device = prepare_cmd.output;
     //   device_set.state = DPU_POWER_OFF;
    }
    else
    {
        dpu_error("invalid device type, please help check \n");
        need_set_device = 0;
    }

    if (need_set_device)
    {

        #if 0
        device_set.async_clk = prepare_cmd.async_clk;
        device_set.bit_depth = prepare_cmd.bit_depth;
        device_set.cea = prepare_cmd.cea;
        device_set.coef = prepare_cmd.coef;
        device_set.color_format = prepare_cmd.color_format;
        device_set.enhanced_frame_mode = prepare_cmd.enhanced_frame_mode;
        device_set.lane_count = prepare_cmd.lane_count;
        device_set.link_rate = prepare_cmd.link_rate;
        device_set.state = DPU_POWER_ON;

        //do set device
        ret = dpu_set_device(dpu_adapter->dpu_manager, &device_set);
        dpu_adapter->current_output_info[device_set.device].power_status = POWER_ON;
        #endif
    }

end:
    return ret;
}

static void cursor_handle_trace(struct cursor_cmd_t *cursor_cmd)
{
    dpu_trace("op %d, op_valid %d  crtc %d crtc_valid %d, type %d, mode %d surface %d s_valid %d \n",
        cursor_cmd->op,
        cursor_cmd->op_valid,
        cursor_cmd->crtc,
        cursor_cmd->crtc_valid,
        cursor_cmd->type,
        cursor_cmd->mode,
        cursor_cmd->surface_index,
        cursor_cmd->si_valid);

    dpu_trace("pos_x %d pos_y %d pos_valid %d, cmd_index %d  cmd_valid %d list %d info %d help %d\n",
        cursor_cmd->pos_x,
        cursor_cmd->pos_y,
        cursor_cmd->pos_valid,
        cursor_cmd->cmd_index,
        cursor_cmd->cmd_valid,
        cursor_cmd->list_cmd,
        cursor_cmd->info_cmd,
        cursor_cmd->help_cmd);
}

static void cursor_handle_list(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct cursor_cmd_t *cached_cmd = NULL;

    dpu_info("list of cached plane cmd: \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[CURSOR_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[CURSOR_CMD][i].cursor_cmd;
                 
            dpu_info("%d: op %s, crtc %d , type %s, mode %s surface %d pos_x %d pos_y %d \n",
                i,
                cached_cmd->op ? "enable" : "disable",
                cached_cmd->crtc,
                g_cursor_type_string[cached_cmd->type],
                (cached_cmd->mode == 1 )? "64x64" : "128x128",
                cached_cmd->surface_index,
                cached_cmd->pos_x,
                cached_cmd->pos_y);
         }
 
    }
}

static void cursor_handle_help()
{
    u32 i = 0;
    for (i = 0; i < ARRAY_SIZE(cursor_options_table); i++)
    {
        dpu_info("%s\n", cursor_options_table[i].options_help);
    }
}

static void cursor_handle_info(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct cursor_info_t *cursor_info = NULL;
    
    for (i = 0; i < CRTC_NUM; i++)
    {
        dpu_info("crtc %d \n",i);
        
        cursor_info = &dpu_adapter->current_cursor_info[i];

        if (cursor_info->plane_state == PLANE_DISABLED || !cursor_info->surface)
        {
            dpu_info("cursor is disabled\n");
        }
        else
        {
             dpu_info("type %s, mode %s g_addr 0x%x c_addr 0x%x pos_x %d pos_y %d \n",
                g_cursor_type_string[cursor_info->type],
                cursor_info->mode == 1? "64x64" : "128x128",
                cursor_info->surface->gpu_addr,
                cursor_info->surface->cpu_addr,
                cursor_info->pos_x,
                cursor_info->pos_y);
        }

    }
}

static TT_STATUS cursor_handle(struct dpu_adapter_t *dpu_adapter, struct cursor_cmd_t *cursor_cmd)
{
    TT_STATUS ret = TT_PASS;
    struct cursor_cmd_t *cached_cmd = NULL;
    struct cursor_cmd_t prepare_cmd = {0};
    struct cursor_info_t *cursor_info = NULL;
 //   struct dpu_cursor_para_t cursor_set ={0};
    struct surface_info_t *surface = NULL;
    u32 new_cmd = 1;
    u32 need_set = 1;
    i32 i = 0, j = 0;


    cursor_handle_trace(cursor_cmd);
    
    if (dpu_adapter->test_domain | TEST_DOS_ONLY)
    {
        dpu_info("de is not available\n");
        goto end;
    }

    if (cursor_cmd->list_cmd)
    {
        cursor_handle_list(dpu_adapter);
        ret = TT_PASS;
        goto end;
    }

    if (cursor_cmd->help_cmd)
    {
        cursor_handle_help();
        ret = TT_PASS;
        goto end;
    }

    if (cursor_cmd->info_cmd)
    {
        cursor_handle_info(dpu_adapter);
        ret = TT_PASS;
        goto end;
    }

    if (cursor_cmd->op_valid && !cursor_cmd->op)
    {   
        cursor_info = &dpu_adapter->current_cursor_info[prepare_cmd.crtc];
        //update plane state here
        cursor_info->plane_state = PLANE_DISABLED;
    //    cursor_set.flag =  DPU_DISABLE_FLIP;
    //    dpu_set_cursor(dpu_adapter->dpu_manager, &cursor_set);

        ret = TT_PASS;
        goto end;
    }
    
    prepare_cmd.cmd_index = 0;
    prepare_cmd.crtc = 0;
    prepare_cmd.surface_index = 0;
    prepare_cmd.op = 1;  //enable
    prepare_cmd.pos_x = 0;
    prepare_cmd.pos_y = 0;
    prepare_cmd.type = CURSOR_COVERAGE;
    prepare_cmd.mode = CURSOR_MODE_64_64;
    

    new_cmd = 1;
    
    if (cursor_cmd->cmd_valid && cursor_cmd->cmd_index < MAX_CACHED_CMD_NUM && 
        dpu_adapter->cached_cmd[CURSOR_CMD][cursor_cmd->cmd_index].valid)
    {
        cached_cmd = &dpu_adapter->cached_cmd[CURSOR_CMD][cursor_cmd->cmd_index].cursor_cmd;

        memcpy(&prepare_cmd, cached_cmd, sizeof(struct cursor_cmd_t));

        new_cmd = 0;
    }



    if (cursor_cmd->crtc_valid )
    {
        if (cursor_cmd->crtc < CRTC_NUM)
        {
            prepare_cmd.crtc = cursor_cmd->crtc;
        }
        else
        {
            dpu_error("input crtc index is invalid ,please help check\n");
            need_set = 0;
        }
    }

    if (cursor_cmd->op_valid)
    {
        prepare_cmd.op = cursor_cmd->op ? 1: 0;
    }

    if (cursor_cmd->pos_valid)
    {
        prepare_cmd.pos_x = cursor_cmd->pos_x;
        prepare_cmd.pos_y = cursor_cmd->pos_y;
    }

    if (cursor_cmd->type)
    {
        if (cursor_cmd->type < CURSOR_TYPE_NUM)
        {
            prepare_cmd.type = cursor_cmd->type;
        }
        else
        {
            dpu_error("input cursor type is invalid ,please help check\n");
            need_set = 0;
        }
    }

    if (cursor_cmd->mode)
    {
        if (cursor_cmd->mode < CURSOR_MODE_NUM)
        {
            prepare_cmd.mode = cursor_cmd->mode;
        }
        else
        {
            dpu_error("input cursor mode is invalid ,please help check\n");
            need_set = 0;
        }
    }



    if (cursor_cmd->si_valid)
    {
        if (cursor_cmd->surface_index < MAX_SURFACE_NUM && dpu_adapter->surface_manager.surfaces[cursor_cmd->surface_index].valid)
        {
            prepare_cmd.surface_index = cursor_cmd->surface_index;
        }
        else
        {
            dpu_error("input surface index is invalid ,please help check\n");
            need_set = 0;
        }
    }

    
    for (i = 0 ;i < MAX_CACHED_CMD_NUM; i++)
    {
        if (!memcmp(&dpu_adapter->cached_cmd[CURSOR_CMD][i].cursor_cmd, &prepare_cmd, sizeof(struct cursor_cmd_t)))
        {
            new_cmd = 0;
            break;
        }
    }


    if (new_cmd)
    {
        for (i = MAX_CACHED_CMD_NUM - 2; i >=0; i--)
        {
            memcpy(&dpu_adapter->cached_cmd[CURSOR_CMD][i+1],
                   &dpu_adapter->cached_cmd[CURSOR_CMD][i],
                   sizeof(struct cached_cmd_t));
        }
         //update cached cmd
        cached_cmd = &dpu_adapter->cached_cmd[CURSOR_CMD][prepare_cmd.cmd_index].cursor_cmd;
        memcpy(cached_cmd, &prepare_cmd, sizeof(struct cursor_cmd_t));
        dpu_adapter->cached_cmd[CURSOR_CMD][prepare_cmd.cmd_index].valid = 1;
    }

   

    surface = &dpu_adapter->surface_manager.surfaces[prepare_cmd.surface_index].surface; 
    if (need_set)
    {
        //update current plane info
        cursor_info = &dpu_adapter->current_cursor_info[prepare_cmd.crtc];

        cursor_info->type = prepare_cmd.type;
        cursor_info->mode = prepare_cmd.mode;
        cursor_info->pos_x = prepare_cmd.pos_x;
        cursor_info->pos_y = prepare_cmd.pos_y;
        cursor_info->surface = surface;

        //get page flip info
     #if 0
        cursor_set.crtc = prepare_cmd.crtc;
        cursor_set.addr = surface->gpu_addr;
        cursor_set.pos_x = prepare_cmd.pos_x;
        cursor_set.pos_y = prepare_cmd.pos_y;

        cursor_set.type = (DPU_CURSOR_TYPE)prepare_cmd.type;
        cursor_set.mode = (DPU_CURSOR_MODE)prepare_cmd.mode;

        cursor_set.flag = prepare_cmd.op ? DPU_ENABLE_FLIP : DPU_DISABLE_FLIP;
       
        //update plane state here
        cursor_info->plane_state = !prepare_cmd.op;

        if (DPU_OK != dpu_set_cursor(dpu_adapter->dpu_manager, &cursor_set))
        {
            dpu_error("set cursor failed ,please help check \n");
            ret = TT_FAIL;
            goto end;
        }
     #endif
    }
    ret = TT_PASS;

end:
    return ret;
}


static void misc_handle_trace(u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    u32 i = 0;

    dpu_trace("in misc handle trace\n");

    for (i = 0; i < word_num; i++)
    {
        dpu_trace("%s ",buffer[i]);
    }

    dpu_trace("\n");
}


static void handle_pcir(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    u8 bus = 0, dev = 0, func = 0;
    u32 offset = 0;
    u8 value = 0;
    u32 read_all = 1;
    u32 write_data = 0;
    u32 i,j;

    
    if (word_num < 4)
    {
        dpu_info(" pcir bus dev func  [offset] [value] \n");
        return ;
    }

    bus = (strtoul(buffer[1], NULL, 16)) & 0xff;
    dev = (strtoul(buffer[2], NULL, 16)) & 0xff;
    func = (strtoul(buffer[3], NULL, 16)) & 0xff;

    if (word_num > 4)
    {
        offset = strtoul(buffer[4], NULL, 16) & 0xff;
        read_all = 0;
    }

    if (word_num >= 6)
    {
        value = (strtoul(buffer[5], NULL, 16)) & 0xff;
        write_data = 1;
    }

    if (write_data)
    {
        tt_write_pci_config_byte(bus, dev, func, offset, value);
    }
    else
    {
        if (read_all)
        {
            //TODO: decode pci space, like lspci format ?
        
            dpu_info("       0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
            for (i = 0; i < 16; i++)
            {
                dpu_info("0x%02x:",i*16);
                for (j = 0; j < 16; j++)
                {
                    tt_read_pci_config_byte(bus, dev, func, i*16 + j, &value);
                    dpu_info(" %02x", value);
                }
                dpu_info("\n");
            }

        }
        else
        {
            tt_read_pci_config_byte(bus, dev, func, offset, &value);
            dpu_info("read 0x%x 0x%x 0x%x offset:0x%x value: 0x%x\n", bus, dev, func, offset, value);
        }
    }
     
    
}


static void handle_reg(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num, u32 base, u32 mask)
{
    u32 index = 0, value = 0;

    if (word_num < 2)
    {
        dpu_info("%s     index   [value]\n", buffer[0]);
        return ;
    }

    index = strtoul(buffer[1], NULL, 16);
    
    if (mask == 0xff)
    {
        value = tt_read_u8(dpu_adapter, base + index);
    }
    else
    {
        value = tt_read_u32(dpu_adapter, base + index);
    }

    dpu_info("%s  0x%x  value : 0x%x\n", buffer[0], base + index, value);



    if (word_num >=3)
    {
        value = strtoul(buffer[2], NULL, 16);
    
        if (mask == 0xff)
        {
            tt_write_u8(dpu_adapter, base + index, (u8)value);
        }
        else
        {
            tt_write_u32(dpu_adapter, base + index, value);
        }

        if (mask == 0xff)
        {
            value = tt_read_u8(dpu_adapter, (u8)(base + index));
        }
        else
        {
            value = tt_read_u32(dpu_adapter, base + index);
        }

        dpu_info("%s  0x%x  new   : 0x%x\n", buffer[0], base + index, value);
    }
     

}

static void handle_mem(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num, MISC_OP_TYPE op )
{
    u32 offset = 0, value = 0, length = 0, addr = 0;
    u32 i = 0, j = 0;

    if (op == OP_READ && word_num < 2)
    {
        dpu_info("memr  offset    [length]\n");
        return ;
    }

    if (op == OP_WRITE && word_num < 3)
    {
        dpu_info("memw  offset    value  [length]\n");
        return ;
    }

    offset = strtoul(buffer[1], NULL, 16);
    
    addr = offset + dpu_adapter->base.fb_base;
    if (op == OP_READ && word_num >= 3)
    {
        length = strtoul(buffer[2], NULL, 16);

        length = length % 8 ? (length/8 + 1): length /8;  //may read more data

        for (i = 0; i < length; i++)
        {
            dpu_info(" 0x%x:",(u32*)addr + i * 8);
            for (j = 0; j < 8; j ++)
            {
                dpu_info("0x%08x ",tt_read_buffer_u32((u32*)(addr) + i * 8 + j));
            }
            dpu_info("\n");
        }
    }
    else
    {
         value = tt_read_buffer_u32((u32*)addr);

         dpu_info(" 0x%08x :  0x%08x\n", addr, value);
    }

    if (op == OP_WRITE)
    {
        value = strtoul(buffer[2], NULL, 16);
        if (word_num >= 4)
        {
            length = strtoul(buffer[3], NULL, 16);
        }
        else
        {
            length = 1;
        }

        for (i = 0; i < length ; i++)
        {
            tt_write_buffer_u32(((u32*)(addr) + i), value);
        }
    }
    
    
}
static void handle_dump(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    //TODO: dump reg 
    //word_num = 1  : dump to console 
    //word_num >=2  : dump to file ?

    u8 *file_name = NULL;
    u8  dump_file = 1;
    FILE *fp = NULL;

    dpu_info("reg dump :");

    if (word_num >=2)
    {
        file_name = buffer[1];

        fp = fopen(file_name, "wt");

        if (fp == NULL)
        {
            dump_file = 0;
        }
    }

    if (dump_file)
    {
        fprintf(fp, "dump all regs value :\n");


        //TODO define some domians, 

        fclose(fp);
    }
    else
    {
        //TODO dump to console
    }
    







}

static void handle_i2c(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    u8 group = 0;
    u8 addr = 0;
    u32 offset = 0;
    u8 value = 0, temp = 0, old = 0, sum = 0;
    u8 get_offset = 0, get_value = 0;
    u32 i = 0, j = 0;


    if (dpu_adapter->test_domain | TEST_DOS_ONLY)
    {
        dpu_info("de is not available\n");
        return;
    }
/***
    struct dpu_i2c_para_t i2c_para = {0};

    if (word_num < 3)
    {
        dpu_info("i2c group  addr offset value \n");
        return ;
    }

    group = strtoul(buffer[1], NULL, 16);
    addr = strtoul(buffer[2], NULL, 16);
    if (word_num >= 4)
    {
        offset = strtoul(buffer[3], NULL, 16);
        get_offset = 1;
    }

    if (word_num >= 5)
    {
        value = strtoul(buffer[4], NULL, 16);
        get_value = 1;
    }

    i2c_para.group = group;
    i2c_para.addr = addr;
    i2c_para.buffer = &temp;
    i2c_para.length = 1;
    i2c_para.offset = 0;

    if (!get_value) //i2c read 
    {
        i2c_para.op = 0;
        if (!get_offset)
        {
            dpu_info("    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            for (i = 0; i < 16; i++)
            {
                dpu_info("%02x ", i);
                for (j = 0; j < 16; j++)
                {
                    i2c_para.offset = i * 16 + j;
                    dpu_set_i2c(dpu_adapter->dpu_manager, &i2c_para);

                    dpu_info(" %02x", temp);
                    if (i < 8)
                    {
                        sum += temp;
                    }
                }
                dpu_info("\n");
            }
            dpu_info("check sum = %02x\n", sum);
        }
        else
        {
            i2c_para.offset = offset;
            
            dpu_set_i2c(dpu_adapter->dpu_manager, &i2c_para);
            dpu_info("group 0x%x addr 0x%x offset 0x%x value :0x%x\n", group, addr, offset, temp);
        }
    }
    else //i2c write
    {
        i2c_para.op = 0;
        i2c_para.offset = offset;
        i2c_para.buffer = &old;
        
        dpu_set_i2c(dpu_adapter->dpu_manager, &i2c_para); 
        //dpu_info("grop 0x%x addr 0x%x offset 0x%x value :0x%x\n",group, addr, offset, temp);

        i2c_para.op = 1;
        i2c_para.buffer = &value;
        
        dpu_set_i2c(dpu_adapter->dpu_manager, &i2c_para);

        i2c_para.op = 0;
        i2c_para.buffer = &temp;
   
        dpu_set_i2c(dpu_adapter->dpu_manager, &i2c_para);

        if (temp != value)
        {
            dpu_info("write group 0x%x addr 0x%x offset 0x%x failed,old value is 0x%x now value is 0x%x\n",
                group,
                addr,
                offset,
                old,
                temp);
        }
        else
        {
            dpu_info("write group 0x%x addr 0x%x offset 0x%x  value 0x%x successfully\n",
                group, 
                addr, 
                offset, 
                value);
        }
    }
***/
}

static void handle_aux(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    struct dpu_aux_para_t aux_para = {0};
    u32 port = 0;
    u32 offset = 0;
    u8 value = 0, temp = 0, old = 0;
    u8  get_value = 0;


    if (dpu_adapter->test_domain | TEST_DOS_ONLY)
    {
        dpu_info("de is not available\n");
        return;
    }

    if (word_num < 3)
    {
        dpu_info("aux port offset value\n");
        return ;
    }

    port = strtoul(buffer[1], NULL, 16);
    offset = strtoul(buffer[2], NULL, 16);

    if (word_num >= 4)
    {
        value = strtoul(buffer[3], NULL, 16);
        get_value = 1;
    }
    
    aux_para.device = port;
    aux_para.offset = offset;

    if (!get_value)
    {
        aux_para.buffer = &temp;
        aux_para.length = 1;
        aux_para.op = 0;

        dpu_set_aux(dpu_adapter->dpu_manager, &aux_para);

        dpu_info("read device 0x%x offset 0x%x value :0x%x\n", port, offset, temp);
    }
    else
    {
        aux_para.buffer = &old;
        aux_para.length = 1;
        aux_para.op = 0;

        dpu_set_aux(dpu_adapter->dpu_manager, &aux_para);

        aux_para.buffer = &value;
        aux_para.length = 1;
        aux_para.op = 1;
        dpu_set_aux(dpu_adapter->dpu_manager, &aux_para);

        aux_para.buffer = &temp;
        aux_para.length = 1;
        aux_para.op = 0;

        dpu_set_aux(dpu_adapter->dpu_manager, &aux_para);
        
        if (temp != value)
        {
            dpu_info("write port 0x%x offset 0x%x failed,old value is 0x%x now value is 0x%x\n",
                port,
                offset,
                old,
                temp);
        }
        else
        {
            dpu_info("write port 0x%x offset 0x%x value 0x%x successfully\n",
                port, 
                offset, 
                value);
        }
    }
}

static void handle_file(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num, MISC_OP_TYPE op)
{
    FILE * fp = NULL;
    u8 *file_name;
    u32 file_size = 0;
    u32 size = 0;
    u32 offset = 0;
 
    if (op == OP_WRITE && word_num < 3)  //write to mem
    {
        dpu_info("lf filename offset \n");
        return ;
    }

    if (op == OP_READ && word_num < 4)
    {
        dpu_info("sf filename offset size \n");
        return ;
    }

    file_name = buffer[1];
    offset = strtoul(buffer[2], NULL, 16);

    fp = fopen(file_name, "wb+");
    if (!fp)
    {
        dpu_info("open file %s failed \n",file_name);
        return;
    }     

    if (op == OP_READ)
    {
        size = strtoul(buffer[3], NULL, 16);
        fwrite((void*)(dpu_adapter->base.fb_base + offset), size, 1, fp);
        
        dpu_info("save to file done\n");
        fclose(fp);
    }
    else
    {
        fseek(fp, 0, SEEK_END);
        file_size = ftell(fp);

        fseek(fp, 0, SEEK_SET);
        fread((void*)(dpu_adapter->base.fb_base + offset),file_size, 1, fp);
        
        dpu_info("load file to offset 0x%x done \n",offset);
        fclose(fp);
    }
}

void handle_help()
{

    dpu_info("mode    -help  for mode help info\n");
    dpu_info("plane   -help  for plane help info\n");
    dpu_info("surface -help  for surface help info\n");
    dpu_info("device  -help  for device help info\n");
    dpu_info("cursor  -help  for cursor help info \n");

    
    dpu_info("\n In misc handle below ,all data is hex\n\n");
    
    dpu_info("pcir  bus  dev  func  [offset] [value] \n");
    dpu_info("cr    index   [value]\n");
    dpu_info("crb   index   [value]\n");
    dpu_info("sr    index   [value]\n");
    dpu_info("srb   index   [value]\n");
    dpu_info("mmio  index   [value]\n");
    dpu_info("memr  offset  [length]\n");
    dpu_info("memw  offset   value [length]\n");
    dpu_info("dump  [file_name]  dump all regs to console/file\n");
    dpu_info("i2c   group  addr   offset value \n");
    dpu_info("aux   port   offset value\n");
    dpu_info("lf    filename     offset \n");     //TODO: maybe we need surface index ?
    dpu_info("sf    filename     offset size \n");
    dpu_info("csc   <path>  <index1>  [index2] \n");
    dpu_info("  path: 1 :plane csc   index1 = crtc index  index2 = plane index\n");  //plane csc just test csc ? 
                                                                                     //device csc test color enhancement ?
    dpu_info("  path: 2 :device csc  index1 = port index\n");
    dpu_info("gamma   <index> <domain> <mode> \n");
    dpu_info("   index: crtc index \n");
    dpu_info("   domain: 1: primary only 2: overlay only 3: blend data \n");
    dpu_info("   mode :  1: 8bit single, 2: 8bit split 3: 10bit single 4: 10bit split \n");
    dpu_info("q  exit program\n");
}


static void handle_csc(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
   struct csc_para_t csc_para = {0};

    if (dpu_adapter->test_domain | TEST_DOS_ONLY)
    {
        dpu_info("de is not available\n");
        return;
    }

   //put csc para to output_info_t

    dpu_info("in handle csc \n");
}


static void handle_gamma(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    //test gamma 

    if (dpu_adapter->test_domain | TEST_DOS_ONLY)
    {
        dpu_info("de is not available\n");
        return;
    }

    dpu_info("in handle gamma \n");

}

static void handle_hda(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    //How ?

    if (dpu_adapter->test_domain | TEST_DOS_ONLY)
    {
        dpu_info("de is not available\n");
        return;
    }
    dpu_info("in handle hda\n");
}


static u8 is_same_str(u8 *str1, u8 *str2)
{
    if (tt_strhash(str1) == tt_strhash(str2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static TT_STATUS misc_handle(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{

    misc_handle_trace(buffer, word_num);

    if (is_same_str("pcir", buffer[0]))
    {
        handle_pcir(dpu_adapter, buffer, word_num);
    }
    else if (is_same_str("mmio", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, MMIO_BASE, 0xffffffff);
    }
    else if (is_same_str("cr", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, CR_BASE, 0xff);
    }
    else if (is_same_str("crb", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, CR_B_BASE, 0xff);
    }
    else if (is_same_str("sr", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, SR_BASE, 0xff);
    }
    else if (is_same_str("srb", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, SR_B_BASE, 0xff);
    }
    else if (is_same_str("memr", buffer[0]))
    {
        handle_mem(dpu_adapter, buffer, word_num, OP_READ);
    }
    else if (is_same_str("memw", buffer[0]))
    {
        handle_mem(dpu_adapter, buffer, word_num, OP_WRITE);
    }
    else if (is_same_str("dump", buffer[0]))
    {
        handle_dump(dpu_adapter, buffer, word_num);
    }
    else if (is_same_str("i2c", buffer[0]))
    {
        handle_i2c(dpu_adapter, buffer, word_num);
    }
    else if (is_same_str("aux", buffer[0]))
    {
        handle_aux(dpu_adapter, buffer, word_num);
    }
    else if (is_same_str("lf", buffer[0]))
    {
        handle_file(dpu_adapter, buffer, word_num, OP_WRITE);
    }
    else if (is_same_str("sf", buffer[0]))
    {
        handle_file(dpu_adapter, buffer, word_num, OP_READ);
    }
    else if (is_same_str("help", buffer[0]))
    {
        handle_help(dpu_adapter, buffer, word_num);
    }
    else if (is_same_str("csc", buffer[0]))
    {
        handle_csc(dpu_adapter, buffer, word_num);
    }
    else if (is_same_str("gamma", buffer[0]))
    {
        handle_gamma(dpu_adapter, buffer, word_num);
    }
    else if (is_same_str("hda", buffer[0]))
    {
        handle_hda(dpu_adapter, buffer, word_num);
    }
    else if (is_same_str("reg", buffer[0]))
    {
        handle_reg_main(dpu_adapter, buffer, word_num);
    }
    else
    {
        dpu_error("unknow misc operation :%s  \n",buffer[0]);
    }

}

#define COMMAND(type)    {#type, type##_handle, type##_options_table, ARRAY_SIZE(type##_options_table), &g_##type##_cmd, sizeof(g_##type##_cmd)}

//add new command here 
struct support_cmd g_support_cmd[] = 
{
        COMMAND(mode),
        COMMAND(plane),
        COMMAND(surface),
        COMMAND(device),
        COMMAND(cursor),
};


static u32 dump_cmd_history(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;

    for (i = 0; i < MAX_INPUT_HISTORY_NUM; i++)
    {
        dpu_info("\n index %d is %s %d\n",i, dpu_adapter->cmd_history[i], strlen(dpu_adapter->cmd_history[i]));
    }

}

static u32 get_cmd_index(struct dpu_adapter_t *dpu_adapter, i32 up_times)
{

    u32 index = 0;
    
    index = (dpu_adapter->cmd_num - up_times + MAX_INPUT_HISTORY_NUM) % MAX_INPUT_HISTORY_NUM;

    return index;

}

static u32 add_to_cmd_history(struct dpu_adapter_t *dpu_adapter, u8* cmd)
{
    u32 index = 0;

    index = (dpu_adapter->cmd_num) % MAX_INPUT_HISTORY_NUM;

    dpu_adapter->cmd_num ++;

    strcpy(dpu_adapter->cmd_history[index], cmd);

    return 0;
}

void get_input(struct dpu_adapter_t *dpu_adapter, u8* cmd_line)
{
    u32 i;
    u8 ch;
    u8 *position = NULL;
    i32 up_times = 0;
    u32 use_input = 0;
    u32 cache_cmd_index = 0;

    dpu_info(">");

   // dump_cmd_history(dpu_adapter);
  
    position = cmd_line;
    do{

        ch = getch();

        //dpu_info("ch is %d ",ch);

        if(ch == KEY_UP_DOWN_PRE)
        {
            tt_delay_micro_seconds(300);
            continue;
        }

        if (ch == KEY_UP)
        {
          //  dpu_info("in key up \n");
            up_times ++;
            i = position - cmd_line;

            while (i > 0)
            {
                *position = '\0';
                dpu_info("%c", KEY_BACKSPACE);
                dpu_info("%c", KEY_SPACE);
                dpu_info("%c", KEY_BACKSPACE);
                i--;
                position--;
            }

            cache_cmd_index = get_cmd_index(dpu_adapter, up_times);

            strcpy(cmd_line, dpu_adapter->cmd_history[cache_cmd_index]);
            position = cmd_line + strlen(cmd_line);

            dpu_info("%s",cmd_line);
           
        }
        else if (ch == KEY_DOWN)
        {
        // dpu_info("in key down \n");
            up_times --;
            i = position - cmd_line;

            while (i > 0)
            {
                *position = '\0';
                dpu_info("%c", KEY_BACKSPACE);
                dpu_info("%c", KEY_SPACE);
                dpu_info("%c", KEY_BACKSPACE);
                i--;
                position--;
            }
            
            cache_cmd_index = get_cmd_index(dpu_adapter, up_times);

            strcpy(cmd_line, dpu_adapter->cmd_history[cache_cmd_index]);
            position = cmd_line + strlen(cmd_line);

            dpu_info("%s",cmd_line);
        }
        else if ((ch != KEY_ENTER) && (ch != KEY_BACKSPACE) && (ch != KEY_ESC))
        {
            *position = ch;
            position ++;
            *position = '\0';

            use_input = 1;
            
            dpu_info("%c", ch);
        }
        else if (ch == KEY_BACKSPACE)
        {
            i = position - cmd_line;

            if (position > cmd_line)
            {
                position --;
            }
            *position = '\0';
 
            if (i > 0)
            {
                dpu_info("%c", KEY_BACKSPACE);
                dpu_info("%c", KEY_SPACE);
                dpu_info("%c", KEY_BACKSPACE);
            }
        }
        else if (ch == KEY_ESC)
  //clear all cmd_line
        {
            i = position - cmd_line;

            while (i > 0)
            {
                *position = '\0';
                dpu_info("%c", KEY_BACKSPACE);
                dpu_info("%c", KEY_SPACE);
                dpu_info("%c", KEY_BACKSPACE);
                i--;
                position--;
            }
            //position = cmd_line;
        }
       // printf("ch is %d\n",ch);       
    }while(ch != KEY_ENTER);

    *position = '\0';

    if (use_input)
    {
       // dump_cmd_history(dpu_adapter);
        add_to_cmd_history(dpu_adapter, cmd_line);
        //dpu_info("\n lei ,add to cmd_line is %s  %d\n", cmd_line, strlen(cmd_line));

        //dump_cmd_history(dpu_adapter);
    }


    dpu_info("\n");
}

void process_cmd(struct dpu_adapter_t *dpu_adapter)
{
    TT_STATUS ret = TT_PASS;
    struct options_table *table;

    void* cmd = NULL;
    u8   found = 0;

    u32   support_cmd_num = 0;
    u32   i = 0, j = 0 ,k = 0;
    u32   item_num = 0;
    u32   word_num = 0;


    u8   cmd_line[MAX_CMD_STRING_NUM];
    u8   str[50][MAX_CMD_OPTION_NAME_SIZE];
    u8   ch;
    u8   *word;
    u8   filter[] = " ,\t\n";

    struct support_cmd *command = NULL;



    dpu_adapter->cmd_num = 0;

    for (i = 0; i < MAX_INPUT_HISTORY_NUM; i++)
    {
        memset(dpu_adapter->cmd_history[i], '\0', MAX_CMD_STRING_NUM);
    }

    while(1)
    {
        memset(cmd_line, 0 , MAX_CMD_STRING_NUM);

        memset(str, 0, 50*MAX_CMD_OPTION_NAME_SIZE);

        get_input(dpu_adapter, cmd_line);

        #if 0
        //dpu_info(">");
        //putchar('>');
        i = 0;
        ch = getchar();
        do{
            cmd_line[i] = ch;
            i++;
            ch = getchar();
        }while(ch != KEY_ENTER);

        cmd_line[i] = '\0';
        #endif
        word = strtok(cmd_line, filter);
   
        if(word != NULL)
        {
            strcpy(str[0], word);
        }
        else
        {
            continue;
        }

        if (str[0][0] == 'q' || str[0][0] == 'Q')
        {
            break;
        }

        i = 1;
        while(word != NULL)
        {
            word = strtok(NULL, filter);
            if(word != NULL)
            {
                strcpy(str[i], word);
                i++;
            }
        }
        word_num = i;

        support_cmd_num = ARRAY_SIZE(g_support_cmd);

        i = 0;
        found = 0;
        while(i < support_cmd_num)
        {
            if (!strcmp(str[0],g_support_cmd[i].cmd_name))
            {
                command = &g_support_cmd[i];
                
                found = 1;
                break;
            }
            i++;
        }

        if (!found)
        {
            ret = misc_handle(dpu_adapter, str, word_num);
            continue;
        }
        else
        {
            memset(command->cmd, 0 , command->cmd_size);
        }
      
        item_num = command->options_item_num;

        found = 0;
        for (i = 1; i < word_num; i++)
        {
            for (j = 0; j < item_num; j++)
            {
                if (str[i][0] == '-' && !strcmp(&str[i][1], command->table[j].options_name))
                {          
                    k = 0;
                    if(command->table[j].options_num == 0)
                    {
                        
                        if(command->table[j].para[k].valid_flag)
                        {
                            *(command->table[j].para[k].valid_flag) = 1;
                        }
                    }
                    else
                    {
                        k = 0;
                        while(k < command->table[j].options_num)
                        {
                            ++i;
                            *(command->table[j].para[k].value) = strtoul(str[i], NULL, command->table[j].para[k].base);

                            if(command->table[j].para[k].valid_flag)
                            {
                                *(command->table[j].para[k].valid_flag) = 1;
                            }

                            k++;
                        }
                    }

                    found = 1;
                    break;
                }
            }
        }
        
        if (found)
        {
            ret = command->func(dpu_adapter, command->cmd);
            if (ret != TT_PASS)
            {
                dpu_error("run cmd failed, please help check \n");
            }
        }
        else
        {
            dpu_info("invalid command please help check \n");
        }
   }//while(1)
   
}

#if 0

void main()
{

    u32 i = 0, j = 0;
    struct dpu_adapter_t  dpu_adapter = {0};

    dpu_info("in main func \n");


    dpu_adapter.num_crtc = 3;

    for (i = 0; i < CRTC_NUM; i++)
    {
        dpu_adapter.current_crtc_info[i].index= i;
    }

    for (i = 0; i < CRTC_NUM; i++)
    {
        for (j = 0; j < PLANE_NUM ; j++)
        {
            dpu_adapter.current_plane_info[i][j].crtc_index = i;
            dpu_adapter.current_plane_info[i][j].plane_type = j;
            dpu_adapter.current_plane_info[i][j].surface = NULL;
            dpu_adapter.current_plane_info[i][j].plane_state = PLANE_DISABLED;
        }
    }

    for (i = 0; i < PORT_NUM; i++)
    {
        dpu_adapter.current_output_info[i].device = 1 << i;
        dpu_adapter.current_output_info[i].connect_status = CONNECTED_STATUS;
        dpu_adapter.current_output_info[i].power_status = POWER_OFF;
        
    }

    for (i = 0; i < MAX_CMD_NUM; i++)
    {
        dpu_adapter.cached_cmd[MODE_CMD][i].mode_cmd.cmd_index = i;
        dpu_adapter.cached_cmd[PLANE_CMD][i].mode_cmd.cmd_index = i;
        dpu_adapter.cached_cmd[SURFACE_CMD][i].mode_cmd.cmd_index = i;
        dpu_adapter.cached_cmd[DEVICE_CMD][i].mode_cmd.cmd_index = i;
    }

    dpu_adapter.log_level = DEBUG_LEVEL;

    dpu_adapter.width_alignment = 32;

    process_cmd(&dpu_adapter);

}

#endif

