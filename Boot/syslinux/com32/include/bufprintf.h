#define BUFPAD	4096

struct print_buf {
    char *buf;
    size_t len;
    size_t size;
};

int vbufprintf(struct print_buf *buf, const char *format, va_list ap);
int bufprintf(struct print_buf *buf, const char *format, ...);
