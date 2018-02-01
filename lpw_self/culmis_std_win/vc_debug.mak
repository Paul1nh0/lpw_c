PROJECT=culmis
INTERFACE_DLL=cul_interface
TOOL=culmis_tool
WJJ=wjj
OUTDIR=vc_debug

INTERFACE_OBJ=.\$(OUTDIR)\cul_interface.obj \
			.\$(OUTDIR)\cul_std_string.obj \
			.\$(OUTDIR)\cul_json.obj \
			.\$(OUTDIR)\cul_wjj.obj \
			.\$(OUTDIR)\cul_config.obj \
			.\$(OUTDIR)\cul_log.obj \
			.\$(OUTDIR)\cul_pinpad.obj \
			.\$(OUTDIR)\cul_common.obj \
			.\$(OUTDIR)\cul_iso8583.obj \
             .\$(OUTDIR)\cul_socket.obj \
             .\$(OUTDIR)\cul_dump.obj
             
INTERFACE_SRC= cul_interface.c \
					 cul_std_string.c \
					 cul_json.c  \
					 cul_wjj.c  \
					 cul_config.c \
					 cul_log.c \
					 cul_pinpad.c \
					 cul_common.c \
					 cul_iso8583.c \
					 cul_socket.c \
					 cul_dump.c
					 
TOOL_OBJ=.\$(OUTDIR)\culmis_tools.obj \
			.\$(OUTDIR)\culmis_main.obj \
			.\$(OUTDIR)\cul_json.obj \
			.\$(OUTDIR)\cul_log.obj

TOOL_SRC = culmis_tools.c \
					 culmis_main.c \
					 cul_json.c \
					 cul_log.c
					 
RES_OBJ= resource.res

RESOURCE = resource.rc

WJJ_SRC = cul_mis.wjj \
			cul_json.wjj
			
INCLUCEDIR=/I"wjjcode"
LIBRARYDIR=/libpath:"wjjcode\bin"
          
LIBRARIES=user32.lib shell32.lib comdlg32.lib
RCFLAGS = /n $(INCLUCEDIR)
MACROS = /D"JNI_SUPPORT" /D"WIN32" /D"_WINDOWS" /D"CUL_WINDOWS" /D"CL"
CFLAGS = /nologo /Zi /W3 /TC /Oy /GA $(MACROS) /D"_CRT_SECURE_NO_DEPRECATE" /D"_DEBUG"  /Fo"$(OUTDIR)/" $(INCLUCEDIR)
LINKFLAGS = /subsystem:windows /machine:X86  /debug /incremental:no \
$(LIBRARYDIR) 

RC =  Rc.exe
CC = cl.exe
LINK = link.exe
WJJC = wjjc.exe
WINDBG = D:\lpw_code\tools\WinDbg\x86\windbg.exe

$(PROJECT):$(INTERFACE_DLL) $(TOOL) $(WJJ)

$(INTERFACE_DLL):$(INTERFACE_OBJ)
	$(LINK) $(INTERFACE_OBJ) $(LINKFLAGS) Advapi32.lib wjj.lib shlwapi.lib wsock32.lib /map:".\$(OUTDIR)\$(INTERFACE_DLL).map"  /pdb:".\$(OUTDIR)\$(INTERFACE_DLL).pdb" /def:"$(INTERFACE_DLL).def" /dll /out:".\$(OUTDIR)\$(INTERFACE_DLL).dll"

$(INTERFACE_OBJ):$(INTERFACE_SRC)
	-mkdir $(OUTDIR)
	$(CC) /c $(CFLAGS) $(INTERFACE_SRC) /Fd"$(OUTDIR)/vcpdb_dll"

$(TOOL):$(TOOL_OBJ) $(RES_OBJ)
	$(LINK) $(TOOL_OBJ) $(RES_OBJ) $(LINKFLAGS)  /map:".\$(OUTDIR)\$(TOOL).map"   /pdb:".\$(OUTDIR)\$(TOOL).pdb"  $(LIBRARIES) /out:".\$(OUTDIR)\$(TOOL).exe"

$(TOOL_OBJ):$(TOOL_SRC)
	-mkdir $(OUTDIR)
	$(CC) /c $(CFLAGS) $(TOOL_SRC) /Fd"$(OUTDIR)/vcpdb_tool"

$(RES_OBJ):$(RESOURCE)
	$(RC) $(RCFLAGS) $(RESOURCE)	

$(WJJ):$(SOURCE3)
	$(WJJC) -o .\$(OUTDIR)\cul_json.wjj cul_json.wjj
	$(WJJC) -o .\$(OUTDIR)\cul_mis.wjj cul_mis.wjj
	
run:$(INTERFACE_DLL) $(TOOL) $(WJJ)
	start .\$(OUTDIR)\$(TOOL).exe & exit

debug_run:$(INTERFACE_DLL) $(TOOL) $(WJJ)
	taskkill /im windbg.exe \
	& start  $(WINDBG)  .\$(OUTDIR)\$(TARGET2).exe & exit 
	
clean:
	-del /Q $(OUTDIR)

