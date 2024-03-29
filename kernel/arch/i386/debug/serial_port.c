#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/asmFunctions.h>
#include <kernel/debug/serial_port.h>

#define PORT 0x3f8 /* COM1 */
// If you are using QEMU use the parameter "-serial file:serial.log" to get output.

void init_serial() {
    outb(PORT + 1, 0x00); // Disable all interrupts
    outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT + 1, 0x00); //                  (hi byte)
    outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int serial_received() {
    return inb(PORT + 5) & 1;
}

char read_serial() {
    while (serial_received() == 0);
    return inb(PORT);
}

int is_transmit_empty() {
    return inb(PORT + 5) & 0x20;
}

void write_serial(char * a) {
    size_t size = strlen(a);
    for (size_t i = 0; i < size; i++) {
        while (is_transmit_empty() == 0);
        outb(PORT, a[i]);
    }
}

void write_serial_char(char b){
while (is_transmit_empty() == 0);
 
   outb(PORT,b);
}
