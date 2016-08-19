/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   Some parts borrowed from chain.c32:
 *
 *   Copyright 2003-2009 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author: H. Peter Anvin
 *
 *   Some parts borrowed from Linux:
 *
 *   Copyright (C) 2002, 2003, 2004 Dell Inc.
 *   by Matt Domsch <Matt_Domsch@dell.com>
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef _GEOM_H_
#define _GEOM_H_

#include <stdint.h>

/**
 * INT 13 Extensions
 *
 * Note: if the size is less than 30 on call, the final DWORD will not be
 *       returned by a v2.x implementation; similarly for the Device Path info
 **/
struct edd_device_parameters {
    uint16_t len;		/* size of returned data */
	/**
	 * Bitfields for IBM/MS INT 13 Extensions information flags:
	 * Bit(s)    Description    (Table 00274)
	 * 0    DMA boundary errors handled transparently
	 * 1    cylinder/head/sectors-per-track information is valid
	 * 2    removable drive
	 * 3    write with verify supported
	 * 4    drive has change-line support (required if drive >= 80h is removable)
	 * 5    drive can be locked (required if drive >= 80h is removable)
	 * 6    CHS information set to maximum supported values, not current media
	 * 15-7    reserved (0)
	 **/
    uint16_t info;		/* information flags */
    uint32_t cylinders;		/* number of physical cylinders on drive */
    uint32_t heads;		/* number of physical heads on drive */
    uint32_t sectors_per_track;	/* number of physical sectors per track */
    uint64_t sectors;		/* total number of sectors on drive */
    uint16_t bytes_per_sector;	/* bytes per sector */
    /* --- v2.0+ --- */
    uint32_t dpte_pointer;	/* EDD configuration parameters, FFFFh:FFFFh if not available */
    /* --- v3.0 --- */
    uint16_t device_path_information;	/* signature BEDDh to indicate presence of Device Path info */
    uint8_t device_path_length;	/* length of Device Path information, including signature and this byte (24h for v3.0) */
    uint8_t device_path_reserved;	/* reserved (0) */
    uint16_t device_path_reserved_2;	/* reserved (0) */
    uint8_t host_bus_type[4];	/* ASCIZ name of host bus ("ISA" or "PCI") */
    uint8_t interface_type[8];	/* ASCIZ name of interface type
				 *         "ATA"
				 *         "ATAPI"
				 *         "SCSI"
				 *         "USB"
				 *         "1394" IEEE 1394 (FireWire)
				 *         "FIBRE" Fibre Channel
				 */
	/**
	 * Format of EDD v3.0 Interface Path:
	 * Offset    Size    Description    (Table 00275)
	 * ---ISA---
	 * 00h    WORD    16-bit base address
	 * 02h 6 BYTEs    reserved (0)
	 * ---PCI---
	 * 00h    BYTE    PCI bus number
	 * 01h    BYTE    PCI device number
	 * 02h    BYTE    PCI function number
	 * 03h 5 BYTEs    reserved (0)
	 **/
    union {
	struct {
	    uint16_t base_address;
	    uint16_t reserved1;
	    uint32_t reserved2;
	} __attribute__ ((packed)) isa;
	struct {
	    uint8_t bus;
	    uint8_t slot;
	    uint8_t function;
	    uint8_t channel;
	    uint32_t reserved;
	} __attribute__ ((packed)) pci;
	/* pcix is same as pci */
	struct {
	    uint64_t reserved;
	} __attribute__ ((packed)) ibnd;
	struct {
	    uint64_t reserved;
	} __attribute__ ((packed)) xprs;
	struct {
	    uint64_t reserved;
	} __attribute__ ((packed)) htpt;
	struct {
	    uint64_t reserved;
	} __attribute__ ((packed)) unknown;
    } interface_path;
	/**
	 * Format of EDD v3.0 Device Path:
	 * Offset    Size    Description    (Table 00276)
	 * ---ATA---
	 * 00h    BYTE    flag: 00h = master, 01h = slave
	 * 01h 7 BYTEs    reserved (0)
	 * ---ATAPI---
	 * 00h    BYTE    flag: 00h = master, 01h = slave
	 * 01h    BYTE    logical unit number
	 * 02h 6 BYTEs    reserved (0)
	 * ---SCSI---
	 * 00h    BYTE    logical unit number
	 * 01h 7 BYTEs    reserved (0)
	 * ---USB---
	 * 00h    BYTE    to be determined
	 * 01h 7 BYTEs    reserved (0)
	 * ---IEEE1394---
	 * 00h    QWORD    64-bit FireWire General Unique Identifier (GUID)
	 * ---FibreChannel---
	 * 00h    QWORD    Word Wide Number (WWN)
	 **/
    union {
	struct {
	    uint8_t device;
	    uint8_t reserved1;
	    uint16_t reserved2;
	    uint32_t reserved3;
	    uint64_t reserved4;
	} __attribute__ ((packed)) ata;
	struct {
	    uint8_t device;
	    uint8_t lun;
	    uint8_t reserved1;
	    uint8_t reserved2;
	    uint32_t reserved3;
	    uint64_t reserved4;
	} __attribute__ ((packed)) atapi;
	struct {
	    uint16_t id;
	    uint64_t lun;
	    uint16_t reserved1;
	    uint32_t reserved2;
	} __attribute__ ((packed)) scsi;
	struct {
	    uint64_t serial_number;
	    uint64_t reserved;
	} __attribute__ ((packed)) usb;
	struct {
	    uint64_t eui;
	    uint64_t reserved;
	} __attribute__ ((packed)) i1394;
	struct {
	    uint64_t wwid;
	    uint64_t lun;
	} __attribute__ ((packed)) fibre;
	struct {
	    uint64_t identity_tag;
	    uint64_t reserved;
	} __attribute__ ((packed)) i2o;
	struct {
	    uint32_t array_number;
	    uint32_t reserved1;
	    uint64_t reserved2;
	} __attribute__ ((packed)) raid;
	struct {
	    uint8_t device;
	    uint8_t reserved1;
	    uint16_t reserved2;
	    uint32_t reserved3;
	    uint64_t reserved4;
	} __attribute__ ((packed)) sata;
	struct {
	    uint64_t reserved1;
	    uint64_t reserved2;
	} __attribute__ ((packed)) unknown;
    } device_path;
    uint8_t reserved;		/* reserved (0) */
    uint8_t checksum;		/* checksum of bytes 1Eh-40h (two's complement of sum, which makes
				 * the 8-bit sum of bytes 1Eh-41h equal 00h) */
} __attribute__ ((packed));

/*
 * Disk parameters
 */
struct driveinfo {
    int disk;			/* Disk port (0x80 - 0xff) */
    /* Legacy C/H/S */
    int cbios;			/* CHS geometry is valid */
    int legacy_max_head;
    int legacy_max_cylinder;
    int legacy_sectors_per_track;
    int legacy_max_drive;
    int legacy_type;		/* Drive type (AT/PS2 floppies only) */
    /* EDD support */
    int ebios;			/* EBIOS supported on this disk */
    int edd_version;		/* EBIOS major version */
    int edd_functionality_subset;
    struct edd_device_parameters edd_params;	/* EDD parameters */
};

/**
 * Format of Phoenix Enhanced Disk Drive Spec translated drive parameter table:
 * Offset    Size    Description    (Table 00277)
 * 00h    WORD    number of cylinders
 * 02h    BYTE    number of heads
 * 03h    BYTE    A0h (signature indicating translated table)
 * 04h    BYTE    number of physical sectors per track
 * 05h    WORD    starting write precompensation cylinder number
 * 07h    BYTE    reserved
 * 08h    BYTE    control byte (see #03198 at INT 41"DISK 0")
 * 09h    WORD    number of physical cylinders
 * 0Bh    BYTE    number of physical heads
 * 0Ch    WORD    cylinder number of landing zone
 * 0Eh    BYTE    number of logical sectors per track
 * 0Fh    BYTE    checksum
 * Program: the Phoenix Enhanced Disk Drive Specification is an addition to the
 *     IBM/MS INT 13 extensions
 *
 * Format of Phoenix Enhanced Disk Drive Spec Fixed Disk Parameter Table:
 * Offset    Size    Description    (Table 00278)
 * 00h    WORD    physical I/O port base address
 * 02h    WORD    disk-drive control port address
 * 04h    BYTE    drive flags (see #00279)
 * 05h    BYTE    proprietary information
 *         bits 7-4 reserved (0)
 *         bits 3-0: Phoenix proprietary (used by BIOS)
 * 06h    BYTE    IRQ for drive (bits 3-0; bits 7-4 reserved and must be 0)
 * 07h    BYTE    sector count for multi-sector transfers
 * 08h    BYTE    DMA control
 *         bits 7-4: DMA type (0-2) as per ATA-2 specification
 *         bits 3-0: DMA channel
 * 09h    BYTE    programmed I/O control
 *         bits 7-4: reserved (0)
 *         bits 3-0: PIO type (1-4) as per ATA-2 specification
 * 0Ah    WORD    drive options (see #00280)
 * 0Ch 2 BYTEs    reserved (0)
 * 0Eh    BYTE    extension revision level (high nybble=major, low nybble=minor)
 *         (currently 10h for v1.0 and 11h for v1.1-3.0)
 * 0Fh    BYTE    2's complement checksum of bytes 00h-0Eh
 *         8-bit sum of all bytes 00h-0Fh should equal 00h
 * SeeAlso: #00277
 *
 * Bitfields for Phoenix Enhanced Disk Drive Spec drive flags:
 * Bit(s)    Description    (Table 00279)
 * 7    reserved (1)
 * 6    LBA enabled
 * 5    reserved (1)
 * 4    drive is slave
 * 3-0    reserved (0)
 * SeeAlso: #00278,#00280
 *
 * Bitfields for Phoenix Enhanced Disk Drive Spec drive options:
 * Bit(s)    Description    (Table 00280)
 * 0    fast PIO enabled
 * 1    fast DMA access enabled
 * 2    block PIO (multi-sector transfers) enabled
 * 3    CHS translation enabled
 * 4    LBA translation enabled
 * 5    removable media
 * 6    ATAPI device (CD-ROM)
 * 7    32-bit transfer mode
 * ---v1.1+ ---
 * 8    ATAPI device uses DRQ to signal readiness for packet command
 *     (must be 0 if bit 6 is 0)
 * 10-9    translation type (must be 00 if bit 3 is 0)
 *     00 Phoenix bit-shifting translation
 *     01 LBA-assisted translation
 *     10 reserved
 *     11 proprietary translation
 * ---v3.0---
 * 11    Ultra DMA access enabled
 * 15-12    reserved
 **/

/*
 * Values for diskette drive type:
 *     01h    360K
 *     02h    1.2M
 *     03h    720K
 *     04h    1.44M
 *     05h    ???
 *            reportedly an obscure drive type shipped on some IBM machines,
 *            2.88M on some machines (at least AMI 486 BIOS)
 *     06h    2.88M
 *     10h    ATAPI Removable Media Device
 */
enum diskette_drive_types {
    DISKETTE_360K = 1,
    DISKETTE_1_2M = 2,
    DISKETTE_720K = 3,
    DISKETTE_1_44M = 4,
    DISKETTE_2_88M = 6,
    DISKETTE_ATAPI = 10,
};

/**
 * chs_to_lba - compute lba value from cylinder, head and sector number
 **/
static inline int chs_to_lba(const struct driveinfo *drive_info,
			     const unsigned int cylinder,
			     const unsigned int head, const unsigned int sector)
{
    /* Use EDD, if valid */
    if (drive_info->edd_params.sectors_per_track > 0 &&
	drive_info->edd_params.heads > 0)
	return (sector - 1) +
	    (head * drive_info->edd_params.sectors_per_track) +
	    (cylinder * (drive_info->edd_params.heads) *
	     drive_info->edd_params.sectors_per_track);
    else if (drive_info->cbios)
	return (sector - 1) + (head * drive_info->legacy_sectors_per_track) +
	    (cylinder * (drive_info->legacy_max_head + 1) *
	     drive_info->legacy_sectors_per_track);
}

void lba_to_chs(const struct driveinfo *drive_info, const int lba,
		unsigned int *cylinder, unsigned int *head,
		unsigned int *sector);
int get_drive_parameters(struct driveinfo *drive_info);

#endif /* _GEOM_H */
