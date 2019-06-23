#ifndef __DEVLINUX__MEM_H
#define __DEVLINUX__MEM_H

#include <stdint.h>
#include <stdbool.h>
#include <vga.h>

typedef struct __attribute__((packed)) {
	void* prev;
	void* next;
} MEM_ALLOC_PREFIX;

extern void* mem_alloc(uint16_t);
extern void mem_free(void*);

#endif