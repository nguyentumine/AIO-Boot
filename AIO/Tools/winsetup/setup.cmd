rem Special thanks to cdob 
rem http://www.msfn.org/board/install-2000-xp-2003-ram-loaded-small-iso-t139737-page-20.html

@echo off
setlocal EnableExtensions EnableDelayedExpansion

if exist %SystemRoot%\System32\drivers\firadisk.sys (
if exist reg.exe (
reg.exe delete HKLM\SYSTEM\CurrentControlSet\Enum\Firadisk /f >> %SystemRoot%\WinPreSetup.log
reg.exe delete HKLM\SYSTEM\CurrentControlSet\Enum\Root\Firadisk /f >> %SystemRoot%\WinPreSetup.log
reg.exe delete HKLM\SYSTEM\CurrentControlSet\Control\Firadisk /f >> %SystemRoot%\WinPreSetup.log
reg.exe load HKLM\Loaded_System config\System.sav >> %SystemRoot%\WinPreSetup.log
reg.exe delete HKLM\Loaded_System\ControlSet001\Enum\Firadisk /f >> %SystemRoot%\WinPreSetup.log
reg.exe delete HKLM\Loaded_System\ControlSet001\Enum\Root\Firadisk /f >> %SystemRoot%\WinPreSetup.log
reg.exe delete HKLM\Loaded_System\ControlSet001\Control\Firadisk /f >> %SystemRoot%\WinPreSetup.log
REM reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnce /v CleanFira /t REG_SZ /d "cmd /c If Exist drivers\firadisk.sys Del drivers\firadisk.sys"
)
if exist net.exe (
if exist sc.exe (
net.exe stop FiraDisk >> %SystemRoot%\WinPreSetup.log
sc.exe delete FiraDisk >> %SystemRoot%\WinPreSetup.log
REM del /f %SystemRoot%\OemDir\firadisk* >> %SystemRoot%\WinPreSetup.log
REM if exist %SystemRoot%\Windows\System32\drivers\firadisk.sys del /f %SystemRoot%\Windows\System32\drivers\firadisk.sys >> %SystemRoot%\WinPreSetup.log
) else (
echo Could not delete Firadisk service, sc.exe does not exist >> %SystemRoot%\WinPreSetup.log
)
) else (
echo Could not stop Firadisk service, net.exe does not exist >> %SystemRoot%\WinPreSetup.log
)
)

if not exist reg.exe (
echo reg.exe not found 
echo reg.exe not found >> %SystemRoot%\WinPreSetup.log
)
if not exist findstr.exe (
echo findstr.exe not found 
echo findstr.exe not found >> %SystemRoot%\WinPreSetup.log
)

if not exist mountvol.exe (
echo findstr.exe not found 
echo findstr.exe not found >> %SystemRoot%\WinPreSetup.log
) else (
echo mountvol.exe output: >> %SystemRoot%\WinPreSetup.log
mountvol.exe >> %SystemRoot%\WinPreSetup.log
)

rem XPpSP2x string is dynamically changed by WinSetupFromUSB when prepariung source
set TAGFILE=\AIO\WS\

if exist mountvol.exe (
for /f "tokens=1 delims=: " %%? in ('mountvol.exe ^|find ":\"') do (
  dir %%?:%TAGFILE% > nul 2>&1 && set CDDRIVE=%%?:
if defined CDDRIVE goto :CDDRIVE_found
)
) else (
FOR %%h IN (U V W X C D E F G H I J K L M N O P Q R S T Y) DO (
IF EXIST "%%h:%TAGFILE%" (
SET CDDRIVE=%%h:
goto :CDDRIVE_found
)
)
)

FOR /L %%G IN (20,-1,0) DO (
%systemroot%\SysWow64\mnt.exe Y: \device\harddisk%%G\partition1
dir Y:%TAGFILE% > nul 2>&1 && set CDDRIVE=Y:
if defined CDDRIVE goto :CDDRIVE_found
%systemroot%\SysWow64\mnt.exe -u Y:
)

echo no %TAGFILE% drive found
echo no %TAGFILE% drive found >> %SystemRoot%\WinPreSetup.log

REM +=======================================================+
REM | prepare USB boot configuration |
REM |-------------------------------------------------------|
REM echo presetup fixBoot.USB
set reboot=

rem second trial: permanent USB changes
if exist reboot.1 if not exist reboot.2 (
set reboot=true
echo reboot USB driver setting >reboot.2
echo prepare USB boot configuration %date% %time% - permanent changes >>%SystemRoot%\WinPreSetup.log
call :set_usb_boot_setting_full SYSTEM CurrentControlSet
reg.exe load HKLM\loaded_SYSTEM config\system.sav
call :set_usb_boot_setting_full loaded_SYSTEM ControlSet001
reg.exe unload HKLM\loaded_SYSTEM
)

rem first trial: minimal, no permanent changes
if not exist reboot.1 (
set reboot=true
echo reboot USB driver setting >reboot.1
echo prepare USB boot configuration %date% %time% - minimal changes>>%SystemRoot%\WinPreSetup.log
call :set_usb_boot_setting SYSTEM CurrentControlSet
reg.exe load HKLM\loaded_SYSTEM config\system.sav
call :set_usb_boot_setting loaded_SYSTEM ControlSet001
reg.exe unload HKLM\loaded_SYSTEM
)

REM +=======================================================+
REM | reboot the machine once, avoid endless loop |
REM |-------------------------------------------------------|
if defined reboot (
(echo reboot definied - %date% %time% &echo.)>> %SystemRoot%\WinPreSetup.log
goto :eof
)



:CDDRIVE_found ===============================================
set srcpath=\??\%CDDRIVE%%TAGFILE%\

echo CDDRIVE %CDDRIVE% - srcpath %srcpath%
echo CDDRIVE %CDDRIVE% - srcpath %srcpath% >> %SystemRoot%\WinPreSetup.log

if exist $winnt$.new del /f $winnt$.new
FOR /F "tokens=1* delims== " %%a in ($winnt$.inf) DO (
set line=%%a = %%b
if %%b.==. set line=%%a
rem requires a drive letter still
rem IF /I sourcepath.==%%a. set line=sourcepath = "\\?\GLOBALROOT\Device\Harddisk1\Partition1\WIN_SETUP\XP_X64"
IF /I sourcepath.==%%a. set line=sourcepath = "%srcpath%"
IF /I dospath.==%%a. set line=;
echo !line!>>$winnt$.new
)
if exist $winnt$.new (
ren $winnt$.inf $winnt$.0
if exist $winnt$.inf del /f $winnt$.inf
ren $winnt$.new $winnt$.inf
)

findstr.exe "sourcepath" $winnt$.inf
findstr.exe "sourcepath" $winnt$.inf >> %SystemRoot%\WinPreSetup.log

rem required at all?
REM %CDDRIVE%
REM start /min "Keeping USB disk mounted workarround, do NOT close!" pushd %CDDRIVE%


echo Preparing setup.cmd in temp folder >> %SystemRoot%\WinPreSetup.log

if exist %SystemRoot%\temp\setup.cmd del /f %SystemRoot%\temp\setup.cmd >> %SystemRoot%\WinPreSetup.log
if exist %SystemRoot%\temp\setup.exe del /f %SystemRoot%\temp\setup.exe >> %SystemRoot%\WinPreSetup.log


if not exist %SystemRoot%\temp md %SystemRoot%\temp >> %SystemRoot%\WinPreSetup.log
copy setup.exe %SystemRoot%\temp >> %SystemRoot%\WinPreSetup.log
echo %CDDRIVE% > %SystemRoot%\temp\setup.cmd
echo pushd %CDDRIVE% >> %SystemRoot%\temp\setup.cmd
echo pause >> %SystemRoot%\temp\setup.cmd
pushd %SystemRoot%\temp
echo Launching setup.exe in temp >> %SystemRoot%\WinPreSetup.log
start %SystemRoot%\temp\setup.exe
popd


rem presetup.cmd place, do NOT edit this line
rem if exist presetup.cmd (
rem hidcon.exe presetup.cmd
rem start /min /wait "BTS presetup.cmd, do not close!" presetup.cmd
rem )

REM +=======================================================+
REM | Prepare Windows to start from USB
REM |-------------------------------------------------------|

rem usb_boot echo prepare USB boot configuration %date% %time% - permanent changes and USBbootWatcher >>%SystemRoot%\WinPreSetup.log
rem usb_boot if exist UsbBootW.exe ren UsbBootW.exe UsbBootWatcher.exe
rem usb_boot if exist UsbBootW.cnf ren UsbBootW.cnf UsbBootWatcher.conf
rem usb_boot call :set_usb_boot_setting_full SYSTEM CurrentControlSet
rem usb_boot call :set_UsbBootWatcher SYSTEM CurrentControlSet
rem usb_boot reg.exe load HKLM\loaded_SYSTEM config\system.sav
rem usb_boot call :set_usb_boot_setting_full loaded_SYSTEM ControlSet001
rem usb_boot call :set_UsbBootWatcher loaded_SYSTEM ControlSet001
rem usb_boot reg.exe unload HKLM\loaded_SYSTEM




REM +=======================================================+
REM | Finally start the installation |
REM |-------------------------------------------------------|


echo deleting setupol.exe >> %SystemRoot%\WinPreSetup.log
if exist setupol.exe del /f setupol.exe >> %SystemRoot%\WinPreSetup.log
echo renaming setup.exe to setupol.exe >> %SystemRoot%\WinPreSetup.log
if exist setup.exe ren setup.exe setupol.exe
echo renaming setupWST.exe to setup.exe >> %SystemRoot%\WinPreSetup.log
if exist setupWST.exe ren setupWST.exe setup.exe
echo finished renaming setup files >> %SystemRoot%\WinPreSetup.log


rem often setup.exe -newsetup
rem workaround for 2000 which does not include reg.exe by default
if exist reg.exe (
goto :startXP
) else (
goto :start2000
)

echo exiting: %date% %time% >> %SystemRoot%\WinPreSetup.log
EXIT
goto :eof ==============end CDDRIVE_found=============================

:startXP
FOR /F "tokens=1-2*" %%a IN ('reg.exe query "HKLM\SYSTEM\Setup" /v "CmdLine"') DO set CmdLine=%%c
IF "%CmdLine:~-2%"=="\0" set CmdLine=%CmdLine:~0,-2%
echo run setup CmdLine: %CmdLine% - %date% %time%
echo run setup CmdLine: %CmdLine% - %date% %time% >> %SystemRoot%\WinPreSetup.log
start /WAIT %CmdLine%
goto :eof


:start2000
echo reg.exe not found, launching "start /WAIT setup.exe -newsetup"
echo reg.exe not found, launching "start /WAIT setup.exe -newsetup" >> %SystemRoot%\WinPreSetup.log
start /WAIT setup.exe -newsetup
goto :eof


:set_usb_boot_setting =================================================
set Services=HKLM\%1\%2\Services
echo on
reg.exe query "%Services%\usbohci" | findstr.exe /I "Start" && (
reg.exe add "%Services%\usbohci" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbohci" /f /v "Group" /d "Boot Bus Extender"
)
reg.exe query "%Services%\usbuhci" | findstr.exe /I "Start" && (
reg.exe add "%Services%\usbuhci" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbuhci" /f /v "Group" /d "Boot Bus Extender"
)
reg.exe query "%Services%\usbehci" | findstr.exe /I "Start" && (
reg.exe add "%Services%\usbehci" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbehci" /f /v "Group" /d "Boot Bus Extender"
)
reg.exe add "%Services%\usbhub" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbhub" /f /v "Group" /d "System Bus Extender"
reg.exe add "%Services%\usbstor" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbstor" /f /v "Group" /d "System Bus Extender"
@echo off
goto :eof === end set_usb_boot_setting ===============================

:set_UsbBootWatcher ====================================================
set Services=HKLM\%1\%2\Services
echo on
rem reg.exe add "HKLM\%1\Setup\AllowStart\UsbBootWatcher /f /ve"
REM reg.exe add "HKLM\%1\Setup\AllowStart\UsbBootWatcher\dummy /f"
REM reg.exe add "%Services%\UsbBootWatcher" /f /t REG_EXPAND_SZ /v "ImagePath" /d "%%SystemRoot%%\system32\UsbBootWatcher.exe"
REM reg.exe add "%Services%\UsbBootWatcher" /f /v "ObjectName" /d "LocalSystem"
REM reg.exe add "%Services%\UsbBootWatcher" /f /v "DisplayName" /d "Usb Boot Watcher Service"
REM reg.exe add "%Services%\UsbBootWatcher" /f /t REG_DWORD /v "ErrorControl" /d 0
REM reg.exe add "%Services%\UsbBootWatcher" /f /t REG_DWORD /v "Start" /d 2
REM reg.exe add "%Services%\UsbBootWatcher" /f /t REG_DWORD /v "Type" /d 0x10
UsbBootWatcher.exe /install
@echo off
goto :eof  === end set_UsbBootWatcher =================================


:set_usb_boot_setting_full ============================================
set CriticalDeviceDatabase=HKLM\%1\%2\Control\CriticalDeviceDatabase
set Services=HKLM\%1\%2\Services

echo on
reg.exe add "%CriticalDeviceDatabase%\PCI#CC_0C0300" /f /v "ClassGUID" /d "{36FC9E60-C465-11CF-8056-444553540000}"
reg.exe add "%CriticalDeviceDatabase%\PCI#CC_0C0300" /f /v "Service" /d "usbuhci"

reg.exe add "%CriticalDeviceDatabase%\PCI#CC_0C0310" /f /v "ClassGUID" /d "{36FC9E60-C465-11CF-8056-444553540000}"
reg.exe add "%CriticalDeviceDatabase%\PCI#CC_0C0310" /f /v "Service" /d "usbohci"

reg.exe add "%CriticalDeviceDatabase%\PCI#CC_0C0320" /f /v "ClassGUID" /d "{36FC9E60-C465-11CF-8056-444553540000}"
reg.exe add "%CriticalDeviceDatabase%\PCI#CC_0C0320" /f /v "Service" /d "usbehci"

reg.exe add "%CriticalDeviceDatabase%\USB#CLASS_08" /f /v "ClassGUID" /d "{36FC9E60-C465-11CF-8056-444553540000}"
reg.exe add "%CriticalDeviceDatabase%\USB#CLASS_08" /f /v "Service" /d "usbstor"

reg.exe add "%CriticalDeviceDatabase%\USB#CLASS_09" /f /v "ClassGUID" /d "{36FC9E60-C465-11CF-8056-444553540000}"
reg.exe add "%CriticalDeviceDatabase%\USB#CLASS_09" /f /v "Service" /d "usbhub"

reg.exe add "%CriticalDeviceDatabase%\USB#ROOT_HUB" /f /v "ClassGUID" /d "{36FC9E60-C465-11CF-8056-444553540000}"
reg.exe add "%CriticalDeviceDatabase%\USB#ROOT_HUB" /f /v "Service" /d "usbhub"

reg.exe add "%CriticalDeviceDatabase%\USB#ROOT_HUB20" /f /v "ClassGUID" /d "{36FC9E60-C465-11CF-8056-444553540000}"
reg.exe add "%CriticalDeviceDatabase%\USB#ROOT_HUB20" /f /v "Service" /d "usbhub"

rem added as per: http://msdn.microsoft.com/en-us/library/ee428799.aspx

reg.exe add "%CriticalDeviceDatabase%\gendisk" /f /v "ClassGUID" /d "{4D36E967-E325-11CE-BFC1-08002BE10318}"
reg.exe add "%CriticalDeviceDatabase%\gendisk" /f /v "Service" /d "disk"

reg.exe add "%CriticalDeviceDatabase%\*pnp0a03" /f /v "ClassGUID" /d "{4D36E97D-E325-11CE-BFC1-08002BE10318}"
reg.exe add "%CriticalDeviceDatabase%\*pnp0a03" /f /v "Service" /d "pci"

reg.exe add "%Services%\usbohci" /f /v "Group" /d "Boot Bus Extender"
reg.exe add "%Services%\usbohci" /f /t REG_DWORD /v "Tag" /d 3
reg.exe add "%Services%\usbohci" /f /t REG_DWORD /v "ErrorControl" /d 1
reg.exe add "%Services%\usbohci" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbohci" /f /t REG_DWORD /v "Type" /d 1

reg.exe add "%Services%\usbuhci" /f /v "Group" /d "Boot Bus Extender"
reg.exe add "%Services%\usbuhci" /f /t REG_DWORD /v "Tag" /d 3
reg.exe add "%Services%\usbuhci" /f /t REG_DWORD /v "ErrorControl" /d 1
reg.exe add "%Services%\usbuhci" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbuhci" /f /t REG_DWORD /v "Type" /d 1

reg.exe add "%Services%\usbehci" /f /v "Group" /d "Boot Bus Extender"
reg.exe add "%Services%\usbehci" /f /t REG_DWORD /v "Tag" /d 3
reg.exe add "%Services%\usbehci" /f /t REG_DWORD /v "ErrorControl" /d 1
reg.exe add "%Services%\usbehci" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbehci" /f /t REG_DWORD /v "Type" /d 1

reg.exe add "%Services%\usbhub" /f /v "Group" /d "System Bus Extender"
reg.exe add "%Services%\usbhub" /f /t REG_DWORD /v "Tag" /d 2
reg.exe add "%Services%\usbhub" /f /t REG_DWORD /v "ErrorControl" /d 1
reg.exe add "%Services%\usbhub" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbhub" /f /t REG_DWORD /v "Type" /d 1

reg.exe add "%Services%\usbstor" /f /v "Group" /d "System Bus Extender"
reg.exe add "%Services%\usbstor" /f /t REG_DWORD /v "Tag" /d 7
reg.exe add "%Services%\usbstor" /f /t REG_DWORD /v "ErrorControl" /d 1
reg.exe add "%Services%\usbstor" /f /t REG_DWORD /v "Start" /d 0
reg.exe add "%Services%\usbstor" /f /t REG_DWORD /v "Type" /d 1
@echo off
goto :eof === end set_usb_boot_setting_full ============================