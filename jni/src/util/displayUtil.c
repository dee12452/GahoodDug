#include "../headers/displayUtil.h"

#include <SDL.h>
#include "../headers/util.h"
#include "../headers/sprite.h"

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

SDL_Rect
gahood_displayGetSpriteLocation(Sprite *sprite) {
    SDL_Rect loc = gahood_spriteGetDstDimensions(sprite);
    loc.x = (gahood_displayGetScreenWidth() - gahood_displayGetRenderWidth()) / 2 + (loc.x * gahood_displayGetRenderWidth()) / WINDOW_WIDTH;
    loc.y = (loc.y * gahood_displayGetRenderHeight()) / WINDOW_HEIGHT;
    loc.w = (loc.w * gahood_displayGetRenderWidth()) / WINDOW_WIDTH;
    loc.h = (loc.h * gahood_displayGetRenderHeight()) / WINDOW_HEIGHT;
    return loc;
} 

bool
gahood_displayCheckCollision(int x, int y, Sprite *sprite) {
    SDL_Rect touchLoc = gahood_displayGetSpriteLocation(sprite);
    SDL_Log("******************** Touched %d, %d but needed %d, %d w: %d h %d\n",
            x, y,
            touchLoc.x, touchLoc.y,
            touchLoc.w, touchLoc.h);
    if(x >= touchLoc.x && x <= touchLoc.x + touchLoc.w) {
        if(y >= touchLoc.y && y <= touchLoc.y + touchLoc.h) {
            return true;
        }
    }
    return false;
}
