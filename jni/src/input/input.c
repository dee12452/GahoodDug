#include "../headers/input.h"

#include <SDL.h>
#include "../headers/util.h"
#include "../headers/displayUtil.h"
#include "../headers/game.h"
#include "../headers/screen.h"
#include "../headers/buttons.h"

/* Game state based handling of finger actions*/
static bool handleFingerDownPlay(SDL_TouchFingerEvent);
static bool handleFingerUpPlay(SDL_TouchFingerEvent);
static bool handleFingerMotionPlay(SDL_TouchFingerEvent);

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
                                if(!handleFingerDownPlay(e.tfinger)) {
                                    gahood_gameSetGameState(GAME_STATE_EXIT);
                                    return false;
                                }
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
                                if(!handleFingerUpPlay(e.tfinger)) {
                                    gahood_gameSetGameState(GAME_STATE_EXIT);
                                    return false;
                                }
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
                                if(!handleFingerMotionPlay(e.tfinger)) {
                                    gahood_gameSetGameState(GAME_STATE_EXIT);
                                    return false;
                                }
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
bool
handleFingerDownPlay(SDL_TouchFingerEvent e) {
    int touchX = (int) (e.x * gahood_displayGetScreenWidth());
    int touchY = (int) (e.y * gahood_displayGetScreenHeight());
    if(gahood_controlStickCheckCollision(touchX, touchY, gahood_screenGetControlStick())) {
        return false;
    }
    return true;
}

bool
handleFingerUpPlay(SDL_TouchFingerEvent e) {
    return true;
} 

bool
handleFingerMotionPlay(SDL_TouchFingerEvent e) {
    return true;
}
