# AIO Boot
AIO Boot is a tool that can help you create a bootable USB with Grub2, Grub4dos, Syslinux, Clover and rEFInd. AIO Boot can boot Windows and most Linux distributions and boot via LAN using Tiny PXE Server.

Currently, there are many USB boot tool with many different features, so you will hardly be able to select a tool to use (unless you have a lot of USB). Also for that reason that I released AIO Boot tool.

Homepage: [AIO Boot](https://www.sitecuatui.com/aio-boot-v0-9/)<br />
Please check the [Releases](https://github.com/nguyentumine/AIO-Boot/releases) page for latest information.

My English is not good, I used Google to translate. Please sympathize with me.

# Features
AIO Boot was released with a lot of great features that other tools do not yet support.
#### The bootloader is supported:
- For Legacy-MBR: Grub2, Grub4dos, Syslinux and Clover [Legacy].<br />
- For UEFI-GPT: Grub2, Clover [UEFI] and rEFInd.
- Boot from LAN: Tiny PXE Server, iPXE and FreeNFS.

#### Some features are supported:
- UEFI-GPT and MBR-Legacy.
- USB and HDD with FAT32 or NTFS format ...
- Supports boot into Legacy mode for the hard disk in GPT style.
- [Boot directly to UEFI mode from Legacy mode using Clover](https://www.sitecuatui.com/uefi-legacy-clover/). Your computer does not need UEFI support.
- Boot via LAN with Tiny PXE Server.
- Integration of package through **AIOCreator.exe** tool.
- Bypass the Secure Boot on the UEFI mode via **Shimx64.efi** (need tester). If your computer has a Secure Boot section, turn it on, then boot **/EFI/Boot/shimx64.efi**.
- Support boot via LAN using UEFI mode.
- Automatically identifying and boot into the operating system installed on HDD: FreeBSD, Mac OS X/Darwin, Windows 7/8.1/10/Vista, Windows NT/2000/XP, Windows 98/ME, MS-DOS, FreeDOS, Linux distributions, Android-x86 and Remix OS 32bit/64bit... You will not need to worry about problems boot error, error loss boot ...
- One or more partitions, AIO Boot also supports hidden partition.
- Support hotkeys for Grub2. At the main menu, if you want to boot into a certain menu, simply press their hot key. For example, to restart your computer, you simply press the "F7" or "F6" to shutdown.
- Support password protection for Grub2.
  - Anyone who does not have a password can not boot, edit menus, and use the Grub2 command line.
  - The password uses the **PBKDF2** method to encrypt so no one can know the password you have set.
  - Anyone can change or remove passwords if they have access to Grub2 files.
- Supports multiple languages, including Vietnamese, English, Russian and French...
- Multiple sets of Windows setup files- XP, 2000, 2003, Vista, WIndows 7, Server 2008, Windows 8, Server 2012, both 32 and 64 bit versions are supported. Both BIOS and (U)EFI mode are supported.
- Support to restore the Windows bootloader for both Legacy and UEFI mode.
- Supports installing Windows 7 on a USB 3.0 port. This will help you resolve the error: `A required CD/DVD drive device driver is missing. If you have a driver floppy disk, CD, DVD, or USB flash drive, please insert it now`.
- Support to edit and delete the MENU ~~(except for Windows packages)~~.
- Automatically identifies the DOS program to integrate.

#### Some issues to be resolved:
- Partition in FAT32 format can not save files larger than 4GB in size. If you want to save the file size is greater than 4GB, please format your USB or HDD to NTFS format.
- To be able to boot UEFI, you need a FAT32 partition. If you want to use NTFS, but still supports UEFI, please create a FAT32 partition and copy that folder into the EFI.

# How to create a bootable USB
AIO Boot has many features but it's very simple and compact. The creation of the AIO Boot is even simpler with just a few clicks.
- Once you have downloaded the application, you need to select the drive where the necessary files should be extracted. This should be the bootable USB or HDD you wish to create.
- After unpacking, the application will be launched automatically, and you can install either Grub2 or Clover with only a single mouse click. Additionally, you can run PXE and choose either Legacy or UEFI mode.

After you've created a bootable USB or HDD is complete, you can boot USB on VirtualBox virtual machines for testing.

# Boot via LAN
Boot via LAN particularly useful for rescue work, ghost and install Win for net shop, or schools, or businesses with a large number of computers. AIO Boot supports booting via LAN with Tiny PXE Server.

Support most of WinPE, the above software and Linux distributions such as Ubuntu, CentOS and Linux Mint. Because time is limited, so I will try to support this tool much more.

AIO Boot using iPXE as bootloader, Tiny PXE Server as PXE Server and FreeNFS as NFS Server. Run **AIOCreator.exe**, then click **Run PXE** to activate PXE Server and NFS Server.
# Download
AIO boot Boot is a lightweight, less than 37 Mb.

**File name:** AIO_Boot_Extractor.exe<br />
**Size:** 37,5 MB<br />
**Version:** 0.9.3.8<br />
**Last updated:** 30.03.2017<br />
**MD5 checksum:** 3b9b4087785716f24974cf5540515745<br />

**Download:** [Google Drive](http://www.sitecuatui.com/out/aiogd) | [Softpedia](http://www.softpedia.com/get/System/Boot-Manager-Disk/AIO-Boot.shtml) | [SourceForge](https://sourceforge.net/projects/aioboot/) | [Mega.co.nz](http://www.sitecuatui.com/out/aiobootmega) | [MediaFire](http://www.sitecuatui.com/out/aiobootmf)

AIO Boot is constructed from a variety of sources, certainly still a lot of flaws, eager for sympathy. I would love to hear from you so that I can improve this tool better.