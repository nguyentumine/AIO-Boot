/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef __BOOTLOADERS_H_
#define __BOOTLOADERS_H_

#include <stdint.h>
#include <disk/geom.h>
#include <disk/partition.h>

int get_bootloader_string(struct driveinfo *, const struct part_entry *,
			  char *, const int);
#endif /* __BOOTLOADERS_H_ */
