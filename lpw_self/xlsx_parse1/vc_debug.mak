PROJECT=xlsx_parse
TARGET1=xlsx_parse
OUTDIR=vc_debug

OBJS1=.\$(OUTDIR)\main.obj \
.\$(OUTDIR)\dlgxp_templet.obj \
.\$(OUTDIR)\encoder.obj \
.\$(OUTDIR)\gbk_string.obj
			

SOURCES1 = main.c \
dlgxp_templet.c \
encoder.c \
gbk_string.c
					

RESOBJ1= resource.res

RESOURCE1 = resource.rc

INCLUCEDIR=/I"D:\git\lpw_c\VS7\Include" \
					/I"D:\git\lpw_c\VS7\WinSDK\Include" \
					/I"D:\git\lpw_c\lpw_self\xlsx_parse\libopc\include"
					
LIBRARYDIR=/libpath:"D:\git\lpw_c\VS7\Lib"  \
          /libpath:"D:\git\lpw_c\VS7\WinSDK\Lib" \
          /libpath:"D:\git\lpw_c\lpw_self\xlsx_parse\libopc\lib"

LIBRARIES=user32.lib shell32.lib comdlg32.lib comctl32.lib wsock32.lib mce.lib opc.lib plib.lib xml.lib zlib.lib
RCFLAGS = /n $(INCLUCEDIR)
CFLAGS = /nologo /Zi /W3 /TC /Ox /GA /D"WIN32" /D"_DEBUG" /Fd"$(OUTDIR)/vcpdb" /Fo"$(OUTDIR)/" $(INCLUCEDIR)
LINKFLAGS = /subsystem:windows /machine:X86 /NODEFAULTLIB:libcmt.lib /debug /incremental:no \
 /pdb:".\$(OUTDIR)\$(TARGET1).pdb" /map:".\$(OUTDIR)\$(TARGET1).map" /out:".\$(OUTDIR)\$(TARGET1).exe" \
 $(LIBRARYDIR) $(LIBRARIES)

RC =  D:\git\lpw_c\VC6\sdk_2k3\Bin\rc.exe
CC = D:\git\lpw_c\VS7\Bin\cl.exe
LINK = D:\git\lpw_c\VS7\Bin\link.exe


.\$(OUTDIR)\$(TARGET1).exe:$(OBJS1) $(RESOBJ1)
	$(LINK) $(OBJS1) $(RESOBJ1) $(LINKFLAGS)

$(OBJS1):$(SOURCES1)
	-if not exist $(OUTDIR) mkdir $(OUTDIR)
	$(CC) /c $(CFLAGS) $(SOURCES1)

$(RESOBJ1):$(RESOURCE1)
	$(RC) $(RCFLAGS) $(RESOURCE1)	

run:.\$(OUTDIR)\$(TARGET1).exe	
	start .\$(OUTDIR)\$(TARGET1).exe  & exit

clean:
	-del /Q $(OUTDIR)