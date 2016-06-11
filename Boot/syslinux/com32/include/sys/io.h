#ifndef _SYS_IO_H
#define _SYS_IO_H

#include <inttypes.h>

static inline uint8_t inb(uint16_t p)
{
    uint8_t v;
    asm volatile ("inb %1,%0":"=a" (v):"Nd"(p));
    return v;
}

static inline uint16_t inw(uint16_t p)
{
    uint16_t v;
    asm volatile ("inw %1,%0":"=a" (v):"Nd"(p));
    return v;
}

static inline uint32_t inl(uint16_t p)
{
    uint32_t v;
    asm volatile ("inl %1,%0":"=a" (v):"Nd"(p));
    return v;
}

static inline void outb(uint8_t v, uint16_t p)
{
    asm volatile ("outb %0,%1"::"a" (v), "Nd"(p));
}

static inline void outw(uint16_t v, uint16_t p)
{
    asm volatile ("outw %0,%1"::"a" (v), "Nd"(p));
}

static inline void outl(uint32_t v, uint16_t p)
{
    asm volatile ("outl %0,%1"::"a" (v), "Nd"(p));
}

#endif /* _SYS_IO_H */
