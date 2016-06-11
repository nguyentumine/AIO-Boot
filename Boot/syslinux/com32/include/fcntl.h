/*
 * fcntl.h
 */

#ifndef _FCNTL_H
#define _FCNTL_H

#include <klibc/extern.h>
#include <klibc/compiler.h>
#include <sys/types.h>

/* None of these are actually supported, although O_RDONLY works */
/* Note this is different from the classical Unix way of doing it */
#define	O_RDONLY	1
#define O_WRONLY	2
#define O_RDWR		3
#define O_DIRECTORY	010
#define O_CREAT		0100
#define O_EXCL		0200
#define O_TRUNC		01000
#define O_APPEND	02000

__extern int open(const char *, int, ...);

#endif /* _FCNTL_H */
