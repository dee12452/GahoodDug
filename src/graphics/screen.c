#include "../headers/screen.h"

#include <SDL2/SDL.h>
#include "../headers/game.h"
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
    GameState currentState = gahood_gameGetGameState();
    if(currentState != currentScreen->screenState) {
        gahood_screenChange(currentState);
    }
    switch(currentScreen->screenState) {
        default:
            break;
    }
}

void 
gahood_screenDraw(SDL_Renderer *r) {
    if(!currentScreen) {
        return;
    }
    for(int i = 0; i < currentScreen->numberOfSprites; i++) {
        gahood_spriteDraw(r, currentScreen->sprites[i]);
    }
}
