#include <gdt.h>

gdtent_t gdt_entries[GDT_LENGTH];

void gdt_set_gate(uint16_t index, gdtent_t entry)
{
	gdt_entries[index] = entry;
}

void gdt_get_ptr(gdtptr_t* ptr)
{
	ptr->size = GDT_LENGTH - 1;
	ptr->offset = (uint32_t)gdt_entries;
}

gdtent_t gdt_encode(uint32_t base, uint32_t limit, uint8_t type)
{
	uint8_t target[8];
	if(limit > 65536)
	{
		limit = limit >> 12;
		target[6] = 0xC0;
	}
	else
	{
		target[6] = 0x40;
	}
	target[0] = limit & 0xFF;
	target[1] = (limit >> 8) & 0xFF;
	target[6] |= (limit >> 16) & 0xF;
	
	target[2] = base & 0xFF;
	target[3] = (base >> 8) & 0xFF;
	target[4] = (base >> 16) & 0xFF;
	target[7] = (base >> 24) & 0xFF;
	
	target[5] = type;
	
	return *(gdtent_t*)target;
}

void gdt_init()
{
	gdtent_t nullSeg = gdt_encode(0, 0, 0);
	gdtent_t codeSeg = gdt_encode(0, 0xFFFFFFFF, 0x9A);
	gdtent_t dataSeg = gdt_encode(0, 0xFFFFFFFF, 0x92);
	gdt_set_gate(0, nullSeg);
	gdt_set_gate(1, codeSeg);
	gdt_set_gate(2, dataSeg);
	gdt_set_gate(3, codeSeg);
	gdt_set_gate(4, dataSeg);
	gdtptr_t gdtptr;
	gdt_get_ptr(&gdtptr);
	gdt_flush((uint32_t)&gdtptr);
}















