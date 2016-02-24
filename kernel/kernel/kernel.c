#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
 
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/asmFunctions.h>
#include <kernel/descriptorTables.h>
#include <kernel/isr.h>
#include <kernel/irq.h>
#include <kernel/timer.h>

#include <kernel/debug/serial_port.h>
#include <kernel/debug/panic.h>
  
void kernel_early(void) {
    terminal_initialize();
    init_descriptor();
    isrs_install();
    irq_install();
    timer_install(50);
    __asm__ __volatile__ ("sti");

}

void kernel_main(void) {
   // printf("Hello World\n");
    //write_serial("Hello Ayan");
  //  PANIC("No free frames!");
        for(;;) {
    asm("hlt");
 }
}



