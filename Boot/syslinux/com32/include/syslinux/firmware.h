#ifndef _SYSLINUX_FIRMWARE_H
#define _SYSLINUX_FIRMWARE_H

#include <inttypes.h>
#include <stdbool.h>

struct term_state;

struct output_ops {
	void (*erase) (int, int, int, int, uint8_t);
	void (*write_char) (uint8_t, uint8_t);
	void (*showcursor) (const struct term_state *);
	void (*scroll_up) (uint8_t, uint8_t, uint8_t);
	void (*set_cursor) (int, int, bool);
	void (*beep) (void);
	void (*get_mode)(int *, int *);
	void (*text_mode)(void);
	void (*get_cursor)(uint8_t *, uint8_t *);
};

struct input_ops {
	char (*getchar)(char *);
	int (*pollchar)(void);
	uint8_t (*shiftflags)(void);
};

struct adv_ops {
	void (*init)(void);
	int (*write)(void);
};

struct vesa_info;
enum vesa_pixel_format;
struct win_info;

struct vesa_ops {
	int (*set_mode)(struct vesa_info *, int *, int *, enum vesa_pixel_format *);
	void (*screencpy)(size_t, const uint32_t *, size_t, struct win_info *);
	int (*font_query)(uint8_t **);
};

enum heap;
struct mem_ops {
	void *(*malloc)(size_t, enum heap, size_t);
	void *(*realloc)(void *, size_t);
	void (*free)(void *);
};

struct initramfs;
struct setup_data;

struct firmware {
	void (*init)(void);
	void (*adjust_screen)(void);
	void (*cleanup)(void);
	struct disk *(*disk_init)(void *);
	struct output_ops *o_ops;
	struct input_ops *i_ops;
	void (*get_serial_console_info)(uint16_t *, uint16_t *, uint16_t *);
	struct adv_ops *adv_ops;
	int (*boot_linux)(void *, size_t, struct initramfs *,
			  struct setup_data *, char *);
	struct vesa_ops *vesa;
	struct mem_ops *mem;
};

extern struct firmware *firmware;

extern void syslinux_register_bios(void);
extern void init(void);

#endif /* _SYSLINUX_FIRMWARE_H */
