/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   Some parts borrowed from chain.c32:
 *
 *   Copyright 2003-2009 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author: H. Peter Anvin
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>

/* For PAGE_SIZE */
#include <cpuid.h>

#define SECTOR 512		/* bytes/sector */

struct ebios_dapa {
    uint16_t len;
    uint16_t count;
    uint16_t off;
    uint16_t seg;
    uint64_t lba;
};

#endif /* _COMMON_H_ */
