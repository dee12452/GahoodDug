#ifndef GAHOOD_TIMER_H
#define GAHOOD_TIMER_H

#include "util.h"

typedef struct Timer {
    uint32_t start;
    uint32_t finish;
    unsigned int targetMs;
} Timer;

Timer * gahood_timer_create(unsigned int);
void gahood_timer_destroy(Timer *);
bool gahood_timer_check(Timer *);
void gahood_timer_reset(Timer *);

#endif
