#include "../headers/sprite.h"

Sprite * gahood_createSprite(SDL_Renderer *r, const char *file) {
    Sprite *sprite = malloc(sizeof(Sprite));
    sprite->spr = IMG_LoadTexture(r, file);
    return sprite;
}

void gahood_destroySprite(Sprite *sprite) {
    SDL_DestroyTexture(sprite->spr);
    sprite->spr = NULL;
    free(sprite);
}
