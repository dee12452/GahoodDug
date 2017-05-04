#include <SDL2/SDL.h>
#include "../headers/input.h"
#include "../headers/game.h"

void gahood_inputHandleEvents() {
    switch(gahood_gameGetGameState()) {
        default: {
            SDL_Event e;
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_QUIT) {
                    gahood_gameSetGameState(GAME_STATE_EXIT);
                }
            }
            break;
        }
    }
}

