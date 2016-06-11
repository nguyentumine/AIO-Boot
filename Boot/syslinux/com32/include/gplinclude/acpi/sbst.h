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

#ifndef SBST_H
#define SBST_H
#include <inttypes.h>
#include <stdbool.h>

#define SBST "SBST"

typedef struct {
    uint64_t *address;
    s_acpi_description_header header;
    bool valid;
    uint32_t warning_energy_level;
    uint32_t low_energy_level;
    uint32_t critical_energy_level;
} s_sbst;

void parse_sbst(s_sbst * sbst);
#endif
