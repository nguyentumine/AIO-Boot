/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef __MBRS_H_
#define __MBRS_H_

#include <stdint.h>
#include <disk/geom.h>

void get_mbr_string(const uint32_t, void *, const int);
uint32_t get_mbr_id(const struct driveinfo *);
#endif /* __MBRS_H_ */
