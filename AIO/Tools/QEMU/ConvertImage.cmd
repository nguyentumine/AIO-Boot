@Echo off
cls
color 9f
TITLE %0 RMPREPUSB Raw Image conversion using qemu-img
REM %1 is image to convert
REM %2 is path of output file

if @%1==@ goto :EOF
if @%2==@ goto :EOF

REM delete target file as RMPrepUSB is polling for this
if exist %2 del %2
SET MYERR=%1 DOES NOT EXIST!
if not exist %1 goto :ERRMSG

echo SOURCE=%1
echo TARGET=%2
echo.
pushd %~dp0
SET MYERR=ERROR: QEMU\QEMU-IMG.EXE file does not exist!
if not exist qemu-img.exe goto :ERRMSG

if exist info.txt del info.txt
if exist info1.txt del info1.txt
if exist err.txt del err.txt
echo.
start /B qemu-img.exe info %1 >info.txt 2>ERR.TXT
if exist info.txt type info.txt
if exist ERR.txt type ERR.txt
find /I "file format:" info.txt > info1.txt
SET MYERR=ERROR: File format of %1 not recognised
if errorlevel 1 goto :ERRMSG

find /I "raw" info1.txt > nul
SET MYERR=File format is already RAW format and does not need converting!
if errorlevel 1 goto :ERRMSG

cls
echo SOURCE=%1
echo TARGET=%2
echo Converting %1 to %2 - please wait...
if exist info.txt del info.txt
if exist info1.txt del info1.txt
if exist err.txt del err.txt
if exist %2 del %2
SET MYERR=ERROR: Failed to convert %1 to RAW format!
echo Running command qemu-img.exe convert -O raw %1 %2
echo Please wait...
start /B /WAIT qemu-img.exe convert -p -O raw %1 %2  2>ERR.TXT

::if exist info.txt type info.txt
if exist ERR.txt type ERR.txt
if errorlevel 1 goto :ERRMSG
if not exist %2 goto :ERRMSG

find /I "error " ERR.TXT
if NOT errorlevel 1 goto :ERRMSG
::find /I "error " INFO.TXT
::if NOT errorlevel 1 goto :ERRMSG


REM check created OK
if exist info.txt del info.txt
if exist info1.txt del info1.txt
if exist err.txt del err.txt
@echo on
start /B /WAIT qemu-img.exe info %2 >info.txt 2>err.txt
find /I "file format:" info.txt > info1.txt
SET MYERR=File format of %2 not recognised
if errorlevel 1 goto :ERRMSG
find /I "raw" info1.txt > nul
SET MYERR=ERROR: File was not converted to RAW format!
if errorlevel 1 goto :ERRMSG

dir %1 > nul
dir %2 > nul
echo %1 CONVERTED OK
echo FILE=%~f2   SIZE=%~z2
REM set errorlevel 0
color 9f
popd
goto :EOF


:ERRMSG
pause
if exist %2 del %2
color f4
echo %MYERR%
REM make a small output file to show we have completed the operation
echo %MYERR%>%2
REM make errorlevel > 0
color 99
popd
