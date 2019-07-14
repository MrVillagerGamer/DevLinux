#ifndef __DEVLINUX__GDT_H
#define __DEVLINUX__GDT_H

#include <stdint.h>

#define GDT_LENGTH 1024*sizeof(gdtent_t)+0
#define TSS_COUNT 16

typedef struct __attribute__((packed)) {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_vhigh;
	uint8_t access;
	uint8_t flags_limit_high;
	uint8_t base_high;
} gdtent_t;

typedef struct __attribute__((packed)) {
	uint16_t size;
	uint32_t offset;
} gdtptr_t;

typedef struct __attribute__((packed)) {
	uint32_t link;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldtr;
	uint16_t trap;
	uint16_t iopb;
} tssent_t;

extern void gdt_set_gate(uint16_t, gdtent_t);
extern void gdt_flush(uint32_t);
extern void gdt_get_ptr(gdtptr_t*);
extern void gdt_init();

#endif
































