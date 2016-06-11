/*
 * sys/times.h
 */

#ifndef _SYS_TIMES_H
#define _SYS_TIMES_H

#include <stdint.h>

struct tms {
    /* Empty */
};

#define HZ		1000
#define CLK_TCK		HZ

typedef uint32_t clock_t;

extern volatile uint32_t __ms_timer;

static inline clock_t times(struct tms *buf)
{
    (void)buf;
    return __ms_timer;
}

#endif /* _SYS_TIMES_H */
