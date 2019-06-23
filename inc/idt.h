#ifndef __DEVLINUX__IDT_H
#define __DEVLINUX__IDT_H

#include <stdint.h>
#include <port.h>
#include <vga.h>

typedef struct __attribute__((packed)) {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t reserved;
	uint8_t type_attr;
	uint16_t offset_high;
} idte_t;

typedef uint32_t (*idth_t)(uint32_t);

extern void irq_entry_handler0();
extern void irq_entry_handler1();
extern void irq_entry_handler2();
extern void irq_entry_handler3();
extern void irq_entry_handler4();
extern void irq_entry_handler5();
extern void irq_entry_handler6();
extern void irq_entry_handler7();
extern void irq_entry_handler8();
extern void irq_entry_handler9();
extern void irq_entry_handler10();
extern void irq_entry_handler11();
extern void irq_entry_handler12();
extern void irq_entry_handler13();
extern void irq_entry_handler14();
extern void irq_entry_handler15();

extern uint32_t int_handle(uint32_t,uint16_t);
extern void idt_init_entries();
extern void idt_init_handlers();
extern void idt_set_entry(uint8_t,idte_t);
extern void idt_set_handler(uint8_t,idth_t);
extern void idt_load();
extern void int_enable();
extern void int_disable();

#endif


