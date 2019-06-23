#include <fat.h>

uint32_t fat_partition_start;
uint32_t fat_partition_length;
uint32_t fat_allocation_table_start;
uint32_t fat_allocation_table_length;
uint32_t fat_root_directory_address;
uint32_t fat_current_directory = 0;

void fat_write_new_partition(uint8_t index, FAT_PARTITION_TABLE_ENTRY* desc)
{
	if(!hd_is_supported())
	{
		return;
	}
	FAT_MASTER_BOOT_RECORD mbr;
	hd_read(0, (uint8_t*)&mbr);
	mbr.partitions[index] = *desc;
	hd_write(0, (uint8_t*)&mbr);
}

void fat_read_partition_info(uint8_t index, FAT_PARTITION_TABLE_ENTRY* desc)
{
	if(!hd_is_supported())
	{
		return;
	}
	FAT_MASTER_BOOT_RECORD mbr;
	hd_read(0, (uint8_t*)&mbr);
	*desc = mbr.partitions[index];
	fat_partition_start = mbr.partitions[index].start_lba;
	fat_partition_length = mbr.partitions[index].length;
	fat_allocation_table_start = fat_partition_start;
	fat_allocation_table_length = (fat_partition_length / FAT_CLUSTER_SIZE) / 256;
	fat_root_directory_address = fat_allocation_table_start + fat_allocation_table_length;
}

void fat_init_allocation_table()
{
	uint32_t start = fat_allocation_table_start;
	uint32_t end = start + fat_allocation_table_length + FAT_CLUSTER_SIZE;
	uint8_t buffer[512];
	for(uint32_t i = 0; i < 512; i++)
	{
		buffer[i] = 0;
	}
	for(uint32_t i = start; i < end; i++)
	{
		hd_write(i, buffer);
	}
}

void fat_read_cluster(uint32_t index, uint8_t* data)
{
	for(uint32_t i = 0; i < FAT_CLUSTER_SIZE; i++)
	{
		hd_read(fat_allocation_table_start+index*FAT_CLUSTER_SIZE+i, data+i*512);
	}
}

void fat_write_cluster(uint32_t index, uint8_t* data)
{
	for(uint32_t i = 0; i < FAT_CLUSTER_SIZE; i++)
	{
		hd_write(fat_allocation_table_start+index*FAT_CLUSTER_SIZE+i, data+i*512);
	}
}

bool fat_cluster_in_use(uint32_t index)
{
	uint8_t buffer[fat_allocation_table_length*512];
	uint32_t j = index / 256;
	hd_read(fat_allocation_table_start+j, buffer+j*512);	
	uint16_t* buffer2 = (uint16_t*)buffer;
	bool in_use = 0;
	if(buffer2[index] != 0) in_use = 1;
	return in_use;
}

uint16_t fat_find_free_cluster()
{
	uint16_t start = fat_allocation_table_length / FAT_CLUSTER_SIZE + 1;
	uint16_t end = (fat_partition_length - (start * FAT_CLUSTER_SIZE)) / FAT_CLUSTER_SIZE;
	for(uint16_t i = start; i < end; i++)
	{
		if(!fat_cluster_in_use(i)) return i;
	}
	return 0;
}

void fat_mark_cluster(uint16_t index, uint16_t value)
{
	uint32_t j = index / 256;
	uint8_t buffer[fat_allocation_table_length*512];
	hd_read(fat_allocation_table_start+j, buffer+j*512);	
	uint16_t* buffer2 = (uint16_t*)buffer;
	buffer2[index] = value;
	hd_write(fat_allocation_table_start+j, buffer+j*512);
}

uint16_t fat_get_value(uint16_t index)
{
	uint32_t j = index / 256;
	uint8_t buffer[fat_allocation_table_length*512];	
	hd_read(fat_allocation_table_start+j, buffer+j*512);
	uint16_t* buffer2 = (uint16_t*)buffer;
	return buffer2[index];
}

bool fat_are_names_equal(uint8_t* n1, uint8_t* n2)
{
	bool equal = 1;
	for(uint8_t i = 0; i < 11; i++)
	{
		if(n1[i] == 0 && n2[i] == 0) break;
		if(n1[i] != n2[i]) equal = 0; 
	}
	return equal;
}

void fat_change_directory(uint8_t* name)
{
	FAT_DIRECTORY_TABLE dt;
	fat_read_cluster(fat_allocation_table_length/FAT_CLUSTER_SIZE+fat_current_directory, (uint8_t*)&dt);
	uint32_t i;
	for(i = 0; i < 32*FAT_CLUSTER_SIZE; i++)
	{
		if(fat_are_names_equal(name, dt.entries[i].name)) break;
	}
	uint32_t offset = fat_allocation_table_length/FAT_CLUSTER_SIZE;
	fat_current_directory = dt.entries[i].address - offset;
}

void fat_create_directory(uint8_t* name)
{
	FAT_DIRECTORY_TABLE dt;
	fat_read_cluster(fat_allocation_table_length/FAT_CLUSTER_SIZE+fat_current_directory, (uint8_t*)&dt);
	uint32_t i;
	for(i = 0; i < 32*FAT_CLUSTER_SIZE; i++)
	{
		if(dt.entries[i].name[0] == 0) break;
	}
	FAT_DIRECTORY_ENTRY entry;
	for(uint8_t j = 0; j < 11; j++)
	{
		entry.name[j] = name[j];
	}
	entry.attributes = 0x10;
	entry.time_created = 0;
	entry.date_created = 0;
	entry.date_accessed = 0;
	entry.time_modified = 0;
	entry.date_modified = 0;
	entry.address = fat_find_free_cluster();
	fat_mark_cluster(entry.address, 0xFFF8);
	
	FAT_DIRECTORY_TABLE table;
	for(uint32_t j = 0; j < 32*FAT_CLUSTER_SIZE; j++)
	{
		table.entries[j].name[0] = 0;
		table.entries[j].attributes = 0;
		table.entries[j].time_created = 0;
		table.entries[j].date_created = 0;
		table.entries[j].date_accessed = 0;
		table.entries[j].time_modified = 0;
		table.entries[j].date_modified = 0;
	}
	uint32_t offset = fat_allocation_table_length/FAT_CLUSTER_SIZE;
	table.entries[0].name[0] = '.';
	table.entries[0].name[1] = '.';
	table.entries[0].name[2] = 0;
	table.entries[0].attributes = 0x10;
	table.entries[0].address = fat_current_directory + offset;
	fat_write_cluster(entry.address, (uint8_t*)&table);
	
	dt.entries[i] = entry;
	fat_write_cluster(fat_allocation_table_length/FAT_CLUSTER_SIZE+fat_current_directory, (uint8_t*)&dt);
}

void fat_create_file(uint8_t* name)
{
	FAT_DIRECTORY_TABLE dt;
	fat_read_cluster(fat_allocation_table_length/FAT_CLUSTER_SIZE+fat_current_directory, (uint8_t*)&dt);
	uint32_t i;
	for(i = 0; i < 32*FAT_CLUSTER_SIZE; i++)
	{
		if(dt.entries[i].name[0] == 0) break;
	}
	FAT_DIRECTORY_ENTRY entry;
	for(uint8_t j = 0; j < 11; j++)
	{
		entry.name[j] = name[j];
	}
	entry.attributes = 0;
	
	entry.time_created = 0;
	entry.date_created = 0;
	entry.date_accessed = 0;
	entry.time_modified = 0;
	entry.date_modified = 0;
	entry.address = fat_find_free_cluster();
	fat_mark_cluster(entry.address, 0xFFF8);
	
	dt.entries[i] = entry;
	fat_write_cluster(fat_allocation_table_length/FAT_CLUSTER_SIZE+fat_current_directory, (uint8_t*)&dt);
}

void fat_write_file(uint8_t* name, uint8_t* data)
{
	FAT_DIRECTORY_TABLE dt;
	fat_read_cluster(fat_allocation_table_length/FAT_CLUSTER_SIZE+fat_current_directory, (uint8_t*)&dt);
	uint32_t i;
	for(i = 0; i < 32*FAT_CLUSTER_SIZE; i++)
	{
		if(fat_are_names_equal(name, dt.entries[i].name))break;
	}
	fat_write_cluster(dt.entries[i].address, data);
}

void fat_read_file(uint8_t* name, uint8_t* data)
{
	FAT_DIRECTORY_TABLE dt;
	fat_read_cluster(fat_allocation_table_length/FAT_CLUSTER_SIZE+fat_current_directory, (uint8_t*)&dt);
	uint32_t i;
	for(i = 0; i < 32*FAT_CLUSTER_SIZE; i++)
	{
		if(fat_are_names_equal(name, dt.entries[i].name)) break;
	}
	fat_read_cluster(dt.entries[i].address, data);
}






































