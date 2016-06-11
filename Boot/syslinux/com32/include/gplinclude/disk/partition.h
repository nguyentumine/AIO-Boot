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

#ifndef _PARTITION_H_
#define _PARTITION_H_

#include <stdint.h>

#define PARTITION_TABLES_OFFSET	0x1be

/* A DOS partition table entry */
struct part_entry {
    uint8_t active_flag;	/* 0x80 if "active" */
    uint8_t start_head;
    uint8_t start_sect;
    uint8_t start_cyl;
    uint8_t ostype;
    uint8_t end_head;
    uint8_t end_sect;
    uint8_t end_cyl;
    uint32_t start_lba;
    uint32_t length;
} __attribute__ ((packed));

void get_label(int label, char **buffer_label);
#endif /* _PARTITION_H_ */
