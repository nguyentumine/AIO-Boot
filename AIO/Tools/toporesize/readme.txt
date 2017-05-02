TopoResize 0.7.1

v0.7.1 notes..

The original v0.7 is packed with e2fsprogs-1.35, but it can't support newer ext2/ext3 format.  Daniel YC Lin  (dlin.tw <at> gmail.com) have compiled the e2fsprogs-1.40.6 package which obtained from http://e2fsprogs.sourceforge.net. That's why the version is now v0.7.1 now. The patch of e2fsprogs is put on e2fsprogs_patch.txt.  That replaced the cygwin1.dll, dumpe2fs.exe, e2fsck.exe, mke2fs.exe, resize2fs.exe of original v0.7 packing.  By the way, Chris has stopped the further developement of this utility.


Original readme.txt file....


This is a replacement for TopoEnlarge0.6 It was renamed because the ability to shrink filesystems was added.
This is beta software

This program was written by Chris Semler to be used with Topologi-Linux and/or coLinux
With this program you can change the size of your base.img file or any ext2 or ext3 image file residing on a windows filesystem. This program is to be run under windows. It will provide a list of base.img files that it has found (for topologilinux) plus an option to browse for the file and an option to create a new file. 

Your system must be ext2 or ext3 . Support for a base.img file formatted to reiserFS is not supported at this time.

In order to increase the size of base.img you must first increase the size of the file itself. That is where this program comes in. Select the file and adjust the slider to the size in MB that you want the file to be then click "resize file" If you are enlarging the file extra blank space will be appended to the end of the file. Then the filesystem will be enlarged. If you are shrinking the file the filesystem will be resized first to 2mb less than you selected and then the file will be truncated to the size you selected. That is all there is to it.

This program provides a front end for mke2fs.exe resize2fs.exe and e2fsck.exe power users may use these programs at the command line to select options other than the defaults.

The program tfile.exe is used to create or resize the file itself in place. the usage is
>tfile c:\path\to\file sizeMB
sizeMB will be the total size of the file in Mb
>tfile
with no arguments will give you the usage.

This tool may also be used to resize the swap.img file. The best way to do that is to delete swap.img from within windows and use the create new option to make a new swap.img file. Set the size to the full size that you want swap to be. Then boot into Linux and as root type 
for Topologilinux
mkswap /dev/loop6 
swapon -a 
You can then use your system normally.

for coLinux
mkswap /dev/cobdX
swapon -a
cobdX is should be the device you selected to be swap in you .xml configuration file. 


You will also be able to use the create new option to create other "partitions" like a home.img . Or a new empty root filesystem. You will have the choice of formating it ext2 or ext3 or not to format so that you can format it after booting to linux. There is also a choice for formating the file to be a swap device but I have not yet been able to port mkswap to windows.

This program is written in TCL/TK and wrapped as a starpack. The source is included but you must unwrap it. See www.equi4.com/tclkit.html for more info on starkits starpacks and tclkit. The document "Beyond Tclkit" by Steve Landers is a good intro.


This program is opensource and may be redistributed under the GPL with exceptions for any of the terms of tclkit starkits starpacks and tcl/tk itself of which I do not think there are any conflicts.

Please report any bugs experiences suggestion to the Topologi-Linux forums on sourceforge.
or chris@topologilinux.com

enjoy,
chris  
