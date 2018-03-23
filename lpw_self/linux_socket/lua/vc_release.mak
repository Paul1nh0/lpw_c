PROJECT=wjjall
TARGET1=wjj
TARGET2=wjjc
TARGET3=wjjr

CORE_O=	wjj_api.obj wjj_code.obj wjj_ctype.obj wjj_debug.obj wjj_do.obj wjj_dump.obj wjj_func.obj wjj_gc.obj wjj_lex.obj \
	wjj_mem.obj wjj_object.obj wjj_opcodes.obj wjj_parser.obj wjj_state.obj wjj_string.obj wjj_table.obj \
	wjj_tm.obj wjj_undump.obj wjj_vm.obj wjj_zio.obj \
	wjj_auxlib.obj wjj_baselib.obj wjj_bitlib.obj wjj_corolib.obj wjj_dblib.obj wjj_iolib.obj \
	wjj_mathlib.obj wjj_oslib.obj wjj_strlib.obj wjj_tablib.obj wjj_utf8lib.obj wjj_loadlib.obj wjj_init.obj

SOURCES = wjj_api.c wjj_code.c wjj_ctype.c wjj_debug.c wjj_do.c wjj_dump.c wjj_func.c wjj_gc.c wjj_lex.c \
	wjj_mem.c wjj_object.c wjj_opcodes.c wjj_parser.c wjj_state.c wjj_string.c wjj_table.c \
	wjj_tm.c wjj_undump.c wjj_vm.c wjj_zio.c \
	wjj_auxlib.c wjj_baselib.c wjj_bitlib.c wjj_corolib.c wjj_dblib.c wjj_iolib.c \
	wjj_mathlib.c wjj_oslib.c wjj_strlib.c wjj_tablib.c wjj_utf8lib.c wjj_loadlib.c wjj_init.c

WJJCOBJ = wjjc.obj	
WJJCSOURCE = wjjc.c

WJJOBJ = wjj.obj
WJJSOURCE = wjj.c

INCLUCEDIR=/I"D:\C-Free\VCompiler\Include" \
					/I"D:\C-Free\VCompiler\WinSDK\Include"
LIBRARYDIR=/libpath:"D:\C-Free\VCompiler\Lib"  \
          /libpath:"D:\C-Free\VCompiler\WinSDK\Lib"
LIBRARIES=user32.lib

CFLAGS = /nologo /W3 /TC /Ox /GA  /D"_CRT_SECURE_NO_DEPRECATE" $(INCLUCEDIR)
LINKFLAGS = /subsystem:console /machine:X86 /NODEFAULTLIB:libcd.lib /incremental:no 


CC = D:\C-Free\VCompiler\Bin\cl.exe
LINK = D:\C-Free\VCompiler\Bin\link.exe

$(PROJECT):$(TARGET1).lib $(TARGET2).exe $(TARGET3).exe

$(TARGET1).lib:$(CORE_O)
	$(LINK) -lib $(CORE_O) $(LINKFLAGS) /out:".\bin\wjj.lib"

$(CORE_O):$(SOURCES)
	$(CC) /c $(CFLAGS) $(SOURCES)
	
$(TARGET2).exe:$(TARGET1).lib $(WJJCOBJ)
	$(LINK) $(WJJCOBJ) $(LINKFLAGS) $(LIBRARYDIR) ".\bin\wjj.lib" /out:".\bin\wjjc.exe"

$(WJJCOBJ):$(WJJCSOURCE)
	$(CC) /c $(CFLAGS) $(WJJCSOURCE)

$(TARGET3).exe:$(TARGET1).lib $(WJJOBJ)
	$(LINK) $(WJJOBJ) $(LINKFLAGS) $(LIBRARYDIR) ".\bin\wjj.lib" /out:".\bin\wjj.exe"

$(WJJOBJ):$(WJJSOURCE)
	$(CC) /c $(CFLAGS) $(WJJSOURCE)
