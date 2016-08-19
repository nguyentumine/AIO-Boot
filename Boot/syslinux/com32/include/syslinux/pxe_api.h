/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2007-2008 H. Peter Anvin - All Rights Reserved
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
 * syslinux/pxe_api.h
 *
 * PXE type and constant definitions for SYSLINUX
 */

#ifndef _SYSLINUX_PXE_API_H
#define _SYSLINUX_PXE_API_H

#include <stdint.h>
#include <netinet/in.h>
#include <klibc/compiler.h>
#include <com32.h>

/* PXE spec structures and definitions.  These mostly follow the PXE
   spec, except when the PXE spec is unnecessarily stupid.  Of course,
   that is most of the time. */

/* Basic types; use Unix-like _t convention instead of SCREAMING; also
   re-use types we already have, like in_addr_t. */

typedef uint16_t pxenv_status_t;

#define MAC_ADDR_LEN	16
typedef uint8_t mac_addr_t[MAC_ADDR_LEN];

/* "Protected mode segment descriptor" according to PXE... */
typedef struct {
    uint16_t sel;
    uint32_t base;
    uint16_t size;
} __packed pxe_segdesc_t;

typedef far_ptr_t segoff16_t;

typedef struct {
    uint8_t opcode;
#define BOOTP_REQ 1
#define BOOTP_REP 2
    uint8_t Hardware;
    uint8_t Hardlen;
    uint8_t Gatehops;
    uint32_t ident;
    uint16_t seconds;
    uint16_t Flags;
#define BOOTP_BCAST 0x8000
    in_addr_t cip;		/* Client IP address */
    in_addr_t yip;		/* You IP address */
    in_addr_t sip;		/* next server IP address */
    in_addr_t gip;		/*relay agent IP address */
    mac_addr_t CAddr;
    uint8_t Sname[64];
    uint8_t bootfile[128];
    union {
#define BOOTP_DHCPVEND 1024
	uint8_t d[BOOTP_DHCPVEND];
	struct {
	    uint8_t magic[4];
#define VM_RFC1048 0x63825363L
	    uint32_t flags;
	    uint8_t pad[56];
	} v;
    } vendor;
} __packed pxe_bootp_t;

/* Function calling structures and constants */

typedef struct s_PXENV_GET_CACHED_INFO {
    pxenv_status_t Status;
    uint16_t PacketType;
#define PXENV_PACKET_TYPE_DHCP_DISCOVER 1
#define PXENV_PACKET_TYPE_DHCP_ACK 2
#define PXENV_PACKET_TYPE_CACHED_REPLY 3
    uint16_t BufferSize;
    segoff16_t Buffer;
    uint16_t BufferLimit;
} __packed t_PXENV_GET_CACHED_INFO;

typedef struct s_PXENV_START_UNDI {
    pxenv_status_t Status;
    uint16_t AX;
    uint16_t BX;
    uint16_t DX;
    uint16_t DI;
    uint16_t ES;
} __packed t_PXENV_START_UNDI;

typedef struct s_PXENV_STOP_UNDI {
    pxenv_status_t Status;
} __packed t_PXENV_STOP_UNDI;

typedef struct s_PXENV_START_BASE {
    pxenv_status_t Status;
} __packed t_PXENV_START_BASE;

typedef struct s_PXENV_STOP_BASE {
    pxenv_status_t Status;
} __packed t_PXENV_STOP_BASE;

typedef struct s_PXENV_TFTP_OPEN {
    pxenv_status_t Status;
    in_addr_t ServerIPAddress;
    in_addr_t GatewayIPAddress;
    uint8_t FileName[128];
    in_port_t TFTPPort;
    uint16_t PacketSize;
} __packed t_PXENV_TFTP_OPEN;

typedef struct s_PXENV_TFTP_CLOSE {
    pxenv_status_t Status;
} __packed t_PXENV_TFTP_CLOSE;

typedef struct s_PXENV_TFTP_READ {
    pxenv_status_t Status;
    uint16_t PacketNumber;
    uint16_t BufferSize;
    segoff16_t Buffer;
} __packed t_PXENV_TFTP_READ;

typedef struct s_PXENV_TFTP_READ_FILE {
    pxenv_status_t Status;
    uint8_t FileName[128];
    uint32_t BufferSize;
    void *Buffer;
    in_addr_t ServerIPAddress;
    in_addr_t GatewayIPAddress;
    in_addr_t McastIPAddress;
    in_port_t TFTPClntPort;
    in_port_t TFTPSrvPort;
    uint16_t TFTPOpenTimeOut;
    uint16_t TFTPReopenDelay;
} __packed t_PXENV_TFTP_READ_FILE;

typedef struct s_PXENV_TFTP_GET_FSIZE {
    pxenv_status_t Status;
    in_addr_t ServerIPAddress;
    in_addr_t GatewayIPAddress;
    uint8_t FileName[128];
    uint32_t FileSize;
} __packed t_PXENV_TFTP_GET_FSIZE;

typedef struct s_PXENV_UDP_OPEN {
    pxenv_status_t status;
    in_addr_t src_ip;
} __packed t_PXENV_UDP_OPEN;

typedef struct s_PXENV_UDP_CLOSE {
    pxenv_status_t status;
} __packed t_PXENV_UDP_CLOSE;

typedef struct s_PXENV_UDP_WRITE {
    pxenv_status_t status;
    in_addr_t ip;
    in_addr_t gw;
    in_port_t src_port;
    in_port_t dst_port;
    uint16_t buffer_size;
    segoff16_t buffer;
} __packed t_PXENV_UDP_WRITE;

typedef struct s_PXENV_UDP_READ {
    pxenv_status_t status;
    in_addr_t src_ip;
    in_addr_t dest_ip;
    in_port_t s_port;
    in_port_t d_port;
    uint16_t buffer_size;
    segoff16_t buffer;
} __packed t_PXENV_UDP_READ;

typedef struct s_PXENV_UNDI_STARTUP {
    pxenv_status_t Status;
} __packed t_PXENV_UNDI_STARTUP;

typedef struct s_PXENV_UNDI_CLEANUP {
    pxenv_status_t Status;
} __packed t_PXENV_UNDI_CLEANUP;

typedef struct s_PXENV_UNDI_INITIALIZE {
    pxenv_status_t Status;
    void *ProtocolIni;
    uint8_t reserved[8];
} __packed t_PXENV_UNDI_INITIALIZE;

#define MAXNUM_MCADDR 8
typedef struct s_PXENV_UNDI_MCAST_ADDRESS {
    uint16_t MCastAddrCount;
    mac_addr_t McastAddr[MAXNUM_MCADDR];
} __packed t_PXENV_UNDI_MCAST_ADDRESS;

typedef struct s_PXENV_UNDI_RESET {
    pxenv_status_t Status;
    t_PXENV_UNDI_MCAST_ADDRESS R_Mcast_Buf;
} __packed t_PXENV_UNDI_RESET;

typedef struct s_PXENV_UNDI_SHUTDOWN {
    pxenv_status_t Status;
} __packed t_PXENV_UNDI_SHUTDOWN;

typedef struct s_PXENV_UNDI_OPEN {
    pxenv_status_t Status;
    uint16_t OpenFlag;
    uint16_t PktFilter;
#define FLTR_DIRECTED 0x0001
#define FLTR_BRDCST 0x0002
#define FLTR_PRMSCS 0x0004
#define FLTR_SRC_RTG 0x0008
     t_PXENV_UNDI_MCAST_ADDRESS R_Mcast_Buf;
} __packed t_PXENV_UNDI_OPEN;

typedef struct s_PXENV_UNDI_CLOSE {
    pxenv_status_t Status;
} __packed t_PXENV_UNDI_CLOSE;

typedef struct s_PXENV_UNDI_TRANSMIT {
    pxenv_status_t Status;
    uint8_t Protocol;
#define P_UNKNOWN 0
#define P_IP 1
#define P_ARP 2
#define P_RARP 3
    uint8_t XmitFlag;
#define XMT_DESTADDR 0x0000
#define XMT_BROADCAST 0x0001
    segoff16_t DestAddr;
    segoff16_t TBD;
    uint32_t Reserved[2];
} __packed t_PXENV_UNDI_TRANSMIT;
#define MAX_DATA_BLKS 8
typedef struct s_PXENV_UNDI_TBD {
    uint16_t ImmedLength;
    segoff16_t Xmit;
    uint16_t DataBlkCount;
    struct DataBlk {
	uint8_t TDPtrType;
	uint8_t TDRsvdByte;
	uint16_t TDDataLen;
	segoff16_t TDDataPtr;
    } DataBlock[MAX_DATA_BLKS];
} __packed t_PXENV_UNDI_TBD;

typedef struct s_PXENV_UNDI_SET_MCAST_ADDRESS {
    pxenv_status_t Status;
     t_PXENV_UNDI_MCAST_ADDRESS R_Mcast_Buf;
} __packed t_PXENV_UNDI_SET_MCAST_ADDR;

typedef struct s_PXENV_UNDI_SET_STATION_ADDRESS {
    pxenv_status_t Status;
    mac_addr_t StationAddress;
} __packed t_PXENV_UNDI_SET_STATION_ADDR;

typedef struct s_PXENV_UNDI_SET_PACKET_FILTER {
    pxenv_status_t Status;
    uint8_t filter;
} __packed t_PXENV_UNDI_SET_PACKET_FILTER;

typedef struct s_PXENV_UNDI_GET_INFORMATION {
    pxenv_status_t Status;
    uint16_t BaseIo;
    uint16_t IntNumber;
    uint16_t MaxTranUnit;
    uint16_t HwType;
#define ETHER_TYPE 1
#define EXP_ETHER_TYPE 2
#define IEEE_TYPE 6
#define ARCNET_TYPE 7
    uint16_t HwAddrLen;
    mac_addr_t CurrentNodeAddress;
    mac_addr_t PermNodeAddress;
    uint16_t ROMAddress;
    uint16_t RxBufCt;
    uint16_t TxBufCt;
} __packed t_PXENV_UNDI_GET_INFORMATION;

typedef struct s_PXENV_UNDI_GET_STATISTICS {
    pxenv_status_t Status;
    uint32_t XmtGoodFrames;
    uint32_t RcvGoodFrames;
    uint32_t RcvCRCErrors;
    uint32_t RcvResourceErrors;
} __packed t_PXENV_UNDI_GET_STATISTICS;

typedef struct s_PXENV_UNDI_CLEAR_STATISTICS {
    pxenv_status_t Status;
} __packed t_PXENV_UNDI_CLEAR_STATISTICS;

typedef struct s_PXENV_UNDI_INITIATE_DIAGS {
    pxenv_status_t Status;
} __packed t_PXENV_UNDI_INITIATE_DIAGS;

typedef struct s_PXENV_UNDI_FORCE_INTERRUPT {
    pxenv_status_t Status;
} __packed t_PXENV_UNDI_FORCE_INTERRUPT;

typedef struct s_PXENV_UNDI_GET_MCAST_ADDRESS {
    pxenv_status_t Status;
    in_addr_t InetAddr;
    mac_addr_t MediaAddr;
} __packed t_PXENV_UNDI_GET_MCAST_ADDR;

typedef struct s_PXENV_UNDI_GET_NIC_TYPE {
    pxenv_status_t Status;
    uint8_t NicType;
#define PCI_NIC 2
#define PnP_NIC 3
#define CardBus_NIC 4
    union {
	struct {
	    uint16_t Vendor_ID;
	    uint16_t Dev_ID;
	    uint8_t Base_Class;
	    uint8_t Sub_Class;
	    uint8_t Prog_Intf;
	    uint8_t Rev;
	    uint16_t BusDevFunc;
	    uint16_t SubVendor_ID;
	    uint16_t SubDevice_ID;
	} pci, cardbus;
	struct {
	    uint32_t EISA_Dev_ID;
	    uint8_t Base_Class;
	    uint8_t Sub_Class;
	    uint8_t Prog_Intf;
	    uint16_t CardSelNum;
	} __packed pnp;
    } __packed info;
} __packed t_PXENV_UNDI_GET_NIC_TYPE;

typedef struct s_PXENV_UNDI_GET_IFACE_INFO {
    pxenv_status_t Status;
    uint8_t IfaceType[16];
    uint32_t LinkSpeed;
    uint32_t ServiceFlags;
    uint32_t Reserved[4];
} __packed t_PXENV_UNDI_GET_IFACE_INFO;
#define PXE_UNDI_IFACE_FLAG_BCAST	0x00000001
#define PXE_UNDI_IFACE_FLAG_MCAST	0x00000002
#define PXE_UNDI_IFACE_FLAG_GROUP	0x00000004
#define PXE_UNDI_IFACE_FLAG_PROMISC	0x00000008
#define PXE_UNDI_IFACE_FLAG_SOFTMAC	0x00000010
#define PXE_UNDI_IFACE_FLAG_STATS	0x00000020
#define PXE_UNDI_IFACE_FLAG_DIAGS	0x00000040
#define PXE_UNDI_IFACE_FLAG_LOOPBACK	0x00000080
#define PXE_UNDI_IFACE_FLAG_RCVCHAIN	0x00000100
#define PXE_UNDI_IFACE_FLAG_IBMSRCRT	0x00000200
#define PXE_UNDI_IFACE_FLAG_RESET	0x00000400
#define PXE_UNDI_IFACE_FLAG_OPEN	0x00000800
#define PXE_UNDI_IFACE_FLAG_IRQ		0x00001000
#define PXE_UNDI_IFACE_FLAG_SRCRT	0x00002000
#define PXE_UNDI_IFACE_FLAG_GDTVIRT	0x00004000
#define PXE_UNDI_IFACE_FLAG_MULTI	0x00008000
#define PXE_UNDI_IFACE_FLAG_LKFISZ	0x00010000

typedef struct s_PXENV_UNDI_GET_STATE {
#define PXE_UNDI_GET_STATE_STARTED 1
#define PXE_UNDI_GET_STATE_INITIALIZED 2
#define PXE_UNDI_GET_STATE_OPENED 3
    pxenv_status_t Status;
    uint8_t UNDIstate;
} __packed t_PXENV_UNDI_GET_STATE;

typedef struct s_PXENV_UNDI_ISR {
    pxenv_status_t Status;
    uint16_t FuncFlag;
    uint16_t BufferLength;
    uint16_t FrameLength;
    uint16_t FrameHeaderLength;
    segoff16_t Frame;
    uint8_t ProtType;
    uint8_t PktType;
} __packed t_PXENV_UNDI_ISR;

typedef struct s_PXENV_FILE_API_CHECK {
    pxenv_status_t Status;
    uint16_t Size;
    uint32_t Magic;
    uint32_t Provider;
    uint32_t APIMask;
    uint32_t Flags;
} __packed t_PXENV_FILE_API_CHECK;

typedef struct s_PXENV_FILE_READ {
    pxenv_status_t Status;
    uint16_t FileHandle;
    uint16_t BufferSize;
    segoff16_t Buffer;
} __packed t_PXENV_FILE_READ;

typedef struct s_PXENV_FILE_OPEN {
    pxenv_status_t Status;
    uint16_t FileHandle;
    segoff16_t FileName;
    uint32_t Reserved;
} __packed t_PXENV_FILE_OPEN;

typedef struct s_PXENV_FILE_CLOSE {
    pxenv_status_t Status;
    uint16_t FileHandle;
} __packed t_PXENV_FILE_CLOSE;

typedef struct s_PXENV_GET_FILE_SIZE {
    pxenv_status_t Status;
    uint16_t FileHandle;
    uint32_t FileSize;
} __packed t_PXENV_GET_FILE_SIZE;

typedef struct s_PXENV_UNLOAD_STACK {
    pxenv_status_t Status;
    uint8_t reserved[10];
} __packed t_PXENV_UNLOAD_STACK;
    
#define PXENV_UNDI_ISR_IN_START 1
#define PXENV_UNDI_ISR_IN_PROCESS 2
#define PXENV_UNDI_ISR_IN_GET_NEXT 3
/* One of these will be returned for
   PXENV_UNDI_ISR_IN_START */
#define PXENV_UNDI_ISR_OUT_OURS 0
#define PXENV_UNDI_USR_OUT_NOT_OURS 1
/* One of these will be returned for
   PXENV_UNDI_ISR_IN_PROCESS and
   PXENV_UNDI_ISR_IN_GET_NEXT */
#define PXENV_UNDI_ISR_OUT_DONE 0
#define PXENV_UNDI_ISR_OUT_TRANSMIT 2
#define PXENV_UNDI_ISR_OUT_RECEIVE 3
#define PXENV_UNDI_ISR_OUT_BUSY 4

/* Function numbers and error codes */

#define PXENV_TFTP_OPEN			0x0020
#define PXENV_TFTP_CLOSE		0x0021
#define PXENV_TFTP_READ			0x0022
#define PXENV_TFTP_READ_FILE		0x0023
#define PXENV_TFTP_READ_FILE_PMODE	0x0024
#define PXENV_TFTP_GET_FSIZE		0x0025

#define PXENV_UDP_OPEN			0x0030
#define PXENV_UDP_CLOSE			0x0031
#define PXENV_UDP_READ			0x0032
#define PXENV_UDP_WRITE			0x0033

#define PXENV_START_UNDI		0x0000
#define PXENV_UNDI_STARTUP		0x0001
#define PXENV_UNDI_CLEANUP		0x0002
#define PXENV_UNDI_INITIALIZE		0x0003
#define PXENV_UNDI_RESET_NIC		0x0004
#define PXENV_UNDI_SHUTDOWN		0x0005
#define PXENV_UNDI_OPEN			0x0006
#define PXENV_UNDI_CLOSE		0x0007
#define PXENV_UNDI_TRANSMIT		0x0008
#define PXENV_UNDI_SET_MCAST_ADDR	0x0009
#define PXENV_UNDI_SET_STATION_ADDR	0x000A
#define PXENV_UNDI_SET_PACKET_FILTER	0x000B
#define PXENV_UNDI_GET_INFORMATION	0x000C
#define PXENV_UNDI_GET_STATISTICS	0x000D
#define PXENV_UNDI_CLEAR_STATISTICS	0x000E
#define PXENV_UNDI_INITIATE_DIAGS	0x000F
#define PXENV_UNDI_FORCE_INTERRUPT	0x0010
#define PXENV_UNDI_GET_MCAST_ADDR	0x0011
#define PXENV_UNDI_GET_NIC_TYPE		0x0012
#define PXENV_UNDI_GET_IFACE_INFO	0x0013
#define PXENV_UNDI_ISR			0x0014
#define	PXENV_STOP_UNDI			0x0015	/* Overlap...? */
#define PXENV_UNDI_GET_STATE		0x0015	/* Overlap...? */

#define PXENV_UNLOAD_STACK		0x0070
#define PXENV_GET_CACHED_INFO		0x0071
#define PXENV_RESTART_DHCP		0x0072
#define PXENV_RESTART_TFTP		0x0073
#define PXENV_MODE_SWITCH		0x0074
#define PXENV_START_BASE		0x0075
#define PXENV_STOP_BASE			0x0076

/* gPXE extensions... */
#define PXENV_FILE_OPEN			0x00e0
#define PXENV_FILE_CLOSE		0x00e1
#define PXENV_FILE_SELECT		0x00e2
#define PXENV_FILE_READ			0x00e3
#define PXENV_GET_FILE_SIZE		0x00e4
#define PXENV_FILE_EXEC			0x00e5
#define PXENV_FILE_API_CHECK		0x00e6

/* Exit codes */
#define PXENV_EXIT_SUCCESS				 0x0000
#define PXENV_EXIT_FAILURE				 0x0001

/* Status codes */
#define PXENV_STATUS_SUCCESS				 0x00
#define PXENV_STATUS_FAILURE				 0x01
#define PXENV_STATUS_BAD_FUNC				 0x02
#define PXENV_STATUS_UNSUPPORTED			 0x03
#define PXENV_STATUS_KEEP_UNDI				 0x04
#define PXENV_STATUS_KEEP_ALL				 0x05
#define PXENV_STATUS_OUT_OF_RESOURCES			 0x06
#define PXENV_STATUS_ARP_TIMEOUT			 0x11
#define PXENV_STATUS_UDP_CLOSED				 0x18
#define PXENV_STATUS_UDP_OPEN				 0x19
#define PXENV_STATUS_TFTP_CLOSED			 0x1a
#define PXENV_STATUS_TFTP_OPEN				 0x1b
#define PXENV_STATUS_MCOPY_PROBLEM			 0x20
#define PXENV_STATUS_BIS_INTEGRITY_FAILURE		 0x21
#define PXENV_STATUS_BIS_VALIDATE_FAILURE		 0x22
#define PXENV_STATUS_BIS_INIT_FAILURE			 0x23
#define PXENV_STATUS_BIS_SHUTDOWN_FAILURE		 0x24
#define PXENV_STATUS_BIS_GBOA_FAILURE			 0x25
#define PXENV_STATUS_BIS_FREE_FAILURE			 0x26
#define PXENV_STATUS_BIS_GSI_FAILURE			 0x27
#define PXENV_STATUS_BIS_BAD_CKSUM			 0x28
#define PXENV_STATUS_TFTP_CANNOT_ARP_ADDRESS		 0x30
#define PXENV_STATUS_TFTP_OPEN_TIMEOUT			 0x32

#define PXENV_STATUS_TFTP_UNKNOWN_OPCODE		 0x33
#define PXENV_STATUS_TFTP_READ_TIMEOUT			 0x35
#define PXENV_STATUS_TFTP_ERROR_OPCODE			 0x36
#define PXENV_STATUS_TFTP_CANNOT_OPEN_CONNECTION	 0x38
#define PXENV_STATUS_TFTP_CANNOT_READ_FROM_CONNECTION	 0x39
#define PXENV_STATUS_TFTP_TOO_MANY_PACKAGES		 0x3a
#define PXENV_STATUS_TFTP_FILE_NOT_FOUND		 0x3b
#define PXENV_STATUS_TFTP_ACCESS_VIOLATION		 0x3c
#define PXENV_STATUS_TFTP_NO_MCAST_ADDRESS		 0x3d
#define PXENV_STATUS_TFTP_NO_FILESIZE			 0x3e
#define PXENV_STATUS_TFTP_INVALID_PACKET_SIZE		 0x3f
#define PXENV_STATUS_DHCP_TIMEOUT			 0x51
#define PXENV_STATUS_DHCP_NO_IP_ADDRESS			 0x52
#define PXENV_STATUS_DHCP_NO_BOOTFILE_NAME		 0x53
#define PXENV_STATUS_DHCP_BAD_IP_ADDRESS		 0x54
#define PXENV_STATUS_UNDI_INVALID_FUNCTION		 0x60
#define PXENV_STATUS_UNDI_MEDIATEST_FAILED		 0x61
#define PXENV_STATUS_UNDI_CANNOT_INIT_NIC_FOR_MCAST	 0x62
#define PXENV_STATUS_UNDI_CANNOT_INITIALIZE_NIC		 0x63
#define PXENV_STATUS_UNDI_CANNOT_INITIALIZE_PHY		 0x64
#define PXENV_STATUS_UNDI_CANNOT_READ_CONFIG_DATA	 0x65
#define PXENV_STATUS_UNDI_CANNOT_READ_INIT_DATA		 0x66
#define PXENV_STATUS_UNDI_BAD_MAC_ADDRESS		 0x67
#define PXENV_STATUS_UNDI_BAD_EEPROM_CHECKSUM		 0x68
#define PXENV_STATUS_UNDI_ERROR_SETTING_ISR		 0x69
#define PXENV_STATUS_UNDI_INVALID_STATE			 0x6a
#define PXENV_STATUS_UNDI_TRANSMIT_ERROR		 0x6b
#define PXENV_STATUS_UNDI_INVALID_PARAMETER		 0x6c
#define PXENV_STATUS_BSTRAP_PROMPT_MENU			 0x74
#define PXENV_STATUS_BSTRAP_MCAST_ADDR			 0x76
#define PXENV_STATUS_BSTRAP_MISSING_LIST		 0x77
#define PXENV_STATUS_BSTRAP_NO_RESPONSE			 0x78
#define PXENV_STATUS_BSTRAP_FILE_TOO_BIG		 0x79
#define PXENV_STATUS_BINL_CANCELED_BY_KEYSTROKE		 0xa0
#define PXENV_STATUS_BINL_NO_PXE_SERVER			 0xa1
#define PXENV_STATUS_NOT_AVAILABLE_IN_PMODE		 0xa2
#define PXENV_STATUS_NOT_AVAILABLE_IN_RMODE		 0xa3
#define PXENV_STATUS_BUSD_DEVICE_NOT_SUPPORTED		 0xb0
#define PXENV_STATUS_LOADER_NO_FREE_BASE_MEMORY		 0xc0
#define PXENV_STATUS_LOADER_NO_BC_ROMID			 0xc1
#define PXENV_STATUS_LOADER_BAD_BC_ROMID		 0xc2
#define PXENV_STATUS_LOADER_BAD_BC_RUNTIME_IMAGE	 0xc3
#define PXENV_STATUS_LOADER_NO_UNDI_ROMID		 0xc4
#define PXENV_STATUS_LOADER_BAD_UNDI_ROMID		 0xc5
#define PXENV_STATUS_LOADER_BAD_UNDI_DRIVER_IMAGE	 0xc6
#define PXENV_STATUS_LOADER_NO_PXE_STRUCT		 0xc8
#define PXENV_STATUS_LOADER_NO_PXENV_STRUCT		 0xc9
#define PXENV_STATUS_LOADER_UNDI_START			 0xca
#define PXENV_STATUS_LOADER_BC_START			 0xcb

int __weak pxe_call(int, void *);
void __weak unload_pxe(uint16_t flags);
uint32_t __weak dns_resolv(const char *);

extern uint32_t __weak SendCookies;
void __weak http_bake_cookies(void);

#endif /* _SYSLINUX_PXE_API_H */
