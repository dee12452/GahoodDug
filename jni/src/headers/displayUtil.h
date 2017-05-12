#ifndef GAHOOD_DISPLAY_UTIL
#define GAHOOD_DISPLAY_UTIL

#include <stdbool.h>

struct SDL_Window;

int gahood_displayGetScreenWidth();
int gahood_displayGetScreenHeight();
int gahood_displayGetRenderWidth();
int gahood_displayGetRenderHeight();
void gahood_displaySetWindowDimensions(struct SDL_Window *, int, int);

#endif
