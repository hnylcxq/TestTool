#ifndef _CONFIG_H_
#define _CONFIG_H_




#define    FLAG_BUFFER_BASE  0x0



#define    SURFACE_MEM_BASE  (FLAG_BUFFER_BASE + FLAG_BUFFER_SIZE)
#define    RESERVED_MEM_SIZE  (FLAG_BUFFER_SIZE)


#define  __KX6000__  1

#if __KX6000__

#define 	VENDER_XX     		0x1d17
#define 	BAR_MMIO_OFFSET  	0x10
#define 	BAR_FB_OFFSET  		0x14
#define    	FLAG_BUFFER_SIZE  	0x1000000



//#define MAX_CRTC_NUM    3
//#define MAX_DEVICE_NUM  3
//#define MAX_PLANE_NUM   2
#else

#define 	VENDER_XX	  		0x15ad
#define 	BAR_MMIO_OFFSET  	0x18
#define 	BAR_FB_OFFSET  		0x14
#define    	FLAG_BUFFER_SIZE    0x0




#endif



#define MAX_SURFACE_NUM         10
#define FORMAT_NAME_LENGTH      32

#define MAX_CACHED_CMD_NUM      5

#define MAX_CMD_OPTION_NAME_SIZE  100

#define MAX_CMD_STRING_NUM      512
#define MAX_INPUT_HISTORY_NUM      10


#define CR_BASE     0x8800
#define CR_B_BASE   0x8900
#define SR_BASE     0x8600
#define SR_B_BASE   0x8700
#define MMIO_BASE   0

#define SCRIPT_ARRAY_MAX_NUM  50
#define SCRIPT_LINE_MAX_NUM   256
#define SCRIPT_LINE_MAX_WORD_NUM    50
#define SCRIPT_MAX_WORD_SIZE   MAX_CMD_OPTION_NAME_SIZE

#define CMODEL_DEBUG  1


#endif
