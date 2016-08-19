/**
 * syslinux/module.h
 *
 * Dynamic ELF modules definitions and services.
 */

#ifndef I386_MODULE_H_
#define I386_MODULE_H_

#include <elf.h>

/*
 * Accepted values for various ELF header parameters found in an ELF dynamic
 * object.
 */
#define MODULE_ELF_CLASS		ELFCLASS32		// 32-bit modules
#define MODULE_ELF_CLASS_SIZE		32			// Size of a word value
#define MODULE_ELF_DATA			ELFDATA2LSB		// Word endianess
#define MODULE_ELF_VERSION		EV_CURRENT		// Object version
#define MODULE_ELF_TYPE			ET_DYN			// Executable type (shared object - .so)
#define MODULE_ELF_MACHINE		EM_386			// Target architecture

#define ELF_MOD_SYS		"32 bit"

typedef Elf32_Addr		Elf_Addr;
typedef Elf32_Dyn		Elf_Dyn;
typedef Elf32_Word		Elf_Word;
typedef Elf32_Off		Elf_Off;
typedef Elf32_Sym		Elf_Sym;
typedef Elf32_Ehdr		Elf_Ehdr;
typedef Elf32_Phdr		Elf_Phdr;
typedef Elf32_Rel		Elf_Rel;
typedef Elf32_Word		Elf_Bword;

#endif // I386_MODULE_H_
