#ifndef BACKEND_H
#define BACKEND_H

#include <stddef.h>
#include <inttypes.h>
#include <stdbool.h>
#include <zlib.h>
#include "serial.h"
#include "tftp.h"

/* Backend flags */
#define BE_NEEDLEN	0x01

struct upload_backend {
    const char *name;
    const char *helpmsg;
    int minargs;

    size_t dbytes;
    size_t zbytes;
    const char **argv;

    uint32_t now;

    int (*write)(struct upload_backend *);

    z_stream zstream;
    char *outbuf;
    size_t alloc;
};

/* zout.c */
int init_data(struct upload_backend *be, const char *argv[]);
int write_data(struct upload_backend *be, const void *buf, size_t len);
int flush_data(struct upload_backend *be);

/* cpio.c */
#define cpio_init init_data
int cpio_hdr(struct upload_backend *be, uint32_t mode, size_t datalen,
	     const char *filename);
int cpio_mkdir(struct upload_backend *be, const char *filename);
int cpio_writefile(struct upload_backend *be, const char *filename,
		   const void *data, size_t len);
int cpio_close(struct upload_backend *be);
#define MODE_FILE	0100644
#define MODE_DIR	0040755

/* backends.c */
struct upload_backend *get_upload_backend(const char *name);

/* backends */
extern struct upload_backend upload_tftp;
extern struct upload_backend upload_ymodem;
extern struct upload_backend upload_srec;

#endif /* BACKEND_H */
