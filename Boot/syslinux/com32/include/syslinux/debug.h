#ifndef DEBUG_H
#define DEBUG_H

#include <stdbool.h>

#ifdef DYNAMIC_DEBUG
#define syslinux_debug_enabled	__syslinux_debug_enabled(__func__)
extern bool __syslinux_debug_enabled(const char *func);
#else
#define syslinux_debug_enabled	(0)
#endif /* DYNAMIC_DEBUG */

extern int syslinux_debug(const char *str, bool enable);

#endif /* DEBUG_H */
