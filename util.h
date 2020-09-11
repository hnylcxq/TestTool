#ifndef _UTIL_H_
#define _UTIL_H

typedef enum _TT_CACHE_FLAG_
{
	CACHE_ENABLE = 1,
	CACHE_DISABLE = 2,
}TT_CACHE_FLAG;


struct pci_card_info_t
{
	u16  vender_id;
	u16  device_id;
	
	
};



#define tt_align(size, align)  ((size + align - 1) & (~(align - 1)))





#endif