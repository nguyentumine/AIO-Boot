/*
 * setjmp.h
 */

#ifndef _SETJMP_H
#define _SETJMP_H

#include <klibc/extern.h>
#include <klibc/compiler.h>
#include <stddef.h>

#if __SIZEOF_POINTER__ == 4
#include <klibc/i386/archsetjmp.h>
#elif __SIZEOF_POINTER__ == 8
#include <klibc/x86_64/archsetjmp.h>
#else
#error "unsupported architecture"
#endif

__extern int setjmp(jmp_buf);
__extern __noreturn longjmp(jmp_buf, int);

typedef jmp_buf sigjmp_buf;

#define sigsetjmp(__env, __save) setjmp(__env)
#define siglongjmp(__env, __val) longjmp(__env, __val)

#endif /* _SETJMP_H */
