/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2007-2009 H. Peter Anvin - All Rights Reserved
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

#ifndef _SYSLINUX_MEMSCAN_H
#define _SYSLINUX_MEMSCAN_H

#include <linux/list.h>
#include <syslinux/movebits.h>	/* addr_t */

typedef int (*scan_memory_callback_t) (void *, addr_t, addr_t,
				       enum syslinux_memmap_types type);

struct syslinux_memscan {
    int (*func)(scan_memory_callback_t callback, void *data);
    struct list_head next;
};

void syslinux_memscan_add(struct syslinux_memscan *entry);
int syslinux_memscan_new(int (*func)(scan_memory_callback_t cb, void *data));
int syslinux_scan_memory(scan_memory_callback_t callback, void *data);

#endif /* _SYSLINUX_MEMSCAN_H */
