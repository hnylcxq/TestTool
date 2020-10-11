

OUTPUTPATH=$(OUTPUT)\output

OBJ_TEST_TOOL = bios_helper.obj \
				core.obj \
				dm.obj \
				main.obj \
				mem.obj \
				script.obj \
				util.obj 

OBJ_DPU = dpu.obj 



CC=wcc386
LINK=link
WLINK=wlink

CC_OPT=-w0 -ef -j -zq -od -d2 -6r -bt=dos -mf -fo=$(OUTPUTPATH)\$*.obj

LINK_OPT=-nologo -out:$@
WLINK_OPT=debug all sys dos32a op q


ALL_OBJ= $(OBJ_TEST_TOOL)  $(OBJ_DPU)
    

ALL:    TestTool.exe

TestTool.exe: $(ALL_OBJ)
    @cd $(OUTPUTPATH)
    @echo "Linking all obj..."
    @$(WLINK) name TestTool $(WLINK_OPT) File $(OUTPUTPATH)\*.obj
    @del /q $(OUTPUTPATH)\*.obj > nul

CLEAN:
    @if exist "$(OUTPUTPATH)\TestTool.*" (del /q $(OUTPUTPATH)\TestTool.* > nul)

$(OBJ_TEST_TOOL)
    @$(CC) $(CC_OPT) $*.c
    @echo $*.c
	
$(OBJ_DPU)
	@$(CC) $(CC_OPT) dpu\$*.c
    @echo $*.c
