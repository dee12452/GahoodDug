#include "../headers/screen.h"

#include <SDL2/SDL.h>
#include "../headers/util.h"
#include "../headers/sprite.h"

typedef struct Screen {
    Sprite **sprites;
    int numberOfSprites;
    GameState screenState;
} Screen;

static Screen *currentScreen = NULL;

static void 
gahood_screenChange(GameState newState) {
    switch(newState) {
        default:
            break;
    }
}

void 
gahood_screenUpdate() {
    if(!currentScreen) {
        return;
    }
    switch(currentScreen->screenState) {
        default:
            break;
    }
}

void 
gahood_screenDraw(SDL_Renderer *r) {
    if(!currentScreen) {
        static int i = 0;
        if(i >= WINDOW_WIDTH) {
            i = 0;
        }
        Sprite *test = gahood_spriteCreate(r, "../res/gahooddug_dirt.png");
        gahood_spriteSetSourceRect(test, 0, 0, 16, 16);
        gahood_spriteSetDestinationRect(test, i, 0, 100, 100);
        gahood_spriteDraw(r, test);
        gahood_spriteDestroy(test);
        test = NULL;
        i+=16;
        return;
    }
    for(int i = 0; i < currentScreen->numberOfSprites; i++) {
        gahood_spriteDraw(r, currentScreen->sprites[i]);
    }
}
