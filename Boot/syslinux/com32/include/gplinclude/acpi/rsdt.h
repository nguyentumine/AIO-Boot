/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009-2011 Erwan Velu - All Rights Reserved
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,
 *   Boston MA 02111-1307, USA; either version 2 of the License, or
 *   (at your option) any later version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

#ifndef RSDT_H
#define RSDT_H
#include <inttypes.h>
#include <stdbool.h>

enum { RSDT_TABLE_FOUND = 1};

#define RSDT "RSDT"

typedef struct {
    uint8_t *address;
    s_acpi_description_header header;
    uint8_t *entry[255];
    uint8_t entry_count;
    bool valid;
} s_rsdt;

int parse_rsdt(s_rsdt * rsdt);
#endif
