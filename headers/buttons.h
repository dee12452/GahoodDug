#ifndef GAHOOD_BUTTONS_H
#define GAHOOD_BUTTONS_H

typedef struct ControlStick ControlStick;
struct SDL_Renderer;

ControlStick * gahood_controlStickCreate(struct SDL_Renderer *, int, int);
void gahood_controlStickDestroy(ControlStick *);
void gahood_controlStickDraw(struct SDL_Renderer *, ControlStick *);

#endif
