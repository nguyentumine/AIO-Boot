/**
 * syslinux/module.h
 *
 * Dynamic ELF modules definitions and services.
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <stdio.h>
#include <elf.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdbool.h>
#include <linux/list.h>

#if __SIZEOF_POINTER__ == 4
#include <i386/module.h>
#elif __SIZEOF_POINTER__ == 8
#include <x86_64/module.h>
#else
#error "unsupported architecture"
#endif

/*
 * The maximum length of the module file name (including path), stored
 * in the struct module descriptor.
 */
#define MODULE_NAME_SIZE		256

/*
 * Some common information about what kind of modules we're dealing with
 */
#define EXEC_MODULE			0		
#define LIB_MODULE			1

#define MAX_NR_DEPS			64

/*
 * Initialization and finalization function signatures
 */

/**
 * module_main_t - pointer to an entry routine
 *
 * The entry routine is present only in executable modules, and represents
 * the entry point for the program.
 */
typedef int (*module_main_t)(int, char**);

/**
 * module_ctor_t - pointer to a constructor or destructor routine
 *
 * A module may have multiple routines that need to be executed before
 * or after the main routine. These are the constructors and
 * destructors, respectively.
 */
typedef void (*module_ctor_t) (void);

/**
 * struct elf_module - structure encapsulating a module loaded in memory.
 *
 * Each SYSLINUX ELF module must have an associated struct elf_module descriptor
 * that keeps track of memory allocations, symbol information, and various other
 * resources needed by the module itself or by other modules that depend on it.
 *
 * There are two types of modules:
 *  - regular modules, which are actual memory images of a loaded & linked shared
 *  object (ELF file). Memory is reserved for the struct elf_module structure itself
 *  and for the object loadable sections read from the file.
 *  - shallow modules, which are not associated with an ELF shared object, but contain
 *  metainformation about a memory region already present and containing the
 *  actual code and data. One particular usage of shallow modules is to access
 *  symbol information from the root COM32 module loaded by the SYSLINUX core.
 *  As their name suggests, memory is reserved only for the elf_module structure
 *  itself and optionally for a usually small memory region containing metainformation
 *  (symbol information).
 *
 *  Module descriptors are related to each other through dependency information. A module
 *  can depend on symbols from other modules, and in turn it can provide symbols used
 *  by other dependant modules. This relationship can be described as a directed
 *  acyclic graph (DAG). The graph is stored using double linked lists of
 *  predecessors and successors. There is also a global linked list containing all
 *  the modules currently loaded.
 */
struct atexit;
struct elf_module {
	char				name[MODULE_NAME_SIZE]; 		// The module name

	bool			shallow;	// Whether the module contains any code

	struct list_head	required;		// Head of the required modules list
	struct list_head	dependants;		// Head of module dependants list
	struct list_head	list;		// The list entry in the module list

	module_ctor_t		*ctors;		// module constructors
	module_ctor_t		*dtors;		// module destructors
	module_main_t		main_func; // The main function (for executable modules)

	void				*module_addr; // The module location in the memory
	Elf_Addr			base_addr;	// The base address of the module
	Elf_Word			module_size; // The module size in memory

	Elf_Word			*hash_table;	// The symbol hash table
	Elf_Word			*ghash_table;	// The GNU style hash table
	char				*str_table;		// The string table
	void 				*sym_table;		// The symbol table
	void				*got;			// The Global Offset Table
	Elf_Dyn			*dyn_table;		// Dynamic loading information table

	Elf_Word			strtable_size;	// The size of the string table
	Elf_Word			syment_size;	// The size of a symbol entry
	Elf_Word			symtable_size;	// The size of the symbol table


	union {
		// Transient - Data available while the module is loading
		struct {
			FILE		*_file;		// The file object of the open file
			Elf_Off	_cr_offset;	// The current offset in the open file
		} l;

		// Process execution data
		struct {
			jmp_buf		process_exit;	// Exit state
			struct atexit  *atexit_list;	// atexit() chain
		} x;
	} u;

	// ELF DT_NEEDED entries for this module
	int				nr_needed;
	Elf_Word			needed[MAX_NR_DEPS];
};

/**
 * struct module_dep - structure encapsulating a module dependency need
 *
 * This structure represents an item in a double linked list of predecessors or
 * successors. The item contents is a pointer to the corresponding module descriptor.
 */
struct module_dep {
	struct list_head	list;		// The list entry in the dependency list

	struct elf_module	*module;	// The target module descriptor
};


/**
 * Unload all modules that have been loaded since @name.
 *
 * Returns the struct elf_module * for @name or %NULL if no modules
 * have been loaded since @name.
 */
extern struct elf_module *unload_modules_since(const char *name);

extern FILE *findpath(char *name);


/**
 * Names of symbols with special meaning (treated as special cases at linking)
 */
#define MODULE_ELF_INIT_PTR		"__module_init_ptr"	// Initialization pointer symbol name
#define MODULE_ELF_EXIT_PTR		"__module_exit_ptr"	// Finalization pointer symbol name
#define MODULE_ELF_MAIN_PTR		"__module_main_ptr" // Entry pointer symbol name

/**
 * modules_head - A global linked list containing all the loaded modules.
 */
extern struct list_head modules_head;


/**
 * for_each_module - iterator loop through the list of loaded modules.
 */
#define for_each_module(m)	list_for_each_entry(m, &modules_head, list)

/**
 * for_each_module_safe - iterator loop through the list of loaded modules safe against removal.
 */
#define for_each_module_safe(m, n)				\
	list_for_each_entry_safe(m, n, &modules_head, list)

/**
 * module_current - return the module at the head of the module list.
 */
static inline struct elf_module *module_current(void)
{
	struct elf_module *head;

	head = list_entry((&modules_head)->next, typeof(*head), list);
	return head;
}

/**
 * modules_init - initialize the module subsystem.
 *
 * This function must be called before any module operation is to be performed.
 */
extern int modules_init(void);


/**
 * modules_term - releases all resources pertaining to the module subsystem.
 *
 * This function should be called after all module operations.
 */
extern void modules_term(void);


/**
 * module_alloc - reserves space for a new module descriptor.
 * @name: 	the file name of the module to be loaded.
 *
 * The function simply allocates a new module descriptor and initializes its fields
 * in order to be used by subsequent loading operations.
 */
extern struct elf_module *module_alloc(const char *name);


/**
 * module_load - loads a regular ELF module into memory.
 * @module:	the module descriptor returned by module_alloc.
 *
 * The function reads the module file, checks whether the file has a
 * valid structure, then loads into memory the code and the data and performs
 * any symbol relocations. A module dependency is created automatically when the
 * relocated symbol is defined in a different module.
 *
 * The function returns 0 if the operation is completed successfully, and
 * a non-zero value if an error occurs. Possible errors include invalid module
 * structure, missing symbol definitions (unsatisfied dependencies) and memory
 * allocation issues.
 */
extern int module_load(struct elf_module *module);


/**
 * module_unload - unloads the module from the system.
 * @module: the module descriptor structure.
 *
 * The function checks to see whether the module can be safely
 * removed, then it executes any destructors and releases all the
 * associated memory. This function can be applied both for standard
 * modules and for shallow modules.
 *
 * A module can be safely removed from the system when no other modules reference
 * symbols from it.
 */
extern int module_unload(struct elf_module *module);

/**
 * _module_unload - unloads the module without running destructors
 * @module: the module descriptor structure.
 *
 * This function is the same as module_unload(), except that the
 * module's destructors are not executed.
 */
extern int _module_unload(struct elf_module *module);

/**
 * get_module_type - get type of the module
 * @module: the module descriptor structure.
 *
 * This function returns the type of module we're dealing with
 * either a library module ( LIB_MODULE ), executable module ( EXEC_MODULE ),
 * or an error ( UNKNOWN_MODULE ). The way it checks the type is by checking to see
 * if the module has its main_func set ( in which case it's an executable ). In case
 * it doesn't it then checks to see if init_func is set ( in which case it's a
 * library module. If this isn't the case either we don't know what it is so bail out
 */
extern int get_module_type(struct elf_module *module);

/**
 * module_unloadable - checks whether the given module can be unloaded.
 * @module: the module descriptor structure
 *
 * A module can be unloaded from the system when no other modules depend on it,
 * that is, no symbols are referenced from it.
 */
extern int module_unloadable(struct elf_module *module);

/**
 * module_find - searches for a module by its name.
 * @name: the name of the module, as it was specified in module_alloc.
 *
 * The function returns a pointer to the module descriptor, if found, or
 * NULL otherwise.
 */
extern struct elf_module *module_find(const char *name);

/**
 * module_find_symbol - searches for a symbol definition in a given module.
 * @name: the name of the symbol to be found.
 * @module: the module descriptor structure.
 *
 * The function searches the module symbol table for a symbol matching exactly
 * the name provided. The operation uses the following search algorithms, in this
 * order:
 *  - If a GNU hash table is present in the module, it is used to find the symbol.
 *  - If the symbol cannot be found with the first method (either the hash table
 *  is not present or the symbol is not found) and if a regular (SysV) hash table
 *  is present, a search is performed on the SysV hash table. If the symbol is not
 *  found, NULL is returned.
 *  - If the second method cannot be applied, a linear search is performed by
 *  inspecting every symbol in the symbol table.
 *
 *  If the symbol is found, a pointer to its descriptor structure is returned, and
 *  NULL otherwise.
 */
extern Elf_Sym *module_find_symbol(const char *name, struct elf_module *module);

/**
 * global_find_symbol - searches for a symbol definition in the entire module namespace.
 * @name: the name of the symbol to be found.
 * @module: an optional (may be NULL) pointer to a module descriptor variable that
 * will hold the module where the symbol was found.
 *
 * The function search for the given symbol name in all the modules currently
 * loaded in the system, in the reverse module loading order. That is, the most
 * recently loaded module is searched first, followed by the previous one, until
 * the first loaded module is reached.
 *
 * If no module contains the symbol, NULL is returned, otherwise the return value is
 * a pointer to the symbol descriptor structure. If the module parameter is not NULL,
 * it is filled with the address of the module descriptor where the symbol is defined.
 */
extern Elf_Sym *global_find_symbol(const char *name, struct elf_module **module);

/**
 * module_get_absolute - converts an memory address relative to a module base address
 * to its absolute value in RAM.
 * @addr: the relative address to convert.
 * @module: the module whose base address is used for the conversion.
 *
 * The function returns a pointer to the absolute memory address.
 */
static inline void *module_get_absolute(Elf_Addr addr, struct elf_module *module) {
	return (void*)(module->base_addr + addr);
}

/**
 * syslinux_current - get the current module process
 */
extern struct elf_module *__syslinux_current;
static inline const struct elf_module *syslinux_current(void)
{
	return __syslinux_current;
}


#endif // MODULE_H_
