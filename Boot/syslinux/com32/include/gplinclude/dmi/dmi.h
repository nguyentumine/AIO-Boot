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

#ifndef DMI_H
#define DMI_H
#include <inttypes.h>
#define MAX_DMI_MEMORY_ITEMS 32
#define MAX_DMI_CACHE_ITEMS 32
#define OEM_STRINGS_SIZE 512
#define HARDWARE_SECURITY_SIZE 16

#define PAGE_SIZE 4096

extern const char *out_of_spec;
extern const char *bad_index;

#define WORD(x) (uint16_t)(*(const uint16_t *)(x))
#define DWORD(x) (uint32_t)(*(const uint32_t *)(x))
#define QWORD(x) (*(const uint64_t *)(x))

enum { DMI_TABLE_PRESENT = 100, ENODMITABLE };

#include "dmi_bios.h"
#include "dmi_system.h"
#include "dmi_base_board.h"
#include "dmi_chassis.h"
#include "dmi_processor.h"
#include "dmi_memory.h"
#include "dmi_battery.h"
#include "dmi_ipmi.h"
#include "dmi_cache.h"

extern char display_line;
#define moreprintf(...) do { display_line++; if (display_line == 24) { char tempbuf[10]; display_line=0; printf("Press enter to continue"); fgets(tempbuf, sizeof tempbuf, stdin);}  printf ( __VA_ARGS__); } while (0);

typedef struct {
    uint16_t num;
    uint16_t len;
    uint16_t ver;
    uint32_t base;
    uint16_t major_version;
    uint16_t minor_version;
} dmi_table;

struct dmi_header {
    uint8_t type;
    uint8_t length;
    uint16_t handle;
    uint8_t *data;
};

typedef struct {
    s_bios bios;
    s_system system;
    s_base_board base_board;
    s_chassis chassis;
    s_processor processor;
    s_battery battery;
    s_memory_module memory_module[MAX_DMI_MEMORY_ITEMS];
    s_memory memory[MAX_DMI_MEMORY_ITEMS];
    s_ipmi ipmi;
    s_cache cache[MAX_DMI_CACHE_ITEMS];
    int memory_module_count;
    int memory_count;
    int cache_count;
    dmi_table dmitable;
    char oem_strings[OEM_STRINGS_SIZE];
    struct {
	char power_on_passwd_status[HARDWARE_SECURITY_SIZE];
	char keyboard_passwd_status[HARDWARE_SECURITY_SIZE];
	char administrator_passwd_status[HARDWARE_SECURITY_SIZE];
	char front_panel_reset_status[HARDWARE_SECURITY_SIZE];
	bool filled;
    } hardware_security;
} s_dmi;

void to_dmi_header(struct dmi_header *h, uint8_t * data);
void dmi_bios_runtime_size(uint32_t code, s_dmi * dmi);
const char *dmi_string(struct dmi_header *dm, uint8_t s);
int dmi_checksum(uint8_t * buf, int len);
void parse_dmitable(s_dmi * dmi);
void dmi_decode(struct dmi_header *h, uint16_t ver, s_dmi * dmi);
int dmi_iterate(s_dmi * dmi);

/* dmi_utils.c */
void display_bios_characteristics(s_dmi * dmi);
void display_base_board_features(s_dmi * dmi);
void display_processor_flags(s_dmi * dmi);
#endif
