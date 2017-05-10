#include "../headers/input.h"

#include <SDL.h>
#include "../headers/util.h"
#include "../headers/game.h"

/* Game state based handling of finger actions*/
static void handleFingerDownPlay(SDL_TouchFingerEvent);
static void handleFingerUpPlay(SDL_TouchFingerEvent);
static void handleFingerMotionPlay(SDL_TouchFingerEvent);

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
            case SDL_FINGERDOWN:
                {
                    switch(gahood_gameGetGameState()) {
                        case GAME_STATE_PLAY:
                            {
                                handleFingerDownPlay(e.tfinger);
                                break;
                            }
                        default:
                            break;
                    }
                    break;
                }
            case SDL_FINGERUP:
                {
                    switch(gahood_gameGetGameState()) {
                        case GAME_STATE_PLAY:
                            {
                                handleFingerUpPlay(e.tfinger);
                                break;
                            }
                        default:
                            break;
                    }
                    break;
                }
            case SDL_FINGERMOTION:
                {
                    switch(gahood_gameGetGameState()) {
                        case GAME_STATE_PLAY:
                            {
                                handleFingerMotionPlay(e.tfinger);
                                break;
                            }
                        default:
                            break;
                    }
                    break;
                }
            default:
                break;
        }
    }
    return true;
}

/**************************/
/* FINGER EVENTS FOR PLAY */
/**************************/
void
handleFingerDownPlay(SDL_TouchFingerEvent e) {

}

void
handleFingerUpPlay(SDL_TouchFingerEvent e) {

} 

void
handleFingerMotionPlay(SDL_TouchFingerEvent e) {

}
