#include <ps2.h>
#include <idt.h>
#include <vga.h>

uint8_t ps2_buffer[3];
uint8_t ps2_offset = 0;
uint8_t ps2_button = 0;
bool ps2_button_down = 0;

int8_t ps2_mouse_delta_x = 0;
int8_t ps2_mouse_delta_y = 0;
uint32_t ps2_mouse_x = 0;
uint32_t ps2_mouse_y = 0;

uint8_t ps2_key_press;
uint8_t ps2_key_release;
bool ps2_key_down = 0;

void ps2_init_keyboard()
{
	vga_text_log_info("Initializing driver for PS/2 keyboard");
	idt_set_handler(0x21, ps2_handler_keyboard);
	while(port_in_byte(PS2_COMMAND_PORT) & 0x1)
	{
		uint8_t ack = port_in_byte(PS2_DATA_PORT);
	}
	port_out_byte(PS2_COMMAND_PORT, 0xAE);
	port_out_byte(PS2_COMMAND_PORT, 0x20);
	uint8_t state = port_in_byte(PS2_DATA_PORT) | 1;
	port_out_byte(PS2_COMMAND_PORT, 0x60);
	port_out_byte(PS2_DATA_PORT, state);
	port_out_byte(PS2_DATA_PORT, 0xF4);
}

uint32_t ps2_handler_keyboard(uint32_t esp)
{
	uint8_t key = port_in_byte(PS2_DATA_PORT);
	if((key & 0x80))
	{
		ps2_key_release = key & ~0x80;
	}
	else
	{
		ps2_key_press = key & ~0x80;
		ps2_key_down = 1;
	}
	return esp;
}

uint8_t ps2_get_key()
{
	return ps2_key_press;
}

uint8_t ps2_await_key()
{
	while(!ps2_key_down) {}
	ps2_key_down = 0;
	return ps2_key_press;
}

void ps2_init_mouse()
{
	vga_text_log_info("Initializing driver for PS/2 mouse");
	idt_set_handler(0x2C, ps2_handler_mouse);
	port_out_byte(PS2_COMMAND_PORT, 0xA8);
	port_out_byte(PS2_COMMAND_PORT, 0x20);
	uint8_t status = port_in_byte(PS2_DATA_PORT) | 2;
	port_out_byte(PS2_COMMAND_PORT, 0x60);
	port_out_byte(PS2_DATA_PORT, status);
	
	port_out_byte(PS2_COMMAND_PORT, 0xD4);
	port_out_byte(PS2_DATA_PORT, 0xF4);
	uint8_t ack = port_in_byte(PS2_DATA_PORT);
}

uint32_t ps2_handler_mouse(uint32_t esp)
{
	ps2_buffer[ps2_offset] = port_in_byte(PS2_DATA_PORT);
	ps2_offset = (ps2_offset + 1) % 3;
	if(ps2_offset == 0)
	{
		ps2_mouse_delta_x = ps2_buffer[1];
		ps2_mouse_delta_y = ps2_buffer[2];
		ps2_mouse_x += ps2_mouse_delta_x;
		ps2_mouse_y += ps2_mouse_delta_y;
		ps2_button = 3;
		if(ps2_buffer[0] & 0x4)
		{
			ps2_button = 2;
			ps2_button_down = 1;
		}
		if(ps2_buffer[0] & 0x2)
		{
			ps2_button = 1;
			ps2_button_down = 1;
		}
		if(ps2_buffer[0] & 0x1)
		{
			ps2_button = 0;
			ps2_button_down = 1;
		}
	}
	return esp;
}

uint32_t ps2_get_mouse_x()
{
	return ps2_mouse_x;
}

uint32_t ps2_get_mouse_y()
{
	return ps2_mouse_y;
}

uint8_t ps2_get_button()
{
	return ps2_button;
}

uint8_t ps2_await_button()
{
	while(!ps2_button_down) { }
	ps2_button_down = 0;
	return ps2_button;
}














