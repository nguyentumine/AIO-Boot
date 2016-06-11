/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2011 Intel Corporation; author: H. Peter Anvin
 *
 *   Permission is hereby granted, free of charge, to any person
 *   obtaining a copy of this software and associated documentation
 *   files (the "Software"), to deal in the Software without
 *   restriction, including without limitation the rights to use,
 *   copy, modify, merge, publish, distribute, sublicense, and/or
 *   sell copies of the Software, and to permit persons to whom
 *   the Software is furnished to do so, subject to the following
 *   conditions:
 *
 *   The above copyright notice and this permission notice shall
 *   be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 *
 * ----------------------------------------------------------------------- */

/*
 * syslinux/sysappend.h
 *
 * List of the Syslinux sysappend strings
 */

#ifndef _SYSLINUX_SYSAPPEND_H
#define _SYSLINUX_SYSAPPEND_H

enum syslinux_sysappend {
    SYSAPPEND_IP,		/* PXELINUX: ip= address */
    SYSAPPEND_BOOTIF,		/* PXELINUX: BOOTIF= address */
    SYSAPPEND_SYSUUID,		/* System UUID from PXE or DMI */
    SYSAPPEND_CPU,		/* CPU features */
    SYSAPPEND_SYSVENDOR,	/* System or MB vendor from DMI */
    SYSAPPEND_SYSPRODUCT,	/* System or MB product from DMI */
    SYSAPPEND_SYSVERSION,	/* System or MB version from DMI */
    SYSAPPEND_SYSSERIAL,	/* System or MB serial from DMI */
    SYSAPPEND_SYSSKU,		/* System SKU from DMI */
    SYSAPPEND_SYSFAMILY,	/* System family from DMI */
    SYSAPPEND_MBVENDOR,		/* System or MB vendor from DMI */
    SYSAPPEND_MBPRODUCT,	/* System or MB product from DMI */
    SYSAPPEND_MBVERSION,	/* System or MB version from DMI */
    SYSAPPEND_MBSERIAL,		/* System or MB serial from DMI */
    SYSAPPEND_MBASSET,		/* MB asset tag from DMI */
    SYSAPPEND_BIOSVENDOR,	/* BIOS vendor */
    SYSAPPEND_BIOSVERSION,	/* BIOS version string */
    SYSAPPEND_SYSFF,		/* System form factor */
    SYSAPPEND_FSUUID,		/* Boot filesystem UUID */
    SYSAPPEND_MAX		/* Total number of strings */
};

#endif
