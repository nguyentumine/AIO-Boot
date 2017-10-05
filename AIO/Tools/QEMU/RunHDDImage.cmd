@echo off
REM %1 if memory size
REM %2 is hard disk image
title RMPrepUSB - QEMU emulator
pushd %~dp0
set MEM=256
SET HDD=-hda "harddisk.img"
if not "%1"=="" set MEM=%1
if not "%2"=="" set HDD=-hda "%2" 
echo Booting QEMU from harddisk.img with %MEM%MB RAM
prompt Executing $g$s
@echo on
qemu.exe %HDD% -boot c -m %MEM% -L . -name "32-bit HDD Emulation" -usb -localtime -usbdevice tablet -net nic,vlan=0 -net user,vlan=0 
@echo off
echo.
if errorlevel 1 echo QEMU FAILED TO RUN!
if errorlevel 1 PAUSE
popd



