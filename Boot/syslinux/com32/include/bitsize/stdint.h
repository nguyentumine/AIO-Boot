/*
 * bits32/stdint.h
 */

#ifndef _BITSIZE_STDINT_H
#define _BITSIZE_STDINT_H

typedef signed char		int8_t;
typedef short int		int16_t;
typedef int			int32_t;

typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;

#if __SIZEOF_POINTER__ == 4
#include <bitsize32/stdint.h>
#elif __SIZEOF_POINTER__ == 8
#include <bitsize64/stdint.h>
#else
#error "Unable to build for to-be-defined architecture type"
#endif
#endif				/* _BITSIZE_STDINT_H */
