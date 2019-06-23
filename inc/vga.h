#ifndef __DEVLINUX__VGA_H
#define __DEVLINUX__VGA_H

#define VGA_MISC_PORT 0x3C2
#define VGA_CRTC_INDEX_PORT 0x3D4
#define VGA_CRTC_DATA_PORT 0x3D5
#define VGA_SEQ_INDEX_PORT 0x3C4
#define VGA_SEQ_DATA_PORT 0x3C5
#define VGA_GC_INDEX_PORT 0x3CE
#define VGA_GC_DATA_PORT 0x3CF
#define VGA_AC_INDEX_PORT 0x3C0
#define VGA_AC_RESET_PORT 0x3CF
#define VGA_AC_WRITE_PORT 0x3C0
#define VGA_AC_READ_PORT 0x3DA

#include <stdint.h>
#include <port.h>

extern uint16_t vga_get_mode_width();
extern uint16_t vga_get_mode_height();
extern void vga_set_color(uint8_t);
extern void vga_text_clear();
extern void vga_text_put_char(uint8_t);
extern void vga_text_put_string(uint8_t*);
extern void vga_text_put_hex4(uint8_t);
extern void vga_text_put_hex8(uint8_t);
extern void vga_text_put_hex16(uint16_t);
extern void vga_text_put_hex32(uint32_t);
extern void vga_text_scroll_down();
extern void vga_text_set_cursor_shape(uint8_t, uint8_t);
extern void vga_text_set_cursor_pos(uint8_t, uint8_t);
extern void vga_set_video_mode(uint8_t);
extern void vga_graph_put_pixel(uint16_t,uint16_t);
//extern void vga_text_log_ok(uint8_t*);
extern void vga_text_log_error(uint8_t*);
extern void vga_text_log_warn(uint8_t*);
extern void vga_text_log_info(uint8_t*);

#endif