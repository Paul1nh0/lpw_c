PROJECT=dlg_templet
TARGET1=dlg_templet
OUTDIR=vc_release

OBJS1=.\$(OUTDIR)\main.obj \
			.\$(OUTDIR)\dlgxp_templet.obj \
#			.\$(OUTDIR)\culstd.obj

SOURCES1 = main.c \
					 dlgxp_templet.c \
#					 culstd.c

RESOBJ1= resource.res

RESOURCE1 = resource.rc

INCLUCEDIR=/I"D:\C-Free\VCompiler\Include" \
					/I"D:\C-Free\VCompiler\WinSDK\Include"
LIBRARYDIR=/libpath:"D:\C-Free\VCompiler\Lib"  \
          /libpath:"D:\C-Free\VCompiler\WinSDK\Lib" 
LIBRARIES=user32.lib


RCFLAGS = /n $(INCLUCEDIR)
CFLAGS = /nologo /W3 /TC /Ox /GA /D"WIN32" /D"_CRT_SECURE_NO_DEPRECATE" /Fo"$(OUTDIR)/" $(INCLUCEDIR)
LINKFLAGS = /subsystem:windows /machine:X86 /NODEFAULTLIB:libcd.lib /incremental:no \
  /map:".\$(OUTDIR)\$(TARGET1).map" /out:".\$(OUTDIR)\$(TARGET1).exe" \
 $(LIBRARYDIR) $(LIBRARIES)

RC =  D:\C-Free\VCompiler\WinSDK\Bin\Rc.exe
CC = D:\C-Free\VCompiler\Bin\cl.exe
LINK = D:\C-Free\VCompiler\Bin\link.exe

.\$(OUTDIR)\$(TARGET1).exe:$(OBJS1) $(RESOBJ1)
	$(LINK) $(OBJS1) $(RESOBJ1) $(LINKFLAGS)

$(OBJS1):$(SOURCES1)
	-mkdir $(OUTDIR)
	$(CC) /c $(CFLAGS) $(SOURCES1)

$(RESOBJ1):$(RESOURCE1)
	$(RC) $(RCFLAGS) $(RESOURCE1)	

run:.\$(OUTDIR)\$(TARGET1).exe	
	start .\$(OUTDIR)\$(TARGET1).exe  & exit

clean:
	-del /Q $(OUTDIR)
	
