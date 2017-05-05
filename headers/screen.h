#ifndef GAHOOD_SCREEN_H
#define GAHOOD_SCREEN_H

struct SDL_Renderer;
enum GameState;

void gahood_screenInit(enum GameState);
void gahood_screenClose();
void gahood_screenUpdate(enum GameState);
void gahood_screenDraw(struct SDL_Renderer *);

#endif
