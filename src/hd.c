#include <hd.h>

HD_READ_WRITE_CALLBACK hd_read_func = (HD_READ_WRITE_CALLBACK)0;
HD_READ_WRITE_CALLBACK hd_write_func = (HD_READ_WRITE_CALLBACK)0;

bool hd_is_supported()
{
	return (hd_read_func != 0 && hd_write_func != 0);
}

void hd_init_read(HD_READ_WRITE_CALLBACK callback)
{
	if(hd_read_func == 0)
	{
		hd_read_func = callback;
	}
}

void hd_init_write(HD_READ_WRITE_CALLBACK callback)
{
	if(hd_write_func == 0)
	{
		hd_write_func = callback;
	}
}

void hd_read(uint32_t addr, uint8_t* data)
{
	(*hd_read_func)(addr, data);
}

void hd_write(uint32_t addr, uint8_t* data)
{
	(*hd_write_func)(addr, data);
}






















