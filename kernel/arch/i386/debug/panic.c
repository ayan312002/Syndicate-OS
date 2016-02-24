#include <kernel/tty.h>
#include <kernel/debug/panic.h>

// #include <stdio.h>         <------- we should make it more kernalable ;)

extern void panic(const char *message, const char *file, uint32_t line)
{
    // We encountered a massive problem and have to stop.
   __asm__ __volatile__("cli"); // Disable interrupts.
 
    terminal_writestring("PANIC(");
    terminal_writestring(message);
    terminal_writestring(") at ");
    terminal_writestring(file);
    terminal_writestring(":");
    terminal_putchar(line);
    terminal_writestring("\n");
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const char *file, uint32_t line, const char *desc)
{
    // An assertion failed, and we have to panic.
   __asm__ __volatile__("cli"); // Disable interrupts.
   
    terminal_writestring("ASSERTION-FAILED(");
    terminal_writestring(desc);
    terminal_writestring(") at ");
    terminal_writestring(file);
    terminal_writestring(":");
    terminal_putchar(line);
    terminal_writestring("\n");
    // Halt by going into an infinite loop.
    for(;;);
}
