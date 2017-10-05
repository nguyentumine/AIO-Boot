@echo off
title RMPrepUSB - QEMU emulator
REM %1 is ISO filename in double-quotes
REM %2 if memory size
REM %3 is hard disk image
pushd %~dp0
if @%1==@ goto :EOF
set MEM=256
SET HDD=
if not "%2"=="" set MEM=%2
if not "%3"=="" set HDD=-hda "%3" 
echo Booting with QEMU from %1 with %MEM%MB RAM
prompt Running $p$s
@echo on
qemu.exe %HDD% -boot dc -m %MEM% -cdrom %1 -L . -name "32-bit ISO Emulation" -usb -localtime -usbdevice tablet -net nic,vlan=0 -net user,vlan=0 
@echo off
echo.
if errorlevel 1 echo QEMU FAILED TO RUN!
if errorlevel 1 PAUSE
popd



