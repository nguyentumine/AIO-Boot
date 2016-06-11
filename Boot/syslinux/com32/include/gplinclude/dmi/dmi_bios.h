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

#ifndef DMI_BIOS_H
#define DMI_BIOS_H

#include "stdbool.h"
#define BIOS_VENDOR_SIZE		65
#define BIOS_VERSION_SIZE		65
#define BIOS_RELEASE_SIZE		65
#define BIOS_RUNTIME_SIZE_UNIT_SIZE	16
#define BIOS_ROM_UNIT_SIZE		16
#define BIOS_BIOS_REVISION_SIZE		16
#define BIOS_FIRMWARE_REVISION_SIZE	16

#define BIOS_CHAR_NB_ELEMENTS		29
#define BIOS_CHAR_X1_NB_ELEMENTS	8
#define BIOS_CHAR_X2_NB_ELEMENTS	3

extern const char *bios_charac_strings[];

/* this struct has BIOS_CHAR_NB_ELEMENTS */
/* each bool is associated with the relevant message above */
typedef struct {
    bool bios_characteristics_not_supported;
    bool isa;
    bool mca;
    bool eisa;
    bool pci;
    bool pc_card;
    bool pnp;
    bool apm;
    bool bios_upgreadable;
    bool bios_shadowing;
    bool vlb;
    bool escd;
    bool boot_from_cd;
    bool selectable_boot;
    bool bios_rom_socketed;
    bool boot_from_pcmcia;
    bool edd;
    bool japanese_floppy_nec_9800_1_2MB;
    bool japanese_floppy_toshiba_1_2MB;
    bool floppy_5_25_360KB;
    bool floppy_5_25_1_2MB;
    bool floppy_3_5_720KB;
    bool floppy_3_5_2_88MB;
    bool print_screen;
    bool keyboard_8042_support;
    bool serial_support;
    bool printer_support;
    bool cga_mono_support;
    bool nec_pc_98;
} __attribute__ ((__packed__)) s_characteristics;

extern const char *bios_charac_x1_strings[];

/* this struct has BIOS_CHAR_X1_NB_ELEMENTS */
/* each bool is associated with the relevant message above */
typedef struct {
    bool acpi;
    bool usb_legacy;
    bool agp;
    bool i2o_boot;
    bool ls_120_boot;
    bool zip_drive_boot;
    bool ieee_1394_boot;
    bool smart_battery;
} __attribute__ ((__packed__)) s_characteristics_x1;

extern const char *bios_charac_x2_strings[];

/* this struct has BIOS_CHAR_X2_NB_ELEMENTS */
/* each bool is associated with the relevant message above */
typedef struct {
    bool bios_boot_specification;
    bool bios_network_boot_by_keypress;
    bool target_content_distribution;
} __attribute__ ((__packed__)) s_characteristics_x2;

typedef struct {
    char vendor[BIOS_VENDOR_SIZE];
    char version[BIOS_VERSION_SIZE];
    char release_date[BIOS_RELEASE_SIZE];
    uint16_t address;
    uint16_t runtime_size;
    char runtime_size_unit[BIOS_RUNTIME_SIZE_UNIT_SIZE];
    uint16_t rom_size;
    char rom_size_unit[BIOS_ROM_UNIT_SIZE];
    s_characteristics characteristics;
    s_characteristics_x1 characteristics_x1;
    s_characteristics_x2 characteristics_x2;
    char bios_revision[BIOS_BIOS_REVISION_SIZE];
    char firmware_revision[BIOS_FIRMWARE_REVISION_SIZE];
/* The filled field have to be set to true when the dmitable implement that item */
    bool filled;
} s_bios;

#endif
