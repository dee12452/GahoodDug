#ifndef GAHOOD_WINDOW_H
#define GAHOOD_WINDOW_H

#include "util.h"

typedef struct Window {
    SDL_Window *win;
    SDL_Renderer *winRenderer;
    SDL_Texture *winTexture;
    int w;
    int h;
    bool running;
} Window;

void gahood_windowStart();
void gahood_windowClose();
bool gahood_isWindowRunning();

#endif
