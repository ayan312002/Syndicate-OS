// timer.h -- Defines the interface for all PIT-related functions. Will add more features here.

#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

void init_timer(uint32_t frequency);
uint64_t pit_get_tck_cnt();

#endif
