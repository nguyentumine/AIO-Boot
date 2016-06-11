/*
 * sys/elfcommon.h
 */

#ifndef _SYS_ELFCOMMON_H
#define _SYS_ELFCOMMON_H

#include <stdint.h>

/* Segment types */
#define PT_NULL		0
#define PT_LOAD		1
#define PT_DYNAMIC	2
#define PT_INTERP	3
#define PT_NOTE		4
#define PT_SHLIB	5
#define PT_PHDR		6
#define PT_LOOS		0x60000000
#define PT_HIOS		0x6fffffff
#define PT_LOPROC	0x70000000
#define PT_HIPROC	0x7fffffff
#define PT_GNU_EH_FRAME	0x6474e550	/* Extension, eh? */

/* ELF file types */
#define ET_NONE		0
#define ET_REL		1
#define ET_EXEC		2
#define ET_DYN		3
#define ET_CORE		4
#define ET_LOPROC	0xff00
#define ET_HIPROC	0xffff

/* ELF machine types */
#define EM_NONE		0
#define EM_M32		1
#define EM_SPARC	2
#define EM_386		3
#define EM_68K		4
#define EM_88K		5
#define EM_486		6	/* Not used in Linux at least */
#define EM_860		7
#define EM_MIPS         8	/* R3k, bigendian(?) */
#define EM_MIPS_RS4_BE	10	/* R4k BE */
#define EM_PARISC	15
#define EM_SPARC32PLUS	18
#define EM_PPC		20
#define EM_PPC64	21
#define EM_S390         22
#define EM_SH		42
#define EM_SPARCV9	43	/* v9 = SPARC64 */
#define EM_H8_300H      47
#define EM_H8S          48
#define EM_IA_64        50	/* Itanic */
#define EM_X86_64       62
#define EM_CRIS         76
#define EM_V850         87
#define EM_ALPHA        0x9026	/* Interrim Alpha that stuck around */
#define EM_CYGNUS_V850  0x9080	/* Old v850 ID used by Cygnus */
#define EM_S390_OLD     0xA390	/* Obsolete interrim value for S/390 */

/* Dynamic type values */
#define DT_NULL		0		/* Marks end of dynamic section */
#define DT_NEEDED	1		/* Name of needed library */
#define DT_PLTRELSZ	2		/* Size in bytes of PLT relocs */
#define DT_PLTGOT	3		/* Processor defined value */
#define DT_HASH		4		/* Address of symbol hash table */
#define DT_STRTAB	5		/* Address of string table */
#define DT_SYMTAB	6		/* Address of symbol table */
#define DT_RELA		7		/* Address of Rela relocs */
#define DT_RELASZ	8		/* Total size of Rela relocs */
#define DT_RELAENT	9		/* Size of one Rela reloc */
#define DT_STRSZ	10		/* Size of string table */
#define DT_SYMENT	11		/* Size of one symbol table entry */
#define DT_INIT		12		/* Address of init function */
#define DT_FINI		13		/* Address of termination function */
#define DT_SONAME	14		/* Name of shared object */
#define DT_RPATH	15		/* Library search path (deprecated) */
#define DT_SYMBOLIC	16		/* Start symbol search here */
#define DT_REL		17		/* Address of Rel relocs */
#define DT_RELSZ	18		/* Total size of Rel relocs */
#define DT_RELENT	19		/* Size of one Rel reloc */
#define DT_PLTREL	20		/* Type of reloc in PLT */
#define DT_DEBUG	21		/* For debugging; unspecified */
#define DT_TEXTREL	22		/* Reloc might modify .text */
#define DT_JMPREL	23		/* Address of PLT relocs */
#define	DT_BIND_NOW	24		/* Process relocations of object */
#define	DT_INIT_ARRAY	25		/* Array with addresses of init fct */
#define	DT_FINI_ARRAY	26		/* Array with addresses of fini fct */
#define	DT_INIT_ARRAYSZ	27		/* Size in bytes of DT_INIT_ARRAY */
#define	DT_FINI_ARRAYSZ	28		/* Size in bytes of DT_FINI_ARRAY */
#define DT_RUNPATH	29		/* Library search path */
#define DT_FLAGS	30		/* Flags for the object being loaded */
#define DT_ENCODING	32		/* Start of encoded range */
#define DT_PREINIT_ARRAY 32		/* Array with addresses of preinit fct*/
#define DT_PREINIT_ARRAYSZ 33		/* size in bytes of DT_PREINIT_ARRAY */
#define	DT_NUM		34		/* Number used */
#define DT_LOOS		0x6000000d	/* Start of OS-specific */
#define DT_HIOS		0x6ffff000	/* End of OS-specific */
#define DT_LOPROC	0x70000000	/* Start of processor-specific */
#define DT_HIPROC	0x7fffffff	/* End of processor-specific */

#define DT_VALRNGLO	0x6ffffd00
#define DT_GNU_PRELINKED 0x6ffffdf5	/* Prelinking timestamp */
#define DT_GNU_CONFLICTSZ 0x6ffffdf6	/* Size of conflict section */
#define DT_GNU_LIBLISTSZ 0x6ffffdf7	/* Size of library list */
#define DT_CHECKSUM	0x6ffffdf8
#define DT_PLTPADSZ	0x6ffffdf9
#define DT_MOVEENT	0x6ffffdfa
#define DT_MOVESZ	0x6ffffdfb
#define DT_FEATURE_1	0x6ffffdfc	/* Feature selection (DTF_*).  */
#define DT_POSFLAG_1	0x6ffffdfd	/* Flags for DT_* entries, effecting
					   the following DT_* entry.  */
#define DT_SYMINSZ	0x6ffffdfe	/* Size of syminfo table (in bytes) */
#define DT_SYMINENT	0x6ffffdff	/* Entry size of syminfo */
#define DT_VALRNGHI	0x6ffffdff
#define DT_VALTAGIDX(tag)	(DT_VALRNGHI - (tag))	/* Reverse order! */
#define DT_VALNUM 12

/* DT_* entries which fall between DT_ADDRRNGHI & DT_ADDRRNGLO use the
   Dyn.d_un.d_ptr field of the Elf*_Dyn structure.

   If any adjustment is made to the ELF object after it has been
   built these entries will need to be adjusted.  */
#define DT_ADDRRNGLO	0x6ffffe00
#define DT_GNU_HASH	0x6ffffef5	/* GNU-style hash table.  */
#define DT_TLSDESC_PLT	0x6ffffef6
#define DT_TLSDESC_GOT	0x6ffffef7
#define DT_GNU_CONFLICT	0x6ffffef8	/* Start of conflict section */
#define DT_GNU_LIBLIST	0x6ffffef9	/* Library list */
#define DT_CONFIG	0x6ffffefa	/* Configuration information.  */
#define DT_DEPAUDIT	0x6ffffefb	/* Dependency auditing.  */
#define DT_AUDIT	0x6ffffefc	/* Object auditing.  */
#define	DT_PLTPAD	0x6ffffefd	/* PLT padding.  */
#define	DT_MOVETAB	0x6ffffefe	/* Move table.  */
#define DT_SYMINFO	0x6ffffeff	/* Syminfo table.  */
#define DT_ADDRRNGHI	0x6ffffeff
#define DT_ADDRTAGIDX(tag)	(DT_ADDRRNGHI - (tag))	/* Reverse order! */
#define DT_ADDRNUM 11

/* The versioning entry types.  The next are defined as part of the
   GNU extension.  */
#define DT_VERSYM	0x6ffffff0

#define DT_RELACOUNT	0x6ffffff9
#define DT_RELCOUNT	0x6ffffffa

/* These were chosen by Sun.  */
#define DT_FLAGS_1	0x6ffffffb	/* State flags, see DF_1_* below.  */
#define	DT_VERDEF	0x6ffffffc	/* Address of version definition
					   table */
#define	DT_VERDEFNUM	0x6ffffffd	/* Number of version definitions */
#define	DT_VERNEED	0x6ffffffe	/* Address of table with needed
					   versions */
#define	DT_VERNEEDNUM	0x6fffffff	/* Number of needed versions */
#define DT_VERSIONTAGIDX(tag)	(DT_VERNEEDNUM - (tag))	/* Reverse order! */
#define DT_VERSIONTAGNUM 16

/* Sun added these machine-independent extensions in the "processor-specific"
   range.  Be compatible.  */
#define DT_AUXILIARY    0x7ffffffd      /* Shared object to load before self */
#define DT_FILTER       0x7fffffff      /* Shared object to get values from */
#define DT_EXTRATAGIDX(tag)	((Elf32_Word)-((Elf32_Sword) (tag) <<1>>1)-1)
#define DT_EXTRANUM	3

/* Auxilliary table entries */
#define AT_NULL		0	/* end of vector */
#define AT_IGNORE	1	/* entry should be ignored */
#define AT_EXECFD	2	/* file descriptor of program */
#define AT_PHDR		3	/* program headers for program */
#define AT_PHENT	4	/* size of program header entry */
#define AT_PHNUM	5	/* number of program headers */
#define AT_PAGESZ	6	/* system page size */
#define AT_BASE		7	/* base address of interpreter */
#define AT_FLAGS	8	/* flags */
#define AT_ENTRY	9	/* entry point of program */
#define AT_NOTELF	10	/* program is not ELF */
#define AT_UID		11	/* real uid */
#define AT_EUID		12	/* effective uid */
#define AT_GID		13	/* real gid */
#define AT_EGID		14	/* effective gid */
#define AT_PLATFORM	15	/* string identifying CPU for optimizations */
#define AT_HWCAP	16	/* arch dependent hints at CPU capabilities */
#define AT_CLKTCK	17	/* frequency at which times() increments */
/* 18..22 = ? */
#define AT_SECURE	23	/* secure mode boolean */

/* Program header permission flags */
#define PF_X            0x1
#define PF_W            0x2
#define PF_R            0x4

/* Section header types */
#define SHT_NULL        0
#define SHT_PROGBITS    1
#define SHT_SYMTAB      2
#define SHT_STRTAB      3
#define SHT_RELA        4
#define SHT_HASH        5
#define SHT_DYNAMIC     6
#define SHT_NOTE        7
#define SHT_NOBITS      8
#define SHT_REL         9
#define SHT_SHLIB       10
#define SHT_DYNSYM      11
#define SHT_NUM         12
#define SHT_LOPROC      0x70000000
#define SHT_HIPROC      0x7fffffff
#define SHT_LOUSER      0x80000000
#define SHT_HIUSER      0xffffffff

/* Section header flags */
#define SHF_WRITE       0x1
#define SHF_ALLOC       0x2
#define SHF_EXECINSTR   0x4
#define SHF_MASKPROC    0xf0000000

/* Special section numbers */
#define SHN_UNDEF       0
#define SHN_LORESERVE   0xff00
#define SHN_LOPROC      0xff00
#define SHN_HIPROC      0xff1f
#define SHN_ABS         0xfff1
#define SHN_COMMON      0xfff2
#define SHN_HIRESERVE   0xffff

/* Symbol table definitions */

/* How to extract and insert information held in the st_info field.  */

#define ELF32_ST_BIND(val)		(((unsigned char) (val)) >> 4)
#define ELF32_ST_TYPE(val)		((val) & 0xf)
#define ELF32_ST_INFO(bind, type)	(((bind) << 4) + ((type) & 0xf))

/* Both Elf32_Sym and Elf64_Sym use the same one-byte st_info field.  */
#define ELF64_ST_BIND(val)		ELF32_ST_BIND (val)
#define ELF64_ST_TYPE(val)		ELF32_ST_TYPE (val)
#define ELF64_ST_INFO(bind, type)	ELF32_ST_INFO ((bind), (type))

/* Legal values for ST_BIND subfield of st_info (symbol binding).  */

#define STB_LOCAL	0		/* Local symbol */
#define STB_GLOBAL	1		/* Global symbol */
#define STB_WEAK	2		/* Weak symbol */
#define	STB_NUM		3		/* Number of defined types.  */
#define STB_LOOS	10		/* Start of OS-specific */
#define STB_HIOS	12		/* End of OS-specific */
#define STB_LOPROC	13		/* Start of processor-specific */
#define STB_HIPROC	15		/* End of processor-specific */

/* Legal values for ST_TYPE subfield of st_info (symbol type).  */

#define STT_NOTYPE	0		/* Symbol type is unspecified */
#define STT_OBJECT	1		/* Symbol is a data object */
#define STT_FUNC	2		/* Symbol is a code object */
#define STT_SECTION	3		/* Symbol associated with a section */
#define STT_FILE	4		/* Symbol's name is file name */
#define STT_COMMON	5		/* Symbol is a common data object */
#define STT_TLS		6		/* Symbol is thread-local data object*/
#define	STT_NUM		7		/* Number of defined types.  */
#define STT_LOOS	10		/* Start of OS-specific */
#define STT_HIOS	12		/* End of OS-specific */
#define STT_LOPROC	13		/* Start of processor-specific */
#define STT_HIPROC	15		/* End of processor-specific */


/* Symbol table indices are found in the hash buckets and chain table
   of a symbol hash table section.  This special index value indicates
   the end of a chain, meaning no further symbols are found in that bucket.  */

#define STN_UNDEF	0		/* End of a chain.  */

/* Lenght of magic at the start of a file */
#define EI_NIDENT	16

/* Magic number constants... */
#define EI_MAG0         0	/* e_ident[] indexes */
#define EI_MAG1         1
#define EI_MAG2         2
#define EI_MAG3         3
#define EI_CLASS        4
#define EI_DATA         5
#define EI_VERSION      6
#define EI_OSABI        7
#define EI_PAD          8

#define ELFMAG0         0x7f	/* EI_MAG */
#define ELFMAG1         'E'
#define ELFMAG2         'L'
#define ELFMAG3         'F'
#define ELFMAG          "\177ELF"
#define SELFMAG         4

#define ELFCLASSNONE    0	/* EI_CLASS */
#define ELFCLASS32      1
#define ELFCLASS64      2
#define ELFCLASSNUM     3

#define ELFDATANONE     0	/* e_ident[EI_DATA] */
#define ELFDATA2LSB     1
#define ELFDATA2MSB     2

#define EV_NONE         0	/* e_version, EI_VERSION */
#define EV_CURRENT      1
#define EV_NUM          2

#define ELFOSABI_NONE   0
#define ELFOSABI_LINUX  3

/* Intel 80386 specific definitions.  */

/* i386 relocs.  */

#define R_386_NONE	   0		/* No reloc */
#define R_386_32	   1		/* Direct 32 bit  */
#define R_386_PC32	   2		/* PC relative 32 bit */
#define R_386_GOT32	   3		/* 32 bit GOT entry */
#define R_386_PLT32	   4		/* 32 bit PLT address */
#define R_386_COPY	   5		/* Copy symbol at runtime */
#define R_386_GLOB_DAT	   6		/* Create GOT entry */
#define R_386_JMP_SLOT	   7		/* Create PLT entry */
#define R_386_RELATIVE	   8		/* Adjust by program base */
#define R_386_GOTOFF	   9		/* 32 bit offset to GOT */
#define R_386_GOTPC	   10		/* 32 bit PC relative offset to GOT */
#define R_386_32PLT	   11
#define R_386_TLS_TPOFF	   14		/* Offset in static TLS block */
#define R_386_TLS_IE	   15		/* Address of GOT entry for static TLS
					   block offset */
#define R_386_TLS_GOTIE	   16		/* GOT entry for static TLS block
					   offset */
#define R_386_TLS_LE	   17		/* Offset relative to static TLS
					   block */
#define R_386_TLS_GD	   18		/* Direct 32 bit for GNU version of
					   general dynamic thread local data */
#define R_386_TLS_LDM	   19		/* Direct 32 bit for GNU version of
					   local dynamic thread local data
					   in LE code */
#define R_386_16	   20
#define R_386_PC16	   21
#define R_386_8		   22
#define R_386_PC8	   23
#define R_386_TLS_GD_32	   24		/* Direct 32 bit for general dynamic
					   thread local data */
#define R_386_TLS_GD_PUSH  25		/* Tag for pushl in GD TLS code */
#define R_386_TLS_GD_CALL  26		/* Relocation for call to
					   __tls_get_addr() */
#define R_386_TLS_GD_POP   27		/* Tag for popl in GD TLS code */
#define R_386_TLS_LDM_32   28		/* Direct 32 bit for local dynamic
					   thread local data in LE code */
#define R_386_TLS_LDM_PUSH 29		/* Tag for pushl in LDM TLS code */
#define R_386_TLS_LDM_CALL 30		/* Relocation for call to
					   __tls_get_addr() in LDM code */
#define R_386_TLS_LDM_POP  31		/* Tag for popl in LDM TLS code */
#define R_386_TLS_LDO_32   32		/* Offset relative to TLS block */
#define R_386_TLS_IE_32	   33		/* GOT entry for negated static TLS
					   block offset */
#define R_386_TLS_LE_32	   34		/* Negated offset relative to static
					   TLS block */
#define R_386_TLS_DTPMOD32 35		/* ID of module containing symbol */
#define R_386_TLS_DTPOFF32 36		/* Offset in TLS block */
#define R_386_TLS_TPOFF32  37		/* Negated offset in static TLS block */
/* Keep this the last entry.  */
#define R_386_NUM	   38

/* AMD x86-64 relocations.  */
#define R_X86_64_NONE		0	/* No reloc */
#define R_X86_64_64		1	/* Direct 64 bit  */
#define R_X86_64_PC32		2	/* PC relative 32 bit signed */
#define R_X86_64_GOT32		3	/* 32 bit GOT entry */
#define R_X86_64_PLT32		4	/* 32 bit PLT address */
#define R_X86_64_COPY		5	/* Copy symbol at runtime */
#define R_X86_64_GLOB_DAT	6	/* Create GOT entry */
#define R_X86_64_JUMP_SLOT	7	/* Create PLT entry */
#define R_X86_64_RELATIVE	8	/* Adjust by program base */
#define R_X86_64_GOTPCREL	9	/* 32 bit signed PC relative
					   offset to GOT */
#define R_X86_64_32		10	/* Direct 32 bit zero extended */
#define R_X86_64_32S		11	/* Direct 32 bit sign extended */
#define R_X86_64_16		12	/* Direct 16 bit zero extended */
#define R_X86_64_PC16		13	/* 16 bit sign extended pc relative */
#define R_X86_64_8		14	/* Direct 8 bit sign extended  */
#define R_X86_64_PC8		15	/* 8 bit sign extended pc relative */
#define R_X86_64_DTPMOD64	16	/* ID of module containing symbol */
#define R_X86_64_DTPOFF64	17	/* Offset in module's TLS block */
#define R_X86_64_TPOFF64	18	/* Offset in initial TLS block */
#define R_X86_64_TLSGD		19	/* 32 bit signed PC relative offset
					   to two GOT entries for GD symbol */
#define R_X86_64_TLSLD		20	/* 32 bit signed PC relative offset
					   to two GOT entries for LD symbol */
#define R_X86_64_DTPOFF32	21	/* Offset in TLS block */
#define R_X86_64_GOTTPOFF	22	/* 32 bit signed PC relative offset
					   to GOT entry for IE symbol */
#define R_X86_64_TPOFF32	23	/* Offset in initial TLS block */
#define R_X86_64_PC64		24	/* PC relative 64 bit */
#define R_X86_64_GOTOFF64	25	/* 64 bit offset to GOT */
#define R_X86_64_GOTPC32	26	/* 32 bit signed pc relative
					   offset to GOT */
#define R_X86_64_GOT64		27	/* 64-bit GOT entry offset */
#define R_X86_64_GOTPCREL64	28	/* 64-bit PC relative offset
					   to GOT entry */
#define R_X86_64_GOTPC64	29	/* 64-bit PC relative offset to GOT */
#define R_X86_64_GOTPLT64	30 	/* like GOT64, says PLT entry needed */
#define R_X86_64_PLTOFF64	31	/* 64-bit GOT relative offset
					   to PLT entry */
#define R_X86_64_SIZE32		32	/* Size of symbol plus 32-bit addend */
#define R_X86_64_SIZE64		33	/* Size of symbol plus 64-bit addend */
#define R_X86_64_GOTPC32_TLSDESC 34	/* GOT offset for TLS descriptor.  */
#define R_X86_64_TLSDESC_CALL   35	/* Marker for call through TLS
					   descriptor.  */
#define R_X86_64_TLSDESC        36	/* TLS descriptor.  */
#define R_X86_64_IRELATIVE	37	/* Adjust indirectly by program base */

#define R_X86_64_NUM		38

#endif				/* _SYS_ELFCOMMON_H */
