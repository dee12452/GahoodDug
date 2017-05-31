#include "../headers/screen.h"

#include <SDL.h>
#include <stdbool.h>
#include "../headers/util.h"
#include "../headers/sprite.h"
#include "../headers/buttons.h"
#include "../headers/fileUtil.h"

#define WORD_SPRITE "Sprite"
#define WORD_NONE "None"

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
static void gahood_screenSpritesCreate();

void
gahood_screenDraw(SDL_Renderer *r) {
    if(screen->needsNewSprites) {
        while(SDL_LockMutex(screen->mutex) < 0) {
            /* Log this */
            SDL_Log("Waiting to lock the drawing thread\n");
        }
        gahood_screenSpritesCreate();
        screen->needsNewSprites = false;
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
        screen = (Screen *) malloc(sizeof(Screen));
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

void
gahood_screenSpritesCreate() {
    if(screen) {

        /*
         * Open a file that describes how sprites are loaded 
         * into the screen based upon the new game state
         */
        deleteScreenSprites();
        SDL_RWops *in = NULL;
        if(screen->screenState == GAME_STATE_MENU) {
            in = gahood_fileUtilOpenFile("screen/MenuScreen.txt");
        }
        if(!in) {
            return;
        }
        
        /* Number of sprites to make */
        int spriteNum = 0;
        
        /* Read the given file line by line */
        char *line = gahood_fileUtilReadLine(in);
        while(line != NULL) {

            /* Read each line word by word */
            char *word = gahood_fileUtilGetWordFromLine(line, 0);
            for(int i = 1; word != NULL; i++) {
                if(gahood_utilStringEquals(word, WORD_SPRITE)) {
                    spriteNum++;
                }
                else if(gahood_utilStringEquals(word, WORD_NONE)) {

                }
                else if(gahood_utilStringToInt(word) != -1) {

                }
                else {
                    char message[255];
                    strcpy(message, "******************* FAILED TO PARSE FILE: ");
                    strcat(message, "screen/MenuScreen.txt ********************");
                    gahood_utilFatalError(message);
                }
                free(word);
                word = gahood_fileUtilGetWordFromLine(line, i);
            }
            
            free(line);
            line = gahood_fileUtilReadLine(in);
        }

        /* FOR FileUtil.c TESTING PURPOSES *
        char *line = gahood_fileUtilReadLine(in);
        while(line != NULL) {
            int i = 0;
            char *word = gahood_fileUtilGetWordFromLine(line, i);
            while(word != NULL) {
                int val = gahood_utilStringToInt(word);
                SDL_Log("********** IT'S AN INT! %d *********\n", val);
                free(word);
                i++;
                word = gahood_fileUtilGetWordFromLine(line, i);
            }
            free(line);
            line = gahood_fileUtilReadLine(in);
        }
        * END TEST */ 

        SDL_RWclose(in);
        in = NULL;
    }
}

ControlStick *
gahood_screenGetControlStick() {
    return screen->controller;
}
