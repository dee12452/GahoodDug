#include "../headers/displayUtil.h"

#include <SDL.h>
#include "../headers/util.h"
#include "../headers/sprite.h"

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

SDL_Rect
gahood_displayGetSpriteLogicalPosition(Sprite *sprite) {
    SDL_Rect touchLoc = gahood_spriteGetDstDimensions(sprite);
    int screenWidth = gahood_displayGetScreenWidth();
    int screenHeight = gahood_displayGetScreenHeight();
    touchLoc.x += (screenWidth - WINDOW_WIDTH) / 2;
    touchLoc.y += (screenHeight - WINDOW_HEIGHT) / 2;
    touchLoc.w = (touchLoc.w * screenWidth) / WINDOW_WIDTH;
    touchLoc.h = (touchLoc.h * screenHeight) / WINDOW_HEIGHT;
    return touchLoc;
}

bool
gahood_displayCheckCollision(int x, int y, Sprite *sprite) {
    SDL_Rect touchLoc = gahood_displayGetSpriteLogicalPosition(sprite);
    if(x >= touchLoc.x && x <= touchLoc.x + touchLoc.w) {
        if(y >= touchLoc.y && y <= touchLoc.y + touchLoc.w) {
            return true;
        }
    }
    return false;
}
