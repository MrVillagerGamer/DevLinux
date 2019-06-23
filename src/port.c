#include <port.h>

void port_out_byte(uint16_t port, uint8_t data)
{
	__asm __volatile("outb %0, %1"::"a"(data),"Nd"(port)); 
}

void port_out_word(uint16_t port, uint16_t data)
{
	__asm __volatile("outw %0, %1"::"a"(data),"Nd"(port)); 
}

void port_out_dword(uint16_t port, uint32_t data)
{
	__asm __volatile("outl %0, %1"::"a"(data),"Nd"(port)); 
}

uint8_t port_in_byte(uint16_t port)
{
	uint8_t data;
	__asm __volatile("inb %1, %0":"=a"(data):"Nd"(port));
	return data;
}

uint16_t port_in_word(uint16_t port)
{
	uint16_t data;
	__asm __volatile("inw %1, %0":"=a"(data):"Nd"(port));
	return data;
}

uint32_t port_in_dword(uint16_t port)
{
	uint32_t data;
	__asm __volatile("inl %1, %0":"=a"(data):"Nd"(port));
	return data;
}























