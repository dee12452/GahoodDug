#include "../headers/screen.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../headers/util.h"
#include "../headers/sprite.h"

typedef struct Screen {
    Sprite **sprites;
    SDL_mutex *mutex;
    int numberOfSprites;
    GameState screenState;
    bool newState;
} Screen;

static Screen currentScreen;

static void changeSprites(SDL_Renderer *, GameState);

static void 
gahood_screenChange(GameState state) {
    currentScreen.screenState = state;
    currentScreen.newState = true;
    if(currentScreen.sprites) {
        for(int i = 0; i < currentScreen.numberOfSprites; i++) {
            if(currentScreen.sprites[i]) {
                gahood_spriteDestroy(currentScreen.sprites[i]);
            }
        }
        free(currentScreen.sprites);
        currentScreen.sprites = NULL;
    }
}

void
gahood_screenInit(GameState state) {
    currentScreen.mutex = SDL_CreateMutex();
    if(!currentScreen.mutex) {
        gahood_utilFatalSDLError("Failed to create the mutex");
    }
    currentScreen.sprites = NULL;
    currentScreen.numberOfSprites = 0;
    currentScreen.screenState = state;
    currentScreen.newState = true;
}

void
gahood_screenClose() {
    if(currentScreen.sprites) {
        for(int i = 0; i < currentScreen.numberOfSprites; i++) {
            if(currentScreen.sprites[i]) {
                gahood_spriteDestroy(currentScreen.sprites[i]);
            }
        }
        free(currentScreen.sprites);
        currentScreen.sprites = NULL;
    }
    if(currentScreen.mutex) {
        SDL_DestroyMutex(currentScreen.mutex);
        currentScreen.mutex = NULL;
    }
}

void 
gahood_screenUpdate(GameState state) {
    /* Lock the mutex */
    while(SDL_LockMutex(currentScreen.mutex) < 0) {
        printf("Trying to lock game thread\n");
        SDL_Delay(DELAY_GAME_LOOP);
    }

    /* If we need to change the state of the screen
     * do so and then unlock the mutex */
    if(state != currentScreen.screenState) {
        gahood_screenChange(state);
        SDL_UnlockMutex(currentScreen.mutex);
        return;
    }
    /* If the renderer has not updated the sprites 
     * do not continue */
    if(currentScreen.newState) {
        SDL_UnlockMutex(currentScreen.mutex);
        return;
    }
    SDL_UnlockMutex(currentScreen.mutex);
    
    /* We are safe to update the sprites */
    switch(currentScreen.screenState) {
        default:
            break;
    }
}

void 
gahood_screenDraw(SDL_Renderer *r) {
    while(SDL_LockMutex(currentScreen.mutex) < 0) {
        printf("Trying to lock window thread\n");
        SDL_Delay(DELAY_RENDER_LOOP);
    }
    if(currentScreen.newState) {
        currentScreen.newState = false;
        changeSprites(r, currentScreen.screenState);
    }
    if(currentScreen.sprites) {
        gahood_spriteDraw(r, currentScreen.sprites[0]);
    }
    SDL_UnlockMutex(currentScreen.mutex);
}

static void 
changeSprites(SDL_Renderer *r, GameState state) {
    if(state == GAME_STATE_PLAY) {
        currentScreen.numberOfSprites = 1;
        currentScreen.sprites = (Sprite **) malloc(sizeof(Sprite *));
        currentScreen.sprites[0] = gahood_spriteCreate(r, RES_FILE_DIRT);
        gahood_spriteSetSourceRect(currentScreen.sprites[0], 0, 0, 16, 16);
        gahood_spriteSetDestinationRect(currentScreen.sprites[0], 0, 0, 50, 50);
    }
}
