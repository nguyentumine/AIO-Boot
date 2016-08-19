/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2012 Intel Corporation; author: H. Peter Anvin
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

#ifndef _HW_VGA_H
#define _HW_VGA_H 1

#include <sys/io.h>

/* These are relative to the CRTC base address */
#define VGA_CRTC_ADDR			0x4
#define VGA_CRTC_DATA			0x5
#define VGA_CRTC_IX_HORIZ_TOTAL		0x00
#define VGA_CRTC_IX_END_HORIZ_DISPLAY	0x01
#define VGA_CRTC_IX_START_HORIZ_BLANK	0x02
#define VGA_CRTC_IX_END_HORIZ_BLANK	0x03
#define VGA_CRTC_IX_START_HORIZ_RETR	0x04
#define VGA_CRTC_IX_END_HORIZ_RETR	0x05
#define VGA_CRTC_IX_VERT_TOTAL		0x06
#define VGA_CRTC_IX_OVERFLOW		0x07
#define VGA_CRTC_IX_PRESET_ROW_SCAN	0x08
#define VGA_CRTC_IX_MAX_SCAN_LINE	0x09
#define VGA_CRTC_IX_CURSOR_START	0x0a
#define VGA_CRTC_IX_CURSOR_END		0x0b
#define VGA_CRTC_IX_START_ADDR_HIGH	0x0c
#define VGA_CRTC_IX_START_ADDR_LOW	0x0d
#define VGA_CRTC_IX_CURSOR_POS_HIGH	0x0e
#define VGA_CRTC_IX_CURSOR_POS_LOW	0x0f
#define VGA_CRTC_IX_START_VERT_RETR	0x10
#define VGA_CRTC_IX_END_VERT_RETR	0x11
#define VGA_CRTC_IX_END_VERT_DISPLAY	0x12
#define VGA_CRTC_IX_OFFSET		0x13
#define VGA_CRTC_IX_UNDERLINE		0x14
#define VGA_CRTC_IX_START_VERT_BLANK	0x15
#define VGA_CRTC_IX_END_VERT_BLANK	0x16
#define VGA_CRTC_IX_MODE_CONTROL	0x17
#define VGA_CRTC_IX_LINE_COMPARE	0x18
#define VGA_CRTC_INPUT_STATUS_1		0xa
#define VGA_CRTC_FEATURE_CONTROL_WRITE	0xa

#define VGA_ATTR_ADDR_DATA		0x3c0
#define VGA_ATTR_DATA_READ		0x3c1
/* 0x00-0x0f are 16->64 palette registers */
#define VGA_ATTR_IX_MODE_CONTROL	0x10
#define VGA_ATTR_IX_OVERSCAN		0x11
#define VGA_ATTR_IX_COLOR_PLANE_ENABLE	0x12
#define VGA_ATTR_IX_HORIZ_PIXEL_PAN	0x13
#define VGA_ADDR_IX_COLOR_SELECT	0x14
#define VGA_INPUT_STATUS_0		0x3c2
#define VGA_MISC_OUTPUT_WRITE		0x3c2
#define VGA_SEQ_ADDR			0x3c4
#define VGA_SEQ_DATA			0x3c5
#define VGA_SEQ_IX_RESET		0
#define VGA_SEQ_IX_CLOCKMODE		1
#define VGA_SEQ_IX_MAP_MASK		2
#define VGA_SEQ_IX_CHAR_MAP		3
#define VGA_SEQ_IX_SEQ_MEM_MODE		4
#define VGA_DAC_STATE			0x3c7
#define VGA_DAC_ADDR_READ_MODE		0x3c7
#define VGA_DAC_ADDR_WRITE_MODE		0x3c8
#define VGA_DAC_DATA			0x3c9
#define VGA_FEATURE_CONTROL_READ	0x3ca
#define VGA_MISC_OUTPUT_READ		0x3cc
#define VGA_GC_ADDR			0x3ce
#define VGA_GC_DATA			0x3cf
#define VGA_GC_IX_SET_RESET		0
#define VGA_GC_IX_ENABLE_SET_RESET	1
#define VGA_GC_IX_COLOR_COMPARE		2
#define VGA_GC_IX_DATA_ROTATE		3
#define VGA_GC_IX_READ_MAP_SELECT	4
#define VGA_GC_IX_GRAPHICS_MODE		5
#define VGA_GC_IX_MISC_GRAPHICS		6
#define VGA_GC_IX_COLOR_DONT_CARE	7
#define VGA_GC_IX_BIT_MASK		8

static inline uint16_t vga_crtc_base(void)
{
    return 0x3b0 + ((inb(VGA_MISC_OUTPUT_READ) & 1) << 5);
}

#endif /* _HW_VGA_H */
