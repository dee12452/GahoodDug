#include "../headers/GahoodSprite.hpp"

#include <SDL2/SDL.h>
#include "../headers/SpriteManager.hpp"

GahoodSprite::GahoodSprite() {
    this->srcDimensions = NULL;
    this->dstDimensions = NULL;
}

GahoodSprite::GahoodSprite(const std::string &tId) : GahoodSprite() {
    setTextureId(tId);
}

GahoodSprite::GahoodSprite(int sX, 
        int sY, 
        int sW, 
        int sH, 
        int dX, 
        int dY, 
        int dW, 
        int dH) {
    setSourceDimensions(sX, sY, sW, sH);
    setDestinationDimensions(dX, dY, dW, dH);
}

GahoodSprite::GahoodSprite(const std::string &tId,
        int sX, 
        int sY, 
        int sW, 
        int sH, 
        int dX, 
        int dY, 
        int dW, 
        int dH) : GahoodSprite(sX, sY, sW, sH, dX, dY, dW, dH) {
    setTextureId(tId);
}

GahoodSprite::~GahoodSprite() {
    if(srcDimensions != NULL) {
        free(srcDimensions);
        srcDimensions = NULL;
    }
    if(dstDimensions != NULL) {
        free(dstDimensions);
        dstDimensions = NULL;
    }
}

void GahoodSprite::setTextureId(const std::string &tId) {
    this->textureId = tId;
}

void GahoodSprite::setSourceDimensions(int x, int y, int w, int h) {
    if(srcDimensions == NULL) {
        srcDimensions = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    }
    srcDimensions->x = x;
    srcDimensions->y = y;
    srcDimensions->w = w;
    srcDimensions->h = h;
}

void GahoodSprite::setDestinationDimensions(int x, int y, int w, int h) {
    if(dstDimensions == NULL) {
        dstDimensions = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    }
    dstDimensions->x = x;
    dstDimensions->y = y;
    dstDimensions->w = w;
    dstDimensions->h = h;
}

void GahoodSprite::setSourceDimensions(SDL_Rect *r) {
    if(r != NULL) {
        if(srcDimensions != NULL) {
            free(srcDimensions);
        }
        srcDimensions = r;
    }
}

void GahoodSprite::setDestinationDimensions(SDL_Rect *r) {
    if(r != NULL) {
        if(dstDimensions != NULL) {
            free(dstDimensions);
        }
        dstDimensions = r;
    }
}

SDL_Rect * GahoodSprite::getSourceDimensions() const { return srcDimensions; }
SDL_Rect * GahoodSprite::getDestinationDimensions() const { return dstDimensions; }

void GahoodSprite::draw(SDL_Renderer *r) {
    SDL_Texture *texture = SpriteManager::getInstance()->getTexture(textureId);
    if(texture != NULL) {
        SDL_RenderCopy(r, texture, srcDimensions, dstDimensions);
    }
}
