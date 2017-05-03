#include "../headers/timer.h"

Timer *
gahood_timer_create(unsigned int timeMs) {
    Timer *timer = (Timer *) malloc(sizeof(Timer));
    timer->targetMs = timeMs;
    gahood_timer_reset(timer);
    return timer;
}

void
gahood_timer_destroy(Timer *timer) {
    free(timer);
}

bool
gahood_timer_check(Timer *timer) {
   timer->finish = SDL_GetTicks();
   if(timer->finish < timer->start) {
       gahood_timer_reset(timer);
       return false;
   }
   else if(timer->finish - timer->start >= timer->targetMs) {
       gahood_timer_reset(timer);
       return true;
   }
   else {
       return false;
   }
}

void
gahood_timer_reset(Timer *timer) {
    timer->start = SDL_GetTicks();
    timer->finish = SDL_GetTicks();
}
