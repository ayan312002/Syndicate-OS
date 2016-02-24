#ifndef _KERNEL_PANIC_H
#define _KERNEL_PANIC_H
 
#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b)) 
#include <stddef.h>
#include <stdint.h>

extern void panic(const char *message, const char *file, uint32_t line);
extern void panic_assert(const char *file,uint32_t line, const char *desc);

#endif
