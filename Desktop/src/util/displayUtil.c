#include "../headers/displayUtil.h"

#include <SDL.h>
#include "../headers/util.h"

#define DISPLAY_INDEX 0

static int screenWidth = 0;
static int screenHeight = 0;

int
gahood_displayGetScreenWidth() {
    if(screenWidth != 0)
        return screenWidth;
    SDL_DisplayMode display;
    if(SDL_GetCurrentDisplayMode(DISPLAY_INDEX, &display) < 0) {
        gahood_utilFatalSDLError("Failed to get the current display mode");
    }
    screenWidth = display.w;
    return display.w;
}

int
gahood_displayGetScreenHeight() {
    if(screenHeight != 0)
        return screenHeight;
    SDL_DisplayMode display;
    if(SDL_GetCurrentDisplayMode(DISPLAY_INDEX, &display) < 0) {
        gahood_utilFatalSDLError("Failed to get the current display mode");
    }
    screenHeight = display.h;
    return display.h;
}

int
gahood_displayGetRenderWidth() {
    return (gahood_displayGetRenderHeight() * WINDOW_WIDTH) / WINDOW_HEIGHT;
}

int
gahood_displayGetRenderHeight() {
    return gahood_displayGetScreenHeight();
}

void
gahood_displaySetWindowDimensions(SDL_Window *win, int w, int h) {
    SDL_SetWindowSize(win, w, h);
}
