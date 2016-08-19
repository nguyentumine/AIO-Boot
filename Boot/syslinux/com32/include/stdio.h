/*
 * stdio.h
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <klibc/extern.h>
#include <stdarg.h>
#include <stddef.h>

/* This structure doesn't really exist, but it gives us something
   to define FILE * with */
struct _IO_file;
typedef struct _IO_file FILE;

#ifndef EOF
# define EOF (-1)
#endif

#ifndef BUFSIZ
# define BUFSIZ 4096
#endif

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/*
 * Convert between a FILE * and a file descriptor.  We don't actually
 * have any in-memory data, so we just abuse the pointer itself to
 * hold the data.  Note, however, that for file descriptors, -1 is
 * error and 0 is a valid value; for FILE *, NULL (0) is error and
 * non-NULL are valid.
 */
static __inline__ int fileno(FILE * __f)
{
    /* This should really be intptr_t, but size_t should be the same size */
    return (int)(size_t) __f - 1;
}

/* This is a macro so it can be used as initializer */
#define __create_file(__fd) ((FILE *)(size_t)((__fd) + 1))

#define stdin  __create_file(0)
#define stdout __create_file(1)
#define stderr __create_file(2)

__extern FILE *fopen(const char *, const char *);
struct dev_info;
__extern FILE *fopendev(const struct dev_info *, const char *);

static __inline__ FILE *fdopen(int __fd, const char *__m)
{
    (void)__m;
    return __create_file(__fd);
}

__extern int fclose(FILE * __f);
__extern int fputs(const char *, FILE *);
__extern int puts(const char *);
__extern int fputc(int, FILE *);
#define putc(c,f)  fputc((c),(f))
#define putchar(c) fputc((c),stdout)

__extern int fgetc(FILE *);
__extern char *fgets(char *, int, FILE *);
#define getc(f) fgetc(f)

__extern size_t _fread(void *, size_t, FILE *);
__extern size_t _fwrite(const void *, size_t, FILE *);

__extern size_t fread(void *, size_t, size_t, FILE *);
__extern size_t fwrite(const void *, size_t, size_t, FILE *);

#ifndef __NO_FREAD_FWRITE_INLINES
#define fread(__p, __s, __n, __f)					\
  ( (__builtin_constant_p(__s) && __s == 1)				\
    ? _fread(__p, __n, __f)						\
    : fread(__p,__s,__n,__f) )

#define fwrite(__p, __s, __n, __f)					\
  ( (__builtin_constant_p(__s) && __s == 1)				\
    ? _fwrite(__p, __n, __f)						\
    : fwrite(__p,__s,__n,__f) )
#endif

/* No seek, but we can tell */
__extern long ftell(FILE *);

__extern int printf(const char *, ...);
__extern int vprintf(const char *, va_list);
__extern int fprintf(FILE *, const char *, ...);
__extern int vfprintf(FILE *, const char *, va_list);
__extern int sprintf(char *, const char *, ...);
__extern int vsprintf(char *, const char *, va_list);
__extern int snprintf(char *, size_t n, const char *, ...);
__extern int vsnprintf(char *, size_t n, const char *, va_list);

__extern int asprintf(char **, const char *, ...);
__extern int vasprintf(char **, const char *, va_list);

#define mp(f, x...) \
        printf("[%s()]: " f "\n", __func__,##x)
#define mpi()	mp("enter")
#define mpo()	mp("exit")

/* No buffering, so no flushing needed */
static __inline__ int fflush(FILE * __f)
{
    (void)__f;
    return 0;
}

__extern int sscanf(const char *, const char *, ...);
__extern int vsscanf(const char *, const char *, va_list);

__extern void perror(const char *);

__extern int rename(const char *, const char *);

/*
 * unhexchar: Convert a hexadecimal digit to the equivalent number
 *
 * Returns 0 if 'data' was converted succesfully, -1 otherwise.
 */
static inline int unhexchar(unsigned char *data)
{
	unsigned char num = *data;

	if (num >= '0' && num <= '9') {
		*data = num - '0';
		return 0;
	} else {
		num |= 0x20;	/* upper case -> lower case */
		if (num >= 'a' && num <= 'f') {
			*data = num - 'a' + 10;
			return 0;
		}
	}

	return -1;
}

#endif /* _STDIO_H */
