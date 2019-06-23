#ifndef __DEVLINUX__RTC_H
#define __DEVLINUX__RTC_H

#include <stdint.h>
#include <port.h>

#define CMOS_INDEX_PORT 0x70
#define CMOS_DATA_PORT 0x71
#define RTC_CURRENT_CENTURY 20

extern uint8_t rtc_update_in_progress();
extern uint8_t rtc_get_register_value(uint8_t reg);
extern void rtc_read_registers();
extern uint8_t rtc_get_current_year();
extern uint8_t rtc_get_current_month();
extern uint8_t rtc_get_current_day();
extern uint8_t rtc_get_current_hour();
extern uint8_t rtc_get_current_minute();
extern uint8_t rtc_get_current_second();

#endif