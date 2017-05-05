#include "../headers/input.h"

#include <SDL.h>
#include "../headers/util.h"
#include "../headers/game.h"

void 
gahood_inputHandleEvents() {
    switch(gahood_gameGetGameState()) {
        default: {
            SDL_Event e;
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_QUIT) {
                    gahood_gameSetGameState(GAME_STATE_EXIT);
                }
                else if(e.type == SDL_WINDOWEVENT) {
                    if(e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        //orientation change
                    }
                }
            }
            break;
        }
    }
}

