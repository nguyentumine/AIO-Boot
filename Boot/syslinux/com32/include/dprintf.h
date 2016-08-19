/*
 * dprintf.h
 */

#ifndef _DPRINTF_H
#define _DPRINTF_H

#include <syslinux/debug.h>

#if !defined(DEBUG_PORT) && !defined(DEBUG_STDIO)
# undef CORE_DEBUG
#endif

#ifdef CORE_DEBUG

# include <stdio.h>

# ifdef DEBUG_STDIO
#  define dprintf  printf
#  define vdprintf vprintf
#  define ddprintf dprintf
# else
void dprintf(const char *, ...);
void vdprintf(const char *, va_list);
#  define ddprintf(...)	{ printf(__VA_ARGS__); dprintf(__VA_ARGS__); }
# endif

#else

#define dprintf(...) \
    if (syslinux_debug_enabled) \
        printf(__VA_ARGS__)
#define vdprintf(fmt, ap) \
    if (syslinux_debug_enabled) \
        vprintf(fmt, ap)
#define ddprintf	printf

#endif /* CORE_DEBUG */

# if CORE_DEBUG >= 2
/* Really verbose debugging... */
#  define dprintf2  dprintf
#  define vdprintf2 vdprintf
# else
#  define dprintf2(fmt, ...)	((void)(0))
#  define vdprintf2(fmt, ap)	((void)(0))
# endif

#endif /* _DPRINTF_H */
