@echo off
echo vs7 Environment
set vs7=D:\git\lpw_c\VS7
echo vs7 environment is %vs7%
SET PATH=%vs7%\bin;D:\git\lpw_c\gnu_make;D:\git\lpw_c\lpw_self\culmis_std\wjjcode\bin;D:\git\lpw_c\lpw_self\culmis_std\7z;%PATH%
SET INCLUDE=%vs7%\include;%vs7%\WinSDK\Include;%INCLUDE%
SET LIB=%vs7%\Lib;%vs7%\WinSDK\Lib;D:\git\lpw_c\lpw_self\culmis_std\wjjcode\bin;%LIB%
del /Q vc_debug
make -f vc_debug.mak
copy cul_config.ini vc_debug\cul_config.ini
cd vc_debug
mkdir package
7z.exe a -t7z ..\package\%date:~0,4%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%%time:~6,2%.7z  cul_interface.dll culmis_tool.exe cul_config.ini cul_mis.wjj cul_json.wjj
pause