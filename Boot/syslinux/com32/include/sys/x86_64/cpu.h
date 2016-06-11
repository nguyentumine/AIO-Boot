#ifndef _CPU_X86_64_H
#define _CPU_X86_64_H

/* x86_64 cpu.h  */

static inline uint64_t rdtsc(void)
{
    uint64_t v;
    asm volatile("rdtsc" : "=A" (v));
    return v;
}

static inline uint32_t rdtscl(void)
{
    uint32_t v;
    asm volatile("rdtsc" : "=a" (v) : : "edx");
    return v;
}

static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
                                unsigned int *ecx, unsigned int *edx)
{
        /* ecx is often an input as well as an output. */
        asm volatile("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx)
            : "memory");
}
/*
 * Generic CPUID function
 * clear %ecx since some cpus (Cyrix MII) do not set or clear %ecx
 * resulting in stale register contents being returned.
 */
static inline void cpuid(uint32_t op,
                         uint32_t *eax, uint32_t *ebx,
                         uint32_t *ecx, uint32_t *edx)
{
        *eax = op;
        *ecx = 0;
        native_cpuid(eax, ebx, ecx, edx);
}

/*
 * CPUID functions returning a single datum
 */
static inline uint32_t cpuid_eax(uint32_t op)
{
        uint32_t eax, ebx, ecx, edx;

        cpuid(op, &eax, &ebx, &ecx, &edx);

        return eax;
}

static inline uint32_t cpuid_ebx(uint32_t op)
{
        uint32_t eax, ebx, ecx, edx;

        cpuid(op, &eax, &ebx, &ecx, &edx);

        return ebx;
}

static inline uint32_t cpuid_ecx(uint32_t op)
{
        uint32_t eax, ebx, ecx, edx;

        cpuid(op, &eax, &ebx, &ecx, &edx);

        return ecx;
}

static inline uint32_t cpuid_edx(uint32_t op)
{
        uint32_t eax, ebx, ecx, edx;

        cpuid(op, &eax, &ebx, &ecx, &edx);

        return edx;
}

static inline void cpuid_count(uint32_t op, uint32_t cnt,
			       uint32_t * eax, uint32_t * ebx,
			       uint32_t * ecx, uint32_t * edx)
{
    asm volatile("movl %%ebx,%1 ; "
		 "cpuid ; "
		 "xchgl %1,%%ebx"
		 : "=a" (*eax), "=SD" (*ebx), "=c" (*ecx), "=d" (*edx)
		 : "a"(op), "c"(cnt));
}

static inline uint64_t rdmsr(uint32_t msr)
{
    uint64_t v;

    asm volatile("rdmsr" : "=A" (v) : "c"(msr));
    return v;
}

static inline void wrmsr(uint64_t v, uint32_t msr)
{
    asm volatile("wrmsr" : : "A" (v), "c" (msr));
}

static inline void cpu_relax(void)
{
    asm volatile("rep ; nop" : : : "memory");
}

static inline void hlt(void)
{
    asm volatile("hlt" : : : "memory");
}

static inline void cli(void)
{
    asm volatile("cli" : : : "memory");
}

static inline void sti(void)
{
    asm volatile("sti" : : : "memory");
}
#endif
