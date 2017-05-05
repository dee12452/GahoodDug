#include "../headers/screen.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../headers/util.h"
#include "../headers/sprite.h"

typedef struct Screen {
    Sprite **sprites;
    int numberOfSprites;
    GameState screenState;
} Screen;

static Screen *currentScreen = NULL;
static bool changingScreen = false;

static void 
gahood_screenChange(GameState newState) {
    changingScreen = true;
    if(currentScreen) {
        for(int i = 0; i < currentScreen->numberOfSprites; i++) {
            gahood_spriteDestroy(currentScreen->sprites[i]);
        }
        free(currentScreen->sprites);
        currentScreen->sprites = NULL;
        free(currentScreen);
        currentScreen = NULL;
    }
    if(newState != GAME_STATE_EXIT) {
        currentScreen = (Screen *) malloc(sizeof(Screen));
        currentScreen->sprites = NULL;
        currentScreen->screenState = newState;
        changingScreen = false;
    }
}

void 
gahood_screenUpdate(GameState currentState) {
    if(!currentScreen || currentScreen->screenState != currentState) {
        gahood_screenChange(currentState);
        return;
    }
    switch(currentScreen->screenState) {
        default:
            break;
    }
}

void 
gahood_screenDraw(SDL_Renderer *r) {
    if(changingScreen || !currentScreen) {
        return;
    }
    if(!currentScreen->sprites) {
        currentScreen->sprites = (Sprite **) malloc(sizeof(Sprite *));
        currentScreen->numberOfSprites = 1;
        currentScreen->sprites[0] = gahood_spriteCreate(r, "../res/gahooddug_dirt.png");
        uint8_t gs_int = (int) currentScreen->screenState;
        gahood_spriteSetSourceRect(currentScreen->sprites[0], 16 * gs_int, 0, 16, 16);
        gahood_spriteSetDestinationRect(currentScreen->sprites[0], 0, 0, 16, 16);
    }
    for(int i = 0; i < currentScreen->numberOfSprites; i++) {
        gahood_spriteDraw(r, currentScreen->sprites[i]);
    }
}
