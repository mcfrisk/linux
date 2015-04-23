/******************************************************************************
 * arch-x86_32.h
 *
 * Guest OS interface to x86 32-bit Xen.
 *
 * Copyright (c) 2004, K A Fraser
 */

#ifndef _UAPI_ASM_X86_XEN_INTERFACE_32_H
#define _UAPI_ASM_X86_XEN_INTERFACE_32_H

#include <linux/types.h>

/*
 * These flat segments are in the Xen-private section of every GDT. Since these
 * are also present in the initial GDT, many OSes will be able to avoid
 * installing their own GDT.
 */
#define FLAT_RING1_CS 0xe019    /* GDT index 259 */
#define FLAT_RING1_DS 0xe021    /* GDT index 260 */
#define FLAT_RING1_SS 0xe021    /* GDT index 260 */
#define FLAT_RING3_CS 0xe02b    /* GDT index 261 */
#define FLAT_RING3_DS 0xe033    /* GDT index 262 */
#define FLAT_RING3_SS 0xe033    /* GDT index 262 */

#define FLAT_KERNEL_CS FLAT_RING1_CS
#define FLAT_KERNEL_DS FLAT_RING1_DS
#define FLAT_KERNEL_SS FLAT_RING1_SS
#define FLAT_USER_CS    FLAT_RING3_CS
#define FLAT_USER_DS    FLAT_RING3_DS
#define FLAT_USER_SS    FLAT_RING3_SS

/* And the trap vector is... */
#define TRAP_INSTR "int $0x82"

#define __MACH2PHYS_VIRT_START 0xF5800000
#define __MACH2PHYS_VIRT_END   0xF6800000

#define __MACH2PHYS_SHIFT      2

/*
 * Virtual addresses beyond this are not modifiable by guest OSes. The
 * machine->physical mapping table starts at this address, read-only.
 */
#define __HYPERVISOR_VIRT_START 0xF5800000

#ifndef __ASSEMBLY__

struct cpu_user_regs {
    __u32 ebx;
    __u32 ecx;
    __u32 edx;
    __u32 esi;
    __u32 edi;
    __u32 ebp;
    __u32 eax;
    __u16 error_code;    /* private */
    __u16 entry_vector;  /* private */
    __u32 eip;
    __u16 cs;
    __u8  saved_upcall_mask;
    __u8  _pad0;
    __u32 eflags;        /* eflags.IF == !saved_upcall_mask */
    __u32 esp;
    __u16 ss, _pad1;
    __u16 es, _pad2;
    __u16 ds, _pad3;
    __u16 fs, _pad4;
    __u16 gs, _pad5;
};
DEFINE_GUEST_HANDLE_STRUCT(cpu_user_regs);

typedef __u64 tsc_timestamp_t; /* RDTSC timestamp */

struct arch_vcpu_info {
    unsigned long cr2;
    unsigned long pad[5]; /* sizeof(struct vcpu_info) == 64 */
};

struct xen_callback {
	unsigned long cs;
	unsigned long eip;
};
typedef struct xen_callback xen_callback_t;

#define XEN_CALLBACK(__cs, __eip)				\
	((struct xen_callback){ .cs = (__cs), .eip = (unsigned long)(__eip) })
#endif /* !__ASSEMBLY__ */


/*
 * Page-directory addresses above 4GB do not fit into architectural %cr3.
 * When accessing %cr3, or equivalent field in vcpu_guest_context, guests
 * must use the following accessor macros to pack/unpack valid MFNs.
 *
 * Note that Xen is using the fact that the pagetable base is always
 * page-aligned, and putting the 12 MSB of the address into the 12 LSB
 * of cr3.
 */
#define xen_pfn_to_cr3(pfn) (((unsigned)(pfn) << 12) | ((unsigned)(pfn) >> 20))
#define xen_cr3_to_pfn(cr3) (((unsigned)(cr3) >> 12) | ((unsigned)(cr3) << 20))

#endif /* _UAPI_ASM_X86_XEN_INTERFACE_32_H */
