DE_PATH    = ../../DE
TEST_TOOL_PATH = ../../TestTool



VERSION = 1.00
CC	= gcc
CC_CPP = g++
LINK = g++
DEBUG =-D__DPU_LINUX_KERNEL__
CFLAGS=   -Werror 
#-Wall
CPPFLAGS = 

TARGET = TestTool

INCLUDES  	=-I ../ -I $(DE_PATH) -I $(DE_PATH)/audio/ -I $(DE_PATH)/chip/chip_A -I $(DE_PATH)/chip/common -I $(DE_PATH)/dp/ -I $(DE_PATH)/dvo -I $(DE_PATH)/hdmi/ -I $(DE_PATH)/include   \
		   -I $(DE_PATH)/include/register \
		   -I $(DE_PATH)/modules/ddc  \
		   -I $(DE_PATH)/modules/edid \
		   -I $(DE_PATH)/modules/mode

CPP_INCLUDES = -I ../dpu_arch/ \
		   -I ../dpu_arch/code_piece

SRC_LIST_CPP =../dpu_arch/dpu_cmodel.cpp\
		../dpu_arch/dpu_csc.cpp\
		../dpu_arch/cmodel_wrapper.cpp \
		../dpu_arch/dpu_ckp.cpp   

SRC_LIST =../core.c   \
		../dm.c  \
		../main.c  \
		../mem.c  \
		../script.c  \
		../util.c  \
		$(DE_PATH)/dpu.c  \
		$(DE_PATH)/dpu_mgr.c \
		$(DE_PATH)/os_func.c \
		$(DE_PATH)/de_util.c \
		$(DE_PATH)/chip/common/common.c \
		$(DE_PATH)/chip/common/hw_util.c \
		$(DE_PATH)/chip/common/pipe.c \
		$(DE_PATH)/chip/common/plane.c \
		$(DE_PATH)/chip/common/mdi.c \
		$(DE_PATH)/chip/common/int.c \
		$(DE_PATH)/chip/chip_A/chip_a.c \
		$(DE_PATH)/hdmi/hdmi.c \
		$(DE_PATH)/hdmi/hdmi_phy.c \
		$(DE_PATH)/audio/codec.c \
		$(DE_PATH)/audio/hda.c \
		$(DE_PATH)/modules/edid/edid.c \
		$(DE_PATH)/modules/ddc/i2c.c \
		$(DE_PATH)/modules/mode/mode.c \
		$(DE_PATH)/dp/aux_engine.c \
		$(DE_PATH)/dp/dp.c \
		$(DE_PATH)/dp/dp_phy.c \
		$(DE_PATH)/dp/encoder_dp.c \
		$(DE_PATH)/dvo/dvo.c \
		../platform/linux/linux_helper.c  \
		../reg/reg_info/codec_reg_field_info.c  \
		../reg/reg_info/codec2_reg_field_info.c  \
		../reg/reg_info/cr_reg_field_info.c  \
		../reg/reg_info/cr_share_reg_field_info.c  \
		../reg/reg_info/cr2_reg_field_info.c  \
		../reg/reg_info/cr3_reg_field_info.c  \
		../reg/reg_info/dp_reg_field_info.c  \
		../reg/reg_info/dvo_reg_field_info.c  \
		../reg/reg_info/hda_reg_field_info.c  \
		../reg/reg_info/hdmi_reg_field_info.c  \
		../reg/reg_info/intg_reg_field_info.c  \
		../reg/reg_info/itg_reg_field_info.c  \
		../reg/reg_info/itg_share_reg_field_info.c  \
		../reg/reg_info/itg2_reg_field_info.c  \
		../reg/reg_info/itg3_reg_field_info.c  \
		../reg/reg_info/mdi_reg_field_info.c  \
		../reg/reg_info/pipe_reg_field_info.c  \
		../reg/reg_info/pipe2_reg_field_info.c  \
		../reg/reg_info/pipe3_reg_field_info.c  \
		../reg/reg_info/pwm_reg_field_info.c  \
		../reg/reg_info/sr_reg_field_info.c  \
		../reg/reg_info/sr2_reg_field_info.c  \
		../reg/reg_info/sr3_reg_field_info.c  \
        ../reg/reg.c

OBJ = $(SRC_LIST_CPP:.cpp=.o) $(SRC_LIST:.c=.o) 

$(TARGET):$(OBJ)
	@mkdir -p output
	$(LINK) $(OBJ)  -o output/$(TARGET)
	@rm -rf $(OBJ)
	
#compile
%.o: %.c
	$(CC) $(INCLUDES) $(CPP_INCLUDES) $(DEBUG) $(CPPFLAGS) -c $(CFLAGS) $< -o $@

%.o:%.cpp
	$(CC_CPP) -o $@ -c $(CPPFLAGS) $< $(CPP_INCLUDES)

.PHONY:clean
clean:
	@echo "Remove linked and compiled files......"
	rm -rf $(OBJ) $(TARGET) output 

