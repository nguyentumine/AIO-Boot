/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2002-2009 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009-2010 Intel Corporation; author: H. Peter Anvin
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
 * com32.h
 *
 * Common declarations for com32 programs.
 */

#ifndef _COM32_H
#define _COM32_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <klibc/compiler.h>	/* For __cdecl */

/*
 * This structure defines the register frame used by the
 * system call interface.
 *
 * The syscall interface is:
 *
 * __intcall(interrupt_#, source_regs, return_regs)
 * __farcall(seg, offs, source_regs, return_regs)
 */
typedef union {
    uint32_t l;
    uint16_t w[2];
    uint8_t b[4];
} reg32_t;

typedef struct {
    uint16_t gs;		/* Offset  0 */
    uint16_t fs;		/* Offset  2 */
    uint16_t es;		/* Offset  4 */
    uint16_t ds;		/* Offset  6 */

    reg32_t edi;		/* Offset  8 */
    reg32_t esi;		/* Offset 12 */
    reg32_t ebp;		/* Offset 16 */
    reg32_t _unused_esp;	/* Offset 20 */
    reg32_t ebx;		/* Offset 24 */
    reg32_t edx;		/* Offset 28 */
    reg32_t ecx;		/* Offset 32 */
    reg32_t eax;		/* Offset 36 */

    reg32_t eflags;		/* Offset 40 */
} com32sys_t;

/* EFLAGS definitions */
#define EFLAGS_CF		0x00000001
#define EFLAGS_PF		0x00000004
#define EFLAGS_AF		0x00000010
#define EFLAGS_ZF		0x00000040
#define EFLAGS_SF		0x00000080
#define EFLAGS_TF		0x00000100
#define EFLAGS_IF		0x00000200
#define EFLAGS_DF		0x00000400
#define EFLAGS_OF		0x00000800
#define EFLAGS_IOPL		0x00003000
#define EFLAGS_NT		0x00004000
#define EFLAGS_RF		0x00010000
#define EFLAGS_VM		0x00020000
#define EFLAGS_AC		0x00040000
#define EFLAGS_VIF		0x00080000
#define EFLAGS_VIP		0x00100000
#define EFLAGS_ID		0x00200000

struct com32_pmapi;

extern struct com32_sys_args {
    uint32_t cs_sysargs;
    char *cs_cmdline;
    void __cdecl (*cs_intcall)(uint8_t, const com32sys_t *, com32sys_t *);
    void *cs_bounce;
    uint32_t cs_bounce_size;
    void __cdecl (*cs_farcall)(uint32_t, const com32sys_t *, com32sys_t *);
    int __cdecl (*cs_cfarcall)(uint32_t, const void *, uint32_t);
    uint32_t cs_memsize;
    const char *cs_name;
    const struct com32_pmapi *cs_pm;
} __com32;

/*
 * System call wrapper functions
 */
void __intcall(uint8_t __i, const com32sys_t * __sr, com32sys_t * __dr);
void __farcall(uint16_t __cs, uint16_t __ip,
	       const com32sys_t * __sr, com32sys_t * __dr);
int __cfarcall(uint16_t __cs, uint16_t __ip,
	       const void *__stack, uint32_t __stack_size);
extern const com32sys_t __com32_zero_regs;

/*
 * Lowmem allocation functions
 */
void *lmalloc(size_t);
void *lzalloc(size_t);
void lfree(void *);
char *lstrdup(const char *);

/*
 * These functions convert between linear pointers in the range
 * 0..0xFFFFF and real-mode style SEG:OFFS pointers.  Note that a
 * 32-bit linear pointer is not compatible with a SEG:OFFS pointer
 * stored in two consecutive 16-bit words.
 *
 * Use OFFS_WRT() if you want to compute an offset relative to a
 * specific segment.  OFFS_VALID() will return whether or not the
 * pointer is actually reachable from the target segment.
 */
#if defined(CORE_DEBUG) && (defined(__COM32__) || defined(__SYSLINUX_CORE__))
__noreturn __bad_SEG(const volatile void *);

static inline uint16_t SEG(const volatile void *__p)
{
    if (__unlikely((uintptr_t)__p > 0xfffff))
	__bad_SEG(__p);

    return (uint16_t) (((uintptr_t) __p) >> 4);
}
#else
static inline uint16_t SEG(const volatile void *__p)
{
    return (uint16_t) (((uintptr_t) __p) >> 4);
}
#endif

static inline uint16_t OFFS(const volatile void *__p)
{
    /* The double cast here is to shut up gcc */
    return (uint16_t) (uintptr_t) __p & 0x000F;
}

static inline uint16_t OFFS_WRT(const volatile void *__p, uint16_t __seg)
{
    return (uint16_t) ((uintptr_t) __p - ((uintptr_t) __seg << 4));
}

#define OFFS_VALID(p,s) _OFFS_VALID((p), sizeof *(p), (s))

static inline bool _OFFS_VALID(const volatile void *__p, size_t __s,
			       uint16_t __seg)
{
    uintptr_t __segstart = (uintptr_t)__seg << 4;
    uintptr_t __offs  = (uintptr_t)__p - __segstart;

    return __offs <= 0x10000-__s;
}

static inline void *MK_PTR(uint16_t __seg, uint16_t __offs)
{
    return (void *)(unsigned long)((__seg << 4) + __offs);
}

/* Some tools to handle 16:16 far pointers in memory */

struct __far_ptr {
    union {
	uint32_t ptr;
	struct {
	    uint16_t offs, seg;
	};
    };
} __attribute__ ((packed));

typedef struct __far_ptr far_ptr_t;

static inline void *GET_PTR(far_ptr_t __fptr)
{
    return MK_PTR(__fptr.seg, __fptr.offs);
}

static inline far_ptr_t FAR_PTR(void *__ptr)
{
    far_ptr_t __fptr;

    __fptr.offs = OFFS(__ptr);
    __fptr.seg  = SEG(__ptr);
    return __fptr;
}

extern const char *com32_cmdline(void);

#endif /* _COM32_H */
