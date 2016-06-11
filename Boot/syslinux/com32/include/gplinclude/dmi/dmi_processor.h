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

#ifndef DMI_PROCESSOR_H
#define DMI_PROCESSOR_H

#include "stdbool.h"
#include "string.h"
#define PROCESSOR_SOCKET_DESIGNATION_SIZE		65
#define PROCESSOR_TYPE_SIZE		32
#define PROCESSOR_FAMILY_SIZE		32
#define PROCESSOR_MANUFACTURER_SIZE     65
#define PROCESSOR_VERSION_SIZE		65	
#define PROCESSOR_VOLTAGE_SIZE		16
#define PROCESSOR_STATUS_SIZE		16
#define PROCESSOR_UPGRADE_SIZE		16
#define PROCESSOR_CACHE_SIZE		16
#define PROCESSOR_SERIAL_SIZE		65
#define PROCESSOR_ASSET_TAG_SIZE	65
#define PROCESSOR_PART_NUMBER_SIZE	65
#define PROCESSOR_ID_SIZE		32

#define PROCESSOR_FLAGS_ELEMENTS	32
/* Intel AP-485 revision 28, table 5 */
extern const char *cpu_flags_strings[PROCESSOR_FLAGS_ELEMENTS];

/* this struct have PROCESSOR_FLAGS_ELEMENTS */
/* each bool is associated to the relevant message above */
typedef struct {
    bool fpu;
    bool vme;
    bool de;
    bool pse;
    bool tsc;
    bool msr;
    bool pae;
    bool mce;
    bool cx8;
    bool apic;
    bool null_10;
    bool sep;
    bool mtrr;
    bool pge;
    bool mca;
    bool cmov;
    bool pat;
    bool pse_36;
    bool psn;
    bool clfsh;
    bool null_20;
    bool ds;
    bool acpi;
    bool mmx;
    bool fxsr;
    bool sse;
    bool sse2;
    bool ss;
    bool htt;
    bool tm;
    bool null_30;
    bool pbe;
} __attribute__ ((__packed__)) s_dmi_cpu_flags;

typedef struct {
    uint8_t type;
    uint8_t family;
    uint8_t model;
    uint8_t stepping;
    uint8_t minor_stepping;
} __attribute__ ((__packed__)) s_signature;

typedef struct {
    char socket_designation[PROCESSOR_SOCKET_DESIGNATION_SIZE];
    char type[PROCESSOR_TYPE_SIZE];
    char family[PROCESSOR_FAMILY_SIZE];
    char manufacturer[PROCESSOR_MANUFACTURER_SIZE];
    char version[PROCESSOR_VERSION_SIZE];
    uint16_t voltage_mv;
    uint16_t external_clock;
    uint16_t max_speed;
    uint16_t current_speed;
    char status[PROCESSOR_STATUS_SIZE];
    char upgrade[PROCESSOR_UPGRADE_SIZE];
    char cache1[PROCESSOR_CACHE_SIZE];
    char cache2[PROCESSOR_CACHE_SIZE];
    char cache3[PROCESSOR_CACHE_SIZE];
    char serial[PROCESSOR_SERIAL_SIZE];
    char asset_tag[PROCESSOR_ASSET_TAG_SIZE];
    char part_number[PROCESSOR_PART_NUMBER_SIZE];
    char id[PROCESSOR_ID_SIZE];
    uint16_t core_count;
    uint16_t core_enabled;
    uint16_t thread_count;
    s_dmi_cpu_flags cpu_flags;
    s_signature signature;
/* The filled field have to be set to true when the dmitable implement that item */
    bool filled;
} s_processor;

const char *dmi_processor_type(uint8_t code);
const char *dmi_processor_family(uint8_t code, char *manufacturer);
const char *dmi_processor_status(uint8_t code);
const char *dmi_processor_upgrade(uint8_t code);
void dmi_processor_cache(uint16_t code, const char *level, uint16_t ver,
			 char *cache);
#endif
