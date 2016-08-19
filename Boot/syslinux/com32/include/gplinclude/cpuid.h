/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2006-2009 Erwan Velu - All Rights Reserved
 *
 *   Portions of this file taken from the Linux kernel,
 *   Copyright 1991-2009 Linus Torvalds and contributors
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2
 *   as published by the Free Software Foundation, Inc.,
 *   51 Franklin St, Fifth Floor, Boston MA 02110-1301;
 *   incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

#ifndef _CPUID_H
#define _CPUID_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cpufeature.h>
#include <sys/bitops.h>
#include <sys/cpu.h>
#include <sys/io.h>
#include <klibc/compiler.h>

#define PAGE_SIZE 4096

#define CPU_MODEL_SIZE  48
#define CPU_VENDOR_SIZE 48

#define CPU_FLAGS(m_) \
m_(bool,  fpu, 			/* Onboard FPU */) \
m_(bool,  vme, 			/* Virtual Mode Extensions */) \
m_(bool,  de, 			/* Debugging Extensions */) \
m_(bool,  pse,			/* Page Size Extensions */) \
m_(bool,  tsc,			/* Time Stamp Counter */) \
m_(bool,  msr,			/* Model-Specific Registers, RDMSR, WRMSR */) \
m_(bool,  pae,			/* Physical Address Extensions */) \
m_(bool,  mce,			/* Machine Check Architecture */) \
m_(bool,  cx8,			/* CMPXCHG8 instruction */) \
m_(bool,  apic,			/* Onboard APIC */) \
m_(bool,  sep,			/* SYSENTER/SYSEXIT */) \
m_(bool,  mtrr,			/* Memory Type Range Registers */) \
m_(bool,  pge,			/* Page Global Enable */) \
m_(bool,  mca,			/* Machine Check Architecture */) \
m_(bool,  cmov,			/* CMOV instruction (FCMOVCC and FCOMI too if FPU present) */) \
m_(bool,  pat,			/* Page Attribute Table */) \
m_(bool,  pse_36,		/* 36-bit PSEs */) \
m_(bool,  psn,			/* Processor serial number */) \
m_(bool,  clflsh,		/* Supports the CLFLUSH instruction */) \
m_(bool,  dts,			/* Debug Trace Store */) \
m_(bool,  acpi,			/* ACPI via MSR */) \
m_(bool,  pbe,			/* Pending Break Enable */) \
m_(bool,  mmx,			/* Multimedia Extensions */) \
m_(bool,  fxsr,			/* FXSAVE and FXRSTOR instructions (fast save and restore of FPU context), and CR4.OSFXSR available */) \
m_(bool,  sse,			/* Streaming SIMD Extensions */) \
m_(bool,  sse2,			/* Streaming SIMD Extensions 2 */) \
m_(bool,  ss,			/* CPU self snoop */) \
m_(bool,  htt,			/* Hyper-Threading */) \
m_(bool,  acc,			/* Automatic clock control */) \
m_(bool,  syscall,		/* SYSCALL/SYSRET */) \
m_(bool,  mp,			/* MP Capable. */) \
m_(bool,  nx,			/* Execute Disable */) \
m_(bool,  mmxext,		/* AMD MMX extensions */) \
m_(bool,  fxsr_opt,		/* FXSAVE/FXRSTOR optimizations */) \
m_(bool,  gbpages,		/* "pdpe1gb" GB pages */) \
m_(bool,  rdtscp,		/* RDTSCP */) \
m_(bool,  lm,			/* Long Mode (x86-64) */) \
m_(bool,  nowext,		/* AMD 3DNow! extensions */) \
m_(bool,  now,			/* 3DNow! */) \
m_(bool,  smp,			/* A smp configuration has been found */) \
m_(bool,  pni,			/* Streaming SIMD Extensions-3 */) \
m_(bool,  pclmulqd,		/* PCLMULQDQ instruction */) \
m_(bool,  dtes64,		/* 64-bit Debug Store */) \
m_(bool,  vmx,			/* Hardware virtualization */) \
m_(bool,  smx,			/* Safer Mode */) \
m_(bool,  est,			/* Enhanced SpeedStep */) \
m_(bool,  tm2,			/* Thermal Monitor 2  */) \
m_(bool,  sse3,			/* Supplemental SSE-3 */) \
m_(bool,  cid,			/* Context ID */) \
m_(bool,  fma,			/* Fused multiply-add  */) \
m_(bool,  cx16,			/* CMPXCHG16B */) \
m_(bool,  xtpr,			/* Send Task Priority Messages */) \
m_(bool,  pdcm,			/* Performance Capabilities  */) \
m_(bool,  dca,			/* Direct Cache Access */) \
m_(bool,  xmm4_1,		/* "sse4_1" SSE-4.1 */) \
m_(bool,  xmm4_2,		/* "sse4_2" SSE-4.2 */) \
m_(bool,  x2apic,		/* x2APIC */) \
m_(bool,  movbe,			/* MOVBE instruction */) \
m_(bool,  popcnt,		/* POPCNT instruction */) \
m_(bool,  aes,			/* AES Instruction */) \
m_(bool,  xsave,			/* XSAVE/XRSTOR/XSETBV/XGETBV */) \
m_(bool,  osxsave,		/* XSAVE enabled in the OS */) \
m_(bool,  avx,			/* Advanced Vector Extensions */) \
m_(bool,  hypervisor,		/* Running on a hypervisor */) \
m_(bool,  ace2,			/* Advanced Cryptography Engine v2 */) \
m_(bool,  ace2_en,		/* ACE v2 enabled */) \
m_(bool,  phe,			/* PadLock Hash Engine */) \
m_(bool,  phe_en,		/* PadLock Hash Engine Enabled */) \
m_(bool,  pmm,			/* PadLock Montgomery Multiplier */) \
m_(bool,  pmm_en,		/* PadLock Montgomery Multiplier enabled */) \
m_(bool,  svm,			/* Secure virtual machine */) \
m_(bool,  extapic,		/* Extended APIC space */) \
m_(bool,  cr8_legacy,		/* CR8 in 32-bit mode */) \
m_(bool,  abm,			/* Advanced bit manipulation */) \
m_(bool,  sse4a,			/* SSE4-A */) \
m_(bool,  misalignsse,		/* Misaligned SSE mode */) \
m_(bool,  nowprefetch,		/* 3DNow prefetch instructions */) \
m_(bool,  osvw,			/* OS Visible Workaround */) \
m_(bool,  ibs,			/*  Instruction Based Sampling */) \
m_(bool,  sse5,			/* SSE5 */) \
m_(bool,  skinit,		/* SKINIT/STGI instructions */) \
m_(bool,  wdt,			/* Watchdog Timer */) \
m_(bool,  ida,			/* Intel Dynamic Acceleration */) \
m_(bool,  arat,			/* Always Running APIC Timer */) \
m_(bool,  tpr_shadow,		/* Intel TPR Shadow */) \
m_(bool,  vnmi,			/* Intel Virtual NMI */) \
m_(bool,  flexpriority,		/* Intel FlexPriority */) \
m_(bool,  ept,			/* Intel Extended Page Table */) \
m_(bool,  vpid,			/* Intel Virtual Processor ID */)

#define STRUCT_MEMBERS(type_, name_, comment_) type_ name_;

#define STRUCT_MEMBER_NAMES(type_, name_, comment_) #name_ , 

#define STRUCTURE_MEMBER_OFFSETS(type_, name_, comment_) \
	  offsetof(s_cpu_flags, name_),

typedef struct {
    CPU_FLAGS(STRUCT_MEMBERS)
} s_cpu_flags;

extern size_t cpu_flags_offset[];
extern const char *cpu_flags_names[];
extern size_t cpu_flags_count;

typedef struct {
    char vendor[CPU_VENDOR_SIZE];
    uint8_t vendor_id;
    uint8_t family;
    char model[CPU_MODEL_SIZE];
    uint8_t model_id;
    uint8_t stepping;
    uint8_t num_cores;
    uint16_t l1_data_cache_size;
    uint16_t l1_instruction_cache_size;
    uint16_t l2_cache_size;
    s_cpu_flags flags;
} s_cpu;

extern bool get_cpu_flag_value_from_name(s_cpu *cpu, const char * flag);
/**********************************************************************************/
/**********************************************************************************/
/* From this point this is some internal stuff mainly taken from the linux kernel */
/**********************************************************************************/
/**********************************************************************************/

/*
 * EFLAGS bits
 */
#define X86_EFLAGS_CF   0x00000001	/* Carry Flag */
#define X86_EFLAGS_PF   0x00000004	/* Parity Flag */
#define X86_EFLAGS_AF   0x00000010	/* Auxillary carry Flag */
#define X86_EFLAGS_ZF   0x00000040	/* Zero Flag */
#define X86_EFLAGS_SF   0x00000080	/* Sign Flag */
#define X86_EFLAGS_TF   0x00000100	/* Trap Flag */
#define X86_EFLAGS_IF   0x00000200	/* Interrupt Flag */
#define X86_EFLAGS_DF   0x00000400	/* Direction Flag */
#define X86_EFLAGS_OF   0x00000800	/* Overflow Flag */
#define X86_EFLAGS_IOPL 0x00003000	/* IOPL mask */
#define X86_EFLAGS_NT   0x00004000	/* Nested Task */
#define X86_EFLAGS_RF   0x00010000	/* Resume Flag */
#define X86_EFLAGS_VM   0x00020000	/* Virtual Mode */
#define X86_EFLAGS_AC   0x00040000	/* Alignment Check */
#define X86_EFLAGS_VIF  0x00080000	/* Virtual Interrupt Flag */
#define X86_EFLAGS_VIP  0x00100000	/* Virtual Interrupt Pending */
#define X86_EFLAGS_ID   0x00200000	/* CPUID detection flag */

#define X86_VENDOR_INTEL 0
#define X86_VENDOR_CYRIX 1
#define X86_VENDOR_AMD 2
#define X86_VENDOR_UMC 3
#define X86_VENDOR_NEXGEN 4
#define X86_VENDOR_CENTAUR 5
#define X86_VENDOR_RISE 6
#define X86_VENDOR_TRANSMETA 7
#define X86_VENDOR_NSC 8
#define X86_VENDOR_UNKNOWN 9 
#define X86_VENDOR_NUM 10 

#define cpu_has(c, bit)                test_bit(bit, (c)->x86_capability)

// Taken from asm/processor-flags.h
// NSC/Cyrix CPU configuration register indexes
#define CX86_CCR2       0xc2
#define CX86_CCR3	0xc3
#define CX86_DIR0       0xfe
#define CX86_DIR1       0xff

static const char Cx86_model[][9] = {
	"Cx486", "Cx486", "5x86 ", "6x86", "MediaGX ", "6x86MX ",
	"M II ", "Unknown"
};

static const char Cx486_name[][5] = {
	"SLC", "DLC", "SLC2", "DLC2", "SRx", "DRx",
	"SRx2", "DRx2"
};

static const char Cx486S_name[][4] = {
	"S", "S2", "Se", "S2e"
};

static const char Cx486D_name[][4] = {
	"DX", "DX2", "?", "?", "?", "DX4"
};


/*
 *  CPU type and hardware bug flags. Kept separately for each CPU.
 *  Members of this structure are referenced in head.S, so think twice
 *  before touching them. [mj]
 */

struct cpuinfo_x86 {
    uint8_t x86;		/* CPU family */
    uint8_t x86_vendor;		/* CPU vendor */
    uint8_t x86_model;
    uint8_t x86_mask;
    char wp_works_ok;		/* It doesn't on 386's */
    char hlt_works_ok;		/* Problems on some 486Dx4's and old 386's */
    char hard_math;
    char rfu;
    int cpuid_level;		/* Maximum supported CPUID level, -1=no CPUID */
    uint32_t x86_capability[NCAPINTS];
    char x86_vendor_id[16];
    char x86_model_id[64];
    uint16_t x86_l1_data_cache_size;	/* in KB, if available */
    uint16_t x86_l1_instruction_cache_size;	/* in KB, if available */
    uint16_t x86_l2_cache_size;	/* in KB, if available */
    int x86_cache_alignment;	/* in bytes */
    char fdiv_bug;
    char f00f_bug;
    char coma_bug;
    char pad0;
    int x86_power;
    unsigned long loops_per_jiffy;
#ifdef CONFIG_SMP
    cpumask_t llc_shared_map;	/* cpus sharing the last level cache */
#endif
    unsigned char x86_num_cores;	/* cpuid returned the number of cores */
    unsigned char booted_cores;	/* number of cores as seen by OS */
    unsigned char apicid;
    unsigned char x86_clflush_size;

} __attribute__ ((__packed__));

struct cpu_model_info {
    int vendor;
    int family;
    char *model_names[16];
};

/* attempt to consolidate cpu attributes */
struct cpu_dev {
    const char *c_vendor;

    /* some have two possibilities for cpuid string */
    const char *c_ident[2];

    struct cpu_model_info c_models[4];

    void (*c_init) (struct cpuinfo_x86 * c);
    void (*c_identify) (struct cpuinfo_x86 * c);
    unsigned int (*c_size_cache) (struct cpuinfo_x86 * c, unsigned int size);
};

/*
 * Structure definitions for SMP machines following the
 * Intel Multiprocessing Specification 1.1 and 1.4.
 */

/*
 * This tag identifies where the SMP configuration
 * information is.
 */

#define SMP_MAGIC_IDENT (('_'<<24)|('P'<<16)|('M'<<8)|'_')

struct intel_mp_floating {
    char mpf_signature[4];	/* "_MP_"                       */
    uint32_t mpf_physptr;	/* Configuration table address  */
    uint8_t mpf_length;		/* Our length (paragraphs)      */
    uint8_t mpf_specification;	/* Specification version        */
    uint8_t mpf_checksum;	/* Checksum (makes sum 0)       */
    uint8_t mpf_feature1;	/* Standard or configuration ?  */
    uint8_t mpf_feature2;	/* Bit7 set for IMCR|PIC        */
    uint8_t mpf_feature3;	/* Unused (0)                   */
    uint8_t mpf_feature4;	/* Unused (0)                   */
    uint8_t mpf_feature5;	/* Unused (0)                   */
};

static inline uint8_t getCx86(uint8_t reg) {
	outb(reg, 0x22);
	return inb(0x23);
}

static inline void setCx86(uint8_t reg, uint8_t data) {
	outb(reg, 0x22);
	outb(data, 0x23);
}

extern void get_cpu_vendor(struct cpuinfo_x86 *c);
extern void detect_cpu(s_cpu * cpu);
#endif
