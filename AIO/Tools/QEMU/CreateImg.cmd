@Echo off
cls
TITLE RMPREPUSB QEMU Virtual Disk Image creation
REM %1 is hard disk name
REM %2 is HDD size

pushd %~dp0
echo EXECUTING %0
echo DRIVE NAME=%1
echo HDD SIZE=%2

echo Sending command qemu-img.exe create %1 %2M to shell...
start /B qemu-img.exe create %1 %2M
if errorlevel 1 echo FAILED!
if errorlevel 1 PAUSE
popd
