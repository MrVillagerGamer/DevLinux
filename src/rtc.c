#include <rtc.h>

uint32_t rtc_year;
uint8_t rtc_month;
uint8_t rtc_day;
uint8_t rtc_hour;
uint8_t rtc_minute;
uint8_t rtc_second;

uint8_t rtc_update_in_progress()
{
	port_out_byte(CMOS_INDEX_PORT, 0x0a);
	return (port_in_byte(CMOS_DATA_PORT) & 0x80);
}

uint8_t rtc_get_register_value(uint8_t reg)
{
	port_out_byte(CMOS_INDEX_PORT, reg);
	return port_in_byte(CMOS_DATA_PORT);
}

void rtc_read_registers()
{
	uint8_t century;
	uint8_t last_second;
	uint8_t last_minute;
	uint8_t last_hour;
	uint8_t last_day;
	uint8_t last_month;
	uint8_t last_year;
	
	while(rtc_update_in_progress());
	rtc_second = rtc_get_register_value(0x00);
	rtc_minute = rtc_get_register_value(0x02);
	rtc_hour = rtc_get_register_value(0x04);
	rtc_day = rtc_get_register_value(0x07);
	rtc_month = rtc_get_register_value(0x08);
	rtc_year = rtc_get_register_value(0x09);
	
	do 
	{
		last_second = rtc_second;
		last_minute = rtc_minute;
		last_hour = rtc_hour;
		last_day = rtc_day;
		last_month = rtc_month;
		last_year = rtc_year;
		
		while(rtc_update_in_progress());
		rtc_second = rtc_get_register_value(0x00);
		rtc_minute = rtc_get_register_value(0x02);
		rtc_hour = rtc_get_register_value(0x04);
		rtc_day = rtc_get_register_value(0x07);
		rtc_month = rtc_get_register_value(0x08);
		rtc_year = rtc_get_register_value(0x09);
	} while((last_second != rtc_second) || (last_minute != rtc_minute) || (last_hour != rtc_hour) ||
               (last_day != rtc_day) || (last_month != rtc_month) || (last_year != rtc_year));
	
	uint8_t register_b = rtc_get_register_value(0x0b);
	if(!(register_b & 0x04))
	{
		rtc_second = (rtc_second & 0x0F) + ((rtc_second / 16) * 10);
		rtc_second = (rtc_minute & 0x0F) + ((rtc_minute / 16) * 10);
		rtc_hour = ((rtc_hour & 0x0F) + (((rtc_hour & 0x70) / 16) * 10)) | (rtc_hour & 0x80);
		rtc_day = (rtc_day & 0x0F) + ((rtc_day / 16) * 10);
		rtc_month = (rtc_month & 0x0F) + ((rtc_month / 16) * 10);
		rtc_year = (rtc_year & 0x0F) + ((rtc_year / 16) * 10);
	}
	if(!(register_b & 0x02) && (rtc_hour & 0x80))
	{
		rtc_hour = ((rtc_hour & 0x7F) + 12) % 24;
	}
	rtc_year += RTC_CURRENT_CENTURY * 100;
}

uint8_t rtc_get_current_year()
{
	return rtc_year;
}

uint8_t rtc_get_current_month()
{
	return rtc_month;
}

uint8_t rtc_get_current_day()
{
	return rtc_day;
}

uint8_t rtc_get_current_hour()
{
	return rtc_hour;
}

uint8_t rtc_get_current_minute()
{
	return rtc_minute;
}

uint8_t rtc_get_current_second()
{
	return rtc_second;
}












