#ifndef GAHOOD_BUTTONS_H
#define GAHOOD_BUTTONS_H

#include <stdbool.h>

typedef struct ControlStick ControlStick;
struct SDL_Renderer;
struct SDL_Rect;
struct SDL_TouchFingerEvent;

ControlStick * gahood_controlStickCreate(struct SDL_Renderer *, int, int);
void gahood_controlStickDestroy(ControlStick *);
void gahood_controlStickDraw(struct SDL_Renderer *, ControlStick *);
void gahood_controlStickTouch(ControlStick *, struct SDL_TouchFingerEvent);
void gahood_controlStickRelease(ControlStick *);
struct SDL_Rect gahood_controlStickGetRect(ControlStick *);
bool gahood_controlStickCheckCollision(int, int, ControlStick *);

#endif