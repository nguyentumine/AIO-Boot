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

#ifndef DMI_CHASSIS_H
#define DMI_CHASSIS_H

#define CHASSIS_MANUFACTURER_SIZE	65
#define CHASSIS_TYPE_SIZE		16
#define CHASSIS_LOCK_SIZE		16
#define CHASSIS_VERSION_SIZE		65
#define CHASSIS_SERIAL_SIZE		65
#define CHASSIS_ASSET_TAG_SIZE		65
#define CHASSIS_BOOT_UP_STATE_SIZE	32
#define CHASSIS_POWER_SUPPLY_STATE_SIZE		32
#define CHASSIS_THERMAL_STATE_SIZE	32
#define CHASSIS_SECURITY_STATUS_SIZE	32
#define CHASSIS_OEM_INFORMATION_SIZE	32

typedef struct {
    char manufacturer[CHASSIS_MANUFACTURER_SIZE];
    char type[CHASSIS_TYPE_SIZE];
    char lock[CHASSIS_LOCK_SIZE];
    char version[CHASSIS_VERSION_SIZE];
    char serial[CHASSIS_SERIAL_SIZE];
    char asset_tag[CHASSIS_ASSET_TAG_SIZE];
    char boot_up_state[CHASSIS_BOOT_UP_STATE_SIZE];
    char power_supply_state[CHASSIS_POWER_SUPPLY_STATE_SIZE];
    char thermal_state[CHASSIS_THERMAL_STATE_SIZE];
    char security_status[CHASSIS_SECURITY_STATUS_SIZE];
    char oem_information[CHASSIS_OEM_INFORMATION_SIZE];
    uint16_t height;
    uint16_t nb_power_cords;
/* The filled field have to be set to true when the dmitable implement that item */
    bool filled;
} s_chassis;

const char *dmi_chassis_type(uint8_t code);
const char *dmi_chassis_lock(uint8_t code);
const char *dmi_chassis_state(uint8_t code);
const char *dmi_chassis_security_status(uint8_t code);
#endif
