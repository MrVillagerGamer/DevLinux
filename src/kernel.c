#include <stdint.h>
#include <idt.h>
#include <vga.h>
#include <ps2.h>
#include <rtc.h>
#include <ide.h>
#include <fat.h>
#include <pci.h>
#include <fat.h>

void kernel_main()
{
	vga_set_video_mode(2);
	
	vga_set_color(0x07);
	vga_text_clear();

	vga_text_log_info("Loaded the global descriptor table");
	
	idt_init_handlers();
	idt_init_entries();
	
	ps2_init_keyboard();
	ps2_init_mouse();
	
	idt_load();
	int_enable();
	
	pci_check_all_buses();
	FAT_PARTITION_TABLE_ENTRY entry;
	entry.start_lba = 1;
	entry.length = 1024*1024*1024 / 512;
	fat_write_new_partition(0, &entry);
	fat_read_partition_info(0, &entry);
	fat_init_allocation_table();
	
	fat_create_file("file1");
	fat_create_file("file2");
	
	uint8_t wbuffer1[512*FAT_CLUSTER_SIZE] = "this is file 1";
	uint8_t wbuffer2[512*FAT_CLUSTER_SIZE] = "this is file 2";
	uint8_t rbuffer1[512*FAT_CLUSTER_SIZE];
	uint8_t rbuffer2[512*FAT_CLUSTER_SIZE];
	
	fat_write_file("file1", wbuffer1);
	fat_write_file("file2", wbuffer2);
	fat_read_file("file1", rbuffer1);
	fat_read_file("file2", rbuffer2);
	
	vga_text_put_string("\n");
	vga_text_put_string(rbuffer1);
	vga_text_put_string("\n");
	vga_text_put_string(rbuffer2);
	
	fat_create_directory("dir1");
	fat_change_directory("dir1");
	fat_create_file("file3");
	fat_create_file("file4");
	
	uint8_t wbuffer3[512*FAT_CLUSTER_SIZE] = "this is file 3 in dir 1";
	uint8_t wbuffer4[512*FAT_CLUSTER_SIZE] = "this is file 4 in dir 1";
	uint8_t rbuffer3[512*FAT_CLUSTER_SIZE];
	uint8_t rbuffer4[512*FAT_CLUSTER_SIZE];
	
	fat_write_file("file3", wbuffer3);
	fat_write_file("file4", wbuffer4);
	fat_read_file("file3", rbuffer3);
	fat_read_file("file4", rbuffer4);
	
	vga_text_put_string("\n");
	vga_text_put_string(rbuffer3);
	vga_text_put_string("\n");
	vga_text_put_string(rbuffer4);
	
	fat_change_directory("..");
	fat_read_file("file1", rbuffer1);
	fat_read_file("file2", rbuffer2);
	vga_text_put_string("\n");
	vga_text_put_string(rbuffer1);
	vga_text_put_string("\n");
	vga_text_put_string(rbuffer2);
	
	//ata_init();
	//ata_select_base(0);
	//ata_set_master(1);
	//ata_identify();
	//uint8_t buffer[256];
	
	
	while(1)
	{
		/*
		rtc_read_registers();
		uint8_t* year = uitoa(rtc_get_current_year(), buffer, 10);
		vga_text_put_string(year);
		vga_text_put_string("/");
		uint8_t* month = uitoa(rtc_get_current_month(), buffer, 10);
		vga_text_put_string(month);
		vga_text_put_string("/");
		uint8_t* day = uitoa(rtc_get_current_day(), buffer, 10);
		vga_text_put_string(day);
		vga_text_put_string(" ");
		uint8_t* hour = uitoa(rtc_get_current_hour(), buffer, 10);
		vga_text_put_string(hour);
		vga_text_put_string(":");
		uint8_t* minute = uitoa(rtc_get_current_minute(), buffer, 10);
		vga_text_put_string(minute);
		vga_text_put_string(":");
		uint8_t* second = uitoa(rtc_get_current_second(), buffer, 10);
		vga_text_put_string(second);
		vga_text_put_string("\n");
		*/
	}
}













