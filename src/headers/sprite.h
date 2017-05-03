#ifndef GAHOOD_SPRITE_H
#define GAHOOD_SPRITE_H

#include "util.h"

typedef struct Sprite {
    SDL_Texture *spr;
    SDL_Rect src;
    SDL_Rect dst;
} Sprite;

Sprite * gahood_createSprite(SDL_Renderer *, const char *);
void gahood_destroySprite(Sprite *);

#endif
