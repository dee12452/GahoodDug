#include "Sprite.hpp"

#include "../game/Window.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

Sprite::Sprite(SDL_Texture *sprSheet) {
    spriteSheet = sprSheet;
    sourceRect = NULL;
    destinationRect = NULL;
}

Sprite::Sprite(SDL_Texture *sprSheet,
        int srcX, int srcY, int srcW, int srcH,
        int dstX, int dstY, int dstW, int dstH) : Sprite(sprSheet) {
    sourceRect = new SDL_Rect;
    destinationRect = new SDL_Rect;
    sourceRect->x = srcX; sourceRect->y = srcY;
    sourceRect->w = srcW, sourceRect->h = srcH;
    destinationRect->x = dstX; destinationRect->y = dstY;
    destinationRect->w = dstW; destinationRect->h = dstH;
}

Sprite::Sprite(SDL_Texture *sprSheet, const SDL_Rect &srcRect, const SDL_Rect &dstRect) 
    : Sprite(sprSheet,
            srcRect.x, srcRect.y, srcRect.w, srcRect.h,
            dstRect.x, dstRect.y, dstRect.w, dstRect.h) {

}

Sprite::~Sprite() {
    if(sourceRect != NULL) {
        delete sourceRect;
        sourceRect = NULL;
    }
    if(destinationRect != NULL) {
        delete destinationRect;
        destinationRect = NULL;
    }
    spriteSheet = NULL;
}

void Sprite::draw(Window *window) const {
    if(window != NULL && spriteSheet != NULL) {
		window->drawTexture(getTexture(), sourceRect, destinationRect);
    }
}

int Sprite::getSrcX() const { return sourceRect == NULL ? 0 : sourceRect->x; }
int Sprite::getSrcY() const { return sourceRect == NULL ? 0 : sourceRect->y; }
int Sprite::getSrcW() const { return sourceRect == NULL ? 0 : sourceRect->w; }
int Sprite::getSrcH() const { return sourceRect == NULL ? 0 : sourceRect->h; }

int Sprite::getDstX() const { return destinationRect == NULL ? 0 : destinationRect->x; }
int Sprite::getDstY() const { return destinationRect == NULL ? 0 : destinationRect->y; }
int Sprite::getDstW() const { return destinationRect == NULL ? 0 : destinationRect->w; }
int Sprite::getDstH() const { return destinationRect == NULL ? 0 : destinationRect->h; }

SDL_Rect * Sprite::getSrcRect() const { return sourceRect; }
SDL_Rect * Sprite::getDstRect() const { return destinationRect; }
SDL_Texture * Sprite::getTexture() const { return spriteSheet; }

void Sprite::setSrcRect(const SDL_Rect &srcRect) {
    if(sourceRect == NULL) { sourceRect = new SDL_Rect; }
    sourceRect->x = srcRect.x; sourceRect->y = srcRect.y;
    sourceRect->w = srcRect.w; sourceRect->h = srcRect.h;
}

void Sprite::setDstRect(const SDL_Rect &dstRect) {
    if(destinationRect == NULL) { destinationRect = new SDL_Rect; }
    destinationRect->x = dstRect.x; destinationRect->y = dstRect.y;
    destinationRect->w = dstRect.w; destinationRect->h = dstRect.h;
}

void Sprite::setSrcX(int srcX) {
    if(sourceRect == NULL) { initRect(sourceRect); }
    sourceRect->x = srcX;
}
void Sprite::setSrcY(int srcY) {
    if(sourceRect == NULL) { initRect(sourceRect); }
    sourceRect->y = srcY;
}
void Sprite::setSrcW(int srcW) {
    if(sourceRect == NULL) { initRect(sourceRect); }
    sourceRect->w = srcW;
}
void Sprite::setSrcH(int srcH) {
    if(sourceRect == NULL) { initRect(sourceRect); }
    sourceRect->h = srcH;
}

void Sprite::setDstX(int dstX) {
    if(destinationRect == NULL) { initRect(destinationRect); }
    destinationRect->x = dstX;
}
void Sprite::setDstY(int dstY) {
    if(destinationRect == NULL) { initRect(destinationRect); }
    destinationRect->y = dstY;
}
void Sprite::setDstW(int dstW) {
    if(destinationRect == NULL) { initRect(destinationRect); }
    destinationRect->w = dstW;
}
void Sprite::setDstH(int dstH) {
    if(destinationRect == NULL) { initRect(destinationRect); }
    destinationRect->h = dstH;
}

void Sprite::setSpriteSheet(SDL_Texture *newSpriteSheet) {
    spriteSheet = newSpriteSheet;
}

void Sprite::initRect(SDL_Rect *&targetRect) const {
    if(targetRect == NULL) targetRect = new SDL_Rect;
    targetRect->x = 0; targetRect->y = 0;
    targetRect->w = 0; targetRect->h = 0;
}
