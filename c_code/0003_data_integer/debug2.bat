set _NT_SYMBOL_PATH=%~dp0
set _NT_SOURCE_PATH=%~dp0 
set PATH=D:\git\lpw_tool\WinDbg\x86\;%PATH%
start windbg  -c ".open data_integer.c" data_integer.exe
exit
