/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef _MSDOS_H_
#define _MSDOS_H_

#include <disk/geom.h>
#include <disk/partition.h>

typedef void (*p_callback) (struct driveinfo *, struct part_entry *, int, int);
int parse_partition_table(struct driveinfo *, p_callback);

#endif /* _MSDOS_H_ */
