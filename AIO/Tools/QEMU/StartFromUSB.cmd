@Echo off
cls
TITLE RMPrepUSB QEMU Launcher
REM %1 is USB drive number
REM %2 is memory size
REM %3 is hard disk image
REM %4 is write-disable NOWRITE

pushd %~dp0
echo EXECUTING %0
echo DRIVE NUMBER=%1
echo MEMORY SIZE=%2

set HDI=
if not "%3"=="" if not "%3"=="NOWRITE" set HDI=%3
if not "%HDI%"=="" echo HARD DISK IMAGE=%HDI%

set NOWRITE=
if "%3"=="NOWRITE" set NOWRITE=1
if "%4"=="NOWRITE" set NOWRITE=1
echo NOWRITE=%NOWRITE%


REM Flush cache (esp. if NTFS filesystem still writing cache to slow disks)
sync 2> nul

SET OS=VISTA_OR_LATER
VER | find /i "5.0." > nul
IF %ERRORLEVEL% EQU 0 ECHO Running 2000
VER | find /i "5.1." > nul
IF %ERRORLEVEL% EQU 0 ECHO Running XP
IF %ERRORLEVEL% EQU 0 SET OS=XP
VER | find /i "5.2." > nul
IF %ERRORLEVEL% EQU 0 ECHO Running Win 2003
IF %ERRORLEVEL% EQU 0 SET OS=2003
set qemu=qemu-system-x86_64.exe 
IF "%OS%"=="5.0" set qemu=qemu.exe
IF "%OS%"=="5.1" set qemu=qemu.exe
IF "%OS%"=="5.2" set qemu=qemu.exe
set qemu=qemu.exe
echo Found OS=%OS% 
IF "%NOWRITE%"=="1" IF     "%HDI%"=="" SET CMD=%qemu% -L . -name "32-bit Emulation Session  RAM=%2MB  WP [Release=Alt+LCtrl]" -boot c -m %2 -drive file=\\.\PhysicalDrive%1,if=ide,index=0,media=disk,snapshot=on
IF "%NOWRITE%"=="1" IF NOT "%HDI%"=="" SET CMD=%qemu% -L . -name "32-bit Emulation Session  RAM=%2MB VirtualHDD=%HDI%  WP [Release=Alt+LCtrl]" -boot c -m %2 -drive file=\\.\PhysicalDrive%1,if=ide,index=0,media=disk,snapshot=on -hdb %HDI%

:: Use DavidB's Start_VM so writes work!
IF NOT "%NOWRITE%"=="1" IF "%HDI%"==""     SET CMD=%qemu% -L . -name "32-bit Emulation Session  RAM=%2MB [Release=Alt+LCtrl]" -boot c -m %2 -drive file=\\.\PhysicalDrive%1,if=ide,index=0,media=disk
IF NOT "%NOWRITE%"=="1" IF NOT "%HDI%"=="" SET CMD=%qemu% -L . -name "32-bit Emulation Session  RAM=%2MB VirtualHDD=%HDI% [Release=Alt+LCtrl]" -boot c -m %2 -drive file=\\.\PhysicalDrive%1,if=ide,index=0,media=disk -hdb %HDI%

IF NOT "%NOWRITE%"=="1" echo Sending command Start_VM.exe %1 500 %CMD% to shell...
IF "%NOWRITE%"=="1"     echo Sending command %CMD% to shell...
echo.
echo THIS CONSOLE WINDOW WILL REMAIN OPEN UNTIL YOU QUIT QEMU
echo.

IF "%NOWRITE%"=="1" %CMD%
IF NOT "%NOWRITE%"=="1" Start_VM.exe %1 500 %CMD%
if errorlevel 1 echo FAILED!
if errorlevel 1 PAUSE
popd

