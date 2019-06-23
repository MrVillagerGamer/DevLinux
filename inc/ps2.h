#ifndef __DEVLINUX__PS2_H
#define __DEVLINUX__PS2_H

#include <stdint.h>
#include <stdbool.h>
#include <port.h>

#define PS2_COMMAND_PORT 0x64
#define PS2_DATA_PORT 0x60

extern void ps2_init_mouse();
extern void ps2_init_keyboard();
extern uint32_t ps2_handler_mouse(uint32_t);
extern uint32_t ps2_handler_keyboard(uint32_t);
//extern void ps2_get_key();
extern uint8_t ps2_get_button();
//extern void ps2_await_key();
extern uint8_t ps2_await_button();
extern uint32_t ps2_get_mouse_x();
extern uint32_t ps2_get_mouse_y();

#endif