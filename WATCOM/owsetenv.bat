@echo off
echo Open Watcom Build Environment
set watcom=%~dp0
echo watcom environment is %watcom%
SET PATH=%watcom%BINW;%PATH%
SET PATH=%watcom%BINNT;%PATH%
SET INCLUDE=%watcom%H\NT;%INCLUDE%
SET INCLUDE=%watcom%H\NT;%INCLUDE%
SET INCLUDE=%INCLUDE%;%watcom%H\NT\DIRECTX
SET INCLUDE=%INCLUDE%;%watcom%H\NT\DDK
SET INCLUDE=%watcom%H;%INCLUDE%
SET WATCOM=%watcom%
SET EDPATH=%watcom%EDDAT
SET WHTMLHELP=%watcom%BINNT\HELP
SET WIPFC=%watcom%WIPFC