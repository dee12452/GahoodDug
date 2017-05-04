#ifndef GAHOOD_SCREEN_H
#define GAHOOD_SCREEN_H

struct SDL_Renderer;
enum GameState;

void gahood_screenUpdate();
void gahood_screenDraw(struct SDL_Renderer *);

#endif
