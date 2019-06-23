#include <pci.h>

PCI_DEVICE_DESCRIPTOR pci_devices[256*32*8];
uint32_t pci_device_count = 0;

uint32_t pci_config_read_dword(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset)
{
	uint32_t id = 0x1 << 31
		| ((bus & 0xff) << 16)
		| ((device & 0x1F) << 11)
		| ((function & 0x07) << 8)
		| (offset & 0xFC);
	
	port_out_dword(PCI_COMMAND_PORT, id);
	uint32_t result = port_in_dword(PCI_DATA_PORT);
	return result >> (8 * (offset % 4));
}

uint16_t pci_config_read_word(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset)
{
	return (uint16_t)pci_config_read_dword(bus, device, function, offset);
}

uint8_t pci_config_read_byte(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset)
{
	return (uint8_t)pci_config_read_dword(bus, device, function, offset);
}

void pci_config_write_dword(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset, uint32_t value)
{
	uint32_t id = 0x1 << 31
		| ((bus & 0xff) << 16)
		| ((device & 0x1F) << 11)
		| ((function & 0x07) << 8)
		| (offset & 0xFC);
	
	port_out_dword(PCI_COMMAND_PORT, id);
	port_out_dword(PCI_DATA_PORT, value);
}

void pci_config_write_word(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset, uint16_t value)
{
	pci_config_write_dword(bus, device, function, offset, value);
}

void pci_config_write_byte(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset, uint8_t value)
{
	pci_config_write_dword(bus, device, function, offset, value);
}

void pci_check_function(uint16_t bus, uint16_t device, uint16_t function)
{
	PCI_DEVICE_DESCRIPTOR dev = pci_get_device_descriptor(bus, device, function);
	if(dev.class_id == 0x01)
	{
		if(dev.subclass_id == 0x01)
		{
			vga_text_log_info("Found supported device called integrated device electronics");
			vga_text_log_info("Initializing driver for integrated device electronics");
			if(!ide_init())
			{
				vga_text_log_error("Initialization failed for integrated device electronics");
				while(1);
			}
		}
	}
}

void pci_check_device(uint16_t bus, uint16_t device)
{
	uint16_t function = 0;
	PCI_DEVICE_DESCRIPTOR dev1 = pci_get_device_descriptor(bus, device, function);
	if(dev1.vendor_id == 0xFFFF)
	{
		return;
	}
	pci_check_function(bus, device, function);
	if((dev1.header_type & 0x80) != 0)
	{
		for(function = 1; function < 8; function++)
		{
			dev1 = pci_get_device_descriptor(bus, device, function);
			if(dev1.vendor_id != 0xFFFF)
			{
				pci_check_function(bus, device, function);
			}
		}
	}
}

void pci_check_all_buses()
{
	vga_text_log_info("Scanning for peripheral component interconnect devices");
	for(uint16_t bus = 0; bus < 256; bus++)
	{
		for(uint16_t device = 0; device < 32; device++)
		{
			pci_check_device(bus, device);
		}
	}
	vga_text_log_info("Finished scanning peripheral component interconnect");
}

PCI_DEVICE_DESCRIPTOR pci_get_device_descriptor(uint16_t bus, uint16_t device, uint16_t function)
{
	PCI_DEVICE_DESCRIPTOR result;
	result.bus = bus;
	result.device = device;
	result.function = function;
	
	result.vendor_id = pci_config_read_dword(bus, device, function, 0x00);
	result.device_id = pci_config_read_dword(bus, device, function, 0x02);
	
	result.class_id = pci_config_read_dword(bus, device, function, 0x0b);
	result.subclass_id = pci_config_read_dword(bus, device, function, 0x0a);
	result.interface_id = pci_config_read_dword(bus, device, function, 0x09);
	
	result.revision = pci_config_read_dword(bus, device, function, 0x08);
	result.interrupt = pci_config_read_dword(bus, device, function, 0x3C);
	result.header_type = pci_config_read_dword(bus, device, function, 0x0E);
	
	return result;
}




















