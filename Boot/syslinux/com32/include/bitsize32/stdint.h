/*
 * bits32/stdint.h
 */


typedef long long int		int64_t;

typedef unsigned long long int	uint64_t;

typedef int			int_fast16_t;
typedef int			int_fast32_t;

typedef unsigned int		uint_fast16_t;
typedef unsigned int		uint_fast32_t;

typedef int			intptr_t;
typedef unsigned int		uintptr_t;

#define __INT64_C(c)   c ## LL
#define __UINT64_C(c)  c ## ULL

#define __PRI64_RANK   "ll"
#define __PRIFAST_RANK ""
#define __PRIPTR_RANK  ""
