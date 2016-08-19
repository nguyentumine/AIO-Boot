/* i386 cpu.h */

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

static inline void cpuid(uint32_t op, uint32_t * eax, uint32_t * ebx,
			 uint32_t * ecx, uint32_t * edx)
{
    cpuid_count(op, 0, eax, ebx, ecx, edx);
}

static inline __constfunc uint32_t cpuid_eax(uint32_t level)
{
    uint32_t v;

    asm volatile("pushl %%ebx ; "
		 "cpuid ; "
		 "popl %%ebx"
		 : "=a" (v)
		 : "a"(level)
		 : "ecx", "edx");
    return v;
}

static inline __constfunc uint32_t cpuid_ebx(uint32_t level)
{
    uint32_t v;

    asm volatile("movl %%ebx,%0 ; "
		 "cpuid ; "
		 "xchgl %0,%%ebx"
		 : "=SD" (v), "+a" (level)
		 : : "ecx", "edx");
    return v;
}

static inline __constfunc uint32_t cpuid_ecx(uint32_t level)
{
    uint32_t v;

    asm volatile("pushl %%ebx ; "
		 "cpuid ; "
		 "popl %%ebx"
		 : "=c" (v), "+a" (level)
		 : : "edx");
    return v;
}

static inline __constfunc uint32_t cpuid_edx(uint32_t level)
{
    uint32_t v;

    asm volatile("pushl %%ebx ; "
		 "cpuid ; "
		 "popl %%ebx"
		 : "=d" (v), "+a" (level)
		 : : "ecx");
    return v;
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
