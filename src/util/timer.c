#include "../headers/timer.h"

#include <SDL2/SDL.h>

struct Timer {
    uint32_t start;
    uint32_t finish;
    uint32_t targetMs;
};

Timer *
gahood_timerCreate(uint32_t timeMs) {
    Timer *timer = (Timer *) malloc(sizeof(Timer));
    timer->targetMs = timeMs;
    gahood_timerReset(timer);
    return timer;
}

void
gahood_timerDestroy(Timer *timer) {
    free(timer);
}

bool
gahood_timerCheck(Timer *timer) {
   timer->finish = SDL_GetTicks();
   if(timer->finish < timer->start) {
       gahood_timerReset(timer);
       return false;
   }
   else if(timer->finish - timer->start >= timer->targetMs) {
       gahood_timerReset(timer);
       return true;
   }
   else {
       return false;
   }
}

void
gahood_timerReset(Timer *timer) {
    timer->start = SDL_GetTicks();
    timer->finish = SDL_GetTicks();
}
