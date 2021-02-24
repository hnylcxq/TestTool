
OUTPUTPATH=$(OUTPUT)\output

OBJ_TEST_TOOL = core.obj \
				dm.obj \
				main.obj \
				mem.obj \
				script.obj \
				util.obj 

OBJ_PLATFORM += bios_helper.obj

OBJ_DPU += dpu.obj
OBJ_DPU += dpu_mgr.obj
OBJ_DPU += os_func.obj
OBJ_DPU += de_util.obj

OBJ_DPU_COMMON += common.obj
OBJ_DPU_COMMON += hw_util.obj
OBJ_DPU_COMMON += pipe.obj
OBJ_DPU_COMMON += plane.obj
OBJ_DPU_COMMON += mdi.obj
OBJ_DPU_COMMON += int.obj
#OBJ_DPU_COMMON += pwm.obj

OBJ_DPU_CHIP_A += chip_a.obj

OBJ_DPU_HDMI += hdmi.obj
OBJ_DPU_HDMI += hdmi_phy.obj

OBJ_DPU_AUDIO += codec.obj
OBJ_DPU_AUDIO += hda.obj

OBJ_DPU_EDID += edid.obj
OBJ_DPU_DDC += i2c.obj
OBJ_DPU_MODE += mode.obj

OBJ_DPU_DP += aux_engine.obj
OBJ_DPU_DP += dp.obj
OBJ_DPU_DP += dp_phy.obj
OBJ_DPU_DP += encoder_dp.obj

OBJ_DPU_DVO += dvo.obj

OBJ_REG_INFO = codec_reg_field_info.obj \
			codec2_reg_field_info.obj \
			cr_reg_field_info.obj \
			cr_share_reg_field_info.obj \
			cr2_reg_field_info.obj \
			cr3_reg_field_info.obj \
			dp_reg_field_info.obj \
			dvo_reg_field_info.obj \
			hda_reg_field_info.obj \
			hdmi_reg_field_info.obj \
			intg_reg_field_info.obj \
			itg_reg_field_info.obj \
			itg_share_reg_field_info.obj \
			itg2_reg_field_info.obj \
			itg3_reg_field_info.obj \
			mdi_reg_field_info.obj \
			pipe_reg_field_info.obj \
			pipe2_reg_field_info.obj \
			pipe3_reg_field_info.obj \
			pwm_reg_field_info.obj \
			sr_reg_field_info.obj \
			sr2_reg_field_info.obj \
			sr3_reg_field_info.obj

OBJ_REG = reg.obj

CC=wcc386
LINK=link
WLINK=wlink

CC_OPT=-w0 -ef -j -zq -od -d2 -6r -bt=dos -mf -fo=$(OUTPUTPATH)\$*.obj \
	-i=$(DE_PATH) \
	-i=$(DE_PATH)\audio \
	-i=$(DE_PATH)\chip\common \
	-i=$(DE_PATH)\chip\chip_A \
	-i=$(DE_PATH)\dp \
	-i=$(DE_PATH)\dvo \
	-i=$(DE_PATH)\hdmi \
	-i=$(DE_PATH)\include \
	-i=$(DE_PATH)\include\register \
	-i=$(DE_PATH)\modules\ddc \
	-i=$(DE_PATH)\modules\edid \
	-i=$(DE_PATH)\modules\mode \
	-i=..\

LINK_OPT=-nologo -out:$@
WLINK_OPT=debug all sys dos32a op q


ALL_OBJ= $(OBJ_TEST_TOOL) $(OBJ_PLATFORM)  $(OBJ_DPU) $(OBJ_DPU_COMMON) $(OBJ_DPU_CHIP_A) \
		$(OBJ_DPU_HDMI) $(OBJ_DPU_AUDIO) $(OBJ_DPU_EDID) \
		$(OBJ_DPU_DDC) $(OBJ_DPU_MODE) \
		$(OBJ_DPU_DP) $(OBJ_DPU_DVO) $(OBJ_REG_INFO) $(OBJ_REG)
    

ALL:    TestTool.exe

TestTool.exe: $(ALL_OBJ)
    @cd $(OUTPUTPATH)
    @echo "Linking all obj..."
    @$(WLINK) name TestTool $(WLINK_OPT) File $(OUTPUTPATH)\*.obj
    @del /q $(OUTPUTPATH)\*.obj > nul

CLEAN:
    @if exist "$(OUTPUTPATH)\TestTool.*" (del /q $(OUTPUTPATH)\TestTool.* > nul)

$(OBJ_TEST_TOOL)
    @$(CC) $(CC_OPT) ..\$*.c
    @echo $*.c



$(OBJ_PLATFORM)
	@$(CC) $(CC_OPT) ..\platform\dos\$*.c
    @echo $*.c

$(OBJ_DPU)
	@$(CC) $(CC_OPT) $(DE_PATH)\$*.c
    @echo $*.c

$(OBJ_DPU_COMMON)
	@$(CC) $(CC_OPT) $(DE_PATH)\chip\common\$*.c
    @echo $*.c

$(OBJ_DPU_CHIP_A)
	@$(CC) $(CC_OPT) $(DE_PATH)\chip\chip_A\$*.c
    @echo $*.c

$(OBJ_DPU_HDMI)
	@$(CC) $(CC_OPT) $(DE_PATH)\hdmi\$*.c
    @echo $*.c

$(OBJ_DPU_AUDIO)
	@$(CC) $(CC_OPT) $(DE_PATH)\audio\$*.c
    @echo $*.c

$(OBJ_DPU_EDID)
	@$(CC) $(CC_OPT) $(DE_PATH)\modules\edid\$*.c
    @echo $*.c

$(OBJ_DPU_DDC)
	@$(CC) $(CC_OPT) $(DE_PATH)\modules\DDC\$*.c
    @echo $*.c

$(OBJ_DPU_MODE)
	@$(CC) $(CC_OPT) $(DE_PATH)\modules\mode\$*.c
    @echo $*.c

$(OBJ_DPU_DP)
	@$(CC) $(CC_OPT) $(DE_PATH)\dp\$*.c
    @echo $*.c

$(OBJ_DPU_DVO)
	@$(CC) $(CC_OPT) $(DE_PATH)\dvo\$*.c
    @echo $*.c
	
$(OBJ_REG_INFO)
	@$(CC) $(CC_OPT) ..\reg\reg_info\$*.c
    @echo $*.c

$(OBJ_REG)
	@$(CC) $(CC_OPT) ..\reg\$*.c
    @echo $*.c
	
