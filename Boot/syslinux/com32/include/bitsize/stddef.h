/*
 * Include stddef.h as appropriate for architecture
 */

#ifndef _BITSIZE_STDDEF_H
#define _BITSIZE_STDDEF_H

#if __SIZEOF_POINTER__ == 4
#include <bitsize32/stddef.h>
#elif __SIZEOF_POINTER__ == 8
#include <bitsize64/stddef.h>
#else
#error "Unable to build for to-be-defined architecture type"
#endif

#endif /* _BITSIZE_STDDEF_H */
