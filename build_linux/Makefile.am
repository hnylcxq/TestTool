AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=TestTool

DE_DIR=../../DE/


AM_CPPFLAGS = -I ../ -I $(DE_DIR) -I $(DE_DIR)/audio/ -I $(DE_DIR)/chip/chip_A -I $(DE_DIR)/chip/common -I $(DE_DIR)/dp/ -I $(DE_DIR)/dvo -I $(DE_DIR)/hdmi/ -I $(DE_DIR)/include   \
		   -I $(DE_DIR)/include/register \
		   -I $(DE_DIR)/modules/ddc  \
		   -I $(DE_DIR)/modules/edid \
		   -I $(DE_DIR)/modules/mode \
		   -I ../dpu_arch/ 

TestTool_CXXFLAGS =   -I ../dpu_arch/code_piece \
		     -I ../dpu_arch/



AM_CPPFLAGS += -D__LINUX__
		   
TestTool_SOURCES= ../dpu_arch/dpu_cmodel.cpp\
		../dpu_arch/dpu_csc.cpp\
		../dpu_arch/cmodel_wrapper.cpp \
		../dpu_arch/dpu_ckp.cpp\
                ../core.c  \
		../dm.c  \
		../main.c  \
		../mem.c  \
		../script.c  \
		../util.c  \
		$(DE_DIR)/dpu.c  \
		$(DE_DIR)/dpu_mgr.c \
		$(DE_DIR)/os_func.c \
		$(DE_DIR)/de_util.c \
		$(DE_DIR)/chip/common/common.c \
		$(DE_DIR)/chip/common/hw_util.c \
		$(DE_DIR)/chip/common/pipe.c \
		$(DE_DIR)/chip/common/plane.c \
		$(DE_DIR)/chip/common/mdi.c \
		$(DE_DIR)/chip/common/int.c \
		$(DE_DIR)/chip/chip_A/chip_a.c \
		$(DE_DIR)/hdmi/hdmi.c \
		$(DE_DIR)/hdmi/hdmi_phy.c \
		$(DE_DIR)/audio/codec.c \
		$(DE_DIR)/audio/hda.c \
		$(DE_DIR)/modules/edid/edid.c \
		$(DE_DIR)/modules/ddc/i2c.c \
		$(DE_DIR)/modules/mode/mode.c \
		$(DE_DIR)/dp/aux_engine.c \
		$(DE_DIR)/dp/dp.c \
		$(DE_DIR)/dp/dp_phy.c \
		$(DE_DIR)/dp/encoder_dp.c \
		$(DE_DIR)/dvo/dvo.c \
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
