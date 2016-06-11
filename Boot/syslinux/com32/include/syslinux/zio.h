/*
 * <syslinux/zio.h>
 */

#ifndef _SYSLINUX_ZIO_H
#define _SYSLINUX_ZIO_H

#include <stdio.h>

int zopen(const char *, int, ...);
FILE *zfopen(const char *, const char *);

#endif /* _SYSLINUX_ZIO_H */
