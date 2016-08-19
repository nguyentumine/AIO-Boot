/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2006-2008 H. Peter Anvin - All Rights Reserved
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

#ifndef _COLORTBL_H
#define _COLORTBL_H

/* Attribute/color table used by ansicon and vesacon to abstract
   out the color selection. */

/* Note: vesacon relies on the encoding of these numbers */
enum color_table_shadow {
    SHADOW_NONE = 0,
    SHADOW_ALL = 1,
    SHADOW_NORMAL = 2,
    SHADOW_REVERSE = 3,
};

struct color_table {
    const char *name;		/* Attribute name (used for customization) */
    const char *ansi;		/* ANSI attribute */
    unsigned int argb_fg;	/* ARGB for foreground */
    unsigned int argb_bg;	/* ARGB for background */
    enum color_table_shadow shadow;	/* Shadow mode */
};

extern struct color_table *console_color_table;
extern int console_color_table_size;

#endif /* _COLORTBL_H */
