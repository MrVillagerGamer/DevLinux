#ifndef __DEVLINUX__PCI_H
#define __DEVLINUX__PCI_H

#include <stdint.h>
#include <stdbool.h>
#include <vga.h>
#include <port.h>
#include <ide.h>

#define PCI_COMMAND_PORT 0xCF8
#define PCI_DATA_PORT 0xCFC

typedef struct {
	uint32_t port_base;
	uint32_t interrupt;
	uint16_t bus;
	uint16_t device;
	uint16_t function;
	uint16_t vendor_id;
	uint16_t device_id;
	uint8_t class_id;
	uint8_t subclass_id;
	uint8_t interface_id;
	uint8_t revision;
	uint8_t header_type;
} PCI_DEVICE_DESCRIPTOR;

extern uint32_t pci_config_read_dword(uint16_t, uint16_t, uint16_t, uint32_t);
extern uint16_t pci_config_read_word(uint16_t, uint16_t, uint16_t, uint32_t);
extern uint8_t pci_config_read_byte(uint16_t, uint16_t, uint16_t, uint32_t);

extern void pci_config_write_dword(uint16_t, uint16_t, uint16_t, uint32_t,uint32_t);
extern void pci_config_write_word(uint16_t, uint16_t, uint16_t, uint32_t,uint16_t);
extern void pci_config_write_byte(uint16_t, uint16_t, uint16_t, uint32_t,uint8_t);

extern bool pci_device_has_functions(uint16_t,uint16_t);
extern PCI_DEVICE_DESCRIPTOR pci_get_device_descriptor(uint16_t, uint16_t, uint16_t);
extern void pci_check_all_buses();
extern void pci_check_device(uint16_t,uint16_t);
extern void pci_check_function(uint16_t,uint16_t,uint16_t);

#endif




















