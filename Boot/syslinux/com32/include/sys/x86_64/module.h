/**
 * syslinux/module.h
 *
 * Dynamic ELF64 modules definitions and services.
 */

#ifndef _X86_64_MODULE_H_
#define _X86_64_MODULE_H_

#include <elf.h>

/*
 * Accepted values for various ELF header parameters found in an ELF dynamic
 * object.
 */
#define MODULE_ELF_CLASS		ELFCLASS64		// 64-bit modules
#define MODULE_ELF_CLASS_SIZE		64			// Size of a word value
#define MODULE_ELF_DATA			ELFDATA2LSB		// Word endianess
#define MODULE_ELF_VERSION		EV_CURRENT		// Object version
#define MODULE_ELF_TYPE			ET_DYN			// Executable type (shared object - .so)
#define MODULE_ELF_MACHINE		EM_X86_64		// Target architecture

#define ELF_MOD_SYS		"64 bit"

typedef Elf64_Addr		Elf_Addr;
typedef Elf64_Dyn		Elf_Dyn;
typedef Elf64_Word		Elf_Word;
typedef Elf64_Off		Elf_Off;
typedef Elf64_Sym		Elf_Sym;
typedef Elf64_Ehdr		Elf_Ehdr;
typedef Elf64_Phdr		Elf_Phdr;
typedef Elf64_Rel		Elf_Rel;
typedef Elf64_Xword		Elf_Bword;

#endif // _X86_64_MODULE_H_
