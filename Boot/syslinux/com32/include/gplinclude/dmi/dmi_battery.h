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

#ifndef DMI_BATTERY_H
#define DMI_BATTERY_H

#include <stdbool.h>
#include <inttypes.h>

#define BATTERY_LOCATION_SIZE		65
#define BATTERY_MANUFACTURER_SIZE	65
#define BATTERY_MANUFACTURE_DATE_SIZE	65
#define BATTERY_SERIAL_SIZE		65
#define BATTERY_DEVICE_NAME_SIZE	65
#define BATTERY_CHEMISTRY_SIZE		32
#define BATTERY_CAPACITY_SIZE		16
#define BATTERY_DESIGN_VOLTAGE_SIZE	16
#define BATTERY_SBDS_SIZE		255
#define BATTERY_MAXIMUM_ERROR_SIZE	32
#define BATTERY_SBDS_SERIAL_SIZE	32
#define BATTERY_SBDS_MANUFACTURE_DATE_SIZE	255
#define BATTERY_SBDS_CHEMISTRY_SIZE	65
#define BATTERY_OEM_INFO_SIZE		255

typedef struct {
    char location[BATTERY_LOCATION_SIZE];
    char manufacturer[BATTERY_MANUFACTURER_SIZE];
    char manufacture_date[BATTERY_MANUFACTURE_DATE_SIZE];
    char serial[BATTERY_SERIAL_SIZE];
    char name[BATTERY_DEVICE_NAME_SIZE];
    char chemistry[BATTERY_CHEMISTRY_SIZE];
    char design_capacity[BATTERY_CAPACITY_SIZE];
    char design_voltage[BATTERY_DESIGN_VOLTAGE_SIZE];
    char sbds[BATTERY_SBDS_SIZE];
    char sbds_serial[BATTERY_SBDS_SERIAL_SIZE];
    char maximum_error[BATTERY_MAXIMUM_ERROR_SIZE];
    char sbds_manufacture_date[BATTERY_SBDS_MANUFACTURE_DATE_SIZE];
    char sbds_chemistry[BATTERY_SBDS_CHEMISTRY_SIZE];
    char oem_info[BATTERY_OEM_INFO_SIZE];
/* The filled field have to be set to true when the dmitable implement that item */
    bool filled;
} s_battery;

const char *dmi_battery_chemistry(uint8_t code);
void dmi_battery_capacity(uint16_t code, uint8_t multiplier, char *capacity);
void dmi_battery_voltage(uint16_t code, char *voltage);
void dmi_battery_maximum_error(uint8_t code, char *error);
#endif
