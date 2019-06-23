#include <idt.h>

idte_t entries[256];
idth_t handlers[256];

void idt_set_entry(uint8_t index, idte_t entry)
{
	entries[index] = entry;
}

void idt_set_handler(uint8_t index, idth_t handler)
{
	handlers[index] = handler;
}

void idt_init_entries()
{
	vga_text_log_info("Initializing the default interrupt handlers");
	
	port_out_byte(0x20, 0x11);
	port_out_byte(0xA0, 0x11);
	port_out_byte(0x21, 0x20);
	port_out_byte(0xA1, 0x28);
	port_out_byte(0x21, 0x04);
	port_out_byte(0xA1, 0x02);
	port_out_byte(0x21, 0x01);
	port_out_byte(0xA1, 0x01);
	port_out_byte(0x21, 0x0);
	port_out_byte(0xA1, 0x0);
	
	idte_t blank_entry = {0};
	blank_entry.type_attr = 0x8e;
	blank_entry.selector = 0x08;
	uint16_t i;
	// Set with default values (null pointing handler functions)
	for(i = 0; i < 256; i++)
	{
		idt_set_entry((uint8_t) i, blank_entry);
	}
	// IRQ 0
	uint32_t irq_addr = (uint32_t) irq_entry_handler0;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(32, blank_entry);
	
	// IRQ 1
	irq_addr = (uint32_t) irq_entry_handler1;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(33, blank_entry);
	
	// IRQ 2
	irq_addr = (uint32_t) irq_entry_handler2;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(34, blank_entry);
	
	// IRQ 3
	irq_addr = (uint32_t) irq_entry_handler3;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(35, blank_entry);
	
	// IRQ 4
	irq_addr = (uint32_t) irq_entry_handler4;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(36, blank_entry);
	
	// IRQ 5
	irq_addr = (uint32_t) irq_entry_handler5;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(37, blank_entry);
	
	// IRQ 6
	irq_addr = (uint32_t) irq_entry_handler6;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(38, blank_entry);
	
	// IRQ 7
	irq_addr = (uint32_t) irq_entry_handler7;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(39, blank_entry);
	
	// IRQ 8
	irq_addr = (uint32_t) irq_entry_handler8;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(40, blank_entry);
	
	// IRQ 9
	irq_addr = (uint32_t) irq_entry_handler9;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(41, blank_entry);
	
	// IRQ 10
	irq_addr = (uint32_t) irq_entry_handler10;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(42, blank_entry);
	
	// IRQ 11
	irq_addr = (uint32_t) irq_entry_handler11;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(43, blank_entry);
	
	// IRQ 12
	irq_addr = (uint32_t) irq_entry_handler12;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(44, blank_entry);
	
	// IRQ 13
	irq_addr = (uint32_t) irq_entry_handler13;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(45, blank_entry);
	
	// IRQ 14
	irq_addr = (uint32_t) irq_entry_handler14;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(46, blank_entry);
	
	// IRQ 15
	irq_addr = (uint32_t) irq_entry_handler15;
	blank_entry.offset_low = irq_addr & 0xffff;
	blank_entry.offset_high = (irq_addr >> 16) & 0xffff;
	idt_set_entry(47, blank_entry);
	
}

void idt_init_handlers()
{
	idth_t null_addr = (idth_t) 0;
	uint16_t i;
	for(i = 0; i < 256; i++)
	{
		idt_set_handler((uint8_t)i, null_addr);
	}
}

uint32_t int_handle(uint32_t esp, uint16_t num)
{
	if(handlers[num] != 0)
	{
		esp = handlers[num](esp);
	}
	if(num != 0x20 && handlers[num] == 0)
	{
		vga_text_log_warn("Unhandled interrupt received");
	}
	
	if(num >= 40)
	{
		port_out_byte(0xA0, 0x20);
	}
	
	if(num >= 32)
	{
		port_out_byte(0x20, 0x20);
	}
	
	return esp;
}

void idt_load()
{
	vga_text_log_info("Loading the interrupt descriptor table");
	extern void load_idt(uint32_t);
	uint32_t idt_addr = (uint32_t) entries;
	uint32_t idt_ptr[2];
	idt_ptr[0] = (sizeof (idte_t) * 256) + ((idt_addr & 0xffff) << 16);
	idt_ptr[1] = idt_addr >> 16;
	load_idt((uint32_t)idt_ptr);
}

void int_enable()
{
	vga_text_log_info("Enabling hardware and software interrupts");
	
	__asm __volatile("sti");
}

void int_disable()
{
	__asm __volatile("cli");
}




