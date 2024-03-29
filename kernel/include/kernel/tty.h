#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
 
#include <stddef.h>
#include <stdint.h>

#include <kernel/vga.h>
 
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_setcolor(uint8_t color);
void terminal_writeDec(int n);
void terminal_writeHex(unsigned int n);

static inline void reset_color()
{
	terminal_setcolor(make_color(COLOR_LIGHT_GREY, COLOR_BLACK));
}
 
#endif
