#ifndef _SYS_PCI_H
#define _SYS_PCI_H

#include <inttypes.h>
#include <sys/io.h>

#define MAX_PCI_FUNC		  8
#define MAX_PCI_DEVICES		 32
#define MAX_PCI_BUSES		256
#define LINUX_KERNEL_MODULE_SIZE 64
#define PCI_VENDOR_NAME_SIZE	256
#define PCI_PRODUCT_NAME_SIZE	256
#define PCI_CLASS_NAME_SIZE	256
#define MAX_KERNEL_MODULES_PER_PCI_DEVICE 10
#define MAX_PCI_CLASSES		256

typedef uint32_t pciaddr_t;

enum {
	ENOPCIIDS = 100,
	ENOMODULESPCIMAP,
	ENOMODULESALIAS
};

/* a structure for extended pci information */
/* XXX: use pointers for these? */
struct pci_dev_info {
    char vendor_name[PCI_VENDOR_NAME_SIZE];
    char product_name[PCI_PRODUCT_NAME_SIZE];
    char linux_kernel_module[LINUX_KERNEL_MODULE_SIZE]
	[MAX_KERNEL_MODULES_PER_PCI_DEVICE];
    int linux_kernel_module_count;
    char class_name[PCI_CLASS_NAME_SIZE];	/* The most precise class name */
    char category_name[PCI_CLASS_NAME_SIZE];	/*The general category */
    uint8_t irq;
    uint8_t latency;
};

/* PCI device (really, function) */
struct pci_device {
    union {
	struct {
	    uint16_t vendor;
	    uint16_t product;
	    uint16_t sub_vendor;
	    uint16_t sub_product;
	    uint8_t revision;
	    uint8_t class[3];
	};
	struct {
	    uint32_t vid_did;
	    uint32_t svid_sdid;
	    uint32_t rid_class;
	};
    };
    struct pci_dev_info *dev_info;
    struct pci_device *next;
};

/* PCI device ("slot") structure */
struct pci_slot {
    struct pci_device *func[MAX_PCI_FUNC];
};

/* PCI bus structure */
struct pci_bus {
    struct pci_slot *slot[MAX_PCI_DEVICES];
};

/* PCI domain structure */
struct pci_domain {
    struct pci_bus *bus[MAX_PCI_BUSES];
};

/* Iterate over a PCI domain */
#define for_each_pci_func(funcp, domain) \
  for (int __pci_bus = 0; __pci_bus < MAX_PCI_BUSES; __pci_bus++) \
    if ((domain)->bus[__pci_bus]) \
      for (int __pci_slot = 0; __pci_slot < MAX_PCI_DEVICES; __pci_slot++) \
	if ((domain)->bus[__pci_bus]->slot[__pci_slot]) \
	  for (int __pci_func = 0; __pci_func < MAX_PCI_FUNC; __pci_func++) \
	    if (((funcp) = (domain)->bus[__pci_bus]->slot[__pci_slot]-> \
		 func[__pci_func]))

#define for_each_pci_func3(funcp, domain, addr) \
  for (int __pci_bus = 0; __pci_bus < MAX_PCI_BUSES; __pci_bus++) \
    if ((domain)->bus[__pci_bus]) \
      for (int __pci_slot = 0; __pci_slot < MAX_PCI_DEVICES; __pci_slot++) \
	if ((domain)->bus[__pci_bus]->slot[__pci_slot]) \
	  for (int __pci_func = 0; __pci_func < MAX_PCI_FUNC; __pci_func++) \
	    if (((addr) = pci_mkaddr(__pci_bus, __pci_slot, __pci_func, 0)), \
		((funcp) = (domain)->bus[__pci_bus]->slot[__pci_slot]-> \
		 func[__pci_func]))

struct match {
    struct match *next;
    uint32_t did;
    uint32_t did_mask;
    uint32_t sid;
    uint32_t sid_mask;
    uint8_t rid_min, rid_max;
    char *filename;
};

static inline pciaddr_t pci_mkaddr(uint32_t bus, uint32_t dev,
				   uint32_t func, uint32_t reg)
{
    return 0x80000000 | ((bus & 0xff) << 16) | ((dev & 0x1f) << 11) |
	((func & 0x07) << 8) | (reg & 0xff);
}

static inline int pci_bus(pciaddr_t addr)
{
    return (addr >> 16) & 0xff;
}

static inline int pci_dev(pciaddr_t addr)
{
    return (addr >> 11) & 0x1f;
}

static inline int pci_func(pciaddr_t addr)
{
    return (addr >> 8) & 0x07;
}

enum pci_config_type {
    PCI_CFG_NONE = -1,		/* badness */
    PCI_CFG_AUTO = 0,		/* autodetect */
    PCI_CFG_TYPE1 = 1,
    PCI_CFG_TYPE2 = 2,
    PCI_CFG_BIOS = 3,
};

enum pci_config_type pci_set_config_type(enum pci_config_type);

uint8_t pci_readb(pciaddr_t);
uint16_t pci_readw(pciaddr_t);
uint32_t pci_readl(pciaddr_t);
void pci_writeb(uint8_t, pciaddr_t);
void pci_writew(uint16_t, pciaddr_t);
void pci_writel(uint32_t, pciaddr_t);

struct pci_domain *pci_scan(void);
void free_pci_domain(struct pci_domain *domain);
struct match *find_pci_device(const struct pci_domain *pci_domain,
			      struct match *list);
int get_name_from_pci_ids(struct pci_domain *pci_domain, char *pciids_path);
int get_module_name_from_pcimap(struct pci_domain *pci_domain, char *modules_pcimap_path);
int get_module_name_from_alias(struct pci_domain *pci_domain, char *modules_alias_path);
int get_class_name_from_pci_ids(struct pci_domain *pci_domain, char *pciids_path);
void gather_additional_pci_config(struct pci_domain *domain);
#endif /* _SYS_PCI_H */
