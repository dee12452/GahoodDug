#include "../headers/buttons.h"

#include <SDL.h>
#include "../headers/sprite.h"
#include "../headers/util.h"

#define STICK_WIDTH 100
#define STICK_HEIGHT 100
#define STICK_BG_WIDTH 200
#define STICK_BG_HEIGHT 200

struct ControlStick {
    Sprite *stick;
    Sprite *stickBG;
    uint8_t direction;
};

ControlStick *
gahood_controlStickCreate(SDL_Renderer *r, int x, int y) {
    ControlStick *controller = (ControlStick *) malloc(sizeof(ControlStick));
    controller->stick = gahood_spriteCreate(r, RES_FILE_CONTROL_STICK);
    controller->stickBG = gahood_spriteCreate(r, RES_FILE_CONTROL_STICK_BG);
    controller->direction = 0;
    return controller;
}

void
gahood_controlStickDestroy(ControlStick *controller) {
    if(controller) {
        if(controller->stick) {
            gahood_spriteDestroy(controller->stick);
            controller->stick = NULL;
        }
        if(controller->stickBG) {
            gahood_spriteDestroy(controller->stickBG);
            controller->stickBG = NULL;
        }
        free(controller);
    }
}

void
gahood_controlStickDraw(SDL_Renderer *r, ControlStick *controller) {
    gahood_spriteDraw(r, controller->stickBG);
    gahood_spriteDraw(r, controller->stick);
}
