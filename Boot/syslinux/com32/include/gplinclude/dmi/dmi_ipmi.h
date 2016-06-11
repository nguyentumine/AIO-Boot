/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2006-2009 Erwan Velu - All Rights Reserved
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,
 *   Boston MA 02111-1307, USA; either version 2 of the License, or
 *   (at your option) any later version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

#ifndef DMI_IPMI_H
#define DMI_IPMI_H

#define IPMI_INTERFACE_TYPE_SIZE	32
#define IPMI_MEMORY_MODEL_SIZE		16

typedef struct {
    char interface_type[IPMI_INTERFACE_TYPE_SIZE];
    uint8_t major_specification_version;
    uint8_t minor_specification_version;
    uint8_t I2C_slave_address;
    uint16_t nv_address;
    uint64_t base_address;

    uint8_t irq;
    bool filled;
} s_ipmi;

void dmi_ipmi_base_address(uint8_t type, const uint8_t * p, s_ipmi * ipmi);
const char *dmi_ipmi_interface_type(uint8_t code);
#endif
