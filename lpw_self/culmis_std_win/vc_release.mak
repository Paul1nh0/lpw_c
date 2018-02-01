PROJECT=dll_templet
TARGET1=dll_templet
OUTDIR=vc_release

OBJS1=.\$(OUTDIR)\main.obj \
#			.\$(OUTDIR)\dlgxp_templet.obj \
#			.\$(OUTDIR)\culstd.obj

SOURCES1 = main.c \
#					 dlgxp_templet.c \
#					 culstd.c

#RESOBJ1= resource.res

#RESOURCE1 = resource.rc

INCLUCEDIR=/I"D:\C-Free\VCompiler\Include" \
					/I"D:\C-Free\VCompiler\WinSDK\Include"
LIBRARYDIR=/libpath:"D:\C-Free\VCompiler\Lib"  \
          /libpath:"D:\C-Free\VCompiler\WinSDK\Lib" 
LIBRARIES=user32.lib


RCFLAGS = /n $(INCLUCEDIR)
CFLAGS = /nologo /W3 /TC /Ox /GA /D"WIN32" /D"UNICODE" /D"_CRT_SECURE_NO_DEPRECATE" /Fo"$(OUTDIR)/" $(INCLUCEDIR)
LINKFLAGS = /subsystem:windows /machine:X86 /NODEFAULTLIB:libcd.lib /incremental:no \
  /map:".\$(OUTDIR)\$(TARGET1).map" /def:"$(TARGET1).def" /dll /out:".\$(OUTDIR)\$(TARGET1).dll" \
 $(LIBRARYDIR) 

RC =  D:\C-Free\VCompiler\WinSDK\Bin\Rc.exe
CC = D:\C-Free\VCompiler\Bin\cl.exe
LINK = D:\C-Free\VCompiler\Bin\link.exe

$(TARGET1).exe:$(OBJS1) 
	$(LINK) $(OBJS1) $(LINKFLAGS)

$(OBJS1):$(SOURCES1)
	-mkdir $(OUTDIR)
	$(CC) /c $(CFLAGS) $(SOURCES1)

clean:
	-del /Q $(OUTDIR)
#$(RESOBJ1):$(RESOURCE1)
#	$(RC) $(RCFLAGS) $(RESOURCE1)	
	
