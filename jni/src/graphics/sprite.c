#include "../headers/sprite.h"

#include <SDL.h>
#include <SDL_image.h>
#include "../headers/util.h"
#include "../headers/displayUtil.h"

struct Sprite {
    SDL_Texture *spriteSheet;
    SDL_Rect *src;
    SDL_Rect *dst;
};

Sprite * 
gahood_spriteCreate(SDL_Renderer *r, 
        const char *file) {
    Sprite *sprite = malloc(sizeof(Sprite));
    sprite->spriteSheet = IMG_LoadTexture(r, file);
    if(!sprite->spriteSheet) {
        char buffer[500];
        strcpy(buffer, "Failed to load sprite texture");
        strcat(buffer, file);
        gahood_utilFatalSDLError(buffer);
    }
    sprite->src = NULL;
    sprite->dst = NULL;
    return sprite;
}

void
gahood_spriteDestroy(Sprite *sprite) {
    if(sprite) {
        if(sprite->spriteSheet) {
            SDL_DestroyTexture(sprite->spriteSheet);
            sprite->spriteSheet = NULL;
        }
        gahood_spriteClearDimensions(sprite);
        free(sprite);
    }
}

void
gahood_spriteDraw(SDL_Renderer *r, Sprite *sprite) {
    if(sprite && sprite->spriteSheet) {
        SDL_RenderCopy(r,
                sprite->spriteSheet,
                sprite->src,
                sprite->dst);
    }
}

void
gahood_spriteSetSrcDimensions(Sprite *sprite, const SDL_Rect srcRect) {
    if(!sprite->src) {
        sprite->src = malloc(sizeof(SDL_Rect));
    }
    sprite->src->x = srcRect.x;
    sprite->src->y = srcRect.y;
    sprite->src->w = srcRect.w;
    sprite->src->h = srcRect.h;
}

void
gahood_spriteSetDstDimensions(Sprite *sprite, const SDL_Rect dstRect) {
    if(!sprite->dst) {
        sprite->dst = malloc(sizeof(SDL_Rect));
    }
    sprite->dst->x = dstRect.x;
    sprite->dst->y = dstRect.y;
    sprite->dst->w = dstRect.w;
    sprite->dst->h = dstRect.h;
}

SDL_Rect
gahood_spriteGetSrcDimensions(Sprite *sprite) {
    if(!sprite || !sprite->src) {
        SDL_Rect na;
        na.x = 0;
        na.y = 0;
        na.w = 0;
        na.h = 0;
        return na;
    }
    return *sprite->src;
}

SDL_Rect
gahood_spriteGetDstDimensions(Sprite *sprite) {
    if(!sprite || !sprite->dst) {
        SDL_Rect na;
        na.x = 0;
        na.y = 0;
        na.w = 0;
        na.h = 0;
        return na;
    }
    return *sprite->dst;
}

void
gahood_spriteClearDimensions(Sprite *sprite) {
    if(sprite->src) {
        free(sprite->src);
        sprite->src = NULL;
    }
    if(sprite->dst) {
        free(sprite->dst);
        sprite->dst = NULL;
    }
}

/* Logical Rendering Functions */
SDL_Rect
gahood_spriteGetLogicalDstDimensions(Sprite *sprite) {
    SDL_Rect logDst = gahood_spriteGetDstDimensions(sprite);
    logDst.x = (gahood_displayGetScreenWidth() - gahood_displayGetRenderWidth()) / 2 + (logDst.x * gahood_displayGetRenderWidth()) / WINDOW_WIDTH;
    logDst.y = (logDst.y * gahood_displayGetRenderHeight()) / WINDOW_HEIGHT;
    logDst.w = (logDst.w * gahood_displayGetRenderWidth()) / WINDOW_WIDTH;
    logDst.h = (logDst.h * gahood_displayGetRenderHeight()) / WINDOW_HEIGHT;
    return logDst;
}

bool
gahood_spriteCheckTouch(const SDL_TouchFingerEvent e, Sprite *sprite) {
    int touchX = e.x * gahood_displayGetScreenWidth();
    int touchY = e.y * gahood_displayGetScreenHeight();
    SDL_Rect sprPos = gahood_spriteGetLogicalDstDimensions(sprite);
    if(touchX >= sprPos.x && touchX <= sprPos.x + sprPos.w) {
        if(touchY >= sprPos.y && touchY <= sprPos.y + sprPos.h) {
            return true;
        }
    }
    return false;
}

void
gahood_spriteSetLogicalPosition(Sprite *sprite, int x, int y) {
    SDL_Rect locRect = gahood_spriteGetDstDimensions(sprite);
    int logX = ((x - (gahood_displayGetScreenWidth() - gahood_displayGetRenderWidth()) / 2) * WINDOW_WIDTH) / gahood_displayGetRenderWidth();
    int logY = (y * WINDOW_HEIGHT) / gahood_displayGetRenderHeight();
    locRect.x = logX - locRect.w / 2;
    locRect.y = logY - locRect.h / 2;
    SDL_Log("********************** %d, %d\n",
            logX,
            logY);
    gahood_spriteSetDstDimensions(sprite, locRect);
}
