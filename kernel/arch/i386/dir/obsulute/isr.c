#include <kernel/isr.h>
#include <kernel/asmFunctions.h>
#include <kernel/tty.h>

#include <stdio.h>

char * exception_messages[];

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs) {
    if (regs.int_no < 32) {
        printf("\n");
        terminal_setcolor(make_color(COLOR_WHITE, COLOR_RED));
        printf("recieved interrupt: %c", regs.int_no);

        printf("\n%s", exception_messages[regs.int_no]);
        printf("\nException. System Halted!");
    //    printf(" Going to Infinity!\n");
        for (;;);
    }
}

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t regs) {
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40) {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }

}

char * exception_messages[] = {
    "Division By Zero",
    "Debug Exception",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};
