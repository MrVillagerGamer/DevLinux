#include <vga.h>

uint32_t vga_x = 0;
uint32_t vga_y = 0;
uint8_t vga_default_color = 0x07;
uint8_t vga_color = 0x07;

uint16_t vga_mode_width = 80;
uint16_t vga_mode_height = 25;

uint16_t vga_get_mode_width()
{
	return vga_mode_width;
}

uint16_t vga_get_mode_height()
{
	return vga_mode_height;
}

uint8_t vga_90x30x16_text[] =
{
/* MISC */
	0xE7,
/* SEQ */
	0x03, 0x01, 0x03, 0x00, 0x02,
/* CRTC */
	0x6B, 0x59, 0x5A, 0x82, 0x60, 0x8D, 0x0B, 0x3E,
	0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x00,
	0xEA, 0x0C, 0xDF, 0x2D, 0x10, 0xE8, 0x05, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00,
};

uint8_t vga_320x200x256_graph[] = {
	/* MISC */
	0x63,
	/* SEQ */
	0x03, 0x01, 0x0F, 0x00, 0x0E,
	/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
	0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
	0xFF,
	/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
	0xFF,
	/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x41, 0x00, 0x0F, 0x00,	0x00
};

uint8_t vga_90x60x16_text[] =
{
/* MISC */
	0xE7,
/* SEQ */
	0x03, 0x01, 0x03, 0x00, 0x02,
/* CRTC */
	0x6B, 0x59, 0x5A, 0x82, 0x60, 0x8D, 0x0B, 0x3E,
	0x00, 0x47, 0x06, 0x07, 0x00, 0x00, 0x00, 0x00,
	0xEA, 0x0C, 0xDF, 0x2D, 0x08, 0xE8, 0x05, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00,
};

uint8_t vga_80x50x16_text[] =
{
/* MISC */
	0x67,
/* SEQ */
	0x03, 0x00, 0x03, 0x00, 0x02,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
	0x00, 0x47, 0x06, 0x07, 0x00, 0x00, 0x01, 0x40,
	0x9C, 0x8E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
	0xFF, 
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF, 
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00,
};

uint8_t vga_80x25x16_text[] =
{
/* MISC */
	0x67,
/* SEQ */
	0x03, 0x00, 0x03, 0x00, 0x02,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
	0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x50,
	0x9C, 0x0E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00
};

void vga_set_color(uint8_t c)
{
	vga_color = c;
	vga_default_color = c;
}

void vga_text_clear()
{
	uint32_t i;
	uint32_t j;
	uint8_t* vram = (uint8_t*)0xb8000;
	for(i = 0; i < vga_mode_width; i++)
	{
		for(j = 0; j < vga_mode_height; j++)
		{
			vram[(i+vga_mode_width*j)*2] = ' ';
			vram[(i+vga_mode_width*j)*2+1] = vga_color;
		}
	}
}

void vga_text_scroll_down()
{
	uint32_t i;
	uint32_t j;
	
	uint8_t* vram = (uint8_t*)0xb8000;
	
	for(i = 0; i < vga_mode_width; i++)
	{
		for(j = 1; j < vga_mode_height; j++)
		{
			vram[(i+vga_mode_width*(j-1))*2] = vram[(i+vga_mode_width*j)*2];
			vram[(i+vga_mode_width*(j-1))*2+1] = vram[(i+vga_mode_width*j)*2+1];
		}
		vram[(i+vga_mode_width*(vga_mode_height-1))*2] = ' ';
		vram[(i+vga_mode_width*(vga_mode_height-1))*2+1] = vga_color;
	}
}

void vga_text_put_char(uint8_t c)
{
	uint8_t* vram = (uint8_t*)0xb8000;
	switch(c)
	{
	case '\n':
		vga_x = 0;
		vga_y++;
		break;
	default:
		vram[(vga_x+vga_mode_width*vga_y)*2] = c;
		vram[(vga_x+vga_mode_width*vga_y)*2+1] = vga_color;
		vga_x++;
		break;
	}
	if(vga_x >= vga_mode_width)
	{
		vga_x = 0;
		vga_y++;
	}
	if(vga_y >= vga_mode_height)
	{
		vga_text_scroll_down();
		vga_y--;
	}
}

void vga_text_put_string(uint8_t* str)
{
	uint32_t i = 0;
	while(str[i])
	{
		vga_text_put_char(str[i]);
		i++;
	}
}

void vga_text_put_hex4(uint8_t value)
{
	char foo[2];
	foo[1] = 0;
	char* bar = "0123456789abcdef";	
	foo[0] = bar[value & 0xf];
	vga_text_put_string(foo);
}

void vga_text_put_hex8(uint8_t value)
{
	char foo[3];
	foo[2] = 0;
	char* bar = "0123456789abcdef";
	for(uint8_t i = 0; i < 2; i++)
	{
		foo[1-i] = bar[(value >> (i * 4)) & 0xf];
	}
	vga_text_put_string(foo);
}

void vga_text_put_hex16(uint16_t value)
{
	char foo[5];
	foo[4] = 0;
	char* bar = "0123456789abcdef";
	for(uint8_t i = 0; i < 4; i++)
	{
		foo[3-i] = bar[(value >> (i * 4)) & 0xf];
	}
	vga_text_put_string(foo);
}

void vga_text_put_hex32(uint32_t value)
{
	char foo[9];
	foo[8] = 0;
	char* bar = "0123456789abcdef";
	for(uint8_t i = 0; i < 8; i++)
	{
		foo[7-i] = bar[(value >> (i * 4)) & 0xf];
	}
	vga_text_put_string(foo);
}

void vga_set_cursor_shape(uint8_t min, uint8_t max)
{
	
}

void vga_set_cursor_pos(uint8_t x, uint8_t y)
{
	
}

void vga_set_video_mode(uint8_t mode)
{
	vga_mode_width = 80;
	vga_mode_height = 25;
	uint8_t* regs = vga_80x25x16_text;
	if(mode == 0x1)
	{
		vga_mode_width = 80;
		vga_mode_height = 50;
		regs = vga_80x50x16_text;
	}
	else if(mode == 0x2)
	{
		vga_mode_width = 90;
		vga_mode_height = 30;
		regs = vga_90x30x16_text;
	}
	else if(mode == 0x3)
	{
		vga_mode_width = 90;
		vga_mode_height = 60;
		regs = vga_90x60x16_text;
	}
	else if(mode == 0x4)
	{
		vga_mode_width = 320;
		vga_mode_height = 200;
		regs = vga_320x200x256_graph;
	}
	port_out_byte(VGA_MISC_PORT, *(regs++));
	for(uint8_t i = 0; i < 5; i++)
	{
		port_out_byte(VGA_SEQ_INDEX_PORT, i);
		port_out_byte(VGA_SEQ_DATA_PORT, *(regs++));
	}
	port_out_byte(VGA_CRTC_INDEX_PORT, 0x03);
	port_out_byte(VGA_CRTC_DATA_PORT, port_in_byte(VGA_CRTC_DATA_PORT) | 0x80);
	port_out_byte(VGA_CRTC_INDEX_PORT, 0x11);
	port_out_byte(VGA_CRTC_DATA_PORT, port_in_byte(VGA_CRTC_DATA_PORT) & ~0x80);
	
	regs[0x03] |= 0x80;
	regs[0x11] &= ~0x80;
	
	for(uint8_t i = 0; i < 25; i++)
	{
		port_out_byte(VGA_CRTC_INDEX_PORT, i);
		port_out_byte(VGA_CRTC_DATA_PORT, *(regs++));
	}
	for(uint8_t i = 0; i < 9; i++)
	{
		port_out_byte(VGA_GC_INDEX_PORT, i);
		port_out_byte(VGA_GC_DATA_PORT, *(regs++));
	}
	for(uint8_t i = 0; i < 21; i++)
	{
		port_in_byte(VGA_AC_RESET_PORT);
		port_out_byte(VGA_AC_INDEX_PORT, i);
		port_out_byte(VGA_AC_WRITE_PORT, *(regs++));
	}
	port_in_byte(VGA_AC_RESET_PORT);
	port_out_byte(VGA_AC_INDEX_PORT, 0x20);
	
}

void vga_graph_put_pixel(uint16_t x, uint16_t y)
{
	uint8_t* vram = (uint8_t*)0xa0000;
	vram[x+vga_mode_width*y] = vga_color;
}

void vga_text_log_warn(uint8_t* msg)
{
	vga_color = vga_default_color;
	vga_text_put_string("\n[");
	vga_color = (vga_default_color & 0xf0) | 0x06;
	vga_text_put_string("WARN");
	vga_color = vga_default_color;
	vga_text_put_string("] ");
	vga_text_put_string(msg);
}

void vga_text_log_error(uint8_t* msg)
{
	vga_color = vga_default_color;
	vga_text_put_string("\n[");
	vga_color = (vga_default_color & 0xf0) | 0x04;
	vga_text_put_string("FAIL");
	vga_color = vga_default_color;
	vga_text_put_string("] ");
	vga_text_put_string(msg);
}

void vga_text_log_info(uint8_t* msg)
{
	vga_color = vga_default_color;
	vga_text_put_string("\n[");
	vga_color = (vga_default_color & 0xf0) | 0x02;
	vga_text_put_string("INFO");
	vga_color = vga_default_color;
	vga_text_put_string("] ");
	vga_text_put_string(msg);
}























