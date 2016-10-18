
                                  INTRODUCTION

wimlib is free and open source software that is available on both UNIX-like
systems and Windows.  This file provides additional information specifically
about the Windows version of wimlib and the command line tool "wimlib-imagex"
that is distributed with it.  It does not obsolete the generic README.txt, which
you should read too.

                              WINDOWS DISTRIBUTION

The Windows distribution of wimlib is a ZIP file containing the following items:

  * wimlib-imagex.exe, a command-line tool to deal with WIM (.wim), split WIM
    (.swm), and ESD (.esd) files that is inspired by Microsoft's ImageX and
    DISM.  This is a ready-to-run executable and not an installer.

  * Very short batch scripts (e.g. wimapply.cmd) which are shortcuts to the
    corresponding wimlib-imagex commands (e.g. `wimlib-imagex apply').

  * The documentation, including this file, the generic README.txt, and
    PDF documentation for wimlib-imagex in the 'doc' directory.

  * The library itself (libwim-15.dll).  The C header wimlib.h is not
    included; download the source if you want it.

  * License files for all software included.  These are all free software
    licenses.  COPYING.txt is the main license, and it refers to
    COPYING.GPLv3.txt and COPYING.LGPLv3.txt.  The other licenses are for
    third-party software included in the library.

Note that there are separate ZIP files for 32-bit (i686) and 64-bit (x86_64)
binaries.  They are both fully supported, but you should prefer the 64-bit
binaries when possible as they can be noticeably faster.

                                 WIMLIB-IMAGEX

wimlib-imagex supports most features of Microsoft's ImageX as well as some
features that are supported by DISM but not by ImageX.  wimlib-imagex also
supports some features that neither ImageX nor DISM support.  Some of the
advantages of wimlib-imagex compared to ImageX and DISM are:

  * wimlib-imagex provides "extract" and "update" commands which allow
    you to quickly work with WIM images without mounting them.

  * wimlib-imagex provides an easy-to-use "optimize" command which removes
    wasted space from a WIM file and optionally recompresses it with stronger
    compression.

  * wimlib includes advanced implementations of all compression algorithms used
    in WIM files.  They usually outperform and outcompress their Microsoft
    equivalents.

  * wimlib-imagex supports solid WIM files and LZMS compression, for example as
    used in ESD (.esd) files.  (These are partially supported by recent DISM
    versions but not by ImageX.)

  * wimlib-imagex supports imaging a live Windows system.  Just use the
    --snapshot option.

  * In many cases, wimlib-imagex has simpler command-line syntax than either
    ImageX or DISM.

  * Whenever possible, wimlib-imagex includes improved documentation and
    informational output compared to Microsoft's software.

  * wimlib and wimlib-imagex are free software, so you can modify and/or audit
    the source code.

However, some limitations of wimlib-imagex compared to ImageX and DISM are:

  * On Windows, wimlib-imagex does not support mounting WIM images.

  * wimlib-imagex has no awareness of Windows "packages".

                                ADDITIONAL NOTES

It's recommended to use wimlib-imagex in scripts to avoid having to
interactively enter commands.  However, note that wimlib-imagex is largely just
a command-line front-end for wimlib, and it's possible to use wimlib's API in
other front-ends or applications.  Currently there is no official graphical user
interface available for wimlib or wimlib-imagex.  However, an unofficial, beta,
Windows-only graphical user interface that provides a thin wrapper around
wimlib-imagex can be downloaded at
http://reboot.pro/files/file/485-wimlib-imagex-command-line-compiler/.

                              BUILDING FROM SOURCE

As with other open source software, advanced users may choose to build wimlib
from source, potentially with customizations.  Although wimlib's build system is
designed for UNIX-like systems and is easiest to use on Linux, it's possible to
build Windows binaries on Windows using Cygwin with MinGW.  To do this, follow
the instructions below.  For the sake of example, I'll assume you are building a
64-bit version of wimlib v1.10.0.

Run the Cygwin installer, available from https://www.cygwin.com/setup-x86.exe.
When you get to the package selection screen, choose the following additional
packages from category "Devel":

    - make
    - mingw64-x86_64-binutils
    - mingw64-x86_64-gcc-g++
    - mingw64-x86_64-libxml2
    - mingw64-x86_64-pkg-config
    - mingw64-x86_64-winpthreads

Download wimlib's source code from https://wimlib.net/downloads/wimlib-1.10.0.tar.gz.

Start a Cygwin terminal and run the following commands:

    cd /cygdrive/c/Users/example/Downloads # (or wherever you downloaded the source to)
    tar xf wimlib-1.10.0.tar.gz
    cd wimlib-1.10.0
    ./configure --host=x86_64-w64-mingw32
    make

If successful, the new binaries "libwim-15.dll" and "wimlib-imagex.exe" will
have been produced in the .libs directory.

By default the binaries are built with debug symbols.  If desired, you can use
x86_64-w64-mingw32-strip to strip them.

libwim-15.dll will be linked to several other DLLs which you will need as well:

    - libwinpthread-1.dll
    - libxml2-2.dll, which also requires:
        - iconv.dll
        - liblzma-5.dll
        - zlib1.dll

These DLLs can be found in "C:\cygwin\usr\x86_64-w64-mingw32\sys-root\mingw\bin"
and must be placed alongside libwim-15.dll for it to run portably.  (In the
official binary release, these third-party libraries are linked to libwim-15.dll
statically rather than dynamically --- or are unnecessary, in the case of
libxml2's dependencies.)

Building 32-bit binaries is very similar, but you'll need to replace "x86_64"
with "i686" everywhere in the above instructions, and libwim-15.dll will also
depend on libgcc_s_sjlj-1.dll.  Note that you can build both 32-bit and 64-bit
binaries from the same Cygwin installation, provided that you install both the
mingw64-i686-* and mingw64-x86_64-* packages; and you can run the Cygwin setup
program to install more packages at any time.
