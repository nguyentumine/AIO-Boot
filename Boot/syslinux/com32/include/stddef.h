/*
 * stddef.h
 */

#ifndef _STDDEF_H
#define _STDDEF_H

#ifndef __KLIBC__
# define __KLIBC__ 1
#endif

#include <bitsize/stddef.h>

#undef NULL
#ifdef __cplusplus
# define NULL 0
#else
# define NULL ((void *)0)
#endif

#undef offsetof
#define offsetof(t,m) ((size_t)&((t *)0)->m)

#undef container_of
/*
 * The container_of construct: if p is a pointer to member m of
 * container class c, then return a pointer to the container of which
 * *p is a member.
 */
#define container_of(p, c, m) ((c *)((char *)(p) - offsetof(c,m)))

#endif /* _STDDEF_H */
