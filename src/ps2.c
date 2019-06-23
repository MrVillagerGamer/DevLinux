#include <ps2.h>
#include <idt.h>
#include <vga.h>

uint8_t buffer[3];
uint8_t offset = 0;
uint8_t button = 0;
uint8_t buttonDown = 0;

int8_t mouse_delta_x = 0;
int8_t mouse_delta_y = 0;
uint32_t mouse_x = 0;
uint32_t mouse_y = 0;

uint8_t key_press;
uint8_t key_release;

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
		key_release = key;
	}
	else
	{
		key_press = key;
	}
	return esp;
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
	buffer[offset] = port_in_byte(PS2_DATA_PORT);
	offset = (offset + 1) % 3;
	if(offset == 0)
	{
		mouse_delta_x = buffer[1];
		mouse_delta_y = buffer[2];
		mouse_x += mouse_delta_x;
		mouse_y += mouse_delta_y;
		button = 3;
		if(buffer[0] & 0x4)
		{
			button = 2;
			buttonDown = 1;
		}
		if(buffer[0] & 0x2)
		{
			button = 1;
			buttonDown = 1;
		}
		if(buffer[0] & 0x1)
		{
			button = 0;
			buttonDown = 1;
		}
	}
	return esp;
}

uint32_t ps2_get_mouse_x()
{
	return mouse_x;
}

uint32_t ps2_get_mouse_y()
{
	return mouse_y;
}

uint8_t ps2_get_button()
{
	return button;
}

uint8_t ps2_await_button()
{
	while(!buttonDown) { }
	buttonDown = 0;
	return button;
}














