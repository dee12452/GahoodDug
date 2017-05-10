#include "../headers/displayUtil.h"

#include <SDL.h>
#include "../headers/util.h"

#define DISPLAY_INDEX 0

int
gahood_displayGetScreenWidth() {
    SDL_DisplayMode display;
    if(SDL_GetCurrentDisplayMode(DISPLAY_INDEX, &display) < 0) {
        gahood_utilFatalSDLError("Failed to get the current display mode");
    }
    return display.w;
}

int
gahood_displayGetScreenHeight() {
    SDL_DisplayMode display;
    if(SDL_GetCurrentDisplayMode(DISPLAY_INDEX, &display) < 0) {
        gahood_utilFatalSDLError("Failed to get the current display mode");
    }
    return display.h;
}

void
gahood_displayOnScreenChange() {
    /* Do nothing for now */
}

void
gahood_displaySetWindowDimensions(SDL_Window *win, int w, int h) {
    SDL_SetWindowSize(win, w, h);
}
