#include "../headers/screen.h"

#include <SDL.h>
#include <stdbool.h>
#include "../headers/util.h"
#include "../headers/sprite.h"
#include "../headers/buttons.h"

typedef struct Screen {
    Sprite **sprites;
    int numOfSprites;
    SDL_mutex *mutex;
    GameState screenState;
    bool needsNewSprites;
    ControlStick *controller;
} Screen;

static Screen *screen = NULL;

static void deleteScreenSprites();

void
gahood_screenCreate(int numOfSprites, Sprite **sprites, ControlStick *controller) {
    if(screen) {
        deleteScreenSprites();
        screen->numOfSprites = numOfSprites;
        screen->sprites = sprites;
        screen->controller = controller;
    }
}

void
gahood_screenDraw(SDL_Renderer *r) {
    if(screen->needsNewSprites) {
        while(SDL_LockMutex(screen->mutex) < 0) {
            /* Log this */
            SDL_Log("Waiting to lock the drawing thread\n");
        }
        switch(screen->screenState) {
            default: {
                screen->needsNewSprites = false;
                break;
            }
        }
        SDL_UnlockMutex(screen->mutex);
    }
    else {
        for(int i = 0; i < screen->numOfSprites; i++) {
            gahood_spriteDraw(r, screen->sprites[i]);
        }
        if(screen->controller) {
            gahood_controlStickDraw(r, screen->controller);
        }
    }
}

void
gahood_screenUpdate(GameState state) {
    if(state != screen->screenState) {
        screen->needsNewSprites = true;
        screen->screenState = state;
    }
    else if(!screen->needsNewSprites) {
        while(SDL_LockMutex(screen->mutex) < 0) {
            SDL_Log("Waiting to lock the game thread\n");
        }
        switch(state) {
            default:
                break;
        }
        SDL_UnlockMutex(screen->mutex);
    }
}

void
gahood_screenInit() {
    if(!screen) {
        screen = malloc(sizeof(Screen));
        screen->mutex = SDL_CreateMutex();
        screen->numOfSprites = 0;
        screen->sprites = NULL;
        screen->screenState = GAME_STATE_NONE;
        screen->needsNewSprites = true;
        screen->controller = NULL;
    }
}

void
gahood_screenClose() {
    if(screen) {
        deleteScreenSprites();
        SDL_DestroyMutex(screen->mutex);
        screen->mutex = NULL;
        free(screen);
        screen = NULL;
    }
}

void
deleteScreenSprites() {
    if(screen->sprites) {
        int tempNum = screen->numOfSprites;
        screen->numOfSprites = 0;
        for(int i = 0; i < tempNum; i++) {
            gahood_spriteDestroy(screen->sprites[i]);
        }
        free(screen->sprites);
        screen->sprites = NULL;
    }
    if(screen->controller) {
        gahood_controlStickDestroy(screen->controller);
        screen->controller = NULL;
    }
}

ControlStick *
gahood_screenGetControlStick() {
    return screen->controller;
}
