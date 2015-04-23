#ifndef _UAPI__CODA_PSDEV_H
#define _UAPI__CODA_PSDEV_H

#include <linux/magic.h>
#include <linux/coda.h>

#define CODA_PSDEV_MAJOR 67
#define MAX_CODADEVS  5	   /* how many do we allow */


/* messages between coda filesystem in kernel and Venus */
struct upc_req {
#ifdef __KERNEL__
	struct list_head    uc_chain;
#endif /* __KERNEL__ */
	caddr_t	            uc_data;
	unsigned short      uc_flags;
	unsigned short      uc_inSize;  /* Size is at most 5000 bytes */
	unsigned short	    uc_outSize;
	unsigned short      uc_opcode;  /* copied from data to save lookup */
	int		    uc_unique;
#ifdef __KERNEL__
	wait_queue_head_t   uc_sleep;   /* process' wait queue */
#endif /* __KERNEL__ */
};

#define CODA_REQ_ASYNC  0x1
#define CODA_REQ_READ   0x2
#define CODA_REQ_WRITE  0x4
#define CODA_REQ_ABORT  0x8

#endif /* _UAPI__CODA_PSDEV_H */
