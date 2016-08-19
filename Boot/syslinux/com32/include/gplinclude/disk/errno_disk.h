/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef _ERRNO_DISK_H
#define _ERRNO_DISK_H

extern int errno_disk;

/* Prefix with ED to avoid confusion with errno */
#define	EDINV	0x01		/* Invalid function in AH or invalid parameter */
#define	EDADDR	0x02		/* Address mark not found */
#define	EDRO	0x03		/* Disk write-protected */
#define	EDNOFND	0x04		/* Sector not found/read error */
#define	EDRFAIL	0x05		/* Reset failed (hard disk) */
#define	EDCHANG	0x06		/* Disk changed (floppy) */
#define	EDFAIL	0x07		/* Drive parameter activity failed (hard disk) */
#define	EDDMA	0x08		/* DMA overrun */
#define	EDBOUND	0x09		/* Data boundary error (attempted DMA across 64K boundary or >80h sectors) */
#define	EDBADS	0x0A		/* Bad sector detected (hard disk) */
#define	EDBADT	0x0B		/* Bad track detected (hard disk) */
#define	EDINVM	0x0C		/* Unsupported track or invalid media */
#define	EDINVS	0x0D		/* Invalid number of sectors on format (PS/2 hard disk) */
#define	EDADDRM	0x0E		/* Control data address mark detected (hard disk) */
#define	EDDMARG	0x0F		/* DMA arbitration level out of range (hard disk) */
#define	EDCRCF	0x10		/* Uncorrectable CRC or ECC error on read */
#define	EDCRCV	0x11		/* Data ECC corrected (hard disk) */
#define	EDCTRL	0x20		/* Controller failure */
#define	EDMEDIA	0x31		/* No media in drive (IBM/MS INT 13 extensions) */
#define	EDCMOS	0x32		/* Incorrect drive type stored in CMOS (Compaq) */
#define	EDSEEKF	0x40		/* Seek failed */
#define	EDTIME	0x80		/* Timeout (not ready) */
#define	EDREADY	0xAA		/* Drive not ready (hard disk) */
#define	EDNLOCK	0xB0		/* Volume not locked in drive (INT 13 extensions) */
#define	EDLOCK	0xB1		/* Volume locked in drive (INT 13 extensions) */
#define	EDREMOV	0xB2		/* Volume not removable (INT 13 extensions) */
#define	EDUSED	0xB3		/* Volume in use (INT 13 extensions) */
#define	EDCOUNT	0xB4		/* Lock count exceeded (INT 13 extensions) */
#define	EDEJF	0xB5		/* Valid eject request failed (INT 13 extensions) */
#define	EDUNKOWN	0xBB	/* Undefined error (hard disk) */
#define	EDWF	0xCC		/* Write fault (hard disk) */
#define	EDRF	0xE0		/* Status register error (hard disk) */
#define	EDSF	0xFF		/* Sense operation failed (hard disk) */

#endif /* _ERRNO_DISK_H */
