#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "reg.h"
#include "../util.h"

#define reg_print printf

#define REG_BLOCK_NAME(name) name##_reg_block_name
#define REG_COUNT(name) name##_reg_count
#define REG_START(name) name##_reg_start
#define REG_END(name) name##_reg_end
#define REG_IN_BYTES(name) name##_reg_in_bytes
#define REG_TOTAL_FIELDS(name) name##_reg_total_field_count
#define REG_BLOCK_INFO(name) name##_reg_info
#define REG_BLOCK_FIELD_INFO(name) name##_reg_field_info

#define DECLARE_REG_INFO_WITH_BLOCK_NAME(name) \
extern char * REG_BLOCK_NAME(name);\
extern unsigned int REG_COUNT(name);\
extern unsigned int REG_START(name);\
extern unsigned int REG_END(name);\
extern unsigned int REG_IN_BYTES(name);\
extern unsigned int REG_TOTAL_FIELDS(name);\
extern struct reg_info * REG_BLOCK_INFO(name)[];\
extern struct reg_field * REG_BLOCK_FIELD_INFO(name)[];\

#define REG_INFO(block_name, index) block_name##_reg_##index

#define INIT_REG_INFO_WITH_BLOCK_NAME(index, name)\
	DECLARE_REG_INFO_WITH_BLOCK_NAME(name);\
	regs[index].reg_id = index;\
	regs[index].block_name = REG_BLOCK_NAME(name);\
	regs[index].reg_count = REG_COUNT(name);\
	regs[index].reg_start = REG_START(name);\
	regs[index].reg_end = REG_END(name);\
	regs[index].reg_in_bytes = REG_IN_BYTES(name);\
	regs[index].total_field_count = REG_TOTAL_FIELDS(name);\
	regs[index].info = REG_BLOCK_INFO(name);\
	regs[index].field_info = REG_BLOCK_FIELD_INFO(name);


struct reg_block_info regs[REG_BLOCK_NUM] = {
		{0},
};

struct dpu_adapter_t *reg_adapter;

void init_reg_info(void)
{
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_DP, dp);         }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_HDMI, hdmi);     }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_HDA, hda);       }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_CODEC, codec);   }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_CODEC2, codec2); }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_CR, cr);         }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_CR2, cr2);       }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_CR3, cr3);       }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_SR, sr);         }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_SR2, sr2);       }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_SR3, sr3);       }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_ITG, itg);       }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_ITG2, itg2);     }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_ITG3, itg3);     }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_PIPE, pipe);     }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_PIPE2, pipe2);   }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_PIPE3, pipe3);   }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_ITG_SHARE, itgs);}
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_CR_SHARE, crs);  }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_PWM, pwm);       }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_INTG, intg);     }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_MDI, mdi);       }
	{INIT_REG_INFO_WITH_BLOCK_NAME(REG_DVO, dvo);       }


}

unsigned int read_u32(unsigned int addr)
{
	return tt_read_u32(reg_adapter, addr);
}

void write_u32(unsigned int addr, unsigned int value)
{
	tt_write_u32(reg_adapter, addr, value);
	reg_print("writer 32, addr:0x%X, val: 0x%X\n", addr, value);
}

unsigned int read_u8(unsigned int addr)
{
	return tt_read_u8(reg_adapter, addr);
}

unsigned int write_u8(unsigned int addr, unsigned int value)
{
	tt_write_u8(reg_adapter, addr, value);
	reg_print("writer 8, addr:0x%X, val: 0x%X\n", addr, value);
}

unsigned int read_by_addr_index(unsigned int addr_index)
{
	unsigned int block_index = 0, field_index = 0;
	unsigned int found = 0, aligned = 0;
	unsigned int i = 0;
	unsigned int ret = 0;

	for(block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		if(regs[block_index].reg_start <= addr_index && regs[block_index].reg_end >= addr_index) {
			if(!(addr_index & (regs[block_index].reg_in_bytes - 1)))
				aligned = 1;
			found = 1;
			break;
		}
	}

	if(found && aligned) {
		unsigned int sub_index = (addr_index - regs[block_index].reg_start) / regs[block_index].reg_in_bytes;
		struct reg_info *info = regs[block_index].info[sub_index];
		unsigned total_field_count = regs[block_index].total_field_count;
		unsigned int reg_value = 0;//read real register here
		if (regs[block_index].reg_in_bytes == 1)
			reg_value = read_u8(addr_index);
		else
			reg_value = read_u32(addr_index);

		ret = 1;

		//printf("register belong to %s block, %d registers in this block, offset in this block is 0x%x, fields_num = %d\n", 
		//	regs[block_index].block_name, regs[block_index].reg_count, sub_index, info->field_num);

		reg_print(" ---------------%5s_0x%04X(0x%X)-----------------\n", regs[block_index].block_name, sub_index, addr_index);
		reg_print("0x%08X\n", reg_value);

		for(field_index = 0;field_index < total_field_count;field_index++) {
			struct reg_field * field = regs[block_index].field_info[field_index];
			if (field->reg_addr == addr_index)
				break;
		}

		for(i = 0; i < info->field_num;i++) {
			struct reg_field * field  = regs[block_index].field_info[field_index + i];

			if (field ->bits_num > 1)
				reg_print("%8X: %s[%d:%d]\n", ((reg_value >> field ->shift) & ((1 << field ->bits_num ) -1)), 
					field ->name, field ->shift + field ->bits_num - 1, field ->shift);
			else
				reg_print("%8X: %s[%d]\n", ((reg_value >> field ->shift) & ((1 << field ->bits_num ) -1)), 
					field ->name, field ->shift);
		}
		reg_print("\n");
		//printf(" ----------------------------------------------------\n");
	} else if(found && !aligned){
		reg_print("address is not aligned!\n");
	} else {
		reg_print("this register is not belong to dpu!\n");
	}

	return ret;
}

unsigned int reg_strstr(char *str1, char* str2)
{
	unsigned int ret = 0;
	char * token = NULL;
	unsigned int match_begining = 1;
	unsigned int match_end = 1;
	char case_str1[256] = {0};
	char case_str2[256] = {0};
	char last_token[256] = {0};
	unsigned int i = 0;
	char * temp_str1 = case_str1;


	for (i = 0; i < strlen(str1);i++) {
		if(str1[i] >= 'A' && str1[i] <= 'Z')
			case_str1[i] = str1[i] - 'A' + 'a';
		else
			case_str1[i] = str1[i];
	}

	for (i = 0; i < strlen(str2);i++) {
		if(str2[i] >= 'A' && str2[i] <= 'Z')
			case_str2[i] = str2[i] - 'A' + 'a';
		else
			case_str2[i] = str2[i];
	}

	if (!strcmp(temp_str1, case_str2))
		return 1;

	if (!strstr(case_str2, "*")) {

		if (strlen(case_str1) != strlen(case_str2))
			return 0;

		if (strcmp(temp_str1, case_str2))
			return 0;
	}

	if (case_str2[0] == '*')
		match_begining = 0;
	if (case_str2[strlen(case_str2) - 1] == '*')
		match_end = 0;

	token = strtok(case_str2, "*");
	if (token == NULL)
		return 0;
	if (match_begining) {
		if (strlen(temp_str1) < strlen(token))
			return 0;

		for (i = 0; i < strlen(token);i++) {
			if(temp_str1[i] != token[i])
				return 0;
		}

		temp_str1 += strlen(token);
	} else {
		if (!strstr(temp_str1, token))
			return 0;
		temp_str1 = strstr(temp_str1, token) + strlen(token);
	}
	while (token) {
		memset(last_token, 0, sizeof(last_token));
		memcpy(last_token, token, strlen(token));
		token = strtok(NULL, "*");
		if (token) {
			if (!strstr(temp_str1, token))
				return 0;
			temp_str1 = strstr(temp_str1, token) + strlen(token);
		}
	}

	if (match_end) {
		for(i = 0;i < strlen(last_token);i++) {
			if (case_str1[strlen(case_str1) - i] != last_token[strlen(last_token) - i])
				return 0;
		}
	}

	return 1;
}

unsigned int read_with_field_name(char* name)
{
	unsigned int block_index = 0, field_index = 0;
	unsigned int ret = 0;

	for (block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		struct reg_block_info * reg_block = &regs[block_index];
		for (field_index = 0; field_index < reg_block->total_field_count; field_index++) {
			char temp_name[256] = {0};
			struct reg_field * field = reg_block->field_info[field_index];

			memcpy(temp_name, name, strlen(name));

			if (reg_strstr(field->name, temp_name)){
				unsigned int addr = field->reg_addr;
				read_by_addr_index(addr);
				while (addr == field->reg_addr) {
					field = reg_block->field_info[++field_index];
				}
				field_index--;
				ret = 1;
			}
		}
	}

	return ret;
}

unsigned int read_with_block_name_and_sub_index(char* name, unsigned int index)
{
	unsigned int block_index = 0, field_index = 0;
	unsigned int found = 0, aligned = 0;
	unsigned int ret = 0;
	for(block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		if (!strcasecmp(regs[block_index].block_name, name)) {
			if(index < regs[block_index].reg_count) {
				unsigned int addr = regs[block_index].reg_start + index * regs[block_index].reg_in_bytes;
				read_by_addr_index(addr);
				ret = 1;
			} else {
				reg_print("index(0x%X) exceeds the scope of %s block\n", index, regs[block_index].block_name);
			}

			break;
		}
	}

	if (block_index == REG_BLOCK_NUM)
		reg_print("no %s block in dpu scope!\n", name);

	return ret;
}

unsigned int dump_with_block_name(char* block_name)
{
	unsigned int block_index = 0, reg_index = 0;
	unsigned int ret = 0;
	unsigned int reg_count = 0;

	for(block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		if (!strcasecmp(regs[block_index].block_name, block_name)) {
			for (reg_index = 0; reg_index < regs[block_index].reg_count;reg_index++) {
				read_by_addr_index(regs[block_index].reg_start + reg_index * regs[block_index].reg_in_bytes);
				reg_count++;
			}
			ret = 1;
		}
	}

	if (ret)
		reg_print("%d registers are dumped\n", reg_count);

	return ret;
}

void dump_all()
{
	unsigned int block_index = 0, reg_index = 0;
	unsigned int reg_count = 0;
	for(block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		for (reg_index = 0; reg_index < regs[block_index].reg_count;reg_index++) {
			read_by_addr_index(regs[block_index].reg_start + reg_index * regs[block_index].reg_in_bytes);
			reg_count++;
		}
	}
	reg_print("%d registers are dumped\n", reg_count);
}

void update_with_addr(unsigned int addr, unsigned value)
{
	unsigned int block_index = 0;

	for(block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		if(regs[block_index].reg_start <= addr && regs[block_index].reg_end >= addr) {
			if(!(addr & (regs[block_index].reg_in_bytes - 1))) {

				if (regs[block_index].reg_in_bytes == 1)
					write_u8(addr, value);
				else
					write_u32(addr, value);

				break;
			}
		}
	}
}
void update_with_field_name(char* field_name, unsigned int value)//need guarantee there's only 1 field_name
{
	unsigned int block_index = 0, field_index = 0;

	for (block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		struct reg_block_info * reg_block = &regs[block_index];
		for (field_index = 0; field_index < reg_block->total_field_count; field_index++) {
			char temp_name[256] = {0};
			struct reg_field * field = reg_block->field_info[field_index];

			memcpy(temp_name, field_name, strlen(field_name));

			if (reg_strstr(field->name, temp_name)) {
				unsigned int new_value = 0;
				unsigned int original_value = 0;

				if (reg_block->reg_in_bytes == 4) {
					original_value = read_u32(field->reg_addr);//read the real register value here
					new_value = original_value & (((1 << field ->bits_num ) -1) << field->shift) | ((value & ((1 << field ->bits_num ) -1)) << field->shift);
					write_u32(field->reg_addr, new_value);
				} else {
					original_value = read_u8(field->reg_addr);//read the real register value here
					new_value = original_value & (((1 << field ->bits_num ) -1) << field->shift) | ((value & ((1 << field ->bits_num ) -1)) << field->shift);
					write_u8(field->reg_addr, new_value);
				}

				if (field->bits_num > 1)
					reg_print("addr 0x%X[%d:%d] is updated to 0x%X\n", 
						field->reg_addr, field->shift + field->bits_num - 1, field->shift, (value & ((1 << field ->bits_num ) -1)));
				else
					reg_print("addr 0x%X[%d] is updated to 0x%X\n", 
						field->reg_addr, field->shift, (value & ((1 << field ->bits_num ) -1)));
				reg_print("addr[%X] is updated from 0x%X to 0x%X\n", field->reg_addr, original_value, new_value);
			}
		}
	}

}

void update_with_field_name_with_given_addr(unsigned int addr, char* field_name, unsigned int value)//need guarantee there's only 1 field_name
{
	unsigned int block_index = 0, field_index = 0, matched_count = 0;

	for (block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		struct reg_block_info * reg_block = &regs[block_index];

		if (addr >= reg_block->reg_start && addr <= reg_block->reg_end) {
			for (field_index = 0; field_index < reg_block->total_field_count; field_index++) {
				char temp_name[256] = {0};
				struct reg_field * field = reg_block->field_info[field_index];

				memcpy(temp_name, field_name, strlen(field_name));

				if (addr == field->reg_addr && reg_strstr(field->name, temp_name)){
					unsigned int new_value = 0;
					unsigned int original_value = 0;

					if (reg_block->reg_in_bytes == 4) {
						original_value = read_u32(field->reg_addr);//read the real register value here
						new_value = original_value & (((1 << field ->bits_num ) -1) << field->shift) | ((value & ((1 << field ->bits_num ) -1)) << field->shift);
						write_u32(field->reg_addr, new_value);
					} else {
						original_value = read_u8(field->reg_addr);//read the real register value here
						new_value = original_value & (((1 << field ->bits_num ) -1) << field->shift) | ((value & ((1 << field ->bits_num ) -1)) << field->shift);
						write_u8(field->reg_addr, new_value);
					}

					if (field->bits_num > 1)
						reg_print("addr 0x%X[%d:%d] is updated to 0x%X\n", 
							field->reg_addr, field->shift + field->bits_num - 1, field->shift, (value & ((1 << field ->bits_num ) -1)));
					else
						reg_print("addr 0x%X[%d] is updated to 0x%X\n", 
							field->reg_addr, field->shift, (value & ((1 << field ->bits_num ) -1)));
					reg_print("addr[%X] is updated from 0x%X to 0x%X\n", field->reg_addr, original_value, new_value);
				}
			}
		}
	}
}

unsigned int get_block_index(char *name)
{
	unsigned int block_index = 0;

	for(block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		if (!strcasecmp(regs[block_index].block_name, name)){
			return block_index;
		}
	}

	return -1;
}

void update_with_block_name_sub_index_field_name_value(char * block, char* index, char * field, char* value)
{
	unsigned int addr = 0, val = 0;
	unsigned int sub_index = 0;
	unsigned int block_index = get_block_index(block);

	sscanf(index, "%X", &sub_index);
	sscanf(value, "%X", &val);
	addr = regs[block_index].reg_start + sub_index * regs[block_index].reg_in_bytes;

	update_with_field_name_with_given_addr(addr, field, val);
}

void update_with_block_and_index(char * block, char * index, char* value)
{
	unsigned int addr = 0, val = 0;
	unsigned int sub_index = 0;
	unsigned int block_index = get_block_index(block);
	sscanf(index, "%X", &sub_index);
	sscanf(value, "%X", &val);

	addr = regs[block_index].reg_start + sub_index * regs[block_index].reg_in_bytes;
	if (regs[block_index].reg_in_bytes == 1)
		write_u8(addr, val);
	else
		write_u32(addr, val);
}

unsigned int is_block_name(char* name, unsigned int *block_id)
{
	unsigned int block_index = 0;

	for(block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		if (!strcasecmp(regs[block_index].block_name, name)){
			*block_id = block_index;
			return 1;
		}
	}

	return 0;
}

unsigned int is_valid_reg_addr(char* addr)
{
	unsigned int block_index = 0;
	unsigned int addr_index = 0;

	sscanf(addr, "%X", &addr_index);

	for(block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		if(regs[block_index].reg_start <= addr_index && regs[block_index].reg_end >= addr_index) {
			if(!(addr_index & (regs[block_index].reg_in_bytes - 1))) {
				return 1;
			}
		}
	}

	return 0;
}

unsigned int is_valid_field_name(char * name, unsigned int * matched_count)
{
	unsigned int block_index = 0, field_index = 0;

	if (!matched_count) {
		reg_print("matched_count is null\n");
		return 0;
	}

	*matched_count = 0;

	for (block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		struct reg_block_info * reg_block = &regs[block_index];
		for (field_index = 0; field_index < reg_block->total_field_count; field_index++) {
			char temp_name[256] = {0};
			struct reg_field * field = reg_block->field_info[field_index];

			memcpy(temp_name, name, strlen(name));

			if (reg_strstr(field->name, temp_name)){
				(*matched_count)++;
			}
		}
	}

	if (*matched_count) {
		return 1;
	}

	return 0;
}

unsigned int is_valid_field_with_given_addr_index(char * name, unsigned int addr)
{
	unsigned int block_index = 0, field_index = 0, matched_count = 0;

	for (block_index = 0;block_index < REG_BLOCK_NUM;block_index++) {
		struct reg_block_info * reg_block = &regs[block_index];

		if (addr >= reg_block->reg_start && addr <= reg_block->reg_end) {
			for (field_index = 0; field_index < reg_block->total_field_count; field_index++) {
				char temp_name[256] = {0};
				struct reg_field * f = reg_block->field_info[field_index];

				memcpy(temp_name, name, strlen(name));

				if (addr == f->reg_addr && reg_strstr(f->name, temp_name)){
					matched_count++;
				}
			}
		}
	}

	if (matched_count == 1)
		return 1;

	if (matched_count > 1)
		reg_print("%d fields are matched with the name of %s in addr 0x%X, need specify more specific field name\n", matched_count, name, addr);
	return 0;
}

unsigned int is_valid_hex(char * hex)
{
	unsigned int i = 0;
	unsigned int len = strlen(hex);
	if (len == 0)
		return 0;

	for (i = 0; i < len; i++) {
		if ((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'a' && hex[i] <= 'f') || (hex[i] >= 'A' && hex[i] <= 'F'))
			continue;
		if ((i == 1) && (hex[i] == 'x') && hex[0] == '0')
			continue;

		return 0;
	}

	return 1;
}

unsigned int is_valid_block_name_and_sub_index(char * name, char * index)
{
	unsigned int block_index = 0;
	if (is_block_name(name, &block_index)) {
		unsigned int sub_index = 0;
		if (is_valid_hex(index)) {
			sscanf(index, "%X", &sub_index);
			if (sub_index < regs[block_index].reg_count)
				return 1;
		}
	}

	return 0;
}

unsigned int is_valid_reg_addr_and_value(char* addr, char* value)
{
	if (is_valid_reg_addr(addr) && is_valid_hex(value))
		return 1;

	return 0;
}

unsigned int is_valid_reg_addr_and_field_and_value(char * addr, char * field, char* value)
{
	unsigned int block_index = 0, field_index = 0;
	unsigned int addr_index = 0;

	if (!is_valid_reg_addr(addr))
		return 0;

	if (!is_valid_hex(value))
		return 0;

	sscanf(addr, "%X", &addr_index);

	if (is_valid_field_with_given_addr_index(field, addr_index))
		return 1;

	return 0;
}
unsigned int is_valid_block_name_sub_index_field_name_value(char * block, char* index, char * field, char* value)
{
	if (is_valid_block_name_and_sub_index(block, index)) {
		unsigned int addr = 0;
		unsigned int sub_index = 0;
		unsigned int block_index = get_block_index(block);

		sscanf(index, "%X", &sub_index);
		addr = regs[block_index].reg_start + sub_index * regs[block_index].reg_in_bytes;
		if (is_valid_field_with_given_addr_index(field, addr) && is_valid_hex(value))
			return 1;
	}

	return 0;
}
unsigned int parse_the_op(int argc, u8 argv[][MAX_CMD_OPTION_NAME_SIZE])
{
	unsigned int matched_count = 0;
	unsigned int block_index = 0;
	if (argc == 1) {
		if(!strcasecmp(argv[0], "dump"))
			return OP_TYPE_DUMP_ALL;
		else if (is_block_name(argv[0], &block_index))
			return OP_TYPE_DUMP_WITH_BLOCK_NAME;
		else if (is_valid_reg_addr(argv[0]))
			return OP_TYPE_READ_WITH_ADDR_INDEX;
		else if (is_valid_field_name(argv[0], &matched_count))
			return OP_TYPE_READ_WITH_FIELD_NAME;
	} else if (argc== 2) {
		if (is_valid_reg_addr_and_value(argv[0], argv[1]))
			return OP_TYPE_UPDATE_WITH_ADDR_INDEX;
		else if (is_valid_block_name_and_sub_index(argv[0], argv[1]))
			return OP_TYPE_READ_WITH_BLOCK_AND_INDEX;
		else if (is_valid_field_name(argv[0], &matched_count)) {
			if ((matched_count == 1) && is_valid_hex(argv[1]))
				return OP_TYPE_UPDATE_WITH_FIELD_NAME;
			else if (matched_count > 1)
				reg_print("%d fields are matched with the name of %s, need more specific info to write this field\n", matched_count, argv[0]);
		}
	} else if (argc == 3) {
		if (is_valid_reg_addr_and_field_and_value(argv[0], argv[1], argv[2]))
			return OP_TYPE_UPDATE_WITH_ADDR_INDEX_AND_FIELD_NAME;
		else if (is_valid_block_name_and_sub_index(argv[0], argv[1]) && is_valid_hex(argv[2])) {
			return OP_TYPE_UPDATE_WITH_BLOCK_AND_INDEX;
		}
		
	} else if (argc == 4) {
		if (is_valid_block_name_sub_index_field_name_value(argv[0], argv[1], argv[2], argv[3]))
			return OP_TYPE_UPDATE_WITH_BLOCK_AND_INDEX_AND_FIELD_NAME;
	}

	return OP_TYPE_INVALID;
}

int handle_reg_main(struct dpu_adapter_t *dpu_adapter, unsigned char argv[][MAX_CMD_OPTION_NAME_SIZE], int argc)
{
	unsigned int addr_index = 0, value = 0, sub_index = 0;
	init_reg_info();
	//read_by_addr_index(0x8601);

	reg_print("%d, %s\r\n", argc, argv[0]);

	reg_adapter = dpu_adapter;

	if (argc == 1) {
		reg_print("read:\n");
		reg_print("./reg 0x4200\n");
		reg_print("./reg dp*en\n");
		reg_print("./reg itg2 0\n");
		reg_print("\nwrite:\n");
		reg_print("./reg 0x4200 0x1\n");
		reg_print("./reg 0x4200 dp*en 1\n");
		reg_print("./reg dp 0 dp*en 1\n");
		reg_print("./reg dp*en 0x1\n");
		reg_print("./reg dp 0 0x1\n");
		reg_print("\ndump:\n");
		reg_print("./reg pipe\n");
		reg_print("./reg dump - dump all the registers\n");
		return 0;
	}

	switch (parse_the_op(argc - 1, &argv[1])) {
		case OP_TYPE_DUMP_ALL:
			dump_all();
			break;
		case OP_TYPE_DUMP_WITH_BLOCK_NAME:
			dump_with_block_name(argv[1]);
			break;
		case OP_TYPE_READ_WITH_ADDR_INDEX:
			sscanf(argv[1], "%X", &addr_index);
			read_by_addr_index(addr_index);
			break;
		case OP_TYPE_READ_WITH_FIELD_NAME:
			read_with_field_name(argv[1]);
			break;
		case OP_TYPE_UPDATE_WITH_ADDR_INDEX:
			sscanf(argv[1], "%X", &addr_index);
			sscanf(argv[2], "%X", &value);
			update_with_addr(addr_index, value);
			reg_print("register 0x%X is updated to 0x%X\n", addr_index, value);
			break;

		case OP_TYPE_READ_WITH_BLOCK_AND_INDEX:
			sscanf(argv[2], "%X", &sub_index);
			read_with_block_name_and_sub_index(argv[1], sub_index);
			break;
		case OP_TYPE_UPDATE_WITH_FIELD_NAME:
			sscanf(argv[2], "%X", &value);
			update_with_field_name(argv[1], value);
			break;
		case OP_TYPE_UPDATE_WITH_ADDR_INDEX_AND_FIELD_NAME:
			sscanf(argv[1], "%X", &addr_index);
			sscanf(argv[3], "%X", &value);
			update_with_field_name_with_given_addr(addr_index, argv[2], value);
			break;
		case OP_TYPE_UPDATE_WITH_BLOCK_AND_INDEX_AND_FIELD_NAME:
			update_with_block_name_sub_index_field_name_value(argv[1], argv[2], argv[3], argv[4]);
			break;
		case OP_TYPE_UPDATE_WITH_BLOCK_AND_INDEX:
			update_with_block_and_index(argv[1], argv[2], argv[3]);
			break;
		case OP_TYPE_INVALID:
			reg_print("command is not recognized\n");
			break;
	}

	/*
	if (argc == 2)
	{
		if (!dump_with_block_name(argv[1])) {
			if (!read_with_field_name(argv[1])) {
				unsigned int addr = 0;
				sscanf(argv[1], "%X", &addr);
				read_by_addr_index(addr);
			}
		}
	}
	else if(argc == 3) {
		unsigned int index = 0;
		sscanf(argv[2], "%X", &index);
		read_with_block_name_and_sub_index(argv[1], index);
	}
	*/
/*
	{
		char str1[100] = {0};
		char str2[100] = {0}; 
		char * str = "dp*";
		int i = 0;
		memcpy(str1, "Dp_En", strlen("Dp_En"));
		memcpy(str2, str, strlen(str));

		printf("result:%d\n", reg_strstr(str1, str2));
	}*/
	
	return 0;
}
