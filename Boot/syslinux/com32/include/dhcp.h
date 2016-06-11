#ifndef DHCP_H
#define DHCP_H

#include <inttypes.h>

struct dhcp_option {
	void *data;
	int len;
};

struct dhcp_packet {
	uint8_t op;		/*   0 */
	uint8_t htype;		/*   1 */
	uint8_t hlen;		/*   2 */
	uint8_t hops;		/*   3 */
	uint32_t xid;		/*   4 */
	uint16_t secs;		/*   8 */
	uint16_t flags;		/*  10 */
	uint32_t ciaddr;	/*  12 */
	uint32_t yiaddr;	/*  16 */
	uint32_t siaddr;	/*  20 */
	uint32_t giaddr;	/*  24 */
	uint8_t chaddr[16];	/*  28 */
	uint8_t sname[64];	/*  44 */
	uint8_t file[128];	/* 108 */
	uint32_t magic;		/* 236 */
	uint8_t options[4];	/* 240 */
};

#define DHCP_VENDOR_MAGIC	0x63825363

int dhcp_pack_packet(void *packet, size_t *len,
		     const struct dhcp_option opt[256]);

int dhcp_unpack_packet(const void *packet, size_t len,
		       struct dhcp_option opt[256]);

#endif /* DHCP_H */
  

