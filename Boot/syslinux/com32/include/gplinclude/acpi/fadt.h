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

#ifndef FADT_H
#define FADT_H
#include <inttypes.h>
#include <stdbool.h>

enum { FADT_TABLE_FOUND = 1};

#define FACP "FACP"
#define FADT "FADT"

/* prefered pm profiles */
enum { PM_UNSPECIFIED = 0,
    PM_DESKTOP = 1,
    PM_MOBILE = 2,
    PM_WORKSTATION = 3,
    PM_ENTERPRISE_SERVER = 4,
    PM_SOHO_SERVER = 5,
    PM_APPLIANCE_PC = 6,
    PM_PERFORMANCE_SERVER = 7
};

/* iapc_boot_arch flags*/
#define IAPC_LEGAGY_DEVICE 1
#define IAPC_8042 1<<1
#define IAPC_VGA_NOT_PRESENT 1<<2
#define IAPC_MSI_NOT_SUPPORTED 1<<3
#define IAPC_PCIE_ASPM_CONTROLS 1<<4

/* feature flags for "flags" */
#define WBINVD 1
#define WBINVD_FLUSH 1<<1
#define PROC_C1 1<<2
#define P_LVL2_UP 1<<3
#define PWR_BUTTON 1<<4
#define SLP_BUTTON 1<<5
#define FIX_RTC 1<<6
#define RTC_S4 1<<7
#define TMR_VAL_EXT 1<<8
#define DCK_CAP 1<<9
#define RESET_REG_SUP 1<<10
#define SEALED_CASE 1<<11
#define HEADLESS 1<<12
#define CPU_SW_SLP 1<<13
#define PCI_EXP_WAK 1<<14
#define USE_PLATEFORM_CLOCK 1<<15
#define S4_RTC_STS_VALID 1<<16
#define REMOTE_POWER_ON_CAPABLE 1<<17
#define FORCE_APIC_CLUSTER_MODEL 1<<18
#define FORCE_APIC_PHYSICAL_DESTINATION_MODE 1<<19

typedef struct {
    uint64_t *address;
    s_acpi_description_header header;
    bool valid;
    uint32_t *firmware_ctrl;
    uint32_t *dsdt_address;
    uint8_t reserved;
    uint8_t prefered_pm_profile;
    uint16_t sci_int;
    uint32_t smi_cmd;
    uint8_t acpi_enable;
    uint8_t acpi_disable;
    uint8_t s4bios_req;
    uint8_t pstate_cnt;
    uint32_t pm1a_evt_blk;
    uint32_t pm1b_evt_blk;
    uint32_t pm1a_cnt_blk;
    uint32_t pm1b_cnt_blk;
    uint32_t pm2_cnt_blk;
    uint32_t pm_tmr_blk;
    uint32_t gpe0_blk;
    uint32_t gpe1_blk;
    uint8_t pm1_evt_len;
    uint8_t pm1_cnt_len;
    uint8_t pm2_cnt_len;
    uint8_t pm_tmr_len;
    uint8_t gpe0_blk_len;
    uint8_t gpe1_blk_len;
    uint8_t gpe1_base;
    uint8_t cst_cnt;
    uint16_t p_lvl2_lat;
    uint16_t p_lvl3_lat;
    uint16_t flush_size;
    uint16_t flush_stride;
    uint8_t duty_offset;
    uint8_t duty_width;
    uint8_t day_alarm;
    uint8_t mon_alarm;
    uint8_t century;
    uint16_t iapc_boot_arch;
    uint8_t reserved_2;
    uint32_t flags;
    s_gas reset_reg;
    uint8_t reset_value;
    uint8_t reserved_3[3];
    uint64_t *x_firmware_ctrl;
    uint64_t *x_dsdt;
    s_gas x_pm1a_evt_blk;
    s_gas x_pm1b_evt_blk;
    s_gas x_pm1a_cnt_blk;
    s_gas x_pm1b_cnt_blk;
    s_gas x_pm2_cnt_blk;
    s_gas x_pm_tmr_blk;
    s_gas x_gpe0_blk;
    s_gas x_gpe1_blk;
} s_fadt;

void parse_fadt(s_fadt * fadt);
#endif
