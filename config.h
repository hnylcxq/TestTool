#ifndef _CONFIG_H_
#define _CONFIG_H_

#define    FLAG_BUFFER_BASE  0x0
#define    FLAG_BUFFER_SIZE  0x1000000


#define    SURFACE_MEM_BASE  (FLAG_BUFFER_BASE + FLAG_BUFFER_SIZE)
#define    RESERVED_MEM_SIZE  (FLAG_BUFFER_SIZE)


#define VENDER_XX     0x1d17
//#define MAX_CRTC_NUM    3
//#define MAX_DEVICE_NUM  3
//#define MAX_PLANE_NUM   2


#define MAX_SURFACE_NUM         10
#define FORMAT_NAME_LENGTH      32

#define MAX_CACHED_CMD_NUM      5

#define MAX_CMD_OPTION_NAME_SIZE  20


#define CR_BASE     0x8800
#define CR_B_BASE   0x8900
#define SR_BASE     0x8600
#define SR_B_BASE   0x8700
#define MMIO_BASE   



0




#endif


