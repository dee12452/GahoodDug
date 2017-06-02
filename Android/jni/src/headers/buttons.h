#ifndef GAHOOD_BUTTONS_H
#define GAHOOD_BUTTONS_H

#include <stdbool.h>

typedef struct ControlStick ControlStick;
enum Direction;
struct SDL_Renderer;
struct SDL_Rect;
struct SDL_TouchFingerEvent;

ControlStick * gahood_controlStickCreate(int, int);
void gahood_controlStickDestroy(ControlStick *);
void gahood_controlStickDraw(struct SDL_Renderer *, ControlStick *);
void gahood_controlStickTouch(ControlStick *, const struct SDL_TouchFingerEvent);
void gahood_controlStickMove(ControlStick *, const struct SDL_TouchFingerEvent);
void gahood_controlStickRelease(ControlStick *);
enum Direction gahood_controlStickGetDirection(ControlStick *);
struct SDL_Rect gahood_controlStickGetRect(ControlStick *);
bool gahood_controlStickCheckCollision(int, int, ControlStick *);

#endif
