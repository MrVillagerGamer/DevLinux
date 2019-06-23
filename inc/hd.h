#ifndef __DEVLINUX__HD_H
#define __DEVLINUX__HD_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*HD_READ_WRITE_CALLBACK)(uint32_t,uint8_t*);

extern void hd_init_read(HD_READ_WRITE_CALLBACK);
extern void hd_init_write(HD_READ_WRITE_CALLBACK);
extern bool hd_is_supported();
extern void hd_write(uint32_t,uint8_t*);
extern void hd_read(uint32_t,uint8_t*);

#endif