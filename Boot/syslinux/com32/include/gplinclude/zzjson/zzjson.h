/* ZZJSON - Copyright (C) 2008 by Ivo van Poorten
 * License: GNU Lesser General Public License version 2.1
 */
#ifndef ZZJSON_H
#define ZZJSON_H

#include <stdlib.h>

/* Version: */

#define ZZJSON_VERSION_MAJOR    1
#define ZZJSON_VERSION_MINOR    1
#define ZZJSON_VERSION_MICRO    0
#define ZZJSON_VERSION_INT      ( 1<<16 | 1<<8 | 0 )
#define ZZJSON_IDENT            "zzjson 1.1.0"

/* Defines: */

#define ZZJSON_ALLOW_EXTRA_COMMA        1
#define ZZJSON_ALLOW_ILLEGAL_ESCAPE     2
#define ZZJSON_ALLOW_CONTROL_CHARS      4
#define ZZJSON_ALLOW_GARBAGE_AT_END     8
#define ZZJSON_ALLOW_COMMENTS           16

#define ZZJSON_VERY_LOOSE               (-1)
#define ZZJSON_VERY_STRICT              0

/* Types: */

/* needed by: pa = parser, pr = printer, f = free, q = query, c = create */
typedef struct ZZJSON_CONFIG {
    int strictness;                                        // pa
    void *ihandle;                                         // pa
    int (*getchar)(void *ihandle);                         // pa
    int (*ungetchar)(int c, void *ihandle);                // pa
    void *(*malloc)(size_t size);                          // pa      c
    void *(*calloc)(size_t nmemb, size_t size);            // pa      c
    void (*free)(void *ptr);                               // pa    f c
    void *(*realloc)(void *ptr, size_t size);              // pa
    void *ehandle;                                         // pa pr   c
    void (*error)(void *ehandle, const char *format, ...); // pa pr   c
    void *ohandle;                                         //    pr
    int (*print)(void *ohandle, const char *format, ...);  //    pr
    int (*putchar)(int c, void *handle);                   //    pr
} ZZJSON_CONFIG;

typedef enum ZZJSON_TYPE {
    ZZJSON_NONE = 0,
    ZZJSON_OBJECT,
    ZZJSON_ARRAY,
    ZZJSON_STRING,
    ZZJSON_NUMBER_NEGINT,
    ZZJSON_NUMBER_POSINT,
    ZZJSON_NUMBER_DOUBLE,
    ZZJSON_NULL,
    ZZJSON_TRUE,
    ZZJSON_FALSE
} ZZJSON_TYPE;

typedef struct ZZJSON {
    ZZJSON_TYPE type;
    union {
        struct {
            char *label;
            struct ZZJSON *val;
        } object;
        struct {
            struct ZZJSON *val;
        } array;
        struct {
            char *string;
        } string;
        struct {
            union {
                unsigned long long ival;
                double             dval;
            } val;
        } number;
    } value;
    struct ZZJSON *next;
} ZZJSON;

/* Functions: */

ZZJSON *zzjson_parse(ZZJSON_CONFIG *config);
void zzjson_free(ZZJSON_CONFIG *config, ZZJSON *zzjson);
int zzjson_print(ZZJSON_CONFIG *config, ZZJSON *zzjson);

ZZJSON *zzjson_object_find_label(ZZJSON *zzjson, char *label);
ZZJSON *zzjson_object_find_labels(ZZJSON *zzjson, ...); // end with , NULL
unsigned int zzjson_object_count(ZZJSON *zzjson);
unsigned int zzjson_array_count(ZZJSON *zzjson);

ZZJSON *zzjson_create_true(ZZJSON_CONFIG *config);
ZZJSON *zzjson_create_false(ZZJSON_CONFIG *config);
ZZJSON *zzjson_create_null(ZZJSON_CONFIG *config);
ZZJSON *zzjson_create_number_d(ZZJSON_CONFIG *config, double d);
ZZJSON *zzjson_create_number_i(ZZJSON_CONFIG *config, long long i);
ZZJSON *zzjson_create_string(ZZJSON_CONFIG *config, char *s);

/* list of ZZJSON *'s and end with , NULL */
ZZJSON *zzjson_create_array(ZZJSON_CONFIG *config, ...);

/* list of char*,ZZJSON* pairs, end with , NULL */
ZZJSON *zzjson_create_object(ZZJSON_CONFIG *config, ...);

ZZJSON *zzjson_array_prepend(ZZJSON_CONFIG *config, ZZJSON *array,
                                                    ZZJSON *val);
ZZJSON *zzjson_array_append (ZZJSON_CONFIG *config, ZZJSON *array,
                                                    ZZJSON *val);

ZZJSON *zzjson_object_prepend(ZZJSON_CONFIG *config, ZZJSON *object,
                                        char *label, ZZJSON *val);
ZZJSON *zzjson_object_append (ZZJSON_CONFIG *config, ZZJSON *object,
                                        char *label, ZZJSON *val);
#endif
