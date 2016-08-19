#ifndef _SWSUSP_H_
#define _SWSUSP_H_

#include <disk/geom.h>
#include <disk/common.h>
#include <disk/partition.h>

#define SWSUSP_SIG	"S1SUSPEND"

struct swsusp_header {
    char reserved[PAGE_SIZE - 20 - sizeof(unsigned long) - sizeof(int)];
    unsigned long image;
    unsigned int flags;		/* Flags to pass to the "boot" kernel */
    char orig_sig[10];
    char sig[10];
} __attribute__ ((packed));

int swsusp_check(struct driveinfo *, struct part_entry *);
#endif /* _SWSUSP_H */
