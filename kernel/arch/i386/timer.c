#include <kernel/irq.h>
#include <kernel/timer.h>
#include <kernel/tty.h>
#include <kernel/asmFunctions.h>

unsigned volatile int timer_ticks = 0;

static void timer_callback(struct regs * r) {
    timer_ticks++;
    // terminal_writestring("Tick: ");
    // terminal_writeDec(timer_ticks);
    // terminal_writestring("\n");
}

void timer_install(uint32_t frequency) {
    // Firstly, register our timer callback.
    irq_install_handler(0, & timer_callback);

    uint32_t divisor = 1193180 / frequency;

    outb(0x43, 0x36);

    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}

void timer_wait(int ticks) {
    unsigned int eticks;

    eticks = timer_ticks + ticks;
    while (timer_ticks < eticks) {
        __asm__ __volatile__("sti//hlt//cli");
    }
}
