@echo off
:: ver 5 - 26 May 2013  SSi
:: ver 6 - 5 Oct 2013  SSi - use oscdimg to make winpe compatible ISOs, add mkisofs command for winpe ISOs
:: ver 7 - 25 Mar 2104 SSi - use new mkisofs version, isolevel 3, use /cygwin/<driveletter with no colon> to suppress warning messages
:: ver 7.1 - 26 Mar 2014 SSi - allow for doublequotes

cls
color 1f
pushd %~dp0

::case sensitive!
set BOOTFILE=grldr

:: Strip quotes
set ISONAME=%~1
set SRCFOLDER=%~2
set VNAME=%~3
set SR=%~4

set SURE=
if /I "SR"=="SURE" set SURE=Y
if /I "%VNAME%"=="SURE" set SURE=Y & set VNAME=

if "%SRCFOLDER%"=="" set SRCFOLDER=%ISONAME% & set ISONAME=
::echo SRCFOLDER=*%SRCFOLDER%* ISONAME=*%ISONAME%*


if "%SRCFOLDER%"=="" goto :XX
if not "%ISONAME%"=="" goto :XX

echo.
echo MAKE A GRUB4DOS BOOTABLE ISO FILE (from a grub4dos bootable USB drive)
echo.
if not exist "%SRCFOLDER%\%BOOTFILE%" (echo ERROR: "%SRCFOLDER%" must be a grub4dos drive and contain the "%BOOTFILE%" file! & pause & goto :EOF)
if "%ISONAME%"=="" set /P ISONAME=Please enter the name of the ISO you want to create (e.g. FRED.ISO) : 
if "%VNAME%"=="" echo Press ENTER for a Volume Name of G4DOS
if "%VNAME%"=="" set /P VNAME=Please enter a Volume Name for the CD/DVD : 


:XX
if "%VNAME%"=="" set VNAME=G4DOS
set CF=
if exist "%SRCFOLDER%\%BOOTFILE%" copy "%SRCFOLDER%\%BOOTFILE%" . >nul & set CF= [%BOOTFILE% from "%SRCFOLDER%" used]
if NOT exist "%SRCFOLDER%\%BOOTFILE%" copy "%BOOTFILE%" "%SRCFOLDER%\%BOOTFILE%" >nul & set CF= [%~dp0%BOOTFILE% used]
if "%SRCFOLDER%"=="" set CF=






cls
echo.
echo MAKE A GRUB4DOS BOOTABLE ISO FILE (from a grub4dos bootable USB drive)
echo ======================================================================
echo.
echo Variable 1 = ISO FILENAME    = %ISONAME%
echo Variable 2 = SOURCE FOLDER   = %SRCFOLDER% 
echo Variable 3 = ISO VOLUME NAME = %VNAME% 
echo              BOOTFILE        = %SRCFOLDER%\%BOOTFILE% %CF%
echo.
if "%ISONAME%"==""   (
echo Usage: %0 [ISO FILENAME] [SOURCE FOLDER] [ISO VOLUME NAME] ["SURE"]
echo.
echo  - OR -
echo.
echo Usage: %0 [SOURCE FOLDER]
goto :EOF)
if "%SRCFOLDER%"=="" echo Usage: %0 [ISO FILENAME] [SOURCE FOLDER] [ISO VOLUME NAME] ["SURE"] && goto :EOF

Echo Make %ISONAME% from %SRCFOLDER% source files
echo using %BOOTFILE% as boot file (ISO volume name=%VNAME%)
echo.
if not exist "%SRCFOLDER%\*" echo "%SRCFOLDER%" does not exist (Note: may need double-quotes in paths)! & pause && goto :EOF
if not exist %BOOTFILE%      echo %BOOTFILE% does not exist (Note: may need double-quotes in paths)! & pause && goto :EOF

Echo To use oscdimg for WinPE ISOs, add oscdimg.exe to the RMPrepUSB\QEMU folder...

set SRCF="%SRCFOLDER%"
if "%SRCFOLDER:~-1,1%"==":" set SRCF=/cygdrive/%SRCFOLDER:~0,-1%

set TT=
echo FRED > %TMP%\t1.tmp
if exist %TMP%\t1.tmp set TT=%TMP%
echo FRED > %TEMP%\t1.tmp
if exist %TEMP%\t1.tmp set TT=%TEMP%

oscdimg.exe > %TT%\t1.tmp 2> nul
find /i "OSCDIMG 2" %TT%\t1.tmp > nul
if not errorlevel 1 goto :OSCDIMG

if exist %TT%\t1.tmp del %TT%\t1.tmp > nul
mkisofs.exe 2> %TT%\t1.tmp 1>nul 
find /i "mkisofs: Missing" %TT%\t1.tmp > nul
if errorlevel 1 goto :NO_OSCD
if exist %TT%\t1.tmp del %TT%\t1.tmp > nul

echo.
if not exist "%SRCFOLDER%\%BOOTFILE%" echo ERROR: %BOOTFILE% NOT FOUND IN "%SRCFOLDER%"! && goto :EOF
echo USING MKISOFS
echo.

if exist "%SRCFOLDER%\BOOT\BCD" echo WinPE \BOOT\BCD folder detected
if exist "%SRCFOLDER%\BOOT\boot.wim" echo WinPE \BOOT\boot.wim file detected
if exist "%SRCFOLDER%\SOURCES\boot.wim" echo WinPE \SOURCES\boot.wim file detected
if exist "%SRCFOLDER%\bootmgr" echo WinPE \bootmgr file detected
echo.
echo Make a grub4dos multiboot ISO or a WinPE ISO?
echo.
echo    Y = Force uppercase filenames, non-Joliet
@echo.
set /P ask=Make a WinPE ISO (Y/N) : 
if /i "%ask%"=="Y" goto :usePE


:: --- Non-WinPE ISO ---
echo.
echo mkisofs  -iso-level 3 -N -D -d -J -r -joliet-long -volid "%VNAME%" -A GRLDR/MKISOFS -sysid "Win32" -b %BOOTFILE% -no-emul-boot -boot-load-seg 0x7C0  -boot-load-size 4 -allow-multidot -hide %BOOTFILE% -hide boot.catalog -o "%ISONAME%" %SRCF%
echo.
echo ABOUT TO EXECUTE MKISOFS COMMAND: 
echo.
if not "%SURE%"=="Y" pause
@echo off
mkisofs  -iso-level 3 -N -D -d -J -r -joliet-long -volid "%VNAME%" -A GRLDR/MKISOFS -sysid "Win32" -b %BOOTFILE% -no-emul-boot -boot-load-seg 0x7C0  -boot-load-size 4 -allow-multidot -hide %BOOTFILE% -hide boot.catalog -o "%ISONAME%" %SRCF%
@echo off
goto :FIN




:usePE
echo.
Echo To use oscdimg for WinPE ISOs, add oscdimg.exe to the RMPrepUSB\QEMU folder...
echo.
echo mkisofs -iso-level 3 -D -force-uppercase -volid "%VNAME%"  -b %BOOTFILE% -no-emul-boot -hide boot.catalog -o "%ISONAME%" %SRCF%
echo.
echo ABOUT TO EXECUTE MKISOFS COMMAND: 
echo.
if not "%SURE%"=="Y" pause
@echo off
mkisofs -iso-level 3 -D -force-uppercase -volid "%VNAME%"  -b %BOOTFILE% -no-emul-boot -hide boot.catalog -o "%ISONAME%" %SRCF%
@echo off
goto :FIN




:OSCDIMG
echo FOUND AND USING OSCDIMG...
echo.
oscdimg.exe > %TT%\t1.tmp > nul
find /i "OSCDIMG 2" %TT%\t1.tmp > nul
if errorlevel 1 goto NO_OSCD
if exist %TT%\t1.tmp del %TT%\t1.tmp
echo.
echo OK TO EXECUTE OSCDIMG COMMAND:
rem echo oscdimg.exe -m  -n -l%VNAME% -bootdata:1#b%BOOTFILE%,e,t0x1000 %SRCFOLDER% %ISONAME%
echo oscdimg.exe -m  -n -o -l%VNAME% -b%BOOTFILE% %SRCFOLDER% %ISONAME%
echo.
pause
rem     oscdimg.exe -m  -n -l%VNAME% -bootdata:1#b%BOOTFILE%,e,t0x1000 %SRCFOLDER% %ISONAME%
     oscdimg.exe -m  -n -o -l%VNAME% -b%BOOTFILE% %SRCFOLDER% %ISONAME%
	 
	 
:FIN
echo.
echo Finished!
echo.
if exist "%ISONAME%" color 2f
for %%i in ("%ISONAME%") do echo %ISONAME%     Size=%%~zi bytes
popd
echo.
pause
goto :EOF



:NO_OSCD
cls
if exist %TT%\t1.tmp del %TT%\t1.tmp > nul
echo OSCDIMG.EXE or MKISOFS.EXE is required to make an %ISONAME% ISO file!
echo.
echo OSCDIMG.EXE
echo ===========
echo Add OSCDIMG.EXE from Microsoft to QEMU folder
echo.
echo.
goto :NOFILE


:NOFILECLS
cls
:NOFILE
echo MKISOFS.EXE
echo ===========
echo Please get mkisofs.exe and cygwin1.dll from http://www.paraglidernc.com/Files/mkisofs2.01-bootcd.ru-cygwin.zip
echo.
goto :EOF

