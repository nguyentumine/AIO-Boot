#ifndef _CPU_H
#define _CPU_H

#include <stdbool.h>
#include <stdint.h>
#include <klibc/compiler.h>

#if __SIZEOF_POINTER__ == 4
#include <i386/cpu.h>
#elif __SIZEOF_POINTER__ == 8
#include <x86_64/cpu.h>
#else 
#error "unsupported architecture"
#endif

typedef unsigned long irq_state_t;

static inline irq_state_t irq_state(void)
{
    irq_state_t __st;

    asm volatile("pushf ; pop %0" : "=rm" (__st) : : "memory");
    return __st;
}

static inline irq_state_t irq_save(void)
{
    irq_state_t __st = irq_state();
    cli();
    return __st;
}

static inline void irq_restore(irq_state_t __st)
{
    asm volatile("push %0 ; popf" : : "rm" (__st) : "memory");
}

/* Standard macro to see if a specific flag is changeable */
static inline __constfunc bool cpu_has_eflag(unsigned long flag)
{
	unsigned long f0, f1;
	asm("pushf ; "
	    "pushf ; "
	    "pop %0 ; "
	    "mov %0,%1 ; "
	    "xor %2,%1 ; "
	    "push %1 ; "
	    "popf ; "
	    "pushf ; "
	    "pop %1 ; "
	    "popf"
	    : "=&r" (f0), "=&r" (f1)
	    : "ri" (flag));
	return !!((f0^f1) & flag);
}

#endif
