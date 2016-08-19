/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2007-2008 H. Peter Anvin - All Rights Reserved
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
 * syslinux/bootpm.h
 *
 * Data structures for shuffle and boot to protected mode
 */

#ifndef _SYSLINUX_BOOTPM_H
#define _SYSLINUX_BOOTPM_H

#include <stdint.h>
#include <syslinux/movebits.h>

struct syslinux_pm_regs {
    uint32_t eax;		/* Offset  0 */
    uint32_t ecx;		/* Offset  4 */
    uint32_t edx;		/* Offset  8 */
    uint32_t ebx;		/* Offset 12 */
    uint32_t esp;		/* Offset 16 */
    uint32_t ebp;		/* Offset 20 */
    uint32_t esi;		/* Offset 24 */
    uint32_t edi;		/* Offset 28 */

    uint32_t eip;		/* Offset 32 */
};

int syslinux_shuffle_boot_pm(struct syslinux_movelist *fraglist,
			     struct syslinux_memmap *memmap,
			     uint16_t bootflags, struct syslinux_pm_regs *regs);

#endif /* _SYSLINUX_BOOTPM_H */
