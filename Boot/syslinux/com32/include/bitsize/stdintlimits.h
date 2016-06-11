/*
 * bitsize/stdintlimits.h
 */

#ifndef _BITSIZE_STDINTLIMITS_H
#define _BITSIZE_STDINTLIMITS_H

#if __SIZEOF_POINTER__ == 4
#include <bitsize32/stdintlimits.h>
#elif __SIZEOF_POINTER__ == 8
#include <bitsize64/stdintlimits.h>
#else
#error "Unable to build for to-be-defined architecture type"
#endif

#endif				/* _BITSIZE_STDINTLIMITS_H */
