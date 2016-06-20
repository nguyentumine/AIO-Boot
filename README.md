# AIO Boot
AIO Boot is a tool that can help you create a bootable USB with Grub2, Grub4dos, Syslinux, Clover and rEFInd. AIO Boot can boot Windows and most Linux distributions and boot via LAN using Tiny PXE Server.

Currently, there are many USB boot tool with many different features, so you will hardly be able to select a tool to use (unless you have a lot of USB). Also for that reason that I released AIO Boot tool.

Homepage: http://www.sitecuatui.com/

My English is not good, I used Google to translate. Please sympathize with me.

# Features
AIO Boot was released with a lot of great features that other tools do not yet support.
#### The bootloader is supported:
- For Legacy-MBR: Grub2, grub4dos and syslinux.<br />
- For UEFI-GPT: Grub2, Clover, refind.

#### Some features are supported:
- UEFI-GPT and MBR-Legacy.
- USB and HDD with FAT32 or NTFS format ...
- Boot via LAN with Tiny PXE Server.
- Automatically identifying and boot into the operating system installed on HDD: FreeBSD, Mac OS X/Darwin, Windows 7/8.1/10/Vista, Windows NT/2000/XP, Windows 98/ME, MS-DOS, FreeDOS, Linux distributions, Android-x86 and Remix OS 32bit/64bit... You will not need to worry about problems boot error, error loss boot ...
- One or more partitions, AIO Boot also supports hidden partition.
- Support hotkeys for Grub2. At the main menu, if you want to boot into a certain menu, simply press their hot key. For example, to restart your computer, you simply press the "r" or "o" to shutdown.
- Supports multiple languages, including Vietnamese, English, Russian and French...

#### Some issues to be resolved:
- Partition in FAT32 format can not save files larger than 4GB in size. If you want to save the file size is greater than 4GB, please format your USB or HDD to NTFS format.
- To be able to boot UEFI, you need a FAT32 partition. If you want to use NTFS, but still supports UEFI, please create a FAT32 partition and copy that folder into the EFI.
- Use BootICE to create multiple partitions and USB. AIO Boot helps you can boot on all the hidden partition.

# How to create a bootable USB
AIO Boot has many features but it's very simple and compact. The creation of the AIO Boot is even simpler with just a few clicks.
- Unzip AIO Boot into the root directory of any USB or HDD partition that you want to create a boot.
- Running MakeBoot.exe and answer options to create.
After you've created a bootable USB or HDD is complete, you can boot USB on VirtualBox virtual machines for testing.

# Boot via LAN
Boot via LAN particularly useful for rescue work, ghost and install Win for net shop, or schools, or businesses with a large number of computers. AIO Boot supports booting via LAN with Tiny PXE Server.

Support most of WinPE, the above software and Linux distributions such as Ubuntu, CentOS and Linux Mint. Because time is limited, so I will try to support this tool much more.

AIO Boot using iPXE as bootloader, Tiny PXE Server as PXE Server and FreeNFS as NFS Server. Runn RunPXE.exe to activate PXE Server and NFS Server.
# Download
AIO boot Boot is a lightweight, less than 25 Mb.

**File name:** AIOBoot-0.1.4.1.7z<br />
**Size:** 24,4 MB<br />
**Version:** 0.1.4.1<br />
**Last updated:** 20.06.2016<br />

**Download:** [Mega.co.nz](http://www.sitecuatui.com/out/aiobootmega) | [MediaFire](http://www.sitecuatui.com/out/aiobootmf) | [4shared](http://www.sitecuatui.com/out/aioboot4shared) [direct link]

To download the software WinPE and list, [see here](http://www.sitecuatui.com/out/aiobootlink).

AIO Boot is constructed from a variety of sources, certainly still a lot of flaws, eager for sympathy. I would love to hear from you so that I can improve this tool better.
