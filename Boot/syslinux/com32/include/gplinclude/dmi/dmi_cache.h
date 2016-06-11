/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer - All Rights Reserved
 *
 *   Some part borrowed from DMI Decode:
 *
 *   (C) 2000-2002 Alan Cox <alan@redhat.com>
 *   (C) 2002-2007 Jean Delvare <khali@linux-fr.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,
 *   Boston MA 02111-1307, USA; either version 2 of the License, or
 *   (at your option) any later version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

#ifndef DMI_CACHE_H
#define DMI_CACHE_H

#include <stdint.h>

#include "stdbool.h"

#define CACHE_SOCKET_DESIGNATION_SIZE  65

typedef struct {
    char socket_designation[CACHE_SOCKET_DESIGNATION_SIZE];
    char configuration[32];
    char mode[32];
    char location[8];
    uint16_t installed_size;
    uint16_t max_size;
    char supported_sram_types[32];
    char installed_sram_types[32];
    uint16_t speed;
    char error_correction_type[32];
    char system_type[16];
    char associativity[32];
} __attribute__ ((__packed__)) s_cache;

const char *dmi_cache_mode(uint8_t code);
const char *dmi_cache_location(uint8_t code);
uint16_t dmi_cache_size(uint16_t code);
void dmi_cache_types(uint16_t code, const char *sep, char *array);
const char *dmi_cache_ec_type(uint8_t code);
const char *dmi_cache_type(uint8_t code);
const char *dmi_cache_associativity(uint8_t code);
#endif /* DMI_CACHE_H */
