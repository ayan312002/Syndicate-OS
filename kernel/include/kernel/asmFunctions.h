#ifndef KERNEL_ASMFUNCTIONS_H
#define KERNEL_ASMFUNCTIONS_H

#include <stdlib.h>

#define sti(); __asm__ __volatile__("sti"); 
#define cli(); __asm__ __volatile__("cli"); 

// Write a byte out to the specified port.
static inline void outb(uint16_t port, uint8_t val)
{
   __asm__ __volatile__ ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}


static inline void outw(uint16_t port,uint16_t val)
{
	__asm__ __volatile__ ("outw %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

static inline uint8_t inw(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

#endif
