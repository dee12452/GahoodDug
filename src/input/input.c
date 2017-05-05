#include "../headers/input.h"

#include <SDL2/SDL.h>
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
                else if(e.type == SDL_KEYUP) {
                    if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        gahood_gameSetGameState(GAME_STATE_EXIT);
                    }
                }
                else if(e.type == SDL_KEYDOWN) {
                    if(e.key.keysym.scancode == SDL_SCANCODE_A) {
                        GameState temp = gahood_gameGetGameState();
                        if(temp == GAME_STATE_PLAY_5) {
                            temp = GAME_STATE_PLAY;
                        }
                        else {
                            temp = (GameState) temp + 1;
                        }
                        gahood_gameSetGameState(temp);
                    }

                }
            }
            break;
        }
    }
}

