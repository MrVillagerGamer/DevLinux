#ifndef __DEVLINUX__PORT_H
#define __DEVLINUX__PORT_H

#include <stdint.h>

extern void port_out_byte(uint16_t,uint8_t);
extern void port_out_word(uint16_t,uint16_t);
extern void port_out_dword(uint16_t,uint32_t);
extern uint8_t port_in_byte(uint16_t);
extern uint16_t port_in_word(uint16_t);
extern uint32_t port_in_dword(uint16_t);

#endif