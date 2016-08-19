#ifndef _BYTESWAP_H
#define _BYTESWAP_H

#include <stdint.h>
#include <klibc/endian.h>
#include <klibc/compiler.h>

/* This assumes an i386 platform */

#define __bswap_16_macro(v) ((uint16_t)		  			\
			     (((uint16_t)(v) << 8) | 			\
			      ((uint16_t)(v) >> 8)))

static inline __constfunc uint16_t __bswap_16(uint16_t v)
{
    return __bswap_16_macro(v);
}

#define bswap_16(x) (__builtin_constant_p(x) ?				\
			__bswap_16_macro(x) : __bswap_16(x))

#define __bswap_32_macro(v) ((uint32_t)					\
			     ((((uint32_t)(v) & 0x000000ff) << 24) |	\
			      (((uint32_t)(v) & 0x0000ff00) << 8)  |	\
			     (((uint32_t)(v) & 0x00ff0000) >> 8)  |	\
			      (((uint32_t)(v) & 0xff000000) >> 24)))

static inline __constfunc uint32_t __bswap_32(uint32_t v)
{
#if defined(__x86_64__)
    asm("bswap %0" : "+r" (v));
#elif defined(__i386__)
    asm("xchgb %h0,%b0 ; roll $16,%0 ; xchgb %h0,%b0"
	: "+q" (v));
#else
    v = __bswap_32_macro(v);
#endif
    return v;
}

#define bswap_32(x) (__builtin_constant_p(x) ?				\
			 __bswap_32_macro(x) : __bswap_32(x))


#define __bswap_64_macro(v) ((uint64_t)					\
    (((uint64_t)__bswap_32_macro((uint32_t)(v)) << 32) |		\
     (__bswap_32_macro((uint32_t)((uint64_t)(v) >> 32)))))

static inline __constfunc uint64_t __bswap_64(uint64_t v)
{
#if defined(__x86_64__)
    asm("bswap %0" : "+r" (v));
#else
    v = ((uint64_t)__bswap_32(v) << 32) | __bswap_32(v >> 32);
#endif
    return v;
}

#define bswap_64(x) (__builtin_constant_p(x) ? 				\
			__bswap_64_macro(x) :  __bswap_64(x))

/* This is generic */

#if __BYTE_ORDER == __LITTLE_ENDIAN

#define be16_to_cpu(x) bswap_16(x)
#define cpu_to_be16(x) bswap_16(x)
#define be32_to_cpu(x) bswap_32(x)
#define cpu_to_be32(x) bswap_32(x)
#define be64_to_cpu(x) bswap_64(x)
#define cpu_to_be64(x) bswap_64(x)

#define le16_to_cpu(x) (x)
#define cpu_to_le16(x) (x)
#define le32_to_cpu(x) (x)
#define cpu_to_le32(x) (x)
#define le64_to_cpu(x) (x)
#define cpu_to_le64(x) (x)

#elif __BYTE_ORDER == __BIG_ENDIAN

#define le16_to_cpu(x) bswap_16(x)
#define cpu_to_le16(x) bswap_16(x)
#define le32_to_cpu(x) bswap_32(x)
#define cpu_to_le32(x) bswap_32(x)
#define le64_to_cpu(x) bswap_64(x)
#define cpu_to_le64(x) bswap_64(x)

#define be16_to_cpu(x) (x)
#define cpu_to_be16(x) (x)
#define be32_to_cpu(x) (x)
#define cpu_to_be32(x) (x)
#define be64_to_cpu(x) (x)
#define cpu_to_be64(x) (x)

#else

#error "Unknown byte order!"

#endif

typedef struct { uint16_t x; } __attribute__((packed)) __ua_uint16_t;
typedef struct { uint32_t x; } __attribute__((packed)) __ua_uint32_t;
typedef struct { uint64_t x; } __attribute__((packed)) __ua_uint64_t;

/* These are guaranteed to support unaligned accesses */
static inline uint16_t get_le16(const uint16_t *p)
{
    const __ua_uint16_t *up = (const __ua_uint16_t *)p;
    return le16_to_cpu(up->x);
}

static inline uint32_t get_le32(const uint32_t *p)
{
    const __ua_uint32_t *up = (const __ua_uint32_t *)p;
    return le32_to_cpu(up->x);
}    

static inline uint64_t get_le64(const uint64_t *p)
{
    const __ua_uint64_t *up = (const __ua_uint64_t *)p;
    return le64_to_cpu(up->x);
}

static inline uint16_t get_be16(const uint16_t *p)
{
    const __ua_uint16_t *up = (const __ua_uint16_t *)p;
    return be16_to_cpu(up->x);
}

static inline uint32_t get_be32(const uint32_t *p)
{
    const __ua_uint32_t *up = (const __ua_uint32_t *)p;
    return be32_to_cpu(up->x);
}    

static inline uint64_t get_be64(const uint64_t *p)
{
    const __ua_uint64_t *up = (const __ua_uint64_t *)p;
    return be64_to_cpu(up->x);
}

static inline void put_le16(uint16_t v, uint16_t *p)
{
    __ua_uint16_t *up = (__ua_uint16_t *)p;
    up->x = cpu_to_le16(v);
}

static inline void put_le32(uint32_t v, uint32_t *p)
{
    __ua_uint32_t *up = (__ua_uint32_t *)p;
    up->x = cpu_to_le32(v);
}

static inline void put_le64(uint64_t v, uint64_t *p)
{
    __ua_uint64_t *up = (__ua_uint64_t *)p;
    up->x = cpu_to_le64(v);
}

static inline void put_be16(uint16_t v, uint16_t *p)
{
    __ua_uint16_t *up = (__ua_uint16_t *)p;
    up->x = cpu_to_be16(v);
}

static inline void put_be32(uint32_t v, uint32_t *p)
{
    __ua_uint32_t *up = (__ua_uint32_t *)p;
    up->x = cpu_to_be32(v);
}

static inline void put_be64(uint64_t v, uint64_t *p)
{
    __ua_uint64_t *up = (__ua_uint64_t *)p;
    up->x = cpu_to_be64(v);
}

#endif /* _BYTESWAP_H */

