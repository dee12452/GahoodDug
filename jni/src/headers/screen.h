#ifndef GAHOOD_SCREEN_H
#define GAHOOD_SCREEN_H

struct ControlStick;
struct SDL_Renderer;
struct Sprite;
enum GameState;

void gahood_screenCreate(int, struct Sprite **, struct ControlStick *);
void gahood_screenInit();
void gahood_screenDraw(struct SDL_Renderer *);
void gahood_screenUpdate(enum GameState);
void gahood_screenClose();
struct ControlStick * gahood_screenGetControlStick();

#endif
