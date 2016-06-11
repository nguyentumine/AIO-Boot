/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Erwan Velu - All Rights Reserved
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,
 *   Boston MA 02111-1307, USA; either version 2 of the License, or
 *   (at your option) any later version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

#ifndef FACS_H
#define FACS_H
#include <inttypes.h>
#include <stdbool.h>

#define FACS "FACS"

/* Features Flags for "flags" */
#define S4BIOS_F 1

/* Features flags for global_lock */
#define PENDING 1
#define OWNED 1<<1

typedef struct {
    uint64_t *address;
    uint8_t signature[4+1];
    uint8_t length;
    uint32_t hardware_signature;
    uint32_t firmware_waking_vector;
    uint32_t global_lock;
    uint32_t flags;
    uint64_t x_firmware_waking_vector;
    uint8_t version;
    bool valid;
} s_facs;

void parse_facs(s_facs *facs);
#endif
