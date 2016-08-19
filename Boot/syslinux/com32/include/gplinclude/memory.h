/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   Some parts borrowed from meminfo.c32:
 *
 *   Copyright 2003-2009 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author: H. Peter Anvin
 *
 *   Some parts borrowed from Linux:
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef _MEMORY_H_
#define _MEMORY_H_
#include <stdint.h>

#define E820MAX 128
#define E820_RAM        1
#define E820_RESERVED   2
#define E820_ACPI       3	/* usable as RAM once ACPI tables have been read */
#define E820_NVS        4

#define RES_START       0xa0000
#define RES_END         0x100000

struct e820entry {
    uint64_t addr;		/* start of memory segment */
    uint64_t size;		/* size of memory segment */
    uint64_t type;		/* type of memory segment */
} __attribute__ ((packed));

const char *const e820_types[5];

void get_type(int, char *, int);
void detect_memory_e820(struct e820entry *desc, int size_map, int *size_found);
int detect_memory_e801(int *, int *);
int detect_memory_88(int *);

/* The following stuff could be merge once the addr_t will be set to 64bits.
 * syslinux_scan_memory can be used for that purpose */
unsigned long memsize_e820(struct e820entry *e820, int e820_nr);
int sanitize_e820_map(struct e820entry *orig_map, struct e820entry *new_bios,
		      short old_nr);
unsigned long detect_memsize(void);
#endif
