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

#ifndef MADT_H
#define MADT_H
#include <inttypes.h>
#include <stdbool.h>

#define MADT "MADT"
#define APIC "APIC"

enum {
    PROCESSOR_LOCAL_APIC = 0,
    IO_APIC = 1,
    INTERRUPT_SOURCE_OVERRIDE = 2,
    NMI = 3,
    LOCAL_APIC_NMI_STRUCTURE = 4,
    LOCAL_APIC_ADDRESS_OVERRIDE_STRUCTURE = 5,
    IO_SAPIC = 6,
    LOCAL_SAPIC = 7,
    PLATEFORM_INTERRUPT_SOURCES = 8
};

/* Features flags for 
 * - processor_local_apic flags
 * - local sapic flags
 */
#define PROCESSOR_LOCAL_APIC_ENABLE 1

#define MAX_S_L_P 255
typedef struct {
    uint8_t type;
    uint8_t length;
    uint8_t acpi_id;
    uint8_t apic_id;
    uint32_t flags;
} __attribute__ ((packed)) s_processor_local_apic;

#define MAX_IO_APIC 255
typedef struct {
    uint8_t type;
    uint8_t length;
    uint8_t io_apic_id;
    uint8_t reserved;
    uint32_t io_apic_address;
    uint32_t global_system_interrupt_base;
} __attribute__ ((packed)) s_io_apic;

/* Features flags for
 * - interrupt_source_override
 * - nmi
 */
/* Bits 1&2 must be set to 0 */
#define POLARITY_CONFORM_MASK 0x0
#define POLARITY_ACTIVE_HIGH 0x1
#define POLARITY_RESERVED 0x2
#define POLARITY_ACTIVE_LOW 0x3
/* Bits 3&4 must be set to 0 */
#define TRIGGER_CONFORM_MASK 0x3
#define TRIGGER_EDGE 0x4
#define TRIGGER_RESERVED 0x8
#define TRIGGER_LEVEL 0xA

#define MAX_I_S_O 255
typedef struct {
    uint8_t type;
    uint8_t length;
    uint8_t bus;
    uint8_t source;
    uint32_t global_system_interrupt;
    uint16_t flags;
} __attribute__ ((packed)) s_interrupt_source_override;

typedef struct {
    uint8_t type;
    uint8_t length;
    uint8_t flags;
    uint32_t global_system_interrupt;
} __attribute__ ((packed)) s_nmi;

#define MAX_LOCAL_APIC_NMI 255
typedef struct {
    uint8_t type;
    uint8_t length;
    uint8_t acpi_processor_id;
    uint16_t flags;
    uint8_t local_apic_lint;
} __attribute__ ((packed)) s_local_apic_nmi;

#define MAX_L_A_A_O 255
typedef struct {
    uint8_t type;
    uint8_t length;
    uint16_t reserved;
    uint64_t local_apic_address;
} __attribute__ ((packed)) s_local_apic_address_override;

#define MAX_IO_SAPIC 255
typedef struct {
    uint8_t type;
    uint8_t length;
    uint8_t io_apic_id;
    uint8_t reserved;
    uint32_t global_system_interrupt_base;
    uint64_t io_sapic_address;
} __attribute__ ((packed)) s_io_sapic;

#define ACPI_PROCESSOR_UID_STRING_OFFSET 16
#define MAX_LOCAL_SAPIC 255
typedef struct {
    uint8_t type;
    uint8_t length;
    uint8_t acpi_processor_id;
    uint8_t local_sapic_id;
    uint8_t local_sapic_eid;
    uint8_t reserved[3];
    uint32_t flags;
    uint32_t acpi_processor_uid_value;
    char *acpi_processor_uid_string;
} __attribute__ ((packed)) s_local_sapic;

typedef struct {
    uint64_t *address;
    s_acpi_description_header header;
    uint32_t local_apic_address;
    uint32_t flags;
    s_processor_local_apic processor_local_apic[MAX_S_L_P];
    uint8_t processor_local_apic_count;
    s_io_apic io_apic[MAX_IO_APIC];
    uint8_t io_apic_count;
    s_interrupt_source_override interrupt_source_override[MAX_I_S_O];
    uint8_t interrupt_source_override_count;
    s_nmi nmi[MAX_I_S_O];
    uint8_t nmi_count;
    s_local_apic_nmi local_apic_nmi[MAX_LOCAL_APIC_NMI];
    uint8_t local_apic_nmi_count;
    s_local_apic_address_override local_apic_address_override[MAX_L_A_A_O];
    uint8_t local_apic_address_override_count;
    s_io_sapic io_sapic[MAX_IO_SAPIC];
    uint8_t io_sapic_count;
    s_local_sapic local_sapic[MAX_LOCAL_SAPIC];
    uint8_t local_sapic_count;
    bool valid;
} s_madt;

void print_madt(s_madt * madt);
#endif
