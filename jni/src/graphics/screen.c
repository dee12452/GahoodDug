#include "../headers/screen.h"

#include <SDL.h>
#include <stdbool.h>
#include "../headers/util.h"
#include "../headers/sprite.h"

typedef struct Screen {
    Sprite **sprites;
    int numOfSprites;
    SDL_mutex *mutex;
    GameState screenState;
    bool needsNewSprites;
} Screen;

Screen *screen = NULL;

static void deleteScreenSprites();

void
gahood_screenDraw(SDL_Renderer *r) {
    while(SDL_LockMutex(screen->mutex) < 0) {
        /* Log this */
        SDL_Log("Waiting to lock the drawing thread\n");
    }
    if(screen->needsNewSprites) {
        SDL_Log("***************** CREATING NEW SPRITES *******************\n");
        switch(screen->screenState) {
            default:
                deleteScreenSprites();
                break;
        }
        SDL_Log("***************** DONE CREATING NEW SPRITES *******************\n");
    }
    else {
        SDL_Log("***************** DRAWING THE SPRITES *******************\n");
        for(int i = 0; i < screen->numOfSprites; i++) {
            gahood_spriteDraw(r, screen->sprites[i]);
        }
        SDL_Log("***************** FINISHED DRAWING THE SPRITES *******************\n");
    }
    SDL_UnlockMutex(screen->mutex);
}

void
gahood_screenUpdate(GameState state) {
    SDL_Log("***************** UPDATING THE SCREEN *******************\n");
    while(SDL_LockMutex(screen->mutex) < 0) {
        SDL_Log("Waiting to lock the game thread\n");
    }
    if(state != screen->screenState) {
        screen->needsNewSprites = true;
        screen->screenState = state;
    }
    else if(!screen->needsNewSprites) {
        switch(state) {
            default:
                break;
        }
    }
    SDL_UnlockMutex(screen->mutex);
    SDL_Log("***************** FINISHED UPDATING THE SCREEN *******************\n");
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
}
