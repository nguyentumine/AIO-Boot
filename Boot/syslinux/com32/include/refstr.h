/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2008 H. Peter Anvin - All Rights Reserved
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 *   Boston MA 02110-1301, USA; either version 2 of the License, or
 *   (at your option) any later version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

/*
 * refstr.h
 *
 * Simple reference-counted strings
 */

#ifndef REFSTR_H
#define REFSTR_H

#include <stddef.h>
#include <stdarg.h>

static inline __attribute__ ((always_inline))
const char *refstr_get(const char *r)
{
    if (r)
	((unsigned int *)r)[-1]++;
    return r;
}

void refstr_put(const char *);
char *refstr_alloc(size_t);
const char *refstrdup(const char *);
const char *refstrndup(const char *, size_t);
int rsprintf(const char **, const char *, ...);
int vrsprintf(const char **, const char *, va_list);

#endif
