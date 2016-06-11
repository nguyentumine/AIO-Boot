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

#ifndef DMI_SYSTEM_H
#define DMI_SYSTEM_H

#define SYSTEM_MANUFACTURER_SIZE	65
#define SYSTEM_PRODUCT_NAME_SIZE	65
#define SYSTEM_VERSION_SIZE		65
#define SYSTEM_SERIAL_SIZE		65
#define SYSTEM_UUID_SIZE		40
#define SYSTEM_WAKEUP_TYPE_SIZE		32
#define SYSTEM_SKU_NUMBER_SIZE		65
#define SYSTEM_FAMILY_SIZE		65

#define SYSTEM_BOOT_STATUS_SIZE		50
#define SYSTEM_CONFIGURATION_OPTIONS_SIZE	50

typedef struct {
    char manufacturer[SYSTEM_MANUFACTURER_SIZE];
    char product_name[SYSTEM_PRODUCT_NAME_SIZE];
    char version[SYSTEM_VERSION_SIZE];
    char serial[SYSTEM_SERIAL_SIZE];
    char uuid[SYSTEM_UUID_SIZE];
    char wakeup_type[SYSTEM_WAKEUP_TYPE_SIZE];
    char sku_number[SYSTEM_SKU_NUMBER_SIZE];
    char family[SYSTEM_FAMILY_SIZE];
/* The filled field have to be set to true when the dmitable implement that item */
    bool filled;
    char system_boot_status[SYSTEM_BOOT_STATUS_SIZE];
    char configuration_options[SYSTEM_CONFIGURATION_OPTIONS_SIZE];
    struct {
	bool filled;
	uint8_t status;
	uint8_t watchdog;
	char boot_option[17];
	char boot_option_on_limit[17];
	char reset_count[8];
	char reset_limit[8];
	char timer_interval[8];
	char timeout[8];
    } system_reset;
} s_system;
#endif
