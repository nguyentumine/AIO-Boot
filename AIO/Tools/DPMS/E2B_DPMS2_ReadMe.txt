DPMS Automatic Driver Detection (DPMS-ADD)for E2B
=================================================

If installing XP to a system which has a SATA (AHCI), SCSI or RAID storage system, XP Setup will require a Mass Storage Driver.
This driver is usually loaded from a Floppy disk manually when the user presses F6 when prompted during XP Setup. 
A common alternative is to 'inject' the drivers into the ISO file and make a new ISO.

The E2B DPMS Automatic Driver Detection package automatically detects what driver is required and generates the correct 'F6' virtual floppy disks in memory. You can thus install XP directly from an unaltered XP ISO file straight onto a system from a USB drive without needing to know what F6 driver is required or obtain the special F6 floppy disk. As the Virtual floppy disks are created in system memory, you do not need a floppy disk drive either!

Typical two virtual F6 floppy disks are generated:

Floppy 0 = Causes XP to load a Ram Disk driver (e.g. FiraDisk or WinVBlock)
Floppy 1 = Causes XP to load an OEM Mass Storage Driver for AHCI/SATA/SCSI/RAID

Note that only the Mass Storage (disk) driver is installed. You will need to install other drivers such as graphics, sound, network, etc. once XP has been installed.


How to use the DPMS Update Package
==================================

You should already have an up-to-date Easy2Boot V1 USB boot drive made (see www.rmprepusb.com Tutorial #72b for details).

1. Copy the DPMS folder to the root of your E2B boot drive to make a new folder at \_ISO\E2B\grub\DPMS.
(some old E2B files in the grub folder may also be updated)

2. Download the latest Mass Storage Driver Pack for XP x86 NT5 from http://driverpacks.net/driverpacks/windows/xp/x86/mass-storage
  e.g. Sep. 24 2012  Windows 200/XP/2003  x86 Mass Storage  version=12.09
   Click on the Download button which will download a Torrent file  (e.g. DP_MassStorage_wnt5_x86-32_1209.7z)
   Use BitTorrent (or your favourite Torrent app) to downlaod the .7z file
   Use 7Zip to unpack the file

3. Extract the contents of the 7zip file to your USB pen at \_ISO\E2B\grub\DPMS.

4. Rename the file at \_ISO\E2B\grub\DPMS\DriverPack_MassStorage_wnt5_x86-32.ini to \_ISO\E2B\grub\DPMS\DriverPack.ini

E2B Folder structure for DPMS is:

\_ISO\E2B\grub\XPStep1.g4b
\_ISO\E2B\grub\XPStep2.g4b
\_ISO\E2B\grub\DPMS\dpms2.bat
\_ISO\E2B\grub\DPMS\chkpci
\_ISO\E2B\grub\DPMS\fat
\_ISO\E2B\grub\DPMS\inifile
\_ISO\E2B\grub\DPMS\E2B_DPMS_ReadMe.txt (this file)
\_ISO\E2B\grub\DPMS\FIRA Firadisk driver folder
\_ISO\E2B\grub\DPMS\WINV WinVBlock driver folder
\_ISO\E2B\grub\DPMS\D folder (no files)
\_ISO\E2B\grub\DPMS\D\M folder containing lots of driver folders (e.g. I3, I4, V, etc.) extracted by you from the DP_MassStorage_wnt5_x86-32_XXXX.7z)

Note: 
The files oem0.txt and oem1.txt will contain copies for the two oemsetup.txt files used by the previous install. 
The files dir0.txt and dir1.txt will contain directory listings of the two floppies.
These files can be inspected after an unsuccessful install or sent to me for problem solving - do not change their size or delete them.

email: rmprep@gmail.com

Donations for this software can be made via PayPal - please visit the website to make a donation if you enjoy using this software!





