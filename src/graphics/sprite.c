#include "../headers/sprite.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/util.h"

typedef struct Sprite {
    SDL_Texture *spr;
    SDL_Rect src;
    SDL_Rect dst;
} Sprite;

Sprite * gahood_createSprite(SDL_Renderer *r, const char *file) {
    Sprite *sprite = malloc(sizeof(Sprite));
    sprite->spr = IMG_LoadTexture(r, file);
    if(!sprite->spr) {
        gahood_utilFatalSDLError(strcat("Failed to load texture", file));
    }
    return sprite;
}

void gahood_destroySprite(Sprite *sprite) {
    SDL_DestroyTexture(sprite->spr);
    sprite->spr = NULL;
    free(sprite);
}
