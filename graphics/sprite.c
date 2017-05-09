#include "../headers/sprite.h"

#include <SDL.h>
#include <SDL_image.h>
#include "../headers/util.h"

struct Sprite {
    SDL_Texture *spriteSheet;
    SDL_Rect src;
    SDL_Rect dst;
};

Sprite * 
gahood_spriteCreate(SDL_Renderer *r, 
        const char *file, 
        SDL_Rect srcDimensions, 
        SDL_Rect dstDimensions) {
    Sprite *sprite = malloc(sizeof(Sprite));
    sprite->spriteSheet = IMG_LoadTexture(r, file);
    if(!sprite->spriteSheet) {
        char buffer[500];
        strcpy(buffer, "Failed to load sprite texture");
        strcat(buffer, file);
        gahood_utilFatalSDLError(buffer);
    }
    sprite->src = srcDimensions;
    sprite->dst = dstDimensions;
    return sprite;
}

void
gahood_spriteDestroy(Sprite *sprite) {
    if(sprite) {
        if(sprite->spriteSheet) {
            SDL_DestroyTexture(sprite->spriteSheet);
            sprite->spriteSheet = NULL;
        }
        free(sprite);
    }
}

void
gahood_spriteDraw(SDL_Renderer *r, Sprite *sprite) {
    if(sprite && sprite->spriteSheet) {
        SDL_RenderCopy(r,
                sprite->spriteSheet,
                &sprite->src,
                &sprite->dst);
    }
}

void
gahood_spriteSetSrcDimensions(Sprite *sprite, const SDL_Rect srcRect) {
    sprite->src = srcRect;
}

void
gahood_spriteSetDstDimensions(Sprite *sprite, const SDL_Rect dstRect) {
    sprite->dst = dstRect;
}

SDL_Rect
gahood_spriteGetSrcDimensions(Sprite *sprite) {
    return sprite->src;
}

SDL_Rect
gahood_spriteGetDstDimensions(Sprite *sprite) {
    return sprite->dst;
}
