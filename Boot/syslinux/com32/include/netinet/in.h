#ifndef _NETINET_IN_H
#define _NETINET_IN_H

/* COM32 will be running on an i386 platform */

#include <klibc/compiler.h>
#include <klibc/extern.h>
#include <stdint.h>
#include <byteswap.h>

#define htons(x) cpu_to_be16(x)
#define ntohs(x) be16_to_cpu(x)
#define htonl(x) cpu_to_be32(x)
#define ntohl(x) be32_to_cpu(x)
#define htonq(x) cpu_to_be64(x)
#define ntohq(x) be64_to_cpu(x)

typedef uint32_t in_addr_t;
typedef uint16_t in_port_t;

struct in_addr {
    in_addr_t s_addr;
};

__extern char *inet_ntoa(struct in_addr);

#endif /* _NETINET_IN_H */
