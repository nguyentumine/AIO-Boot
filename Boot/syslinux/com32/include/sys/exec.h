/*
 * exec.h
 *
 *  Created on: Aug 14, 2008
 *      Author: Stefan Bucur <stefanb@zytor.com>
 */

#ifndef EXEC_H_
#define EXEC_H_

#include <sys/module.h>
#include <stdlib.h>

/**
 * EXEC_ROOT_NAME - The name of the ELF module associated with the COM32 module.
 *
 * This is a shallow ELF module, that contains only the symbol table for
 * the code and data sections of the loaded COM32 root module.
 */
#define EXEC_ROOT_NAME			"_root_.c32"

/**
 * spawn_load - Load a library module or executes an executable one
 * @name	the name of the library/executable to use, including the extension
 * 			(e.g. 'sort.c32')
 * @argc:	the number of string arguments in @argv
 * @argv:	a NULL-terminated vector of string arguments, starting with
 * 			the program name.
 *
 * This procedure in essence loads takes the name of a module and checks to see what
 * kind of module it is ( executable or library ), after which is performs the
 * appropriate action, either spawning or simply loading the module into memory.
 */
extern int spawn_load(const char *name, int argc, char **argv);

/**
 * spawnv - Executes a program in the current environment.
 * @name:	the name of the program to spawn, including the extension
 * 			(e.g. 'hello.c32')
 * @argv:	a NULL-terminated vector of string arguments, starting with
 * 			the program name.
 *
 * A program is an ELF module that contains a main routine. A program is
 * loaded into memory, executed, then unloaded, thus remaining in memory only
 * while the main() function is executing. A program also defines a
 * memory allocation context, and a simple garbage collection mechanism
 * it thus provided. This is done by internally associating with the program
 * module each pointer returned by malloc(). After the program finishes
 * its execution, all the unallocated memory pertaining to the program
 * is automatically cleaned up.
 *
 * Note that this association takes place both for the allocations happening
 * directly in the program, or indirectly through a library function. Libraries
 * do not create allocation contexts, thus each allocation they made belong
 * to the innermost calling program.
 */
extern int spawnv(const char *name, const char **argv);

/**
 * spawnl - Executes a program in the current environment.
 * @name:	the name of the program to spawn, including the extension
 * 			(e.g. 'hello.c32')
 * @arg:	the first argument (argv[0]) to be passed to the main function
 * 			of the program
 * @...:	optional subsequent arguments that are passed o the main function
 * 			of the program
 *
 * This is another version of the spawn routine. Please see 'spawnv' for
 * a full presentation.
 */
extern int spawnl(const char *name, const char *arg, ...);

/**
 * exec_term - Releases the resources of the execution environment.
 */
extern void exec_term(void);


#endif /* EXEC_H_ */
