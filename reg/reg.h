#ifndef __REG_H__
#define __REG_H__

#include "../config.h"

struct reg_field{
	char * name;
	unsigned int bits_num;
	unsigned int shift;
	unsigned int reg_addr;
};

struct reg_info {
	char* reg_block_name;
	unsigned int reg_mmio_addr;
	unsigned int reg_sub_index;
	unsigned int field_num;
	unsigned int reg_in_bytes;
};

enum REG_CATEGORY {
	REG_DP = 0,
	REG_HDMI,
	REG_HDA,
	REG_CODEC,
	REG_CODEC2,
	REG_CR,
	REG_CR2,
	REG_CR3,
	REG_SR,
	REG_SR2,
	REG_SR3,
	REG_ITG,
	REG_ITG2,
	REG_ITG3,
	REG_PIPE,
	REG_PIPE2,
	REG_PIPE3,
	REG_ITG_SHARE,
	REG_CR_SHARE,
	REG_PWM,
	REG_INTG,
	REG_MDI,
	REG_DVO,
//	REG_SR_SHARE,
	REG_BLOCK_NUM
};

enum PARA_CONTENT_TYPE {
	PARA_TYPE_INVALID = 0,
	PARA_TYPE_ADDR_INDEX,
	PARA_TYPE_ADDR_BLOCK_NAME,
	PARA_TYPE_FIELD_NAME,
};

enum PARA_OP_TYPE {
	OP_TYPE_INVALID = 0,
	OP_TYPE_READ_WITH_ADDR_INDEX,
	OP_TYPE_READ_WITH_BLOCK_AND_INDEX,
	OP_TYPE_READ_WITH_FIELD_NAME,
	OP_TYPE_DUMP_WITH_BLOCK_NAME,
	OP_TYPE_DUMP_ALL,
	OP_TYPE_UPDATE_WITH_ADDR_INDEX,
	OP_TYPE_UPDATE_WITH_FIELD_NAME,
	OP_TYPE_UPDATE_WITH_ADDR_INDEX_AND_FIELD_NAME,
	OP_TYPE_UPDATE_WITH_BLOCK_AND_INDEX,
	OP_TYPE_UPDATE_WITH_BLOCK_AND_INDEX_AND_FIELD_NAME,
};

struct reg_block_info
{
	enum REG_CATEGORY reg_id;
	char* block_name;
	unsigned int reg_count;
	unsigned int reg_start;
	unsigned int reg_end;
	unsigned int reg_in_bytes;
	unsigned int total_field_count;
	struct reg_info ** info;
	struct reg_field **field_info;
};

int handle_reg_main(struct dpu_adapter_t *dpu_adapter, unsigned char argv[][MAX_CMD_OPTION_NAME_SIZE], int argc);
#endif
