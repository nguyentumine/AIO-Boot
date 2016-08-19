/*
 * bitsize/stdintconst.h
 */

#ifndef _BITSIZE_STDINTCONST_H
#define _BITSIZE_STDINTCONST_H

#if __SIZEOF_POINTER__ == 4
#include <bitsize32/stdintconst.h>
#elif __SIZEOF_POINTER__ == 8
#include <bitsize64/stdintconst.h>
#else
#error "Unable to build for to-be-defined architecture type"
#endif

#endif				/* _BITSIZE_STDINTCONST_H */
