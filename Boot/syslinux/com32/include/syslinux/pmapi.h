/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2002-2009 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author: H. Peter Anvin
 *
 *   Permission is hereby granted, free of charge, to any person
 *   obtaining a copy of this software and associated documentation
 *   files (the "Software"), to deal in the Software without
 *   restriction, including without limitation the rights to use,
 *   copy, modify, merge, publish, distribute, sublicense, and/or
 *   sell copies of the Software, and to permit persons to whom
 *   the Software is furnished to do so, subject to the following
 *   conditions:
 *
 *   The above copyright notice and this permission notice shall
 *   be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 *
 * ----------------------------------------------------------------------- */

/*
 * pmapi.h
 *
 * Definitions for the Syslinux 4 protected-mode ABI
 */

#ifndef _SYSLINUX_PMAPI_H
#define _SYSLINUX_PMAPI_H

#include <stddef.h>
#include <inttypes.h>

/*
 * Note: add new members to this structure only at the end.
 * The position of elements in this structure is an ABI.
 */
struct _DIR_;
struct dirent;

struct com32_filedata {
    size_t size;		/* File size */
    int blocklg2;		/* log2(block size) */
    uint16_t handle;		/* File handle */
};

struct com32_pmapi {
    size_t __pmapi_size;

    void *(*lmalloc)(size_t);
    void (*lfree)(void *);

    int (*open_file)(const char *, int, struct com32_filedata *);
    size_t (*read_file)(uint16_t *, void *, size_t);
    void (*close_file)(uint16_t);

    struct _DIR_ *(*opendir)(const char *);
    struct dirent *(*readdir)(struct _DIR_ *);
    int (*closedir)(struct _DIR_ *);

    void (*idle)(void);
    void (*reset_idle)(void);

    int (*chdir)(const char *);
    char *(*getcwd)(char *, size_t);

    /* Should be "const volatile", but gcc miscompiles that sometimes */
    volatile uint32_t *jiffies;
    volatile uint32_t *ms_timer;

    const int sysappend_count;
    const char * const *sysappend_strings;
};

#endif /* _SYSLINUX_PMAPI_H */
