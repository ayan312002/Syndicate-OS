#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/vga.h>
#include <kernel/tty.h>
#include <kernel/asmFunctions.h>

 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

static void scroll();
 
void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}
 
static void move_cursor()
{
   // The screen is 80 characters wide...
   uint16_t cursorLocation = terminal_row * 80 + terminal_column;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}


void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}
 
void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (terminal_row + 1 == VGA_HEIGHT) {
            scroll();
        } else
            terminal_row++;

        move_cursor();
        return;
    }

    // Handle carriage return	
    if (c == '\r') {
        terminal_column = 0;
        move_cursor();
        return;
    }

    // Handle a backspace, by moving the cursor back one space and printing a blank character..
    if (c == 0x08 && terminal_column) {
        if (terminal_column > 0) {
            if (terminal_column != 0) terminal_column--;
            terminal_writestring(" ");
            move_cursor();
            if (terminal_column != 0) terminal_column--;
        }
        return;
    }
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

void scroll()
{

   for(unsigned int i = 0; i < VGA_HEIGHT; i++){
		for (unsigned int m = 0; m < VGA_WIDTH; m++){
			terminal_buffer[i * VGA_WIDTH + m] = terminal_buffer[(i + 1) * VGA_WIDTH + m];
		}
	}
}



void terminal_write(const char* data, size_t size)
{
	for ( size_t i = 0; i < size; i++ )
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

void terminal_writeHex(unsigned int n)
{
	int i, temp;
	char noZ = 1;	// Boolean to see if we have any Preceding zeros.

	terminal_writestring("0x");	// Bit of formatting so we know it's hexadecimal.

	for(i = 28; i>0; i -= 4) {
		temp = (n >> i) & 0xF;				// Base Shift 10 -> 16
		if (temp == 0 && noZ != 0) {
			continue;	// We don't want leading Zeros, Ignore it.
		} else if (temp >= 0xA) {			// A-F
			noZ = 0;	// Number has a Sig-Dig, Don't ignore 0 anymore.
			terminal_putchar(temp - 0xA + 'A');	// Ascii shift.
		} else {		// 0-9
			noZ = 0;						// No longer a leading zero.
			terminal_putchar(temp + '0');
		}
	}

	temp = n & 0xF;
	if (temp >= 0xA) {
		terminal_putchar(temp - 0xA + 'A');
	} else {
		terminal_putchar(temp + '0');
	}
}

void terminal_writeDec(int n)
{

    if (n == 0)
    {
        terminal_putchar('0');
        return;
    }

    int acc = n;			//make a copy
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    terminal_writestring(c2);

}
