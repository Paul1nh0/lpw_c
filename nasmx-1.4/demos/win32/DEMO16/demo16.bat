@echo off
set file=DEMO16
if exist %file%.obj del %file%.obj
if not exist %file%.asm goto errasm

..\..\..\bin\nasm -f win32 -I ..\\..\\..\\inc\\ %file%.asm -o %file%.obj
if errorlevel 1 goto errasm

..\..\..\bin\GoLink.exe /console /mix /entry _main  %file%.obj "libgtk-win32-2.0-0.dll" "libgobject-2.0-0.dll"
if errorlevel 1 goto errlink

if exist %file%.obj del %file%.obj
goto TheEnd

:errlink
echo _
echo Link error
pause
goto TheEnd

:errasm
echo _
echo Assembly Error
pause
goto TheEnd

:TheEnd
echo _

