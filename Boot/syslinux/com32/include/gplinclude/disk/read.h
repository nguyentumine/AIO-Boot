/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef _READ_H_
#define _READ_H_

#include <disk/geom.h>

int read_mbr(int, void *);
int dev_read(int, void *, unsigned int, int);
int read_sectors(struct driveinfo *, void *, const unsigned int, const int);
#endif /* _READ_H */
