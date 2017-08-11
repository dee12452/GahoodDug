#include "../headers/Sprite.hpp"
#include <SDL2/SDL.h>
#include "../headers/Window.hpp"
#include "../headers/ImageLoader.hpp"
#include "../headers/Timer.hpp"
#include "../headers/Constants.hpp"

Sprite::Sprite(const std::string &id) {
    this->src = NULL;
    this->dst = NULL;
    this->updateTimer = NULL;
    this->alpha = Constants::SPRITE_ALPHA_FULL;
    setImageId(id);
}

Sprite::Sprite(const std::string &id, 
        int srcX, int srcY, int srcW, int srcH, 
        int dstX, int dstY, int dstW, int dstH) : Sprite(id) {
    setSourceRect(srcX, srcY, srcW, srcH);
    setDestinationRect(dstX, dstY, dstW, dstH);
}

Sprite::Sprite(const std::string &id, 
        const SDL_Rect &srcR, 
        const SDL_Rect &dstR) : Sprite(id) {
    setSourceRect(srcR);
    setDestinationRect(dstR);
}

Sprite::~Sprite() {
    if(src != NULL) {
        delete src;
        src = NULL;
    }
    if(dst != NULL) {
        delete dst;
        dst = NULL;
    }
    if(updateTimer != NULL) {
        delete updateTimer;
        updateTimer = NULL;
    }
}

void Sprite::draw(Window *win) {
    SDL_Texture *texture = ImageLoader::getInstance()->getImage(id);
    SDL_SetTextureAlphaMod(texture, alpha);
	win->drawTexture(texture, src, dst);
    texture = NULL;
}

void Sprite::update() {
	/*
	 * Updating should NEVER happen if 
	 * there is no updateTimer set for the updating
	 */
    if(updateTimer != NULL) {
        if(updateTimer->check()) {
            onUpdate();
        }
    }
}

void Sprite::setUpdateTimer(unsigned int updateTimerMs) {
    updateTimer = new Timer(updateTimerMs);
}

void Sprite::setImageId(const std::string &id) {
    this->id = id;
}

void Sprite::setAlpha(uint8_t alpha) {
    this->alpha = alpha;
}

std::string Sprite::getImageId() const { return this->id; }

SDL_Rect * Sprite::getSourceRect() const { return src; }
void Sprite::setSourceRect(int x, int y, int w, int h) {
    if(src == NULL) {
        src = new SDL_Rect;
    }
    src->x = x;
    src->y = y;
    src->w = w;
    src->h = h;
}
void Sprite::setSourceRect(const SDL_Rect &rect) {
    setSourceRect(rect.x, rect.y, rect.w, rect.h);
}

SDL_Rect * Sprite::getDestinationRect() const { return dst; }
void Sprite::setDestinationRect(int x, int y, int w, int h) {
    if(dst == NULL) {
        dst = new SDL_Rect;
    }
    dst->x = x;
    dst->y = y;
    dst->w = w;
    dst->h = h;
}
void Sprite::setDestinationRect(const SDL_Rect &rect) {
    setDestinationRect(rect.x, rect.y, rect.w, rect.h);
}
