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

#ifndef DSDT_H
#define DSDT_H
#include <inttypes.h>
#include <stdbool.h>

#define DSDT "DSDT"

typedef struct {
    uint64_t *address;
    s_acpi_description_header header;
    uint8_t *definition_block;
    bool valid;
} s_dsdt;

void parse_dsdt(s_dsdt *dsdt);
#endif
