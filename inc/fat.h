// DEPRECATED: We will be using our own for speed and reliability sake

#ifndef __DEVLINUX__FAT_H
#define __DEVLINUX__FAT_H

#include <stdint.h>
#include <stdbool.h>
#include <vga.h>
#include <hd.h>

#define FAT_CLUSTER_SIZE 16

typedef struct __attribute__((packed)) {
	uint8_t name[11];
	uint8_t attributes;
	uint16_t reserved;
	uint16_t time_created;
	uint16_t date_created;
	uint16_t date_accessed;
	uint16_t zero;
	uint16_t time_modified;
	uint16_t date_modified;
	uint16_t address;
	uint32_t file_size;
} FAT_DIRECTORY_ENTRY;

typedef struct __attribute__((packed)) {
	FAT_DIRECTORY_ENTRY entries[32*FAT_CLUSTER_SIZE];
} FAT_DIRECTORY_TABLE;

typedef struct __attribute__((packed)) {
	uint8_t bootable;
	uint8_t start_head;
	uint8_t start_sector;
	uint8_t start_cylinder;
	uint8_t system_id;
	uint8_t end_head;
	uint8_t end_sector;
	uint8_t end_cylinder;
	uint32_t start_lba;
	uint32_t length;
} FAT_PARTITION_TABLE_ENTRY;

typedef struct __attribute__((packed)) {
	uint8_t bootloader[440];
	uint32_t signature;
	uint16_t unused;
	FAT_PARTITION_TABLE_ENTRY partitions[4];
	uint16_t boot_signature;
	
} FAT_MASTER_BOOT_RECORD;

extern void fat_write_new_partition(uint8_t,FAT_PARTITION_TABLE_ENTRY*);
extern void fat_read_partition_info(uint8_t,FAT_PARTITION_TABLE_ENTRY*);
extern void fat_init_allocation_table();
extern void fat_create_file(uint8_t*);
//extern void fat_delete_file(uint8_t*);
extern void fat_write_file(uint8_t*,uint8_t*);
extern void fat_read_file(uint8_t*,uint8_t*);
extern void fat_create_directory(uint8_t*);
extern void fat_change_directory(uint8_t*);

#endif


















