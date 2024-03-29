#include <kernel/isr.h>
#include <kernel/descriptorTables.h>
#include <kernel/debug/panic.h>

#include <kernel/tty.h>

void isrs_install() {
    idt_set_gate(0, (unsigned) isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned) isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned) isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned) isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned) isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned) isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned) isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned) isr7, 0x08, 0x8E);

    idt_set_gate(8, (unsigned) isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned) isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned) isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned) isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned) isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned) isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned) isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned) isr15, 0x08, 0x8E);

    idt_set_gate(16, (unsigned) isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned) isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned) isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned) isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned) isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned) isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned) isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned) isr23, 0x08, 0x8E);

    idt_set_gate(24, (unsigned) isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned) isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned) isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned) isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned) isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned) isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned) isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned) isr31, 0x08, 0x8E);
}

static const char *exception_messages[32] = {
	"Division by zero",
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Detected overflow",
	"Out-of-bounds",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt",
	"Coprocessor fault",
	"Alignment check",
	"Machine check",
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

void isr_handler(struct regs *r)
{
    /* Is this a fault whose number is from 0 to 31? */
    if (r->int_no < 32)
    {
        /* Display the description for the Exception that occurred.
        *  In this tutorial, we will simply halt the system using an
        *  infinite loop */
       terminal_writestring("recieved interrupt: ");
       terminal_writestring(exception_messages[r->int_no]);	//TODO Add a better way to print interrupt
       int i=r->int_no;
       terminal_writestring(" ");
       terminal_writeDec(i); 					   
        for (;;);
    }
}

