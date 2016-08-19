/*
 * bits32/limits.h
 */

#ifndef _BITSIZE_LIMITS_H
#define _BITSIZE_LIMITS_H

#if __SIZEOF_POINTER__ == 4
#include <bitsize32/limits.h>
#elif __SIZEOF_POINTER__ == 8
#include <bitsize64/limits.h>
#else
#error "Unable to build for to-be-defined architecture type"
#endif

#endif /* _BITSIZE_LIMITS_H */
