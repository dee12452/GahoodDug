#ifndef GAHOOD_TIMER_H
#define GAHOOD_TIMER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Timer Timer;

struct Timer * gahood_timerCreate(uint32_t);
void gahood_timerDestroy(struct Timer *);
bool gahood_timerCheck(struct Timer *);
void gahood_timerReset(struct Timer *);

#endif
