#include <stdint.h>
#include <idt.h>
#include <vga.h>
#include <ps2.h>
#include <rtc.h>
#include <ide.h>
#include <pci.h>
#include <gdt.h>

/*
  ____             _     _                  
 |  _ \  _____   _| |   (_)_ __  _   ___  __
 | | | |/ _ \ \ / / |   | | '_ \| | | \ \/ /
 | |_| |  __/\ V /| |___| | | | | |_| |>  < 
 |____/ \___| \_/ |_____|_|_| |_|\__,_/_/\_\
                                            
*/

void show_menu()
{
	uint8_t sel = 0;
	bool filesystem_mounted = 0;
	while(1)
	{
		vga_set_color(0x07);
		vga_text_clear();
		//vga_text_put_string_big(" DevLinux\n");
		vga_text_put_string("  ____             _     _                  \n");
		vga_text_put_string(" |  _ \\  _____   _| |   (_)_ __  _   ___  __\n");
		vga_text_put_string(" | | | |/ _ \\ \\ / / |   | | '_ \\| | | \\ \\/ /\n");
		vga_text_put_string(" | |_| |  __/\\ V /| |___| | | | | |_| |>  < \n");
		vga_text_put_string(" |____/ \\___| \\_/ |_____|_|_| |_|\\__,_/_/\\_\\\n");
		vga_text_put_string("\n");
		if(sel == 0)
			vga_set_color(0x70);
		else
			vga_set_color(0x07);
		vga_text_put_string("  Start DevLinux    \n");
		if(sel == 1)
			vga_set_color(0x70);
		else
			vga_set_color(0x07);
		vga_text_put_string("  Advanced Options  \n");
		if(sel == 2)
			vga_set_color(0x70);
		else
			vga_set_color(0x07);
		vga_text_put_string("  Mount Filesystem  \n");
		if(sel == 3)
			vga_set_color(0x70);
		else
			vga_set_color(0x07);
		vga_text_put_string("  Create Partition  \n");
		uint8_t key = ps2_await_key();
		if(key == 72 && sel > 0)
		{
			sel--;
		}
		if(key == 80 && sel < 3)
		{
			sel++;
		}
		if(key == 28)
		{
			if(sel == 0)
			{
				break;
			}
			if(sel == 2)
			{
				filesystem_mounted = 1;
			}
		}
	}
	vga_text_clear();
	if(!filesystem_mounted)
	{
		vga_text_log_error("No filesystem.");
		while(1);
	}
}

void kernel_main(uint32_t multiboot_structure)
{	
	vga_text_clear();
	vga_text_log_info("Loading the global descriptor table.");
	gdt_init();
	idt_init_handlers();
	idt_init_entries();
	ps2_init_keyboard();
	ps2_init_mouse();
	idt_load();
	int_enable();
	pci_check_all_buses();
	show_menu();
	vga_text_put_string("\nDevLinux has booted successfully.");
	
	while(1);
}













