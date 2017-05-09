#include "../headers/input.h"

#include <SDL.h>
#include "../headers/util.h"
#include "../headers/game.h"

bool
gahood_inputPollEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_KEYDOWN:
                {
                    switch(e.key.keysym.sym) {
                        case SDLK_AC_BACK:
                            {
                                gahood_gameSetGameState(GAME_STATE_EXIT);
                                return false;
                            }
                        default:
                            break;
                    }
                }
            case SDL_FINGERUP:
                {
                    GameState currState = gahood_gameGetGameState();
                    if(currState == GAME_STATE_PLAY)
                        currState = GAME_STATE_PLAY_2;
                    else if(currState == GAME_STATE_PLAY_2)
                        currState = GAME_STATE_PLAY;
                    gahood_gameSetGameState(currState);
                }
            default:
                break;
        }
    }
    return true;
}
