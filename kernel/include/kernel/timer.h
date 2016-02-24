#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

/* TIMER.C */
void timer_install(uint32_t frequency);
void timer_wait(int ticks);
#endif
