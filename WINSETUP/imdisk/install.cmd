@echo off

setlocal

title ImDisk Virtual Disk Driver setup

echo ImDisk Virtual Disk Driver setup
echo.

set IMDISK_TOTAL_DEVICES=0
set IMDISK_VALID_DEVICES=0
set IMDISK_PENDING_REMOVAL_DEVICES=0

if exist "%SystemRoot%\system32\imdisk.exe" (
  for /f %%a in ('imdisk -l -n ^| find /v /i ^"No^"') do call :addline "%%a"
)

if %IMDISK_VALID_DEVICES% GTR 0 (
  echo Number of existing ImDisk virtual disks: %IMDISK_VALID_DEVICES%
  echo.
  if "%IMDISK_SILENT_SETUP%" == "1" (
    echo Please dismount all existing ImDisk virtual disks before upgrade!
    echo.
  ) else (
    msgboxw "Please dismount all existing ImDisk virtual disks before upgrade!" 16 "ImDisk Virtual Disk Driver setup"
    start control imdisk.cpl
  )
  endlocal
  goto :eof
)

echo Number of existing ImDisk virtual disks: %IMDISK_TOTAL_DEVICES%
echo.
if %IMDISK_TOTAL_DEVICES% == 0 (
  net stop imdsksvc
  net stop awealloc
  net stop imdisk
  if exist "%SystemRoot%\system32\taskkill.exe" taskkill /F /IM imdsksvc.exe
)

pushd "%~dp0"
rundll32 setupapi.dll,InstallHinfSection DefaultInstall 132 .\imdisk.inf
popd

if errorlevel 1 (
  if not "%IMDISK_SILENT_SETUP%" == "1" msgboxw "Setup failed. Please try to reboot the computer and then try to run the setup package again." 16 "ImDisk Virtual Disk Driver setup"
  endlocal
  goto :eof
)

set IMDISK_START_FAILED=1
if %IMDISK_TOTAL_DEVICES% == 0 (
  set IMDISK_START_FAILED=0
  net start imdsksvc || set IMDISK_START_FAILED=1
  net start awealloc || set IMDISK_START_FAILED=1
  net start imdisk || set IMDISK_START_FAILED=1
)

if not "%IMDISK_SILENT_SETUP%" == "1" (
  if %IMDISK_START_FAILED% == 0 (
    msgboxw "Setup finished successfully. Open ImDisk Virtual Disk Driver applet in Control Panel or use imdisk command line to manage your virtual disks!" 0 "ImDisk Virtual Disk Driver setup"
  ) else (
    msgboxw "Setup finished, but drivers or services could not start. Please try to reboot the computer and then try to run the setup package again." 16 "ImDisk Virtual Disk Driver setup"
  )
)

endlocal

goto :eof

:addline

imdisk -l -u %~1 > nul 2>&1

if errorlevel 1 (
  set /a IMDISK_PENDING_REMOVAL_DEVICES=%IMDISK_PENDING_REMOVAL_DEVICES% + 1 > nul
) else (
  set /a IMDISK_VALID_DEVICES=%IMDISK_VALID_DEVICES% + 1 > nul
)

set /a IMDISK_TOTAL_DEVICES=%IMDISK_TOTAL_DEVICES% + 1 > nul

goto :eof
