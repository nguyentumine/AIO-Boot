#ifndef CLI_H
#define CLI_H

#define MAX_CMD_HISTORY 64
#define COMMAND_DELIM		" \t\n"	// Whitespace delimiters
#define MAX_COMMAND_ARGS	40

struct cli_command {
    struct list_head list;
    char *command;
};

extern void clear_screen(void);
extern int mygetkey(clock_t timeout);
extern const char *edit_cmdline(const char *input, int top /*, int width */ ,
				int (*pDraw_Menu) (int, int, int),
				void (*show_fkey) (int), bool *);

extern struct menu *root_menu, *start_menu, *hide_menu, *menu_list, *default_menu;
#endif
