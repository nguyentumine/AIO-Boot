/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2007-2008 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author: H. Peter Anvin
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
 * syslinux/bootrm.h
 *
 * Data structures for shuffle and boot to protected mode
 */

#ifndef _SYSLINUX_BOOTRM_H
#define _SYSLINUX_BOOTRM_H

#include <stdint.h>
#include <stdbool.h>
#include <com32.h>
#include <syslinux/movebits.h>

/* This register set is used by the shuffle and boot interface.  It is
   a completely different structure from what the __intcall() and
   __farcall() interfaces use! */
struct syslinux_rm_regs {
    uint16_t es;		/* Offset  0 */
    uint16_t _unused_cs;	/* Offset  2 */
    uint16_t ss;		/* Offset  4 */
    uint16_t ds;		/* Offset  6 */
    uint16_t fs;		/* Offset  8 */
    uint16_t gs;		/* Offset 10 */

    reg32_t eax;		/* Offset 12 */
    reg32_t ecx;		/* Offset 16 */
    reg32_t edx;		/* Offset 20 */
    reg32_t ebx;		/* Offset 24 */
    reg32_t esp;		/* Offset 28 */
    reg32_t ebp;		/* Offset 32 */
    reg32_t esi;		/* Offset 36 */
    reg32_t edi;		/* Offset 40 */

    uint16_t ip;		/* Offset 44 */
    uint16_t cs;		/* Offset 46 */

    bool sti;			/* Offset 48 */
};

int syslinux_shuffle_boot_rm(struct syslinux_movelist *fraglist,
			     struct syslinux_memmap *memmap,
			     uint16_t bootflags, struct syslinux_rm_regs *regs);

#endif /* _SYSLINUX_BOOTRM_H */
