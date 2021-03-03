#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include"types.h"
#include"util.h"
#include"config.h"

#include"dpu.h"


#if CMODEL_DEBUG

#define cmodel_debug  	dpu_info

#else

#define cmodel_debug 
#endif



//#include"dpu_arch/dpu_cmodel.h"
#ifdef __DPU_LINUX_KERNEL__

#include <termios.h>
#include <unistd.h>
#include"cmodel_wrapper.h"

int getch (void)
{
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;

}
#endif



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
    {"os",  "[-os output signal] 0x1:RGB 0x2: YUV444 0x4: YUV422 0x8: YUV 420",1, {{16, &g_mode_cmd.output_signal}},},
    {"list",   "[-list] list cached modes", 0, {{0, NULL, &g_mode_cmd.list_cmd}}},
    {"info",   "[-info] current mode info ", 0,{{0, NULL, &g_mode_cmd.info_cmd}}},
    {"help",   "[-help] help", 0, {{0, NULL, &g_mode_cmd.help_cmd},}},
    {"set",   "[-set index], set cached cmd[index]", 1, {{10, &g_mode_cmd.cmd_index, &g_mode_cmd.cmd_valid},}},
    {"bpc", "[-bpc value], set color depth", 1, {{10, &g_mode_cmd.bpc,},}}
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
    {"kp", "[-kp kp ks]  kp ks", 2, {{10, &g_plane_cmd.overlay_cmd.kp, &g_plane_cmd.overlay_cmd.kps_valid},
                                                                            {10, &g_plane_cmd.overlay_cmd.ks}}},
    {"kv", "[-kv key_l key_h]", 2,{{16, &g_plane_cmd.overlay_cmd.key_low, &g_plane_cmd.overlay_cmd.key_valid}, {16, &g_plane_cmd.overlay_cmd.key_high}}},
    {"info", "[-info]  current plane info", 0 ,{{0, NULL, &g_plane_cmd.info_cmd},}},
    {"list", "[-list]  list cached plane config",0, {{0, NULL, &g_plane_cmd.list_cmd}}},
    {"help", "[-help] help ", 0, {{0, NULL, &g_plane_cmd.help_cmd},}},
    {"set", "[-set index] set cached cmd[index]", 1, {{10, &g_plane_cmd.cmd_index, &g_plane_cmd.cmd_valid},}},
};





//need refine later : 
//1,assign a surface handle by user
//2,ld cmd support load file to surface handle( 20210303 done)
//if surface handle has alloc video memory, then check widht/pitch/height/fmt etc
//if has same caps ,no need alloc new video memory, otherwize free the old video memory ,alloc new video memory
//purpose: user could use a certain surface handle for flip

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
    {"config","[-config] current device config",0, {0, NULL, &g_device_cmd.config_cmd}},
    {"help","[-help] list help info",0,{0, NULL, &g_device_cmd.help_cmd}},
    {"set", "[-set index] set cached cmd[index]", 1, {10, &g_device_cmd.cmd_index, &g_device_cmd.cmd_valid},},
    {"info", "[-info] print display info", 0, {0, NULL, &g_device_cmd.info_cmd},},
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

static bool_t match_mode(struct dpu_display_mode_list_t *mode_list, struct dpu_display_mode_t *mode_get, int x, int y, int rr)
{
	int  i = 0;
	struct dpu_display_mode_t *mode;

	for (i = 0; i < mode_list->num; i++) {
		mode = &mode_list->modes[i];

		if (mode->hactive != x)
			continue;
		if (mode->vactive != y)
			continue;
		if (mode->refresh_rate != rr)
			continue;

		memcpy(mode_get, mode, sizeof(struct dpu_display_mode_t));
		return TRUE;
	}

	return FALSE;
}

static void mode_handle_trace(struct mode_cmd_t *mode_info)
{

    dpu_info(TRACE_LEVEL,"crtc %d crtc_valid %d, cmd_index %d cmd_index_valid %d, output %d,src(%d,%d) dst(%d,%d),rr %d list %d info %d help %d\n",
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

    dpu_info(INFO_LEVEL,"list of cached mode options: \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[MODE_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[MODE_CMD][i].mode_cmd;

            dpu_info(INFO_LEVEL,"%d: crtc %d output 0x%x, src_mode (%d %d) dst_mode (%d %d), rr %d, output_signal %s\n",
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
        dpu_info(INFO_LEVEL,"%s\n", mode_options_table[i].options_help);
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
            dpu_info(INFO_LEVEL,"crtc_%d: not active\n", i);
        }
        else
        {
            dpu_info(INFO_LEVEL,"crtc_%d: output 0x%5x, hw mode(%4d %4d) adjust mode(%4d %4d), rr %d, output_signal %s\n",
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
    struct crtc_info_t *crtc_info;
    struct crtc_info_t crtc_set = {0};
	struct output_info_t *output_info;
    u32 index = 0;

    struct dpu_crtc_mode_set_para_t crtc_mode = {0};
    struct dpu_encoder_mode_set_para_t encoder_mode = {0};

    u32     new_cmd = 0;

    u32     valid = 0;
    u32     temp = 0;
    TT_STATUS ret = TT_PASS;

    mode_handle_trace(mode_info);

    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        dpu_info(INFO_LEVEL,"de is not available\n");
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
    prepare_cmd.output = DPU_PORT_0;

    prepare_cmd.src_xres = 1280;//1920;
    prepare_cmd.src_yres = 720;//1080;
    prepare_cmd.dst_xres = 1280;//1920;
    prepare_cmd.dst_yres = 720;//1080;
    prepare_cmd.rr = 60;
    prepare_cmd.output_signal = DPU_RGB_SIGNAL;
    prepare_cmd.bpc = 8;

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
        //if (prepare_cmd.rr < 100)
        //{
        //    prepare_cmd.rr *= 100;
        //}
    }

	if (mode_info->bpc)
		prepare_cmd.bpc  = mode_info->bpc;

	if (mode_info->output & dpu_adapter->support_device)
	{
		prepare_cmd.output = tt_get_last_bit(mode_info->output & dpu_adapter->support_device);
	}

	if (mode_info->crtc_valid)
	{
		prepare_cmd.crtc_index = mode_info->crtc_index;
	}

    if (mode_info->output_signal)
    {
        prepare_cmd.output_signal = mode_info->output_signal;
    }

	if (prepare_cmd.crtc_index >= DPU_MAX_CRTC_NUM)
	{
		dpu_info(INFO_LEVEL,"invalid crtc %d", prepare_cmd.crtc_index);
		goto end;
	}

	if (!(prepare_cmd.output & dpu_adapter->support_device))
	{
		dpu_info(INFO_LEVEL,"invalid devive 0x%x\n", prepare_cmd.output);
		goto end;
	}

	output_info = &dpu_adapter->current_output_info[tt_get_last_bit(prepare_cmd.output)];
	crtc_info = &dpu_adapter->current_crtc_info[prepare_cmd.crtc_index];

	if (!(prepare_cmd.output_signal & output_info->display_caps.support_signal.output_signal))
	{
		dpu_info(INFO_LEVEL,"Warring: monitor doesn't support  output signal %d\n",prepare_cmd.output_signal);
	}

	if (!(prepare_cmd.bpc > output_info->display_caps.max_color_depth))
	{
		dpu_info(INFO_LEVEL,"Warring: monitor doesn't support  bpc %d \n", prepare_cmd.bpc);
	}

	if (!match_mode(&output_info->mode_list, &crtc_info->hw_mode, prepare_cmd.src_xres, prepare_cmd.src_yres, prepare_cmd.rr))
	{
		dpu_info(INFO_LEVEL,"can't match hw mode\n");
		goto end;
	}
	if (!match_mode(&output_info->mode_list, &crtc_info->adjust_mode, prepare_cmd.dst_xres, prepare_cmd.dst_yres, prepare_cmd.rr))
	{
		dpu_info(INFO_LEVEL,"can't match adjust mode\n");
		goto end;
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
    crtc_info->output = prepare_cmd.output;
    memcpy(&crtc_mode.hw_mode, &crtc_info->hw_mode, sizeof(struct dpu_display_mode_t));
    memcpy(&crtc_mode.adjust_mode, &crtc_info->adjust_mode, sizeof(struct dpu_display_mode_t));
    crtc_mode.crtc = prepare_cmd.crtc_index;

    crtc_mode.hw_mode.output_signal = prepare_cmd.output_signal;

    crtc_mode.hw_mode.bpc = prepare_cmd.bpc;

    encoder_mode.crtc = prepare_cmd.crtc_index;
    encoder_mode.conn = dpu_get_connector_from_port(dpu_adapter->dpu_manager, prepare_cmd.output);
    encoder_mode.encoder = dpu_get_best_encoder(dpu_adapter->dpu_manager, encoder_mode.conn);

	dpu_handle_display_topology(dpu_adapter->dpu_manager, &encoder_mode);

    dpu_encoder_dpms(dpu_adapter->dpu_manager, encoder_mode.encoder, DPU_POWER_OFF);
    dpu_crtc_dpms(dpu_adapter->dpu_manager, encoder_mode.crtc, DPU_POWER_OFF);

    dpu_crtc_mode_set(dpu_adapter->dpu_manager, &crtc_mode);
    dpu_encoder_mode_set(dpu_adapter->dpu_manager, &encoder_mode);

    dpu_crtc_dpms(dpu_adapter->dpu_manager, encoder_mode.crtc, DPU_POWER_OFF);
    dpu_encoder_dpms(dpu_adapter->dpu_manager, encoder_mode.encoder, DPU_POWER_OFF);

    if (prepare_cmd.output & DPU_PORT_0)
    {
        index = 0;
    }
    else if (prepare_cmd.output & DPU_PORT_1)
    {
        index = 1;
    }
    else if (prepare_cmd.output & DPU_PORT_2)
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
    dpu_info(INFO_LEVEL,"crtc %d, ci_valid %d surface %d surface_valid %d, plane %d, plane_valid %d  info %d list %d help %d \n",
         plane_cmd->crtc_index,
         plane_cmd->ci_valid,
         plane_cmd->surface_index,
         plane_cmd->si_valid,
         plane_cmd->plane_type,
         plane_cmd->pt_valid,
         plane_cmd->info_cmd,
         plane_cmd->list_cmd,
         plane_cmd->help_cmd);
    
    dpu_info(INFO_LEVEL,"src_window (%d,%d,%d,%d) src_valid %d dst_window(%d,%d,%d,%d) dst_valid %d cmd_index %d, cmd_valid %d disable %d, d_v %d\n",
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
    
    dpu_info(INFO_LEVEL,"overlay key mode %d mode_valid %d kp %d  ks %d  kps_valid %d key_low 0x%x key_high 0x%x  key_valid %d\n",
         plane_cmd->overlay_cmd.mode,
         plane_cmd->overlay_cmd.m_valid,
         plane_cmd->overlay_cmd.kp,
         plane_cmd->overlay_cmd.ks,
         plane_cmd->overlay_cmd.kps_valid,
         plane_cmd->overlay_cmd.key_low,
         plane_cmd->overlay_cmd.key_high,
         plane_cmd->overlay_cmd.key_valid);
}

static void plane_handle_list(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct plane_cmd_t *cached_cmd = NULL;

    dpu_info(INFO_LEVEL,"list of cached plane cmd: \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[PLANE_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[PLANE_CMD][i].plane_cmd;
                 
            dpu_info(INFO_LEVEL,"index %d: crtc %d, plane %d, surface %d src(%d,%d,%d,%d) dst(%d,%d,%d,%d) disable %d\n",
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
            dpu_info(INFO_LEVEL,"          overlay: key mode %d kp %d ks %d key_l 0x%x  key_h 0x%x \n",
                cached_cmd->overlay_cmd.mode,
                cached_cmd->overlay_cmd.kp,
                cached_cmd->overlay_cmd.ks,
                cached_cmd->overlay_cmd.key_low,
                cached_cmd->overlay_cmd.key_high);  
        }
    }
}

static void plane_handle_help()
{
    u32 i = 0;
    for (i = 0; i < ARRAY_SIZE(plane_options_table); i++)
    {
        dpu_info(INFO_LEVEL,"%s\n", plane_options_table[i].options_help);
    }

    //add more help info here

    dpu_info(INFO_LEVEL,"--detail info about [-kp kp ks] [-kv key_low key_high]\n");
    dpu_info(INFO_LEVEL,"  0: Constant_Alpha;                 alpha = key_low\n");
    dpu_info(INFO_LEVEL,"  1: PS Alpha Blending;              alpha blend type = kp(0: coverage; 1: pre-multiplied), plane value = ks(0x00~0xFF)\n");
    dpu_info(INFO_LEVEL,"  2: SS/TS Over PS    Color Key;     kp, ks , colory_key = key_low\n");
    dpu_info(INFO_LEVEL,"  3: PS    Over SS/TS Color Key;     kp, ks , colory_key = key_low, need 30bpp color key\n");
    dpu_info(INFO_LEVEL,"  4: SS/TS Over PS    Window Key;    kp = kp(0~8), ks = ks(0~8)  NOTE: kp + ks = 8\n");
    dpu_info(INFO_LEVEL,"  5: SS/TS Over PS    Alpha Key;     kp = kp(0~8), ks = ks(0~8), alpha key = key_low(0x00~0xFF)  NOTE: kp + ks = 8\n");
    dpu_info(INFO_LEVEL,"  6: PS    Over SS/TS Window Key;    kp = kp(0~8), ks = ks(0~8)  NOTE: kp + ks = 8\n");
    dpu_info(INFO_LEVEL,"  7: PS    Over SS/TS Alpha Key;     kp = kp(0~8), ks = ks(0~8), alpha key = key_low(0x00~0xFF)  NOTE: kp + ks = 8\n");
    dpu_info(INFO_LEVEL,"  8: SS/TS Alpha Blending.           alpha blend type = kp(0: coverage; 1: pre-multiplied), plane value = ks\n\n");
    dpu_info(INFO_LEVEL,"  9: chroma Key;     lower key = key_low, key_hight = key_high\n");

}

static void plane_handle_info(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0, j = 0;
    struct plane_info_t *plane_info = NULL;
    
    for (i = 0; i < CRTC_NUM; i++)
    {
        dpu_info(INFO_LEVEL,"crtc %d \n",i);
        for (j = 0; j < PLANE_NUM; j++)
        {
            plane_info = &dpu_adapter->current_plane_info[i][j];

            if (plane_info->plane_state == PLANE_DISABLED || !plane_info->surface)
            {
                dpu_info(INFO_LEVEL,"      plane %d is disabled\n",j);
            }
            else
            {
                dpu_info(INFO_LEVEL,"      plane %d :src(%d,%d,%d,%d) dst(%d,%d,%d,%d) g_addr 0x%08x c_addr 0x%8x size (%d,%d) pitch %d, fmt %s, compress %d sur_index %d\n",
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
        

            if (1)//plane_info->plane_type != PRIMARY_PLANE)
            {
                dpu_info(INFO_LEVEL,"            overlay info : mode %s ", g_key_mode_string[plane_info->overlay_info.mode]);
                switch(plane_info->overlay_info.mode)
                {
                    case CONSTANT_ALPHA:
                        dpu_info(INFO_LEVEL,"            alpha: 0x%x, invert_alpha %d\n",
                        plane_info->overlay_info.constant_alpha_blending.constant_alpha,
                        plane_info->overlay_info.constant_alpha_blending.invert);
                        if (plane_info->overlay_info.constant_alpha_blending.plane_blending)
                        {
                            dpu_info(INFO_LEVEL,"            with plane bending: 0x%x \n",
                            plane_info->overlay_info.constant_alpha_blending.plane_value);
                        }
                        else
                        {
                            dpu_info(INFO_LEVEL,"            with no plane bneding\n");
                        }

                        break;
                    case PS_ALPHA_BLENDING:
                    case SS_ALPHA_BLENDING:
                        dpu_info(INFO_LEVEL,"            %s, use %s alpha, invert_alpha %d\n",
                        plane_info->overlay_info.alpha_blending.premul_blend ? "premult":"coverage",
                        plane_info->overlay_info.alpha_blending.use_ps_alpha ? "PS" : "SS",
                        plane_info->overlay_info.alpha_blending.invert_alpha);

                        dpu_info(INFO_LEVEL,"            with plane bending: 0x%x\n",
                        plane_info->overlay_info.alpha_blending.plane_value);
                  
                        break;
                    case POS_COLOR_KEY:
                    case SOP_COLOR_KEY:
                    //TODO: type ?
                        dpu_info(INFO_LEVEL,"color key 0x%x kp %d ks %d \n",
							plane_info->overlay_info.key_low, 
							plane_info->overlay_info.kp,
							plane_info->overlay_info.ks);
                        break;
                    case SOP_WINDOW_KEY:
                    case POS_WINDOW_KEY:
						dpu_info(INFO_LEVEL,"window key 0x%x kp %d ks %d \n",
							plane_info->overlay_info.key_low, 
							plane_info->overlay_info.kp,
							plane_info->overlay_info.ks);

                        break;
                    case  SOP_ALPHA_KEY:
                    case  POS_ALPHA_KEY:
                        dpu_info(INFO_LEVEL,"alpha key 0x%x kp %d ks %d\n",
							plane_info->overlay_info.key_low,
	                        plane_info->overlay_info.kp,
	                        plane_info->overlay_info.ks);
                        break;
                    case  CHROMA_KEY:

                        dpu_info(INFO_LEVEL,"lower bound 0x%x, upper bound 0x%x, kp %d ks %d\n",
	                        plane_info->overlay_info.key_low,
	                        plane_info->overlay_info.key_high,					
	                        plane_info->overlay_info.kp,
	                        plane_info->overlay_info.ks);
                        break;
                    default:

                        dpu_info(ERROR_LEVEL,"unknow blending mode !!!\n");
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
    struct dpu_plane_update_para_t plane_set ={0};
    struct surface_info_t *surface = NULL;
    u32 new_cmd = 1;
    u32 need_page_flip = 1;
    i32 i = 0, j = 0;

    plane_handle_trace(plane_cmd);

    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        dpu_info(INFO_LEVEL,"de is not available\n");
        goto end;
    }

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
            dpu_info(ERROR_LEVEL,"input crtc index is invalid ,please help check\n");
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
            dpu_info(ERROR_LEVEL,"input surface index is invalid ,please help check\n");
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
            dpu_info(ERROR_LEVEL,"input plane type is invalid ,please help check\n");
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
            dpu_info(ERROR_LEVEL,"input overlay key mode is invalid ,please help check\n");
            need_page_flip = 0;
        }       
    }

    
    if (plane_cmd->overlay_cmd.kps_valid)
    {
        prepare_cmd.overlay_cmd.kp = plane_cmd->overlay_cmd.kp;
        prepare_cmd.overlay_cmd.ks = plane_cmd->overlay_cmd.ks;
        prepare_cmd.overlay_cmd.kps_valid = 1;
    }

	if (plane_cmd->overlay_cmd.key_valid)
    {
        prepare_cmd.overlay_cmd.key_high = plane_cmd->overlay_cmd.key_high;
        prepare_cmd.overlay_cmd.key_low = plane_cmd->overlay_cmd.key_low;
        prepare_cmd.overlay_cmd.key_valid = 1;
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

        plane_set.crtc_index = prepare_cmd.crtc_index;

        if (prepare_cmd.plane_type <= DPU_CURSOR_PLANE)
        {
            plane_set.plane_type = prepare_cmd.plane_type;
        }

        if (plane_info->plane_state == PLANE_ENABLED)
        {
            if (prepare_cmd.disable_plane)
            {
                plane_set.flag = DPU_DISABLE_FLIP;
            }
            else
            {
                plane_set.flag = DPU_PAGE_FLIP;
            }
        }
        else
        {
            if (prepare_cmd.disable_plane)
            {
                plane_set.flag = DPU_ENABLE_FLIP;
            }
            else
            {
                plane_set.flag = DPU_PAGE_FLIP;
            }

        }

		plane_set.base.surface.addr = (plane_set.flag != DPU_DISABLE_FLIP) ? surface->gpu_addr : 0x12345680;

        plane_set.base.surface.format = surface->format;
        plane_set.base.surface.width = surface->width;
        plane_set.base.surface.height = surface->height;
        plane_set.base.surface.bit_cnt = surface->bit_cnt;
  
        plane_set.base.surface.pitch = surface->pitch;
        plane_set.base.surface.compressed =  0;

        plane_set.base.src_x = prepare_cmd.src_x ;
        plane_set.base.src_y = prepare_cmd.src_y ;
        plane_set.base.src_w = prepare_cmd.src_w;
        plane_set.base.src_h = prepare_cmd.src_h;

        plane_set.base.dst_x = prepare_cmd.dst_x;
        plane_set.base.dst_y = prepare_cmd.dst_y;
        plane_set.base.dst_w = prepare_cmd.dst_w;
        plane_set.base.dst_h = prepare_cmd.dst_h;

        if(0)//plane_cmd->plane_type == DPU_PRIMARY_PLANE)
        {
        	plane_set.base.overlay.mode = DPU_SOP_WINDOW_KEY;
            plane_set.base.overlay.kp = 0;
            plane_set.base.overlay.ks = 8;
        }

		//update && get overlay info 
		if (prepare_cmd.overlay_cmd.m_valid)
		{
		  	switch(prepare_cmd.overlay_cmd.mode)
		  	{
			  	case CONSTANT_ALPHA:
					plane_info->overlay_info.constant_alpha_blending.constant_alpha = prepare_cmd.overlay_cmd.key_low;
					plane_info->overlay_info.mode = CONSTANT_ALPHA;
					plane_set.base.overlay.constant_alpha = prepare_cmd.overlay_cmd.key_low;
					plane_set.base.overlay.mode = DPU_CONSTANT_ALPHA;
				  	break;
			  case PS_ALPHA_BLENDING:
					plane_info->overlay_info.alpha_blending.premul_blend = prepare_cmd.overlay_cmd.kp ? 1: 0;
					plane_info->overlay_info.mode = PS_ALPHA_BLENDING;
					plane_info->overlay_info.alpha_blending.plane_value = prepare_cmd.overlay_cmd.ks;
					plane_set.base.overlay.premul_blend = prepare_cmd.overlay_cmd.kp ? 1: 0;
					plane_set.base.overlay.mode = DPU_PS_ALPHA_BLENDING;
					plane_set.base.overlay.plane_alpha  = prepare_cmd.overlay_cmd.ks & 0xff;
					break;
			  case SOP_COLOR_KEY:
					plane_info->overlay_info.mode = SOP_COLOR_KEY;
					plane_info->overlay_info.key_low = prepare_cmd.overlay_cmd.key_low;
					plane_info->overlay_info.key_high = prepare_cmd.overlay_cmd.key_high;
					plane_info->overlay_info.kp = prepare_cmd.overlay_cmd.kp;
					plane_info->overlay_info.ks = prepare_cmd.overlay_cmd.ks;
					plane_set.base.overlay.mode = DPU_SOP_COLOR_KEY;
					plane_set.base.overlay.low_key = prepare_cmd.overlay_cmd.key_low;
					plane_set.base.overlay.high_key = prepare_cmd.overlay_cmd.key_high;
					plane_set.base.overlay.kp  = prepare_cmd.overlay_cmd.kp;
					plane_set.base.overlay.ks  = prepare_cmd.overlay_cmd.ks;		
					break;
			  case POS_COLOR_KEY:
					plane_info->overlay_info.mode = POS_COLOR_KEY;
					plane_info->overlay_info.key_low = prepare_cmd.overlay_cmd.key_low;
					plane_info->overlay_info.key_high = prepare_cmd.overlay_cmd.key_high;
					plane_info->overlay_info.kp = prepare_cmd.overlay_cmd.kp;
					plane_info->overlay_info.ks = prepare_cmd.overlay_cmd.ks;
					plane_set.base.overlay.mode = DPU_POS_COLOR_KEY;
					plane_set.base.overlay.kp  = prepare_cmd.overlay_cmd.kp;
					plane_set.base.overlay.ks  = prepare_cmd.overlay_cmd.ks;
					plane_set.base.overlay.low_key = prepare_cmd.overlay_cmd.key_low;
					plane_set.base.overlay.high_key = prepare_cmd.overlay_cmd.key_high;

					break;
			  case SOP_WINDOW_KEY:
					plane_info->overlay_info.mode = SOP_WINDOW_KEY;
					plane_info->overlay_info.kp = prepare_cmd.overlay_cmd.kp;
					plane_info->overlay_info.ks = prepare_cmd.overlay_cmd.ks;
					plane_info->overlay_info.key_low = prepare_cmd.overlay_cmd.key_low;
					plane_info->overlay_info.key_high = prepare_cmd.overlay_cmd.key_high;

					//printf("prepare kp %d ks %d key low 0x%x key_h 0x%x\n", prepare_cmd.overlay_cmd.kp,prepare_cmd.overlay_cmd.ks,prepare_cmd.overlay_cmd.key_low,prepare_cmd.overlay_cmd.key_high);
					//printf("planei  kp %d ks %d key low 0x%x key_h 0x%x\n",plane_info->overlay_info.kp,plane_info->overlay_info.ks,plane_info->overlay_info.key_low,
					//	plane_info->overlay_info.key_high);


					plane_set.base.overlay.mode = DPU_SOP_WINDOW_KEY;
					plane_set.base.overlay.kp = prepare_cmd.overlay_cmd.kp;
					plane_set.base.overlay.ks = prepare_cmd.overlay_cmd.ks;
					plane_set.base.overlay.low_key = prepare_cmd.overlay_cmd.key_low;
					plane_set.base.overlay.high_key = prepare_cmd.overlay_cmd.key_high;
					break;
			  case SOP_ALPHA_KEY:
					plane_info->overlay_info.mode = SOP_WINDOW_KEY;
					plane_info->overlay_info.kp = prepare_cmd.overlay_cmd.kp;
					plane_info->overlay_info.ks = prepare_cmd.overlay_cmd.ks;
					plane_info->overlay_info.key_low = prepare_cmd.overlay_cmd.key_low;
					plane_info->overlay_info.key_high = prepare_cmd.overlay_cmd.key_high;
					plane_set.base.overlay.mode = DPU_SOP_WINDOW_KEY;
					plane_set.base.overlay.kp = prepare_cmd.overlay_cmd.kp;
					plane_set.base.overlay.ks = prepare_cmd.overlay_cmd.ks;
					plane_set.base.overlay.low_key = prepare_cmd.overlay_cmd.key_low;
					plane_set.base.overlay.high_key  = prepare_cmd.overlay_cmd.key_high;
					break;
			  case POS_WINDOW_KEY:
					plane_info->overlay_info.mode = POS_WINDOW_KEY;
					plane_info->overlay_info.kp = prepare_cmd.overlay_cmd.kp;
					plane_info->overlay_info.ks = prepare_cmd.overlay_cmd.ks;
					plane_info->overlay_info.key_low = prepare_cmd.overlay_cmd.key_low;
					plane_info->overlay_info.key_high = prepare_cmd.overlay_cmd.key_high;
					plane_set.base.overlay.mode = DPU_POS_WINDOW_KEY;
					plane_set.base.overlay.kp = prepare_cmd.overlay_cmd.kp;
					plane_set.base.overlay.ks = prepare_cmd.overlay_cmd.ks;
					plane_set.base.overlay.low_key = prepare_cmd.overlay_cmd.key_low;
					plane_set.base.overlay.high_key = prepare_cmd.overlay_cmd.key_high;
					break;
			  case POS_ALPHA_KEY:
					plane_info->overlay_info.mode = POS_ALPHA_KEY;
					plane_info->overlay_info.kp = prepare_cmd.overlay_cmd.kp;
					plane_info->overlay_info.ks = prepare_cmd.overlay_cmd.ks;
					plane_info->overlay_info.key_low = prepare_cmd.overlay_cmd.key_low;
					plane_info->overlay_info.key_high = prepare_cmd.overlay_cmd.key_high;
					plane_set.base.overlay.mode = DPU_POS_ALPHA_KEY;
					plane_set.base.overlay.kp = prepare_cmd.overlay_cmd.kp;
					plane_set.base.overlay.ks = prepare_cmd.overlay_cmd.ks;
					plane_set.base.overlay.low_key = prepare_cmd.overlay_cmd.key_low;
					plane_set.base.overlay.high_key = prepare_cmd.overlay_cmd.key_high;

					break;
			  case SS_ALPHA_BLENDING:
					plane_info->overlay_info.alpha_blending.premul_blend = prepare_cmd.overlay_cmd.kp ? 1: 0;
					plane_info->overlay_info.mode = SS_ALPHA_BLENDING;
					plane_info->overlay_info.alpha_blending.plane_value = prepare_cmd.overlay_cmd.ks & 0xff;
					plane_set.base.overlay.premul_blend = prepare_cmd.overlay_cmd.kp ? 1: 0;
					plane_set.base.overlay.mode = DPU_SS_ALPHA_BLENDING;
					plane_set.base.overlay.plane_alpha = prepare_cmd.overlay_cmd.ks & 0xff;

					break;
			  case CHROMA_KEY:
					plane_info->overlay_info.key_low = prepare_cmd.overlay_cmd.key_low;
					plane_info->overlay_info.key_high = prepare_cmd.overlay_cmd.key_high;
					plane_info->overlay_info.kp = prepare_cmd.overlay_cmd.kp;
					plane_info->overlay_info.ks = prepare_cmd.overlay_cmd.ks;
					plane_info->overlay_info.mode = CHROMA_KEY;
					plane_set.base.overlay.mode = DPU_CHROMA_KEY;
					plane_set.base.overlay.high_key  = prepare_cmd.overlay_cmd.key_low;
					plane_set.base.overlay.low_key= prepare_cmd.overlay_cmd.key_high;
					plane_set.base.overlay.kp = prepare_cmd.overlay_cmd.kp;
					plane_set.base.overlay.ks = prepare_cmd.overlay_cmd.ks;

					break;
			  default:
				  	dpu_info(INFO_LEVEL,"shouldn't be here , invalid overlay key mode !!!\n");
				  	break;
		  	}

		}

        plane_info->plane_state = prepare_cmd.disable_plane;

        ret =  (dpu_plane_update(dpu_adapter->dpu_manager, &plane_set) == DPU_OK) ? TT_PASS : TT_FAIL;
    }


    ret = TT_PASS;

end:
    return ret;
}


static void surface_handle_trace(struct surface_cmd_t *surface_cmd)
{
    dpu_info(TRACE_LEVEL,"surface_index: %d si_valid %d, width %d height %d, alpha 0x%x, a_valid %d, pattern %d, format %d\n",
        surface_cmd->surface_index,
        surface_cmd->si_valid,
        surface_cmd->width,
        surface_cmd->height,
        surface_cmd->alpha,
        surface_cmd->alpha_valid,
        surface_cmd->pattern,
        surface_cmd->format);
    dpu_info(TRACE_LEVEL,"no_draw %d, premult %d, compressed %d, list_cmd %d, info_cmd %d help %d, cmd_index %d c_valid %d\n",
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
    
    dpu_info(INFO_LEVEL,"\nTotal surface num is %d\n", dpu_adapter->surface_manager.num);


    for (i = 0; i < MAX_SURFACE_NUM; i ++)
    {
        if (dpu_adapter->surface_manager.surfaces[i].valid == 0)
        {
            continue;
        }
        surface = &dpu_adapter->surface_manager.surfaces[i].surface;

        dpu_info(INFO_LEVEL,"surface %d: w %4d h %4d pitch %4d  %s,  %s, gpu_addr 0x%8x cpu_addr 0x%8x compress %d, do_premult %d\n",
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

     dpu_info(INFO_LEVEL,"\n");
}

static void surface_handle_help()
{
    u32 i = 0;
    for (i = 0; i < ARRAY_SIZE(surface_options_table); i++)
    {
        dpu_info(INFO_LEVEL,"%s\n", surface_options_table[i].options_help);
    }

    dpu_info(INFO_LEVEL,"--format index:\n");
    for (i = 1; i < ARRAY_SIZE(g_format_info_string); i++)
    {
        if (i % 10 == 0)
        {
            dpu_info(INFO_LEVEL,"\n");
        }

        dpu_info(INFO_LEVEL,"%d %s,",i,g_format_info_string[i].format_name);
    }

    dpu_info(INFO_LEVEL,"\n");
}

static void surface_handle_list(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct surface_cmd_t *cached_cmd = NULL;

    dpu_info(INFO_LEVEL,"list of cached surface cmd (just cache create cmd): \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[SURFACE_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[SURFACE_CMD][i].surface_cmd;
                 
            dpu_info(INFO_LEVEL,"index %d: width %d height %d aplha %d , pattern %s, format %s, no_draw %d, premult %d, compress %d\n",
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

        dpu_info(INFO_LEVEL,"please increase macro MAX_SURFACE_NUM \n");
        surface = NULL;
        return surface;
    }

    for (i = 0; i < MAX_SURFACE_NUM; i ++)
    {
        if (dpu_adapter->surface_manager.surfaces[i].valid == 0)
        {
            surface = &dpu_adapter->surface_manager.surfaces[i].surface;
            dpu_info(INFO_LEVEL,"create new surface, it's index is %d\n",i);
            break;
        }
    }

    if (i == MAX_SURFACE_NUM)
    {
        dpu_info(ERROR_LEVEL,"No enough surface id, please help check\n");
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
        dpu_info(ERROR_LEVEL,"%s:  invalid para \n",__func__);
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
            dpu_info(ERROR_LEVEL,"invalid surface format, please help check \n");
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
            dpu_info(ERROR_LEVEL,"invalid color pattern ,please help check \n");
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

        dpu_info(INFO_LEVEL,"create surface \n");
        ret = tt_create_surface(dpu_adapter, &prepare_cmd);
    }

end:
    return ret;
    
}

static void device_handle_trace(struct device_cmd_t *device_cmd)
{
    dpu_info(TRACE_LEVEL,"output 0x%x, disable %d, lr %d lc %d async_clck %d, enhanced_frame_mode %d\n",
        device_cmd->output,
        device_cmd->disable,
        device_cmd->link_rate,
        device_cmd->lane_count,
        device_cmd->async_clk,
        device_cmd->enhanced_frame_mode
        );


    dpu_info(TRACE_LEVEL,"bit_depth %d, color_fromat %d, cea %d, coef %d, modelist %d, info %d, list %d, help %d, cmd %d cmd valid %d\n",
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
        dpu_info(INFO_LEVEL,"%s\n", device_options_table[i].options_help);
    }

}

static void device_handle_info(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct output_info_t *output = NULL;

    dpu_info(INFO_LEVEL,"support device 0x%x \n", dpu_adapter->support_device);

    for (i = 0; i < PORT_NUM; i++)
    {
        output = &dpu_adapter->current_output_info[i];
        if (output->connect_status == DISCONNECTED)
        {
            dpu_info(INFO_LEVEL,"output 0x%x disconnected\n",output->device);
            continue;
        }

        if (output->power_status == POWER_OFF)
        {
            dpu_info(INFO_LEVEL,"output 0x%x is power off\n", output->device);
            continue;
        }

        if (output->crtc)
        {
            dpu_info(INFO_LEVEL,"crtc %d --- output 0x%x num_modes is %d, lr %d lc %d async_clck %d, enhanced_frame_mode %d\n",
                output->crtc->index,
                output->device,
                output->mode_list.num,
                output->link_rate,
                output->lane_count,
                output->async_clk,
                output->enhanced_frame_mode);

            dpu_info(INFO_LEVEL,"             bit_depth %d, color_fromat %d, cea %d, coef %d\n",
                output->bit_depth,
                output->color_format,
                output->cea,
                output->coef);
        }
        else
        {
            dpu_info(INFO_LEVEL,"device 0x%x is not active \n",output->device);
        }
    }
}


static void device_handle_list(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct device_cmd_t *cached_cmd = NULL;

    dpu_info(INFO_LEVEL,"list of cached device cmd: \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[DEVICE_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[DEVICE_CMD][i].device_cmd;
                 
            dpu_info(INFO_LEVEL,"index %d: output 0x%x, lr %d, lc %d, async_clock %d, frame_mode %d, bit_depth %d color_format %d cea %d coef %d\n",
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
	struct dpu_display_mode_t *mode;

    for (i = 0; i < PORT_NUM; i++)
    {
        if (output == dpu_adapter->current_output_info[i].device)
        {
            dpu_info(INFO_LEVEL,"mode num of 0x%x is %d \n",output,dpu_adapter->current_output_info[i].mode_list.num);

            for (j = 0; j < dpu_adapter->current_output_info[i].mode_list.num; j++)
            {
            	mode = &dpu_adapter->current_output_info[i].mode_list.modes[j];
                dpu_info(INFO_LEVEL,"%d: %d x %d @ %d\n",
                    j,
                    mode->hactive,
                    mode->vactive,
                    mode->refresh_rate);
            }
			break;
        }
    }
}

void print_display_info(struct dpu_adapter_t *dpu_adapter, u32 output)
{
    u32 i = 0,j = 0;
	struct output_info_t *output_info;
	struct dpu_display_info_t *display_info;;

    for (i = 0; i < PORT_NUM; i++)
    {
        if (output == dpu_adapter->current_output_info[i].device)
        {
			output_info = &dpu_adapter->current_output_info[i];
			display_info = &output_info->display_caps;

			if (display_info->monitor_type == MONITOR_TYPE_HDMI) {
				dpu_info(INFO_LEVEL,"hdmi: %s by %s, (%dx%d)cm\n", display_info->monitor_name, display_info->monitor_vendor,
					display_info->horizontal_cm, display_info->vertical_cm);
				dpu_info(INFO_LEVEL,"rgb color depth support: %s %s %s %s %s\n", 
					display_info->hdmi_caps.rgb_dc.dc_6 ? "6 bit" : "",
					display_info->hdmi_caps.rgb_dc.dc_10 ? "10 bit" : "",
					display_info->hdmi_caps.rgb_dc.dc_12 ? "12 bit" : "",
					display_info->hdmi_caps.rgb_dc.dc_14 ? "14 bit" : "",
					display_info->hdmi_caps.rgb_dc.dc_16 ? "16 bit" : "");
					dpu_info(INFO_LEVEL,"ycbcr444 color depth support: %s %s %s %s %s %s\n", 
					display_info->hdmi_caps.ycbcr444_dc.dc_6 ? "6 bit" : "",
					display_info->hdmi_caps.ycbcr444_dc.dc_10 ? "10 bit" : "",
					display_info->hdmi_caps.ycbcr444_dc.dc_12 ? "12 bit" : "",
					display_info->hdmi_caps.ycbcr444_dc.dc_14 ? "14 bit" : "",
					display_info->hdmi_caps.ycbcr444_dc.dc_16 ? "16 bit" : "");
					dpu_info(INFO_LEVEL,"ycbcr420 color depth support: %s %s %s %s %s %s\n", 
					display_info->hdmi_caps.ycbcr420_dc.dc_6 ? "6 bit" : "",
					display_info->hdmi_caps.ycbcr420_dc.dc_10 ? "10 bit" : "",
					display_info->hdmi_caps.ycbcr420_dc.dc_12 ? "12 bit" : "",
					display_info->hdmi_caps.ycbcr420_dc.dc_14 ? "14 bit" : "",
					display_info->hdmi_caps.ycbcr420_dc.dc_16 ? "16 bit" : "");
				dpu_info(INFO_LEVEL,"scramble support: %s\n", display_info->hdmi_caps.scramble ? "YES" : "NO");
				dpu_info(INFO_LEVEL,"scdc support: %s\n", display_info->hdmi_caps.scdc_support ? "YES" : "NO");
				dpu_info(INFO_LEVEL,"read request support: %s\n", display_info->hdmi_caps.read_request ? "YES" : "NO");
				
			}else if (display_info->monitor_type == MONITOR_TYPE_DVI) {
				dpu_info(INFO_LEVEL,"dvi: %s by %s, (%dx%d)cm\n", display_info->monitor_name, display_info->monitor_vendor,
					display_info->horizontal_cm, display_info->vertical_cm);
			} else if (display_info->monitor_type == MONITOR_TYPE_DP) {
				dpu_info(INFO_LEVEL,"dp: %s by %s, (%dx%d)cm\n", display_info->monitor_name, display_info->monitor_vendor,
					display_info->horizontal_cm, display_info->vertical_cm);
				dpu_info(INFO_LEVEL,"max link rate %d\n", display_info->dp_caps.max_link_rate);
				dpu_info(INFO_LEVEL,"max link cnt %d\n", display_info->dp_caps.max_link_cnt);
			} else if (display_info->monitor_type == MONITOR_TYPE_EDP) {
				dpu_info(INFO_LEVEL,"backlight support: %s\n", display_info->panel_caps.backlight_support ? "YES" : "NO");
				if (display_info->panel_caps.backlight_support) {
					dpu_info(INFO_LEVEL,"range: [%d - %d]\n", display_info->panel_caps.min_bl_level,
						display_info->panel_caps.max_bl_level);
				}
			}

			dpu_info(INFO_LEVEL,"max color depth %d\n", display_info->max_color_depth);
			dpu_info(INFO_LEVEL,"max tmds clock %d\n", display_info->max_tmds_clk);
			dpu_info(INFO_LEVEL,"output signal support: %s %s %s\n",
				display_info->support_signal.rgb ? "RGB" : "",
				display_info->support_signal.ycbcr444 ? "YCBCR444" : "",
				display_info->support_signal.ycbcr422 ? "YCBCR422" : "");
			dpu_info(INFO_LEVEL,"hdr support: %s\n", display_info->hdr_caps.hdr_support ? "YES" : "NO");
			if (display_info->hdr_caps.hdr_support) {
				dpu_info(INFO_LEVEL,"colorimetry support %s %s %s\n",
					display_info->hdr_caps.colorimetry.BT2020CYCC ? "BT2020 C YCC" : "",
					display_info->hdr_caps.colorimetry.BT2020YCC ? "BT2020 YCC" : "",
					display_info->hdr_caps.colorimetry.BT2020RGB ? "BT2020 RGB" : "");
				dpu_info(INFO_LEVEL,"eotf(gamma): %s %s %s %s", 
					display_info->hdr_caps.static_hdr.SMPT_2084 ? "SMPT 2084" : "",
					display_info->hdr_caps.static_hdr.HLG_gamma ? "HLG" : "");
				dpu_info(INFO_LEVEL,"luminance: [%d - %d] avr: %d\n",
					display_info->hdr_caps.static_hdr.desired_min_luminance,
					display_info->hdr_caps.static_hdr.desired_max_luminance,
					display_info->hdr_caps.static_hdr.desired_max_average_luminance);
			}
			dpu_info(INFO_LEVEL,"dynamic range support: %s\n", display_info->monitor_range.support ? "YES" : "NO");
			if (display_info->monitor_range.support)
				dpu_info(INFO_LEVEL,"%d - %d Hz\n", display_info->monitor_range.min_vrate, display_info->monitor_range.max_vrate);

			dpu_info(INFO_LEVEL,"audio support: %s\n", display_info->audio_support ? "YES ": "NO");

			
			break;
        }
    }
}


//Éè¼ÆÒ»¸ö×¨ÃÅµÄdpu º¯ÊýÀ´×ödevice ²ÎÊýµÄ´«µÝ£¬ ºÍdevice on off ²¢ÁÐ´æÔÚ£ ×öcts  test ?
static TT_STATUS device_handle(struct dpu_adapter_t *dpu_adapter, struct device_cmd_t *device_cmd)
{
    TT_STATUS ret = TT_PASS;
    u32 new_cmd = 1;
    u32 need_set_device = 1;

    struct dpu_device_set_t  device_set = {0};
    i32 i = 0;

    struct device_cmd_t prepare_cmd = {0};
    struct device_cmd_t *cached_cmd = NULL;

    device_handle_trace(device_cmd);

    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        dpu_info(INFO_LEVEL,"de is not available\n");
        goto end;
    }

    if (device_cmd->config_cmd)
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

	if (device_cmd->info_cmd)
	{
		print_display_info(dpu_adapter, device_cmd->output);
		goto end;
	}

    if (device_cmd->disable)
    {
        if (device_cmd->output & ((1 << PORT_NUM) - 1))
        {
            device_set.device = tt_get_last_bit(device_cmd->output);
            //device_set.state = DPU_POWER_OFF;
            dpu_set_device(dpu_adapter->dpu_manager, &device_set);

            dpu_adapter->current_output_info[device_set.device].power_status = POWER_OFF;
        }
        else
        {
            dpu_info(ERROR_LEVEL,"invalid device type, please help check \n");
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
        dpu_info(ERROR_LEVEL,"invalid device type, please help check \n");
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
    dpu_info(TRACE_LEVEL,"op %d, op_valid %d  crtc %d crtc_valid %d, type %d, mode %d surface %d s_valid %d \n",
        cursor_cmd->op,
        cursor_cmd->op_valid,
        cursor_cmd->crtc,
        cursor_cmd->crtc_valid,
        cursor_cmd->type,
        cursor_cmd->mode,
        cursor_cmd->surface_index,
        cursor_cmd->si_valid);

    dpu_info(TRACE_LEVEL,"pos_x %d pos_y %d pos_valid %d, cmd_index %d  cmd_valid %d list %d info %d help %d\n",
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

    dpu_info(INFO_LEVEL,"list of cached plane cmd: \n");
    for (i = 0; i < MAX_CACHED_CMD_NUM; i++)
    {
        if (dpu_adapter->cached_cmd[CURSOR_CMD][i].valid)
        {
            cached_cmd = &dpu_adapter->cached_cmd[CURSOR_CMD][i].cursor_cmd;
                 
            dpu_info(INFO_LEVEL,"%d: op %s, crtc %d , type %s, mode %s surface %d pos_x %d pos_y %d \n",
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
        dpu_info(INFO_LEVEL,"%s\n", cursor_options_table[i].options_help);
    }
}

static void cursor_handle_info(struct dpu_adapter_t *dpu_adapter)
{
    u32 i = 0;
    struct cursor_info_t *cursor_info = NULL;
    
    for (i = 0; i < CRTC_NUM; i++)
    {
        dpu_info(INFO_LEVEL,"crtc %d \n",i);
        
        cursor_info = &dpu_adapter->current_cursor_info[i];

        if (cursor_info->plane_state == PLANE_DISABLED || !cursor_info->surface)
        {
            dpu_info(INFO_LEVEL,"cursor is disabled\n");
        }
        else
        {
             dpu_info(INFO_LEVEL,"type %s, mode %s g_addr 0x%x c_addr 0x%x pos_x %d pos_y %d \n",
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
    
    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        dpu_info(INFO_LEVEL,"de is not available\n");
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
            dpu_info(ERROR_LEVEL,"input crtc index is invalid ,please help check\n");
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
            dpu_info(ERROR_LEVEL,"input cursor type is invalid ,please help check\n");
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
            dpu_info(ERROR_LEVEL,"input cursor mode is invalid ,please help check\n");
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
            dpu_info(ERROR_LEVEL,"input surface index is invalid ,please help check\n");
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
            dpu_info(ERROR_LEVEL,"set cursor failed ,please help check \n");
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

    dpu_info(TRACE_LEVEL,"in misc handle trace\n");

    for (i = 0; i < word_num; i++)
    {
        dpu_info(TRACE_LEVEL,"%s ",buffer[i]);
    }

    dpu_info(TRACE_LEVEL,"\n");
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
        dpu_info(INFO_LEVEL," pcir bus dev func  [offset] [value] \n");
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
        
            dpu_info(INFO_LEVEL,"       0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
            for (i = 0; i < 16; i++)
            {
                dpu_info(INFO_LEVEL,"0x%02x:",i*16);
                for (j = 0; j < 16; j++)
                {
                    tt_read_pci_config_byte(bus, dev, func, i*16 + j, &value);
                    dpu_info(INFO_LEVEL," %02x", value);
                }
                dpu_info(INFO_LEVEL,"\n");
            }

        }
        else
        {
            tt_read_pci_config_byte(bus, dev, func, offset, &value);
            dpu_info(INFO_LEVEL,"read 0x%x 0x%x 0x%x offset:0x%x value: 0x%x\n", bus, dev, func, offset, value);
        }
    }
     
    
}


static void handle_reg(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num, u32 base, u32 mask)
{
    u32 index = 0, value = 0;

    if (word_num < 2)
    {
        dpu_info(INFO_LEVEL,"%s     index   [value]\n", buffer[0]);
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

    dpu_info(INFO_LEVEL,"%s  0x%x  value : 0x%x\n", buffer[0], base + index, value);



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

        dpu_info(INFO_LEVEL,"%s  0x%x  new   : 0x%x\n", buffer[0], base + index, value);
    }
     

}

static void handle_mem(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num, MISC_OP_TYPE op )
{
    u32 offset = 0, value = 0, length = 0;
	void *addr = NULL;
    u32 i = 0, j = 0;

    if (op == OP_READ && word_num < 2)
    {
        dpu_info(INFO_LEVEL,"memr  offset    [length]\n");
        return ;
    }

    if (op == OP_WRITE && word_num < 3)
    {
        dpu_info(INFO_LEVEL,"memw  offset    value  [length]\n");
        return ;
    }

    offset = strtoul(buffer[1], NULL, 16);
    
    addr = offset + (u8*)dpu_adapter->base.fb_base;

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
    else if (op == OP_READ && word_num >= 3)
    {
        length = strtoul(buffer[2], NULL, 16);

        length = length % 8 ? (length/8 + 1): length /8;  //may read more data

        for (i = 0; i < length; i++)
        {
            dpu_info(INFO_LEVEL," 0x%x:",offset + i * 8);
            for (j = 0; j < 8; j ++)
            {
                dpu_info(INFO_LEVEL,"0x%08x ",tt_read_buffer_u32((u32*)addr + i * 8 + j));
            }
            dpu_info(INFO_LEVEL,"\n");
        }
    }
    else
    {
         value = tt_read_buffer_u32((u32*)addr);
         dpu_info(INFO_LEVEL," 0x%08x :  0x%08x\n", addr, value);
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

    dpu_info(INFO_LEVEL,"reg dump :");

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
    u8 device = 0;
    u8 addr = 0;
    u32 offset = 0;
    u8 value = 0, temp = 0, old = 0, sum = 0;
    u8 get_offset = 0, get_value = 0;
    u32 i = 0, j = 0;
    struct dpu_i2c_para_t i2c_para = {0};


    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        dpu_info(INFO_LEVEL,"de is not available\n");
        return;
    }

    if (word_num < 3)
    {
        dpu_info(INFO_LEVEL,"i2c group  addr offset value \n");
        return ;
    }

    device = dpu_get_connector_from_port(dpu_adapter->dpu_manager, strtoul(buffer[1], NULL, 16));

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

    i2c_para.slave_addr = addr;
    i2c_para.data = &temp;
    i2c_para.length = 1;
    i2c_para.offset = 0;

    if (!get_value) //i2c read 
    {
        i2c_para.rw = 0;
        if (!get_offset)
        {
            dpu_info(INFO_LEVEL,"    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            for (i = 0; i < 16; i++)
            {
                dpu_info(INFO_LEVEL,"%02x ", i);
                for (j = 0; j < 16; j++)
                {
                    i2c_para.offset = i * 16 + j;
                    dpu_i2c_transfer(dpu_adapter->dpu_manager, device, &i2c_para);

                    dpu_info(INFO_LEVEL," %02x", temp);
                    if (i < 8)
                    {
                        sum += temp;
                    }
                }
                dpu_info(INFO_LEVEL,"\n");
            }
            dpu_info(INFO_LEVEL,"check sum = %02x\n", sum);
        }
        else
        {
            i2c_para.offset = offset;
            
            dpu_i2c_transfer(dpu_adapter->dpu_manager, device, &i2c_para);
            dpu_info(INFO_LEVEL,"group 0x%x addr 0x%x offset 0x%x value :0x%x\n", device, addr, offset, temp);
        }
    }
    else //i2c write
    {
        i2c_para.rw = 0;
        i2c_para.offset = offset;
        i2c_para.data = &old;
        
        dpu_i2c_transfer(dpu_adapter->dpu_manager, device, &i2c_para); 
        //dpu_info(INFO_LEVEL,"grop 0x%x addr 0x%x offset 0x%x value :0x%x\n",group, addr, offset, temp);

        i2c_para.rw = 1;
        i2c_para.data = &value;
        
        dpu_i2c_transfer(dpu_adapter->dpu_manager, device, &i2c_para);

        i2c_para.rw = 0;
        i2c_para.data = &temp;
   
        dpu_i2c_transfer(dpu_adapter->dpu_manager, device, &i2c_para);

        if (temp != value)
        {
            dpu_info(INFO_LEVEL,"write device 0x%x addr 0x%x offset 0x%x failed,old value is 0x%x now value is 0x%x\n",
                device,
                addr,
                offset,
                old,
                temp);
        }
        else
        {
            dpu_info(INFO_LEVEL,"write device 0x%x addr 0x%x offset 0x%x  value 0x%x successfully\n",
                device, 
                addr, 
                offset, 
                value);
        }
    }
}

static void handle_aux(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    struct dpu_aux_para_t aux_para = {0};
    u32 port = 0;
    u32 offset = 0;
    u8 value = 0, temp = 0, old = 0;
    u8  get_value = 0;


    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        dpu_info(INFO_LEVEL,"de is not available\n");
        return;
    }

    if (word_num < 3)
    {
        dpu_info(INFO_LEVEL,"aux port offset value\n");
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

        dpu_info(INFO_LEVEL,"read device 0x%x offset 0x%x value :0x%x\n", port, offset, temp);
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
            dpu_info(INFO_LEVEL,"write port 0x%x offset 0x%x failed,old value is 0x%x now value is 0x%x\n",
                port,
                offset,
                old,
                temp);
        }
        else
        {
            dpu_info(INFO_LEVEL,"write port 0x%x offset 0x%x value 0x%x successfully\n",
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
        dpu_info(INFO_LEVEL,"lf filename offset \n");
        return ;
    }

    if (op == OP_READ && word_num < 4)
    {
        dpu_info(INFO_LEVEL,"sf filename offset size \n");
        return ;
    }

    file_name = buffer[1];
    offset = strtoul(buffer[2], NULL, 16);


	if(offset < MAX_SURFACE_NUM)
	{
		if (dpu_adapter->surface_manager.surfaces[offset].valid)
		{
			offset = dpu_adapter->surface_manager.surfaces[offset].surface.gpu_addr;
		}
		else
		{
			dpu_info(INFO_LEVEL, "surface %d has no video memory yet\n",offset);
			return ;
		}
	}
       

    if (op == OP_READ)
    {
      	fp = fopen(file_name, "wb+");
		
	    if (!fp)
	    {
	        dpu_info(INFO_LEVEL,"open file %s failed \n",file_name);
	        return;
	    }
        size = strtoul(buffer[3], NULL, 16);
        fwrite((void*)((u8*)dpu_adapter->base.fb_base + offset), size, 1, fp);
        
        dpu_info(INFO_LEVEL,"save to file done\n");
        fclose(fp);
    }
    else
    {
    	fp = fopen(file_name, "rb");
		
	    if (!fp)
	    {
	        dpu_info(INFO_LEVEL,"open file %s failed \n",file_name);
	        return;
	    }
        fseek(fp, 0, SEEK_END);
        file_size = ftell(fp);

		dpu_info(INFO_LEVEL, "load file size is %d\n", file_size);

        fseek(fp, 0, SEEK_SET);
        fread((void*)((u8*)dpu_adapter->base.fb_base + offset), file_size, 1, fp);
        
        dpu_info(INFO_LEVEL,"load file to offset 0x%x done \n",offset);
        fclose(fp);
    }
}

void handle_help()
{

    dpu_info(INFO_LEVEL,"mode    -help  for mode help info\n");
    dpu_info(INFO_LEVEL,"plane   -help  for plane help info\n");
    dpu_info(INFO_LEVEL,"surface -help  for surface help info\n");
    dpu_info(INFO_LEVEL,"device  -help  for device help info\n");
    dpu_info(INFO_LEVEL,"cursor  -help  for cursor help info \n");

    
    dpu_info(INFO_LEVEL,"\n In misc handle below ,all data is hex\n\n");
    
    dpu_info(INFO_LEVEL,"pcir  bus  dev  func  [offset] [value] \n");
    dpu_info(INFO_LEVEL,"cr    index   [value]\n");
    dpu_info(INFO_LEVEL,"crb   index   [value]\n");
    dpu_info(INFO_LEVEL,"sr    index   [value]\n");
    dpu_info(INFO_LEVEL,"srb   index   [value]\n");
    dpu_info(INFO_LEVEL,"mmio  index   [value]\n");
    dpu_info(INFO_LEVEL,"memr  offset  [length]\n");
    dpu_info(INFO_LEVEL,"memw  offset   value [length]\n");
    dpu_info(INFO_LEVEL,"dump  [file_name]  dump all regs to console/file\n");
    dpu_info(INFO_LEVEL,"i2c   group  addr   offset value \n");
    dpu_info(INFO_LEVEL,"aux   port   offset value\n");
    dpu_info(INFO_LEVEL,"lf    filename     offset \n");     //TODO: maybe we need surface index ?
    dpu_info(INFO_LEVEL,"sf    filename     offset size \n");
    dpu_info(INFO_LEVEL,"csc   <path>  <index1>  [index2] \n");
    dpu_info(INFO_LEVEL,"  path: 1 :plane csc   index1 = crtc index  index2 = plane index\n");  //plane csc just test csc ? 
                                                                                     //device csc test color enhancement ?
    dpu_info(INFO_LEVEL,"  path: 2 :device csc  index1 = port index\n");
    dpu_info(INFO_LEVEL,"gamma   <index> <domain> <mode> \n");
    dpu_info(INFO_LEVEL,"   index: crtc index \n");
    dpu_info(INFO_LEVEL,"   domain: 1: primary only 2: overlay only 3: blend data \n");
    dpu_info(INFO_LEVEL,"   mode :  1: 8bit single, 2: 8bit split 3: 10bit single 4: 10bit split \n");


	dpu_info(INFO_LEVEL,"check crtc   check hw signature with sw value\n");
    dpu_info(INFO_LEVEL,"q  exit program\n");
}


static void handle_csc(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
   struct csc_para_t csc_para = {0};

    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        dpu_info(INFO_LEVEL,"de is not available\n");
        return;
    }

   //put csc para to output_info_t

    dpu_info(INFO_LEVEL,"in handle csc \n");
}


static void handle_gamma(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    //test gamma 

    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        dpu_info(INFO_LEVEL,"de is not available\n");
        return;
    }

    dpu_info(INFO_LEVEL,"in handle gamma \n");

}

static void handle_hda(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
    //How ?

    if (dpu_adapter->test_domain & TEST_WITHOUT_DE)
    {
        dpu_info(INFO_LEVEL,"de is not available\n");
        return;
    }
    dpu_info(INFO_LEVEL,"in handle hda\n");
}

static void handle_echo(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
	u32 i = 1;

	while(i < word_num)
	{
		dpu_info(INFO_LEVEL, "%s ",buffer[i]);
		i++;
	}

	dpu_info(INFO_LEVEL, "\n");
}


void get_hw_signature(struct dpu_adapter_t *dpu_adapter, u32 crtc, u64* value)
{
	struct hw_signature_t  sig = {0};

	sig.crtc = crtc;
	dpu_get_hw_signature(dpu_adapter->dpu_manager, &sig);

	*value = sig.value;
}

TT_STATUS do_signature_compare(struct dpu_adapter_t *dpu_adapter, u32 crtc, u32 sw_value)
{
	u32 i = 3;
	u64 hw_value = 0;

	get_hw_signature(dpu_adapter, crtc, &hw_value);

	while(--i && sw_value != hw_value)
	{
		tt_delay_micro_seconds(17);
		get_hw_signature(dpu_adapter, crtc, &hw_value);
	}

	if (i == 0)
	{
		dpu_info(ERROR_LEVEL, "Signature check failed  !!!\n");
		return TT_FAIL;
	}
	else
	{
		dpu_info(ERROR_LEVEL, "Signature check successed\n");

		return TT_PASS;
	}

}

#ifdef __DPU_LINUX_KERNEL__


static void load_data(u8* file_name, void * dst, u32_t bpp, u32_t width, u32_t height);

void prepare_cmodel_args(struct dpu_adapter_t *dpu_adapter, struct cmodel_args_t *args, struct de_hw_env_t *hw_env)
{
	u32 size = 0;

	u32 i = 0;

	memset(args, 0, sizeof(struct cmodel_args_t));

	args->plane_info[0] = &dpu_adapter->current_plane_info[args->crtc][0];
	args->plane_info[1] = &dpu_adapter->current_plane_info[args->crtc][1];

	args->cursor_info = &dpu_adapter->current_cursor_info[args->crtc];

	if (hw_env->iwin.iwin_en)
	{
		size = hw_env->iwin.height * hw_env->iwin.width * sizeof(struct bus_1010108);
		args->iwin= tt_malloc_mem(size);
	}

	size = dpu_adapter->current_crtc_info[args->crtc].adjust_mode.hactive * 
			dpu_adapter->current_crtc_info[args->crtc].adjust_mode.vactive * sizeof(struct bus_1010108);

	//backgroud used for overlay ,must destination size
	args->background =  tt_malloc_mem(size);

	dpu_info(INFO_LEVEL, "in prepare_cmodel_args \n");
	
	for (i = 0; i < 2; i++)
	{
		if (hw_env->spl[i].spl_en)
		{

			size = args->plane_info[i]->src_w * args->plane_info[i]->src_h * 4;
			#if __KX6000__ 
			args->spl_input_src[i] = (u8*)(dpu_adapter->base.fb_base) + hw_env->spl[i].base_addr + hw_env->spl[i].base_off;
			#else
			args->spl_input_src[i] = tt_malloc_mem(size);

			load_data("dump_0000.bin", args->spl_input_src[i], 4, args->plane_info[i]->src_w,args->plane_info[i]->src_h);

			#endif
			
			size = args->plane_info[i]->src_w * args->plane_info[i]->src_h * sizeof(struct bus_1010108);
			dpu_info(INFO_LEVEL,"spl input dst size %d\n",size);
			args->spl_input_dst[i] =  tt_malloc_mem(size); //need check input module	s
			size = args->plane_info[i]->dst_w * args->plane_info[i]->dst_h * sizeof(struct bus_1010108);
			dpu_info(INFO_LEVEL,"scl dst size %d\n",size);
			args->spl_scl_dst[i] = tt_malloc_mem(size);
			args->spl_csc_dst[i] = tt_malloc_mem(size);
		}
	}
	#if 0
	if (hw_env->spl[1].spl_en)
	{
		args->spl_input_src[1] = (u8*)(dpu_adapter->base.fb_base + hw_env->spl[1].gpu_addr);
		size = args->plane_info[1]->src_w * args->plane_info[1]->src_h * sizeof(struct bus_1010108);
		args->spl_input_dst[1] = tt_malloc_mem(size);
		size = args->plane_info[1]->dst_w * args->plane_info[1]->dst_h * sizeof(struct bus_1010108);
		args->spl_scl_dst[1] = tt_malloc_mem(size);
		args->spl_csc_dst[1] = tt_malloc_mem(size);
	}
	#endif

	if(hw_env->cur.cur_en)
	{
		args->cur_input_src = dpu_adapter->current_cursor_info[args->crtc].surface->cpu_addr;
		//should be big enough
		size = args->cursor_info->surface->width * args->cursor_info->surface->height * 4; 
		args->cur_input_dst = tt_malloc_mem(size);
		args->cur_csc_dst = tt_malloc_mem(size);   //need consider x_off ,y_off ???
	}
	
	//lut,csc, dither size is destination window ,right ?
	size = dpu_adapter->current_crtc_info[args->crtc].adjust_mode.hactive * 
			dpu_adapter->current_crtc_info[args->crtc].adjust_mode.vactive * sizeof(struct bus_1010108);
	args->pipe_pu_dst = tt_malloc_mem(size);
	args->pipe_lut_dst = tt_malloc_mem(size);
	args->pipe_csc_dst = tt_malloc_mem(size);
	args->pipe_dither_dst = tt_malloc_mem(size);

	args->dest_win_w = dpu_adapter->current_crtc_info[args->crtc].adjust_mode.hactive;
	args->dest_win_h = dpu_adapter->current_crtc_info[args->crtc].adjust_mode.vactive;

}

void release_cmodel_res(struct cmodel_args_t  *args)
{
	tt_free_mem(args->iwin);
	tt_free_mem(args->background);
	//tt_free_mem(args->spl_input_src[0]);
	//tt_free_mem(args->spl_input_src[1]);
	tt_free_mem(args->spl_input_dst[0]);
	tt_free_mem(args->spl_input_dst[1]);
	tt_free_mem(args->spl_scl_dst[0]);
	tt_free_mem(args->spl_scl_dst[1]);
	tt_free_mem(args->spl_csc_dst[0]);
	tt_free_mem(args->spl_csc_dst[1]);
	tt_free_mem(args->cur_csc_dst);
	//tt_free_mem(args->cur_input_src);
	tt_free_mem(args->cur_input_dst);
	tt_free_mem(args->pipe_pu_dst);
	tt_free_mem(args->pipe_dither_dst);
	tt_free_mem(args->pipe_lut_dst);
	tt_free_mem(args->pipe_csc_dst);
	
}

void prepare_input_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct input_para_t * para, u32 pipe)
{
	memset(para, 0, sizeof(struct input_para_t ));

	para->stride = hw_env->spl[pipe].stride;
	para->spl_abgr = hw_env->spl[pipe].abgr;
	para->spl_crycb = hw_env->spl[pipe].crycb;
	para->spl_cbycry = hw_env->spl[pipe].cbycry;
	para->pix_off = hw_env->spl[pipe].pix_off;
	para->spl_fmt = hw_env->spl[pipe].spl_fmt;

	para->src = (unsigned short * )args->spl_input_src[pipe];
	para->dst = (unsigned short * )args->spl_input_dst[pipe];

	para->width = args->plane_info[pipe]->src_w;
	para->height = args->plane_info[pipe]->src_h;

}


void prepare_curosr_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct cursor_para_t *para)
{
	memset(para, 0, sizeof(struct cursor_para_t ));


	para->src = (unsigned short*)args->cur_input_src;
	para->dst = (unsigned short*)args->cur_input_dst;
	para->panel_width = hw_env->iwin.width;
	para->panel_height = hw_env->iwin.height;
	para->x_start = hw_env->cur.x_start;
	para->y_start =	hw_env->cur.y_start;
	para->x_off =  hw_env->cur.x_offset;
	para->y_off = hw_env->cur.y_offset;
	para->cur_size = hw_env->cur.cur_size;
	para->cur_type = hw_env->cur.cur_type;
	para->cur_mono_bg = hw_env->cur.mono_bg;
	para->cur_mono_fg = hw_env->cur.mono_fg;
}

void prepare_scl_stream_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct scl_stream_para_t *para, u32 pipe)
{
	memset(para, 0, sizeof(struct scl_stream_para_t ));


	para->src_w = hw_env->spl[pipe].src_w;
	para->src_h = hw_env->spl[pipe].src_h;
	para->dst_w = hw_env->spl[pipe].dst_w;
	para->dst_h = hw_env->spl[pipe].dst_h;

    para->is_cos_h = hw_env->spl[pipe].is_cos_h;
    para->is_cos_v = hw_env->spl[pipe].is_cos_v;
    para->is_alpha_ups = hw_env->spl[pipe].is_alpha_ups;
    para->is_v_duplicate = hw_env->spl[pipe].is_v_duplicate;
    para->keyl =  hw_env->spl[pipe].keyl;
    para->keyh = hw_env->spl[pipe].keyh;
    para->key_mode = (pipe == 0) ? hw_env->ovl.ovl0_key_mode : hw_env->ovl.ovl1_key_mode;
    para->h_acc = hw_env->spl[pipe].hacc;
    para->v_acc = hw_env->spl[pipe].vacc;


	cmodel_debug(INFO_LEVEL,"cmodel_dump:sw(%d,%d) dw(%d,%d),cos_h %d cos_v %d alpha_up %d v_dup %d key1 0x%x keyh 0x%x, key_mode %d, h_acc 0x%x v_acc 0x%x\n",
		para->src_w,
		para->src_h,
		para->dst_w,
		para->dst_h,
		para->is_cos_h,
		para->is_cos_v,
		para->is_alpha_ups,
		para->is_v_duplicate,
		para->keyl,
		para->keyh,
		para->key_mode,
		para->h_acc,
		para->v_acc);


	para->src = (unsigned short*)args->spl_input_dst[pipe];
	para->dst = (unsigned short*)args->spl_scl_dst[pipe];

}

void prepare_csc_plane_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct csc_plane_para_t *para, u32 pipe)
{
	memset(para, 0, sizeof(struct csc_plane_para_t ));

	para->width = hw_env->spl[pipe].dst_w;
	para->height = hw_env->spl[pipe].dst_h;

	para->infmt = hw_env->spl[pipe].csc.input_fmt;
	para->outfmt = hw_env->spl[pipe].csc.output_fmt;
	para->bright = hw_env->spl[pipe].csc.bright;

	para->prog = hw_env->spl[pipe].csc.prog;

	para->coef1 = hw_env->spl[pipe].csc.coef1;
	para->coef2 = hw_env->spl[pipe].csc.coef2;
	para->coef3 = hw_env->spl[pipe].csc.coef3;
	para->coef4 = hw_env->spl[pipe].csc.coef4;
	para->coef5 = hw_env->spl[pipe].csc.coef5;
	para->coef6 = hw_env->spl[pipe].csc.coef6;
	para->coef7 = hw_env->spl[pipe].csc.coef7;
	para->coef8 = hw_env->spl[pipe].csc.coef8;
	para->coef9 = hw_env->spl[pipe].csc.coef9;

	para->src = (unsigned short*)args->spl_scl_dst[pipe];
	para->dst = (unsigned short*)args->spl_csc_dst[pipe];
	

}

void prepare_csc_cursor_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct csc_cursor_para_t *para, i32 out_w, i32 out_h)
{
	memset(para, 0, sizeof(struct csc_cursor_para_t ));
	
	para->width = out_w;
	para->height = out_h;

	para->fmt = hw_env->cur.out_fmt;

	para->src =(unsigned short*)args->cur_input_dst;
	para->dst =(unsigned short*)args->cur_csc_dst;


}



void prepare_overlay_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct overlay_para_t *para, u32 out_w, u32 out_h)
{
	memset(para, 0, sizeof(struct overlay_para_t ));


	
	para->ovl0_key_mode = hw_env->ovl.ovl0_key_mode;
	para->ovl0_pla_fct = hw_env->ovl.ovl0_kp;
	para->ovl0_plb_fct = hw_env->ovl.ovl0_ks;
	para->ovl0_bld_mode = hw_env->ovl.ovl0_bld_mode;
	para->ovl0_is_inv_alpha = hw_env->ovl.ovl0_inv_alpha;
	para->ovl0_plane_alpha_val = hw_env->ovl.ovl0_plane_alpha;
	para->ovl0_alpha_key_sel = hw_env->ovl.ovl0_alpha_key_sel;
	para->ovl0_color_key_sel = hw_env->ovl.ovl0_color_key_sel;
	para->ovl0_is_alpha_rang = hw_env->ovl.ovl0_is_alpha_rang;
	para->ovl0_is_mdi_sec = hw_env->spl[0].spl_sec;
	para->ovl0_is_ref_int = hw_env->itg.spl_ref_iwin;
	para->ovl0_is_ycbcr = hw_env->spl[0].csc.output_fmt > 1 ? 1 : 0;
	
	para->ovl1_key_mode = hw_env->ovl.ovl1_key_mode;
	para->ovl1_pla_fct = hw_env->ovl.ovl1_kp;
	para->ovl1_plb_fct = hw_env->ovl.ovl1_ks;
	para->ovl1_bld_mode = hw_env->ovl.ovl1_bld_mode;
	para->ovl1_is_inv_alpha = hw_env->ovl.ovl1_inv_alpha;
	para->ovl1_plane_alpha_val = hw_env->ovl.ovl1_plane_alpha;
	para->ovl1_alpha_key_sel = hw_env->ovl.ovl1_alpha_key_sel;
	para->ovl1_color_key_sel = hw_env->ovl.ovl1_color_key_sel;
	para->ovl1_is_alpha_rang = hw_env->ovl.ovl1_is_alpha_rang;
	para->ovl1_is_mdi_sec = hw_env->spl[1].spl_sec;
	para->ovl1_is_ref_int = hw_env->itg.spl_ref_iwin;
	para->ovl1_is_ycbcr =  hw_env->spl[1].csc.output_fmt > 1 ? 1 : 0;

	para->pu_en = hw_env->pu.pus_en;

	if (hw_env->spl[0].spl_en)
	{
		para->win_0_start_x = hw_env->spl[0].start_x;
		para->win_0_start_y = hw_env->spl[0].start_y;
		para->win_0_width = hw_env->spl[0].dst_w;
		para->win_0_height = hw_env->spl[0].dst_h;
	}
	else
	{
		para->win_0_start_x = 1;
		para->win_0_start_y = 1;
		para->win_0_width = 0;
		para->win_0_height = 0;
	}

	if (hw_env->spl[1].spl_en)
	{
		para->win_1_start_x = hw_env->spl[1].start_x;
		para->win_1_start_y = hw_env->spl[1].start_y;
		para->win_1_width = hw_env->spl[1].dst_w;
		para->win_1_height = hw_env->spl[1].dst_h;
	}
	else
	{
		para->win_1_start_x = 1;
		para->win_1_start_y = 1;
		para->win_1_width = 0;
		para->win_1_height = 0;
	}

	if (hw_env->cur.cur_en)
	{
		para->win_cur_start_x = hw_env->cur.x_start;
		para->win_cur_start_y = hw_env->cur.y_start;
		para->win_cur_width = out_w;
		para->win_cur_height = out_h;
	}
	else
	{
		para->win_cur_start_x = 1;
		para->win_cur_start_y = 1;
		para->win_cur_width = 0;
		para->win_cur_height = 0;
	}

	para->bg_color = hw_env->ovl.bg_color;
	para->bg_ycbcr = hw_env->ovl.bg_ycbcr;

	para->win0_src = (unsigned short*)args->spl_csc_dst[0];
	para->win1_src = (unsigned short*)args->spl_csc_dst[1];
	para->cur_src = (unsigned short*)args->cur_csc_dst;

	para->cur_type = hw_env->cur.cur_type;
	para->is_curs_ycbcr = hw_env->cur.out_fmt > 1 ? 1 : 0;
	para->is_curs_ref_int = hw_env->itg.cur_ref_iwin;

	para->iwin_start_x = hw_env->iwin.start_x;
	para->iwin_start_y = hw_env->iwin.start_y;
	para->iwin_width = hw_env->iwin.width;
	para->iwin_height = hw_env->iwin.height;

	para->dst_width = args->dest_win_w;
	para->dst_height = args->dest_win_h;

	para->dst = (unsigned short*)args->background;

	cmodel_debug(INFO_LEVEL,"pu_en is %d iwin_start_x  %d iwin_start_y %d  iwin_w %d iwin_h %d d_w %d, d_h %d\n",
			para->pu_en,
			para->iwin_start_x,
			para->iwin_start_y,
			para->iwin_width,
			para->iwin_height,
			para->dst_width,
			para->dst_height);

	

	cmodel_debug(INFO_LEVEL,"spl0  width %d height %d rect[%d,%d,%d,%d] \n",
						para->win_0_width, 
						para->win_0_height,
						para->win_0_start_x,
						para->win_0_start_y,
						para->win_0_width,
						para->win_0_height);

	cmodel_debug(INFO_LEVEL,"spl1  width %d height %d rect[%d,%d,%d,%d] \n",
						para->win_1_width, 
						para->win_1_height,
						para->win_1_start_x,
						para->win_1_start_y,
						para->win_1_width,
						para->win_1_height);
	cmodel_debug(INFO_LEVEL,"cursor  width %d height %d rect[%d,%d,%d,%d] \n",
						para->win_cur_width, 
						para->win_cur_height,
						para->win_cur_start_x,
						para->win_cur_start_y,
						para->win_cur_width,
						para->win_cur_height);

	cmodel_debug(INFO_LEVEL,"cmodel_dump: bg_color is %d bg_ycbcr is %d\n", para->bg_color, para->bg_ycbcr);

	cmodel_debug(INFO_LEVEL,"cmodel_dump: key_mode_0 %d, pla_fct_0 %d plb_fct_0 %d bld_mode_0 %d is_inv_alpha_0 %d\n",
		para->ovl0_key_mode,
		para->ovl0_pla_fct,
		para->ovl0_plb_fct,
		para->ovl0_bld_mode,
		para->ovl0_is_inv_alpha);
	
	cmodel_debug(INFO_LEVEL,"cmodel_dump: plane_alpha_0 0x%x alpha_key_sel_0 %d is_alpha_rang_0 %d color_key_sel_0 %d is_ycbcr_0 %d is_mdi_sec_0 %d  is_ref_int_0 %d\n",
		para->ovl0_plane_alpha_val,
		para->ovl0_alpha_key_sel,
		para->ovl0_is_alpha_rang,
		para->ovl0_color_key_sel,
		para->ovl0_is_ycbcr,
		para->ovl0_is_mdi_sec,
		para->ovl0_is_ref_int);
	
	cmodel_debug(INFO_LEVEL,"cmodel_dump: key_mode_1 %d, pla_fct_1 %d plb_fct_1 %d bld_mode_1 %d is_inv_alpha_1 %d\n",
		para->ovl1_key_mode,
		para->ovl1_pla_fct,
		para->ovl1_plb_fct,
		para->ovl1_bld_mode,
		para->ovl1_is_inv_alpha);

	cmodel_debug(INFO_LEVEL,"cmodel_dump: plane_alpha_1 0x%x alpha_key_sel_1 %d is_alpha_rang_1 %d color_key_sel_1 %d is_ycbcr_1 %d is_mdi_sec_1 %d  is_ref_int_1 %d\n",
		para->ovl1_plane_alpha_val,
		para->ovl1_alpha_key_sel,
		para->ovl1_is_alpha_rang,
		para->ovl1_color_key_sel,
		para->ovl1_is_ycbcr,
		para->ovl1_is_mdi_sec,
		para->ovl1_is_ref_int);
	cmodel_debug(INFO_LEVEL,"cmodel_dump: cursor type %d cur_ycbcr %d  cur_is_int %d efuse_sec %d\n",
		para->cur_type,
		para->is_curs_ycbcr,
		para->is_curs_ref_int,
		0);

}

void prepare_scl_panel_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct scl_panel_para_t* para)
{
	memset(para, 0, sizeof(struct scl_panel_para_t ));

	para->src_w = hw_env->iwin.width;
	para->src_h = hw_env->iwin.height;
	para->dst_w = hw_env->pu.pus_width_dst;
	para->dst_h = hw_env->pu.pus_height_dst;

	para->start_x = hw_env->iwin.start_x;
	para->start_y = hw_env->iwin.start_y;

	para->panel_width = args->dest_win_w;
	para->panel_height = args->dest_win_h;

	para->en = hw_env->pu.pus_en;
    para->h_en = hw_env->pu.pus_hen;
    para->v_en = hw_env->pu.pus_ven;
    para->h_acc = hw_env->pu.pus_ratio_h;
    para->v_acc = hw_env->pu.pus_ration_v;

    para->is_cos = hw_env->pu.pus_cos2tap;
    para->is_hw_ratio = hw_env->pu.pus_ration_mode;
    para->ratio_plus = hw_env->pu.pus_ratio_plus;

	para->bg_color = hw_env->ovl.bg_color;

	para->src = (unsigned short *)args->background;
	para->dst = (unsigned short *)args->pipe_pu_dst;

	cmodel_debug(INFO_LEVEL,"cmodel_dump: pu_en %d h_en %d v_en %d h_acc 0x%x v_acc 0x%x is_cos %d is_hw_ratio %d ratio_pus %d bg 0x%x\n",
		para->en,
		para->h_en,
		para->v_en,
		para->h_acc,
		para->v_acc,
		para->is_cos,
		para->is_hw_ratio,
		para->ratio_plus,
		para->bg_color);
	cmodel_debug(INFO_LEVEL,"cmodel_dump: s_w %d s_h %d d_w %d d_h %d start_x %d start_y %d dest_w %d dest_h %d\n",
		para->src_w,
		para->src_h,
		para->dst_w,
		para->dst_h,
		para->start_x,
		para->start_y,
		para->panel_width,
		para->panel_height);

}

void prepare_lut_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct lut_para_t *para)
{
	memset(para, 0, sizeof(struct lut_para_t ));

	para->width = args->dest_win_w;
	para->height = args->dest_win_h;
		
	para->lut_en = hw_env->lut.lut_lut_en;
	para->lut_intp_on = hw_env->lut.lut_intp_on;
	para->lut_bitwidth = hw_env->lut.lut_bitwidth;
	
	memcpy(para->lut_data, hw_env->lut.lut_data, 256 * sizeof(unsigned int));

	para->src = (unsigned short*)args->pipe_pu_dst;
	para->dst = (unsigned short*)args->pipe_lut_dst;

}


void prepare_dither_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct dither_para_t *para)
{
	memset(para, 0, sizeof(struct dither_para_t ));

	para->width = args->dest_win_w;
	para->height = args->dest_win_h;

	para->dither_en = hw_env->dither.dither_en;
	para->dist_en = hw_env->dither.dither_dist_en;
	para->base = hw_env->dither.dither_base;
	para->bitsel = hw_env->dither.dither_bitsel;

	para->src = (unsigned short*)args->pipe_csc_dst;
	para->dst = (unsigned short*)args->pipe_dither_dst;
}


void prepare_csc_panel_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct csc_plane_para_t *para)
{
	memset(para, 0, sizeof(struct csc_plane_para_t ));

	para->width = args->dest_win_w;
	para->height = args->dest_win_h;

	para->infmt = hw_env->pipe_csc.input_fmt;
	para->outfmt = hw_env->pipe_csc.output_fmt;
	para->bright = hw_env->pipe_csc.bright;

	para->prog = hw_env->pipe_csc.prog;

	para->coef1 = hw_env->pipe_csc.coef1;
	para->coef2 = hw_env->pipe_csc.coef2;
	para->coef3 = hw_env->pipe_csc.coef3;
	para->coef4 = hw_env->pipe_csc.coef4;
	para->coef5 = hw_env->pipe_csc.coef5;
	para->coef6 = hw_env->pipe_csc.coef6;
	para->coef7 = hw_env->pipe_csc.coef7;
	para->coef8 = hw_env->pipe_csc.coef8;
	para->coef9 = hw_env->pipe_csc.coef9;

	para->src = (unsigned short*)args->pipe_lut_dst;
	para->dst = (unsigned short*)args->pipe_csc_dst;


}

void prepare_signature_args(struct cmodel_args_t  *args, struct de_hw_env_t *hw_env, struct signature_para_t *para)
{
	memset(para, 0, sizeof(struct signature_para_t ));

	para->width = args->dest_win_w;
	para->height = args->dest_win_h;

	para->src = (unsigned short*)args->pipe_dither_dst;
}


static u32_t file_name_count = 0;
static void dump_data(u8* file_name, void * src, u32_t bpp, u32_t width, u32_t height)
{
	FILE * fp = NULL;
	u32 file_size = 0;
	u32 size = 0;


    fp = fopen(file_name, "wb+");
    if (!fp)
    {
        dpu_info(INFO_LEVEL,"open file %s failed ,dump data failed\n",file_name);
        return;
    }     

	
    size = bpp * width * height;

	cmodel_debug(INFO_LEVEL,"cmodel_dump: dump file: %s %p  w %d  h %d  bpp %d\n", file_name, src, width, height, bpp);
	
    file_size = fwrite((void*)src, size, 1, fp);

	if (file_size != 1)
	{
		cmodel_debug(INFO_LEVEL,"cmodel_dump: error expect write %d size, actually write %d  !!!\n",size ,file_size);
	}
    
    //dpu_info(INFO_LEVEL,"save to file done\n");
    fclose(fp);

  

}


static void load_data(u8* file_name, void * dst, u32_t bpp, u32_t width, u32_t height)
{
	FILE * fp = NULL;
	u32 file_size = 0;
	u32 size = 0;


    fp = fopen(file_name, "rb");
    if (!fp)
    {
        dpu_info(INFO_LEVEL,"open file %s failed ,load data failed\n", file_name);
        return;
    }     

	
    size = bpp * width * height;

	cmodel_debug(INFO_LEVEL,"cmodel_dump: load file: %s %p  w %d  h %d  bpp %d\n", file_name, dst, width, height, bpp);
	
    file_size = fread((void*)dst, size, 1, fp);

	if (file_size != 1)
	{
		cmodel_debug(INFO_LEVEL,"cmodel_dump: error expect load %d size, actually load %d  !!!\n",size ,file_size);
	}
    
    //dpu_info(INFO_LEVEL,"save to file done\n");
    fclose(fp);

  

}


TT_STATUS do_dpu_process(struct dpu_adapter_t *dpu_adapter, u32 crtc, u64* sw_sig)
{
	TT_STATUS ret = TT_PASS;
	struct de_hw_env_t hw_env = {0};
	struct cmodel_args_t  args = {0};
	struct input_para_t input_para ={0};
	struct cursor_para_t cursor_para = {0};
	struct scl_stream_para_t  scl_stream_para = {0};
	struct csc_plane_para_t  csc_plane_para = {0};
	struct csc_cursor_para_t csc_cursor_para = {0};
	struct overlay_para_t    overlay_para = {0};
	struct scl_panel_para_t  scl_panel_para = {0};

	struct lut_para_t 	lut_para = {0};
	struct dither_para_t dither_para = {0};
	struct signature_para_t signature_para = {0};

	i32_t out_h, out_w;

	hw_env.crtc = crtc;
	dpu_get_hw_env(dpu_adapter->dpu_manager, &hw_env);

	args.crtc = crtc;
	prepare_cmodel_args(dpu_adapter, &args, &hw_env);

	if (hw_env.spl[0].spl_en)
	{
		prepare_input_args(&args, &hw_env, &input_para, 0);
		dump_data("dump_data/spl0_input_src.bin", input_para.src, 4, input_para.width, input_para.height);
		
		input_wrapper(&input_para); 
		dump_data("dump_data/spl0_input_dst.bin", input_para.dst, 8, input_para.width, input_para.height);

		prepare_scl_stream_args(&args, &hw_env, &scl_stream_para, 0);
		scl_stream_wrapper(&scl_stream_para);
		dump_data("dump_data/spl0_scl_dst.bin", scl_stream_para.dst, 8, scl_stream_para.dst_w, scl_stream_para.dst_h);
		
		prepare_csc_plane_args(&args, &hw_env, &csc_plane_para, 0);
	    csc_plane_wrapper(&csc_plane_para);
		dump_data("dump_data/spl0_csc_dst.bin", csc_plane_para.dst, 8, csc_plane_para.width, csc_plane_para.height);
	}

	if (hw_env.spl[1].spl_en)
	{
		prepare_input_args(&args, &hw_env, &input_para, 1);
		dump_data("dump_data/spl1_input_src.bin", input_para.src, 4, input_para.width, input_para.height);

		input_wrapper(&input_para);
		dump_data("dump_data/spl1_input_dst.bin", input_para.dst, 8, input_para.width, input_para.height);

		prepare_scl_stream_args(&args, &hw_env, &scl_stream_para, 1);
		scl_stream_wrapper(&scl_stream_para);
		dump_data("dump_data/spl1_scl_dst.bin", scl_stream_para.dst, 8, scl_stream_para.dst_w, scl_stream_para.dst_h);

		prepare_csc_plane_args(&args, &hw_env, &csc_plane_para, 1);
		csc_plane_wrapper(&csc_plane_para);
		dump_data("dump_data/spl1_csc_dst.bin", csc_plane_para.dst, 8, csc_plane_para.width, csc_plane_para.height);
	}

	if (hw_env.cur.cur_en)
	{
		prepare_curosr_args(&args, &hw_env, &cursor_para);
		cursor_wrapper(&cursor_para, &out_w, &out_h);

		prepare_csc_cursor_args(&args, &hw_env, &csc_cursor_para, out_w, out_h);
		csc_cursor_wrapper(&csc_cursor_para);
	}

	//overlay bg,spl0,spl1,cursor together to  bg layer(destinatio window) ,need iwin info
	prepare_overlay_args(&args, &hw_env, &overlay_para, out_w, out_h);
	overlay_wrapper(&overlay_para);

	dump_data("dump_data/pipe_ovl_dst.bin", overlay_para.dst, 8, overlay_para.dst_width, overlay_para.dst_height);

	prepare_scl_panel_args(&args, &hw_env, &scl_panel_para);
	//if pu is diable ,will copy src to dst
	scl_panel_wrapper(&scl_panel_para);
	dump_data("dump_data/pipe_scl_dst.bin", scl_panel_para.dst, 8, scl_panel_para.panel_width, scl_panel_para.panel_height);

	prepare_lut_args(&args, &hw_env, &lut_para);
	//pass lut, will copy src to dst
	lut_wrapper(&lut_para);
	dump_data("dump_data/pipe_lut_dst.bin", lut_para.dst, 8, lut_para.width, lut_para.height);

	prepare_csc_panel_args(&args, &hw_env, &csc_plane_para);
	//can't bypass csc,  translate src to dst
	csc_plane_wrapper(&csc_plane_para);
	dump_data("dump_data/pipe_lut_dst.bin", csc_plane_para.dst, 8, csc_plane_para.width, csc_plane_para.height);

	prepare_dither_args(&args, &hw_env, &dither_para);
	//pass dither, will copy src to dst
	dither_wrapper(&dither_para);
	dump_data("dump_data/pipe_lut_dst.bin", dither_para.dst, 8, dither_para.width, dither_para.height);

	prepare_signature_args(&args, &hw_env, &signature_para);
	*sw_sig = signature_wrapper(&signature_para);

	dpu_info(INFO_LEVEL,"get cmodel signature 0x%x\n", *sw_sig);


	release_cmodel_res(&args);
 
}


static TT_STATUS handle_check_signature(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
	u32  crtc = 0 ;
	TT_STATUS ret = TT_PASS;
	u64  sw_sig = 0;


	if (word_num >= 2)
	{
		crtc = strtoul(buffer[1], NULL, 10);

		if (crtc > CRTC_NUM)
		{
			dpu_info(ERROR_LEVEL," invalid crtc index %d\n",crtc);
			return TT_FAIL;
		}
	}
	else
	{
		dpu_info(ERROR_LEVEL, "need crtc index \n");
		return TT_FAIL;
	}

	ret = do_dpu_process(dpu_adapter, crtc, &sw_sig);
	if (ret != TT_PASS)
	{
		dpu_info(ERROR_LEVEL, "dpu cmodel process failed \n");
		goto end;
	}

	//ret = do_signature_compare(dpu_adapter, crtc, sw_sig);

end:
	return ret;

}
#else

static TT_STATUS handle_check_signature(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{

	dpu_info(ERROR_LEVEL, "signature check are only supported on linux \n");
	return TT_FAIL;
}


#endif


static TT_STATUS misc_handle(struct dpu_adapter_t *dpu_adapter, u8 buffer[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
	TT_STATUS ret = TT_PASS;
    misc_handle_trace(buffer, word_num);

    if (tt_is_same_str("pcir", buffer[0]))
    {
        handle_pcir(dpu_adapter, buffer, word_num);
    }
    else if (tt_is_same_str("mmio", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, MMIO_BASE, 0xffffffff);
    }
    else if (tt_is_same_str("cr", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, CR_BASE, 0xff);
    }
    else if (tt_is_same_str("crb", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, CR_B_BASE, 0xff);
    }
    else if (tt_is_same_str("sr", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, SR_BASE, 0xff);
    }
    else if (tt_is_same_str("srb", buffer[0]))
    {
        handle_reg(dpu_adapter, buffer, word_num, SR_B_BASE, 0xff);
    }
    else if (tt_is_same_str("memr", buffer[0]))
    {
        handle_mem(dpu_adapter, buffer, word_num, OP_READ);
    }
    else if (tt_is_same_str("memw", buffer[0]))
    {
        handle_mem(dpu_adapter, buffer, word_num, OP_WRITE);
    }
    else if (tt_is_same_str("dump", buffer[0]))
    {
        handle_dump(dpu_adapter, buffer, word_num);
    }
    else if (tt_is_same_str("i2c", buffer[0]))
    {
        handle_i2c(dpu_adapter, buffer, word_num);
    }
    else if (tt_is_same_str("aux", buffer[0]))
    {
        handle_aux(dpu_adapter, buffer, word_num);
    }
    else if (tt_is_same_str("lf", buffer[0]))
    {
        handle_file(dpu_adapter, buffer, word_num, OP_WRITE);
    }
    else if (tt_is_same_str("sf", buffer[0]))
    {
        handle_file(dpu_adapter, buffer, word_num, OP_READ);
    }
    else if (tt_is_same_str("help", buffer[0]))
    {
        handle_help(dpu_adapter, buffer, word_num);
    }
    else if (tt_is_same_str("csc", buffer[0]))
    {
        handle_csc(dpu_adapter, buffer, word_num);
    }
    else if (tt_is_same_str("gamma", buffer[0]))
    {
        handle_gamma(dpu_adapter, buffer, word_num);
    }
    else if (tt_is_same_str("hda", buffer[0]))
    {
        handle_hda(dpu_adapter, buffer, word_num);
    }
	else if (tt_is_same_str("echo", buffer[0]))
	{
		handle_echo(dpu_adapter, buffer, word_num);
	}
	else if (tt_is_same_str("check", buffer[0]))
	{
		ret = handle_check_signature(dpu_adapter, buffer, word_num);
	}
    else
    {
        dpu_info(ERROR_LEVEL,"unknow misc operation :%s  \n",buffer[0]);
    }

	return ret;

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
        dpu_info(INFO_LEVEL,"\n index %d is %s %d\n",i, dpu_adapter->cmd_history[i], strlen(dpu_adapter->cmd_history[i]));
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
    u8 ch;
    u8 *position = NULL;
    i32 up_times = 0;
    u32 use_input = 0;
    u32 cache_cmd_index = 0;
	u32 i;


    dpu_info(INFO_LEVEL,">");

	//dpu_info(INFO_LEVEL,">");

   // dump_cmd_history(dpu_adapter);
  
    position = cmd_line;
    do{

        ch = getch();
		//dpu_info(INFO_LEVEL,"ch is  0x%x	 ",ch);

#ifdef __DPU_LINUX_KERNEL__
        if(ch == KEY_UP_DOWN_PRE)
        {
        	ch = getch();
           	if (ch == 91)   // 27  91  65/66 on linux
           	{
				ch = getch();

				if(ch == 65)
				{
					ch = KEY_UP;
				}
				else if (ch == 66)
				{
					ch = KEY_DOWN;
				}
				else
			    {
					continue;
				}
		    }
		    else if (ch == 27)  //need type twice
			{
				ch = KEY_ESC;
			}
			else
		    {
		    	continue;
		    }
        }

#endif
        if (ch == KEY_UP)
        {
            up_times ++;
            i = position - cmd_line;

            while (i > 0)
            {
                *position = '\0';
                dpu_info(INFO_LEVEL,"%c", KEY_BACKSPACE);
                dpu_info(INFO_LEVEL,"%c", KEY_SPACE);
                dpu_info(INFO_LEVEL,"%c", KEY_BACKSPACE);
                i--;
                position--;
            }

            cache_cmd_index = get_cmd_index(dpu_adapter, up_times);

            strcpy(cmd_line, dpu_adapter->cmd_history[cache_cmd_index]);
            position = cmd_line + strlen(cmd_line);

            dpu_info(INFO_LEVEL,"%s",cmd_line);
           
        }
        else if (ch == KEY_DOWN)
        {
            up_times --;
            i = position - cmd_line;

            while (i > 0)
            {
                *position = '\0';
                dpu_info(INFO_LEVEL,"%c", KEY_BACKSPACE);
                dpu_info(INFO_LEVEL,"%c", KEY_SPACE);
                dpu_info(INFO_LEVEL,"%c", KEY_BACKSPACE);
                i--;
                position--;
            }
            
            cache_cmd_index = get_cmd_index(dpu_adapter, up_times);

            strcpy(cmd_line, dpu_adapter->cmd_history[cache_cmd_index]);
            position = cmd_line + strlen(cmd_line);

            dpu_info(INFO_LEVEL,"%s",cmd_line);
        }
        else if ((ch != KEY_ENTER) && (ch != KEY_BACKSPACE) && (ch != KEY_ESC) && (ch != 127))
        {
            *position = ch;
            position ++;
            *position = '\0';

            use_input = 1;
            
            dpu_info(INFO_LEVEL,"%c", ch);
        }
        else if (ch == 127 || ch == KEY_BACKSPACE)
        {
            i = position - cmd_line;
            if (position > cmd_line)
            {
                position --;
            }
            *position = '\0';
 
            if (i > 0)
            {
                dpu_info(INFO_LEVEL,"%c", KEY_BACKSPACE); //0x8
                dpu_info(INFO_LEVEL,"%c", KEY_SPACE);
                dpu_info(INFO_LEVEL,"%c", KEY_BACKSPACE);
            }
        }
        else if (ch == KEY_ESC)//clear all cmd_line
        {
            i = position - cmd_line;

            while (i > 0)
            {
                *position = '\0';
                dpu_info(INFO_LEVEL,"%c", KEY_BACKSPACE);
                dpu_info(INFO_LEVEL,"%c", KEY_SPACE);
                dpu_info(INFO_LEVEL,"%c", KEY_BACKSPACE);
                i--;
                position--;
            }
            //position = cmd_line;
        }
    }while(ch != KEY_ENTER);

    *position = '\0';

    if (use_input)
    {
       // dump_cmd_history(dpu_adapter);
        add_to_cmd_history(dpu_adapter, cmd_line);
        //dpu_info(INFO_LEVEL,"\n  ,add to cmd_line is %s  %d\n", cmd_line, strlen(cmd_line));

        //dump_cmd_history(dpu_adapter);
    }
    dpu_info(INFO_LEVEL,"\n");
}


TT_STATUS do_exec_cmd(struct dpu_adapter_t *dpu_adapter, u8 str[][MAX_CMD_OPTION_NAME_SIZE], u32 word_num)
{
	struct options_table *table;
	struct support_cmd *command = NULL;
	void* cmd = NULL;
	u8   found = 0;

	u32   support_cmd_num = 0;
	u32   i = 0, j = 0 ,k = 0;
	u32   item_num = 0;

	TT_STATUS ret = TT_PASS;

	support_cmd_num = ARRAY_SIZE(g_support_cmd);

	i = 0;
	found = 0;
	while(i < support_cmd_num)
	{
	    if (!strcmp(str[0], g_support_cmd[i].cmd_name))
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
	}
	else
	{
	    memset(command->cmd, 0 , command->cmd_size);
	

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
		}
		else
		{
			ret = TT_FAIL;
		}
	}

	return ret;

}
void process_cmd(struct dpu_adapter_t *dpu_adapter)
{
    TT_STATUS ret = TT_PASS;
 
	u32 	word_num = 0;
    u8   	cmd_line[MAX_CMD_STRING_NUM];
    u8   	str[50][MAX_CMD_OPTION_NAME_SIZE];


	//
	do_script_exec(dpu_adapter);


    while(1)
    {
        memset(cmd_line, 0 , MAX_CMD_STRING_NUM);

        memset(str, 0, 50 * MAX_CMD_OPTION_NAME_SIZE);

        get_input(dpu_adapter, cmd_line);

		ret = tt_get_words(cmd_line, &word_num, str);

		if (ret != TT_PASS)
		{
			break;
		}

		if (word_num == 0)
		{
			continue;
		}

        ret = do_exec_cmd(dpu_adapter, str, word_num);

		if (ret != TT_PASS)
		{
			int i = 0;

			dpu_info(ERROR_LEVEL, "run cmd failed :");
			while(i < word_num)
			{
				dpu_info(ERROR_LEVEL,"%s ",str[i]);
				i++;
			}
			dpu_info(ERROR_LEVEL,"\n");
		}

   }
   
}

#if 0

void main()
{

    u32 i = 0, j = 0;
    struct dpu_adapter_t  dpu_adapter = {0};

    dpu_info(INFO_LEVEL,"in main func \n");


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

