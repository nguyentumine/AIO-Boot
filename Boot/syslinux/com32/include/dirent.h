/*
 * dirent.h
 */

#ifndef _DIRENT_H
#define _DIRENT_H

#include <klibc/extern.h>
#include <klibc/compiler.h>
#include <stddef.h>
#include <sys/types.h>

#include <sys/dirent.h>

__extern DIR *opendir(const char *);
__extern struct dirent *readdir(DIR *);
__extern int closedir(DIR *);
__extern DIR *fdopendir(int);

#endif /* Not _DIRENT_H */
