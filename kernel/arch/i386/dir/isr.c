#include <kernel/isr.h>
#include <stdio.h>

#include  <kernel/asmFunctions.h>

isr_t interrupt_handlers[256];
// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t * regs) {
    int i = regs -> int_no;
    //uint8_t int_no = regs.int_no ;
    printf("recieved interrupt: %c \n", i);

    return;
}

void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
}


void register_interrupt_handler(int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}
