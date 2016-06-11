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

#ifndef RSDP_H
#define RSDP_H
#include <inttypes.h>
#include <stdbool.h>

#define RSDP_MIN_ADDRESS 0x0E0000
#define RSDP_MAX_ADDRESS 0x0FFFFF

#define RSDP "RSD PTR"

enum { RSDP_TABLE_FOUND = 1 };

typedef struct {
    uint8_t *address;
    uint8_t signature[8 + 1];
    uint8_t checksum;
    uint8_t oem_id[6 + 1];
    uint8_t revision;
    uint8_t *rsdt_address;
    uint32_t length;
    uint8_t *xsdt_address;
    uint8_t extended_checksum;
    bool valid;
} s_rsdp;

#endif
