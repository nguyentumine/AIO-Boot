/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2006 Erwan Velu - All Rights Reserved
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,
 *   Boston MA 02111-1307, USA; either version 2 of the License, or
 *   (at your option) any later version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

#ifndef VPD_H
#define VPD_H
#include <inttypes.h>
#include <stdbool.h>

enum { VPD_TABLE_PRESENT = 100, ENOVPDTABLE };

typedef struct {
    char bios_build_id[10];
    char box_serial_number[8];
    char motherboard_serial_number[12];
    char machine_type_model[8];
    char bios_release_date[9];
    char default_flash_filename[13];
    char bios_version[255];
    char base_address[16];
    bool filled;
} s_vpd;

int vpd_decode(s_vpd * vpd);
#endif
