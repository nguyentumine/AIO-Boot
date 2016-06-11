/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2004-2008 H. Peter Anvin - All Rights Reserved
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
 * console.h
 *
 * Alternative consoles
 */

#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <klibc/extern.h>
#include <inttypes.h>
#include <dev.h>

__extern int openconsole(const struct input_dev *, const struct output_dev *);

/* Standard line-oriented console */
extern const struct input_dev dev_stdcon_r;
extern const struct output_dev dev_stdcon_w;
/* Raw character-oriented console */
extern const struct input_dev dev_rawcon_r;
extern const struct output_dev dev_rawcon_w;

/* These are output-only consoles; combine with one of the input methods */

/* Serial port only */
extern const struct output_dev dev_serial_w;
/* ANSI console (output only; combine with one of the input methods) */
extern const struct output_dev dev_ansicon_w;
/* ANSI plus serial port */
extern const struct output_dev dev_ansiserial_w;

/* VESA graphics console (output only) */
extern const struct output_dev dev_vesacon_w;
/* VESA plus serial port */
extern const struct output_dev dev_vesaserial_w;

#endif /* _CONSOLE_H */
