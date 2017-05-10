#ifndef GAHOOD_DISPLAY_UTIL
#define GAHOOD_DISPLAY_UTIL

#include <stdbool.h>

struct SDL_Window;

int gahood_displayGetScreenWidth();
int gahood_displayGetScreenHeight();
void gahood_displayOnScreenChange();
void gahood_displaySetWindowDimensions(struct SDL_Window *, int, int);

#endif
