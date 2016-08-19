#ifndef LIBUTIL_LOADFILE_H
#define LIBUTIL_LOADFILE_H

#include <stddef.h>
#include <stdio.h>

/* loadfile() returns the true size of the file, but will guarantee valid,
   zero-padded memory out to this boundary. */
#define LOADFILE_ZERO_PAD	64

int loadfile(const char *, void **, size_t *);
int zloadfile(const char *, void **, size_t *);
int floadfile(FILE *, void **, size_t *, const void *, size_t);

#endif
