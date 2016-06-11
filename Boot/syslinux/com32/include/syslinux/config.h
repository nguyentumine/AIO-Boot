/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2007-2009 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author: H. Peter Anvin
 *
 *   Permission is hereby granted, free of charge, to any person
 *   obtaining a copy of this software and associated documentation
 *   files (the "Software"), to deal in the Software without
 *   restriction, including without limitation the rights to use,
 *   copy, modify, merge, publish, distribute, sublicense, and/or
 *   sell copies of the Software, and to permit persons to whom
 *   the Software is furnished to do so, subject to the following
 *   conditions:
 *
 *   The above copyright notice and this permission notice shall
 *   be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 *
 * ----------------------------------------------------------------------- */

/*
 * syslinux/config.h
 *
 * Query syslinux configuration information.
 */

#ifndef _SYSLINUX_CONFIG_H
#define _SYSLINUX_CONFIG_H

#include <stdint.h>
#include <com32.h>

enum syslinux_filesystem {
    SYSLINUX_FS_UNKNOWN  = 0x30,
    SYSLINUX_FS_SYSLINUX = 0x31,
    SYSLINUX_FS_PXELINUX = 0x32,
    SYSLINUX_FS_ISOLINUX = 0x33,
    SYSLINUX_FS_EXTLINUX = 0x34,
};

struct syslinux_version {
    uint16_t version;		/* (major << 8)+minor */
    uint16_t max_api;
    enum syslinux_filesystem filesystem;
    const char *version_string;
    const char *copyright_string;
};

struct syslinux_ipinfo {
    uint32_t ipver;
    uint32_t myip;
    uint32_t serverip;
    uint32_t gateway;
    uint32_t netmask;
};

extern __nocommon struct syslinux_version __syslinux_version;
static inline const struct syslinux_version *syslinux_version(void)
{
    return &__syslinux_version;
}

union syslinux_derivative_info {
    struct {
	com32sys_t r;
	const void *esbx;
	const void *fssi;
	const void *gsdi;
    } rr;			/* real raw */
    struct {
	uint16_t _pad1[4];
	uint32_t _pad2[7];
	uint8_t filesystem;
	uint8_t ah;
	uint16_t axh;
    } c;			/* common */
    struct {
	uint16_t gs;
	uint16_t fs;
	uint16_t es;
	uint16_t ds;
	uint16_t di, dih;
	uint16_t si, sih;
	uint16_t bp, bph;
	uint16_t sp, sph;
	uint16_t bx, bxh;
	uint16_t dx, dxh;
	uint16_t cx, cxh;
	uint16_t ax, axh;
	uint32_t eflags;
	const void *esbx;
	const void *fssi;
	const void *gsdi;
    } r;			/* raw */
    struct {
	uint16_t _gs, _fs, _es, _ds;
	uint32_t _edi, _esi, _ebp, _esp, _ebx;
	uint8_t drive_number, dh;
	uint16_t _dxh;
	uint8_t sector_shift, ch;
	uint16_t _cxh;
	uint8_t filesystem, ah;
	uint16_t _axh;
	uint32_t _eflags;
	const void *ptab_ptr;
	const uint32_t *esdi_ptr;
	const uint64_t *partoffset;
    } disk;			/* syslinux/extlinux */
    struct {
	uint16_t _gs, stack_seg, pxenv_seg, _ds;
	uint32_t _edi, stack_offs, _ebp, _esp, pxenv_offs;
	uint16_t apiver;
	uint16_t _dxh;
	uint32_t myip;
	uint8_t filesystem, ah;
	uint16_t _axh;
	uint32_t _eflags;
	const void *pxenvptr;
	const void *stack;
	const struct syslinux_ipinfo *ipinfo;
    } pxe;			/* pxelinux */
    struct {
	uint16_t _gs, _fs, _es, _ds;
	uint32_t _edi, _esi, _ebp, _esp, _ebx;
	uint8_t drive_number, dh;
	uint16_t _dxh;
	uint8_t sector_shift, cd_mode;
	uint16_t _cxh;
	uint8_t filesystem, ah;
	uint16_t _axh;
	uint32_t _eflags;
	const void *spec_packet;
	const uint32_t *esdi_ptr;
	const uint64_t *partoffset;
    } iso;			/* isolinux */
};

extern __nocommon union syslinux_derivative_info __syslinux_derivative_info;
static inline const union syslinux_derivative_info
    *syslinux_derivative_info(void)
{
    return &__syslinux_derivative_info;
}

struct syslinux_serial_console_info {
    uint16_t iobase;
    uint16_t divisor;
    uint16_t flowctl;
};

extern void __syslinux_set_serial_console_info(void);

extern __nocommon struct syslinux_serial_console_info
    __syslinux_serial_console_info;
static inline const struct syslinux_serial_console_info
    *syslinux_serial_console_info(void)
{
    return &__syslinux_serial_console_info;
}

extern char ConfigName[];
static inline const char *syslinux_config_file(void)
{
    return ConfigName;
}

struct syslinux_ipappend_strings {
    int count;
    const char *const *ptr;
};
extern __nocommon struct syslinux_ipappend_strings __syslinux_ipappend_strings;
static inline const struct syslinux_ipappend_strings
    *syslinux_ipappend_strings(void)
{
    return &__syslinux_ipappend_strings;
}

static inline enum syslinux_filesystem syslinux_filesystem(void)
{
    return syslinux_derivative_info()->c.filesystem;
}

extern void get_derivative_info(union syslinux_derivative_info *di);

#endif /* _SYSLINUX_CONFIG_H */
