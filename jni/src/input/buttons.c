#include "../headers/buttons.h"

#include <SDL.h>
#include <stdbool.h>
#include "../headers/sprite.h"
#include "../headers/util.h"
#include "../headers/displayUtil.h"
#include "../headers/math.h"

#define STICK_WIDTH 75
#define STICK_HEIGHT 75
#define STICK_BG_WIDTH 125
#define STICK_BG_HEIGHT 125

struct ControlStick {
    Sprite *stick;
    Sprite *stickBG;
    SDL_Rect origin;
    Direction direction;
    bool move;
};

static void determineControlStickDirection(ControlStick *);

ControlStick *
gahood_controlStickCreate(SDL_Renderer *r, int x, int y) {
    ControlStick *controller = (ControlStick *) malloc(sizeof(ControlStick));
    controller->stick = gahood_spriteCreate(r, RES_FILE_CONTROL_STICK);
    controller->stickBG = gahood_spriteCreate(r, RES_FILE_CONTROL_STICK_BG);
    controller->direction = DIRECTION_NONE;
    SDL_Rect stickRect, stickBGRect;
    stickRect.w = STICK_WIDTH;
    stickRect.h = STICK_HEIGHT;
    stickBGRect.w = STICK_BG_WIDTH;
    stickBGRect.h = STICK_BG_HEIGHT;
    stickBGRect.x = x;
    stickBGRect.y = y;
    stickRect.x = stickBGRect.x + (STICK_BG_WIDTH / 2 - stickRect.w / 2);
    stickRect.y = stickBGRect.y + (STICK_BG_HEIGHT / 2 - stickRect.h / 2);
    controller->origin = stickRect;
    gahood_spriteSetDstDimensions(controller->stickBG, stickBGRect);
    gahood_spriteSetDstDimensions(controller->stick, stickRect);
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

Direction
gahood_controlStickGetDirection(ControlStick *controller) {
    determineControlStickDirection(controller);
    return controller->direction;
}

void
gahood_controlStickTouch(ControlStick *controller, const SDL_TouchFingerEvent e) {
    if(gahood_spriteCheckTouch(e, controller->stickBG)) {
        controller->move = true;
    }
}

void
gahood_controlStickMove(ControlStick *controller, const SDL_TouchFingerEvent e) {
    if(controller->move) {
        int touchX, touchY;
        SDL_Rect bgRect = gahood_spriteGetLogicalDstDimensions(controller->stickBG);
        gahood_mathGetControllerTouchPosition(e.x, e.y, &touchX, &touchY, bgRect);
        gahood_spriteSetLogicalPosition(controller->stick, touchX, touchY);
    }
}

bool
gahood_controlStickCheckCollision(int x, int y, ControlStick *controller) {
    return true;
}

void
gahood_controlStickRelease(ControlStick *controller) {
    if(controller->move) {
        gahood_spriteSetDstDimensions(controller->stick, controller->origin);
        controller->move = false;
    }
}

SDL_Rect
gahood_controlStickGetRect(ControlStick *controller) {
    return gahood_spriteGetDstDimensions(controller->stickBG);
}

void 
determineControlStickDirection(ControlStick *controller) {
    SDL_Rect rect = gahood_spriteGetDstDimensions(controller->stick);
    SDL_Rect rectBG = gahood_spriteGetDstDimensions(controller->stickBG);
    int centerX = rectBG.x + rectBG.w / 2;
    int centerY = rectBG.y + rectBG.h / 2;
    int stickX = rect.x + rect.w / 2;
    int stickY = rect.y + rect.h / 2;
    if(stickX > centerX) {
        if(abs(stickX - centerX) > abs(stickY - centerY)) {
            controller->direction = DIRECTION_RIGHT;
        }
        else {
            if(stickY > centerY) {
                controller->direction = DIRECTION_DOWN;
            }
            else {
                controller->direction = DIRECTION_UP;
            }
        }
    }
    else if(stickX < centerX) {
        if(abs(stickX - centerX) > abs(stickY - centerY)) {
            controller->direction = DIRECTION_LEFT;
        }
        else {
            if(stickY > centerY) {
                controller->direction = DIRECTION_DOWN;
            }
            else {
                controller->direction = DIRECTION_UP;
            }
        }

    }
    else {
        controller->direction = DIRECTION_NONE;
    }
}
