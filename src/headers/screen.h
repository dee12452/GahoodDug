#ifndef GAHOOD_SCREEN_H
#define GAHOOD_SCREEN_H

enum GameState;
struct SDL_Renderer;

void gahood_screenUpdate(enum GameState);
void gahood_screenDraw(struct SDL_Renderer *);

#endif
