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

#ifndef _UTIL_H_
#define _UTIL_H_

#include <com32.h>

int int13_retry(const com32sys_t * inreg, com32sys_t * outreg);
#endif /* _UTIL_H_ */
