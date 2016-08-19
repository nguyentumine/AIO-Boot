#ifndef SERIAL_H
#define SERIAL_H

#include <stddef.h>

struct serial_if {
    uint16_t port;
    bool console;
    struct {
	uint8_t dll, dlm, ier, iir, lcr, mcr;
    } old;
};

int serial_init(struct serial_if *sif, const char *argv[]);
void serial_read(struct serial_if *sif, void *data, size_t n);
void serial_write(struct serial_if *sif, const void *data, size_t n);
void serial_cleanup(struct serial_if *sif);

#endif /* SERIAL_H */
