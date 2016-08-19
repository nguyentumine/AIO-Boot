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
 * syslinux/adv.h
 */

#ifndef _SYSLINUX_ADV_H
#define _SYSLINUX_ADV_H

#include <klibc/extern.h>
#include <stddef.h>
#include <syslinux/advconst.h>

__extern void *__syslinux_adv_ptr;
__extern size_t __syslinux_adv_size;

static inline void *syslinux_adv_ptr(void)
{
    return __syslinux_adv_ptr;
}

static inline size_t syslinux_adv_size(void)
{
    return __syslinux_adv_size;
}

__extern int syslinux_adv_write(void);

__extern int syslinux_setadv(int, size_t, const void *);
__extern const void *syslinux_getadv(int, size_t *);

#endif /* _SYSLINUX_ADV_H */
