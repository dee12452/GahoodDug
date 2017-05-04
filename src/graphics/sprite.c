#include "../headers/sprite.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/util.h"

struct Sprite {
    SDL_Texture *spr;
    SDL_Rect src;
    SDL_Rect dst;
};

Sprite * 
gahood_spriteCreate(SDL_Renderer *r, const char *file) {
    Sprite *sprite = malloc(sizeof(Sprite));
    sprite->spr = IMG_LoadTexture(r, file);
    if(!sprite->spr) {
        gahood_utilFatalSDLError(strcat("Failed to load texture", file));
    }
    return sprite;
}

void 
gahood_spriteDestroy(Sprite *sprite) {
    SDL_DestroyTexture(sprite->spr);
    sprite->spr = NULL;
    free(sprite);
}

void 
gahood_spriteDraw(SDL_Renderer *r, Sprite *sprite) {
    if(sprite) {
        SDL_RenderCopy(r, sprite->spr, &sprite->src, &sprite->dst);
    }
}

SDL_Rect 
gahood_spriteGetSourceRect(Sprite *sprite) {
    SDL_Rect retRect;
    retRect.x = sprite->src.x;
    retRect.y = sprite->src.y;
    retRect.w = sprite->src.w;
    retRect.h = sprite->src.h;
    return retRect;
}

SDL_Rect 
gahood_spriteGetDestinationRect(Sprite *sprite) {
    SDL_Rect retRect;
    retRect.x = sprite->dst.x;
    retRect.y = sprite->dst.y;
    retRect.w = sprite->dst.w;
    retRect.h = sprite->dst.h;
    return retRect;

}

void 
gahood_spriteSetSourceRect(Sprite *sprite, int x, int y, int w, int h) {
    sprite->src.x = x;
    sprite->src.w = w;
    sprite->src.y = y;
    sprite->src.h = h;
}

void 
gahood_spriteSetDestinationRect(Sprite *sprite, int x, int y, int w, int h) {
    sprite->dst.x = x;
    sprite->dst.w = w;
    sprite->dst.y = y;
    sprite->dst.h = h;
}
