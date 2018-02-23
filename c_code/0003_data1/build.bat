@echo off
echo vs7 Environment
set vs7=D:\git\lpw_c\VS7
echo vs7 environment is %vs7%
SET PATH=%vs7%\bin;%PATH%
SET INCLUDE=%vs7%\include;%INCLUDE%
SET LIB=%vs7%\Lib;%vs7%\WinSDK\Lib;%LIB%
cl /ZI data1.c /link /pdb:"data1.pdb" /debug
pause