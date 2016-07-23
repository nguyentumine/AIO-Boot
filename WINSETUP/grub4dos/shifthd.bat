!BAT

::small batch to shift HD possitions by Ilko
::the purpose is to set USB disk last or make sure it is, even if boot grub4dos from a CD, shifting all other hard disks one possition up 
::if it was seen as a floppy call PLoP

clear
echo Shifting USB disk to be last...

::debug off
errorcheck off
::find if PLoP is already loaded
::http://forum.plop.at/index.php/topic,165.0.html
cat --hex --locate=PoLPu@ (md)0x3D0+0x130 > nul && goto :plop_detected
goto :start

:start
::echo Locating usbdrive.tag
ls /WINSETUP/grub4dos/usbdrive.tag > nul || find --set-root --devices=hf /WINSETUP/grub4dos/usbdrive.tag > nul
checkrange 0x80 read 0x82A0 > nul && goto :usb_is_hd0
checkrange 0x00,0x01 read 0x82A0 > nul && goto :usb_is_fd
checkrange 0x00,0x01,0x80 read 0x82A0 > nul || goto :usb_is_not_hd0

:plop_detected
echo
echo It seems PLoP has been loaded
checkrange 0:2 calc *0x475&0xff  > nul && goto :start
set /a hdn=*0x475 & 0xff > nul
set /a hdm=%hdn% - 1 > nul
map (hd-1) (hd-2)
map --harddrives=%hdm%
map --rehook
goto :start

:usb_is_not_hd0
::http://cvwyg-blog.appspot.com/grub/GRUB4DOS5mlsy.htm
::http://reboot.pro/16069/page__view__findpost__p__145675
::Other internal variables in README_GRUB4DOS.txt
::get current root drive
set /a cur_drv=*0x82A0 & 0x7F  > nul
::number of hard disks as BIOS reports them
set /a hdn=*0x475 & 0xff  > nul
set /a hdm=%hdn% - 1  > nul
if %cur_drv%==%hdm% echo USB disk is already last- hd%cur_drv% && set /a HDCNT=%hdn% && set /a RDSK=%cur_drv% && goto :s_end
echo USB disk was not hd0, setting it hd0
map () (hd0)
map (hd0) ()
map --rehook
goto :usb_is_hd0

:usb_is_hd0
checkrange 2 calc *0x475 & 0xFF > nul && goto :hd2
checkrange 1 calc *0x475 & 0xFF > nul && goto :hd1
checkrange 3 calc *0x475 & 0xFF > nul && goto :hd3
checkrange 4 calc *0x475 & 0xFF > nul && goto :hd4
checkrange 5 calc *0x475 & 0xFF > nul && goto :hd5
checkrange 6:999 calc *0x475 & 0xFF > nul && goto :hd6

goto :s_end

:hd6
echo Found more than 5 hard disks or mass storage devices attached!
echo It's safer to shut down the computer and disconnect or disable temporarily the unneeded ones
echo if you want to install Windows 2000/XP/2003 on the disk numbered above 4 and you boot from USB disk.
echo Will set USB disk as hd4 so it should be safe to install to hd0-hd3.
pause Press any key to continue...
goto :hd5

:hd5
set /a HDCNT=5  > nul 
set /a RDSK=%HDCNT% - 1  > nul
map (hd0) (hd4)
map (hd1) (hd0)
map (hd2) (hd1)
map (hd3) (hd2)
map (hd4) (hd3)
map --rehook
echo Found %HDCNT% disks, set USB disk hd%RDSK%
::pause --wait=1
goto :s_end

:hd4
set /a HDCNT=4  > nul
set /a RDSK=%HDCNT% - 1 > nul
map (hd0) (hd3)
map (hd1) (hd0)
map (hd2) (hd1)
map (hd3) (hd2)
map --rehook
echo Found %HDCNT% disks, set USB disk hd%RDSK%
::pause --wait=1
goto :s_end

:hd3
set /a HDCNT=3 > nul
set /a RDSK=%HDCNT% - 1 > nul
map (hd0) (hd2)
map (hd1) (hd0)
map (hd2) (hd1)
map --rehook
echo Found %HDCNT% disks, set USB disk hd%RDSK%
::pause --wait=1
goto :s_end

:hd2
set /a HDCNT=2 > nul
set /a RDSK=%HDCNT% - 1 > nul
map (hd0) (hd1)
map (hd1) (hd0)
map --rehook
echo Found %HDCNT% disks, set USB disk hd%RDSK%
::pause --wait=1
goto :s_end

:hd1
set /a HDCNT=1 > nul
set /a RDSK=%HDCNT% - 1 > nul
echo Found %HDCNT% disks, set USB disk hd%RDSK%
::pause --wait=1
goto :s_end

:usb_is_fd
::start PLoP
::find if PLoP is already loaded
::http://forum.plop.at/index.php/topic,165.0.html
::cat --hex --locate=PoLPu@ (md)0x3D0 0x130 && goto XXX
cat --hex --locate=PoLPu@ (md)0x3D0 0x130 && echo It seems PLoP was already loaded && goto :s_end
echo It seems your USB disk was seen as a Floppy/ZIP disk by BIOS.
echo Will try to launch PLoP boot manager which might help to make the USB disk seen as a hard disk.
echo This is experimental and is not guaranteed to work as expected.
echo If you are using USB keyboard, you won't be able to use it after the menu reloads.
echo
echo The highlighted menu entry will auto start after 10 seconds. You can shut down or reset the computer if it's not the desired one.
echo
pause --wait=20 Press any key to continue or wait 20 seconds to timeout 
ls /WINSETUP/grub4dos/plpbt.bin > nul || find --set-root --devices=hf /WINSETUP/grub4dos/plpbt.bin
savedefault
::debug on
chainloader /WINSETUP/grub4dos/plpbt.bin
boot
goto :s_end

:s_end
echo 
errorcheck on
::debug on
exit