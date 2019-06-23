#ifndef __DEVLINUX__IDE_H
#define __DEVLINUX__IDE_H

#include <stdint.h>
#include <stdbool.h>
#include <port.h>
#include <vga.h>
#include <idt.h>
#include <hd.h>

#define IDE_DATA_PORT 0
#define IDE_ERROR_PORT 1
#define IDE_SECTOR_COUNT_PORT 2
#define IDE_LBA_LOW_PORT 3
#define IDE_LBA_MID_PORT 4
#define IDE_LBA_HIGH_PORT 5
#define IDE_DEVICE_PORT 6
#define IDE_COMMAND_PORT 7
#define IDE_CONTROL_PORT 0x206

extern void ide_select_base(uint8_t);
extern void ide_set_master(bool);
extern bool ide_identify();
extern void ide_write_lba28(uint32_t, uint8_t*);
extern bool ide_init();
//extern void ide_write_lba48(uint32_t, uint8_t*, uint16_t);
extern void ide_read_lba28(uint32_t, uint8_t*);
extern void ide_flush();
//extern void ide_read_lba48(uint64_t, uint8_t*, uint16_t);

#endif