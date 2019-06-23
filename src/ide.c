#include <ide.h>

bool ide_master = 0;
uint16_t ide_port_base = 0;

bool ide_init()
{
	ide_select_base(0);
	ide_set_master(1);
	bool success = ide_identify();
	if(success)
	{
		hd_init_read(&ide_read_lba28);
		hd_init_write(&ide_write_lba28);
	}
	return success;
}

void ide_wait_rdy()
{
	uint8_t status = port_in_byte(IDE_COMMAND_PORT + ide_port_base);
	while((status & 0x80) == 0x80)
	{
		status = port_in_byte(IDE_COMMAND_PORT + ide_port_base);
	}
}

void ide_wait_bsy()
{
	uint8_t status = port_in_byte(IDE_COMMAND_PORT + ide_port_base);
	while((status & 0x80) == 0x80)
	{
		status = port_in_byte(IDE_COMMAND_PORT + ide_port_base);
	}
}

void ide_select_base(uint8_t num)
{
	switch(num)
	{
	case 0:
		ide_port_base = 0x1F0;
		break;
	case 1:
		ide_port_base = 0x170;
		break;
	default:
		ide_port_base = 0x1F0;
		break;
	}
}

void ide_set_master(bool master)
{
	ide_master = master;
}

bool ide_identify()
{
	port_out_byte(IDE_DEVICE_PORT + ide_port_base, ide_master ? 0xA0 : 0xB0);
	
	uint8_t status1 = port_in_byte(IDE_CONTROL_PORT + ide_port_base);
	status1 |= 0x2;
	port_out_byte(IDE_CONTROL_PORT + ide_port_base, status1);
	
	port_out_byte(IDE_SECTOR_COUNT_PORT + ide_port_base, 0);
	port_out_byte(IDE_LBA_LOW_PORT + ide_port_base, 0);
	port_out_byte(IDE_LBA_MID_PORT + ide_port_base, 0);
	port_out_byte(IDE_LBA_HIGH_PORT + ide_port_base, 0);
	ide_wait_bsy();
	port_out_byte(IDE_COMMAND_PORT + ide_port_base, 0xEC);
	uint8_t status = port_in_byte(IDE_COMMAND_PORT + ide_port_base);
	if(status == 0x00)
	{
		return 0;
	}
	while(((status & 0x80) == 0x80))
	{
		status = port_in_byte(IDE_COMMAND_PORT + ide_port_base);
	}
	uint8_t check = port_in_byte(IDE_LBA_MID_PORT + ide_port_base);
	if(check != 0)
	{
		return 0;
	}
	check = port_in_byte(IDE_LBA_HIGH_PORT + ide_port_base);
	if(check != 0)
	{
		return 0;
	}
	while(((status & 0x08) != 0x08) && ((status & 0x01) != 0x01))
	{
		status = port_in_byte(IDE_COMMAND_PORT + ide_port_base);
	}
	if((status & 0x01) == 0x01)
	{
		return 0;
	}
	ide_wait_rdy();
	for(uint16_t i = 0; i < 256; i++)
	{
		uint16_t data = port_in_word(IDE_DATA_PORT + ide_port_base);
	}

	return 1;
}

void ide_write_lba28(uint32_t sector, uint8_t* data)
{
	if(sector & 0xf0000000)
	{
		return;
	}
	port_out_byte(IDE_DEVICE_PORT + ide_port_base, (ide_master ? 0xE0 : 0xF0) | ((sector >> 24) & 0x0F));                                                                     
	port_out_byte(IDE_ERROR_PORT + ide_port_base, 0);
	
	port_out_byte(IDE_SECTOR_COUNT_PORT + ide_port_base, 1);
	port_out_byte(IDE_LBA_LOW_PORT + ide_port_base, sector & 0xff);
	port_out_byte(IDE_LBA_MID_PORT + ide_port_base, (sector & 0xff00) >> 8);
	port_out_byte(IDE_LBA_HIGH_PORT + ide_port_base, (sector & 0xff0000) >> 16);
	ide_wait_bsy();
	port_out_byte(IDE_COMMAND_PORT + ide_port_base, 0x30);
	ide_wait_rdy();
	for(uint16_t i = 0; i < 256; i++)
	{
		uint16_t wdata = data[i];
		wdata |= (uint16_t)data[i+1] << 8;
		port_out_word(IDE_DATA_PORT + ide_port_base, wdata);
	}
	ide_flush();
}

void ide_read_lba28(uint32_t sector, uint8_t* data)
{
	if(sector & 0xf0000000)
	{
		return;
	}
	port_out_byte(IDE_DEVICE_PORT + ide_port_base, (ide_master ? 0xE0 : 0xF0) | ((sector >> 24) & 0x0F));                                                                     
	port_out_byte(IDE_ERROR_PORT + ide_port_base, 0);
	
	port_out_byte(IDE_SECTOR_COUNT_PORT + ide_port_base, 1);
	port_out_byte(IDE_LBA_LOW_PORT + ide_port_base, sector & 0xff);
	port_out_byte(IDE_LBA_MID_PORT + ide_port_base, (sector & 0xff00) >> 8);
	port_out_byte(IDE_LBA_HIGH_PORT + ide_port_base, (sector & 0xff0000) >> 16);
	ide_wait_bsy();
	port_out_byte(IDE_COMMAND_PORT + ide_port_base, 0x20);
	
	ide_wait_rdy();
	for(uint16_t i = 0; i < 256; i++)
	{
		uint16_t rdata = port_in_word(IDE_DATA_PORT + ide_port_base);
		
		data[i] = rdata & 0xff;
		data[i+1] = (rdata >> 8) & 0xff;
	}
}

void ide_flush()
{
	ide_wait_bsy();
	port_out_byte(IDE_COMMAND_PORT + ide_port_base, 0xE7);
	uint8_t status = port_in_byte(IDE_COMMAND_PORT + ide_port_base);
	while((status & 0x80) == 0x80)
	{
		status = port_in_byte(IDE_COMMAND_PORT + ide_port_base);
	}
}




























