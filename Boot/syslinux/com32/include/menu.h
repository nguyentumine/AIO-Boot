/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2004-2008 H. Peter Anvin - All Rights Reserved
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 *   Boston MA 02110-1301, USA; either version 2 of the License, or
 *   (at your option) any later version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

/*
 * menu.h
 *
 * Header file for the simple menu system
 */

#ifndef MENU_H
#define MENU_H

#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <inttypes.h>
#include <unistd.h>
#include <colortbl.h>
#include <stdbool.h>
#include <getkey.h>
#include "refstr.h"

/* #define DEBUG 1 */
#include <dprintf.h>

#ifndef CLK_TCK
# define CLK_TCK sysconf(_SC_CLK_TCK)
#endif

struct menu;

/* Note: the _UNRES variants must always be immediately after their
   "normal" versions. */
enum menu_action {
    MA_NONE,			/* Undefined value */
    MA_CMD,			/* Execute a command */
    MA_DISABLED,		/* Disabled menu entry */
    MA_SUBMENU,			/* This is a submenu entry */
    MA_GOTO,			/* Go to another menu */
    MA_GOTO_UNRES,		/* Unresolved go to */
    MA_QUIT,			/* Quit to CLI */
    MA_EXIT,			/* Exit to higher-level menu */
    MA_EXIT_UNRES,		/* Unresolved exit */
    MA_HELP,			/* Show help text */
};

struct menu_entry {
    struct menu *menu;		/* Parent menu */
    const char *displayname;
    const char *label;
    const char *passwd;
    char *helptext;
    const char *cmdline;
    const char *background;
    struct menu *submenu;
    struct menu_entry *next;	/* Linked list of all labels across menus */
    int entry;			/* Entry number inside menu */
    enum menu_action action;
    unsigned char hotkey;
    bool immediate;		/* Hotkey action does not require Enter */
    bool save;			/* Save this entry if selected */
};

static inline bool is_disabled(struct menu_entry *me)
{
    return me->action == MA_DISABLED;
}

enum kernel_type {
    /* Meta-types for internal use */
    KT_NONE,
    KT_LOCALBOOT,

    /* The ones we can pass off to SYSLINUX, in order */
    KT_KERNEL,			/* Undefined type */
    KT_LINUX,			/* Linux kernel */
    KT_BOOT,			/* Bootstrap program */
    KT_BSS,			/* Boot sector with patch */
    KT_PXE,			/* PXE NBP */
    KT_FDIMAGE,			/* Floppy disk image */
    KT_COM32,			/* COM32 image */
    KT_CONFIG,			/* Configuration file */
};

/* Configurable integer parameters */
enum parameter_number {
    P_WIDTH,
    P_MARGIN,
    P_PASSWD_MARGIN,
    P_MENU_ROWS,
    P_TABMSG_ROW,
    P_CMDLINE_ROW,
    P_END_ROW,
    P_PASSWD_ROW,
    P_TIMEOUT_ROW,
    P_HELPMSG_ROW,
    P_HELPMSGEND_ROW,
    P_HSHIFT,
    P_VSHIFT,
    P_HIDDEN_ROW,

    NPARAMS
};

/* Configurable messages */
enum message_number {
    MSG_TITLE,
    MSG_AUTOBOOT,
    MSG_TAB,
    MSG_NOTAB,
    MSG_PASSPROMPT,

    MSG_COUNT
};

struct messages {
    const char *name;		/* Message configuration name */
    const char *defmsg;		/* Default message text */
};

struct menu_parameter {
    const char *name;
    int value;
};

extern const struct menu_parameter mparm[NPARAMS];

struct fkey_help {
    const char *textname;
    const char *background;
};

struct menu {
    struct menu *next;		/* Linked list of all menus */
    const char *label;		/* Goto label for this menu */
    struct menu *parent;
    struct menu_entry *parent_entry;	/* Entry for self in parent */

    struct menu_entry **menu_entries;
    struct menu_entry *menu_hotkeys[256];

    const char *messages[MSG_COUNT];
    int mparm[NPARAMS];

    int nentries;
    int nentries_space;
    int defentry;
    int timeout;

    bool allowedit;
    bool immediate;		/* MENU IMMEDIATE default for this menu */
    bool save;			/* MENU SAVE default for this menu */

    int curentry;
    int curtop;

    const char *title;
    const char *ontimeout;
    const char *onerror;
    const char *menu_master_passwd;
    const char *menu_background;

    struct color_table *color_table;

    struct fkey_help fkeyhelp[12];
};

extern struct menu *root_menu, *start_menu, *hide_menu, *menu_list;

/* 2048 is the current definition inside syslinux */
#define MAX_CMDLINE_LEN	 2048

/* These are global parameters regardless of which menu we're displaying */
extern int shiftkey;
extern int hiddenmenu;
extern int clearmenu;
extern long long totaltimeout;
extern clock_t kbdtimeout;
extern const char *hide_key[KEY_MAX];

void parse_configs(char **argv);
int draw_background(const char *filename);
void set_resolution(int x, int y);
void start_console(void);
void local_cursor_enable(bool);

static inline int my_isspace(char c)
{
    return (unsigned char)c <= ' ' || (unsigned char)c == '\x7f';
}

int my_isxdigit(char c);
unsigned int hexval(char c);
unsigned int hexval2(const char *p);
uint32_t parse_argb(char **p);

extern const int message_base_color, menu_color_table_size;
int mygetkey(clock_t timeout);
int show_message_file(const char *filename, const char *background);

/* passwd.c */
int passwd_compare(const char *passwd, const char *entry);

/* colors.c */
#define MSG_COLORS_DEF_FG	0x90ffffff
#define MSG_COLORS_DEF_BG	0x80ffffff
#define MSG_COLORS_DEF_SHADOW	SHADOW_NORMAL
void set_msg_colors_global(struct color_table *tbl,
			   unsigned int fg, unsigned int bg,
			   enum color_table_shadow shadow);
struct color_table *default_color_table(void);
struct color_table *copy_color_table(const struct color_table *master);
extern const int message_base_color;

/* background.c */
extern const char *current_background;
void set_background(const char *new_background);

/* drain.c */
void drain_keyboard(void);

/* chainboot.c */
void chainboot_file(const char *file, enum kernel_type type);

#endif /* MENU_H */
