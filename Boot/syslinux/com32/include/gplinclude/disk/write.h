/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   Some parts borrowed from chain.c32:
 *
 *   Copyright 2003-2009 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author: H. Peter Anvin
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef _WRITE_H_
#define _WRITE_H_

#include <disk/geom.h>

int write_sectors(const struct driveinfo *, const unsigned int,
		  const void *, const int);
int write_verify_sector(struct driveinfo *drive_info,
			const unsigned int, const void *);
int write_verify_sectors(struct driveinfo *,
			 const unsigned int, const void *, const int);
#endif
