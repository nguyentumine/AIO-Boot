/*
 * bits64/stdint.h
 */


typedef long int		int64_t;

typedef unsigned long int	uint64_t;

typedef long int		int_fast16_t;
typedef long int		int_fast32_t;

typedef unsigned long int	uint_fast16_t;
typedef unsigned long int	uint_fast32_t;

typedef long int		intptr_t;
typedef unsigned long int	uintptr_t;

#define __INT64_C(c)  c ## L
#define __UINT64_C(c) c ## UL

#define __PRI64_RANK	"l"
#define __PRIFAST_RANK  "l"
#define __PRIPTR_RANK	"l"
