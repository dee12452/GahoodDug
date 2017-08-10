#include "../headers/Sprite.hpp"
#include <SDL2/SDL.h>
#include "../headers/Window.hpp"
#include "../headers/ImageLoader.hpp"
#include "../headers/Timer.hpp"
#include "../headers/Constants.hpp"

Sprite::Sprite(const std::string &id) {
    this->src = NULL;
    this->dst = NULL;
    this->timer = NULL;
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
    if(timer != NULL) {
        delete timer;
        timer = NULL;
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
	 * there is no timer set for the updating
	 */
    if(timer != NULL) {
        if(timer->check()) {
            onUpdate();
        }
    }
}

void Sprite::setUpdateTimer(unsigned int timerMs) {
    timer = new Timer(timerMs);
}

void Sprite::setImageId(const std::string &id) {
    this->id = id;
}
void Sprite::setX(int x) {
    if(dst == NULL) {
        setDestinationRect(x, 0, 0, 0);
    }
    else {
        dst->x = x;
    }
}
void Sprite::setY(int y) {
    if(dst == NULL) {
        setDestinationRect(0, y, 0, 0);
    }
    else {
        dst->y = y;
    }
}
void Sprite::setWidth(int w) {
    if(dst == NULL) {
        setDestinationRect(0, 0, w, 0);
    }
    else {
        dst->w = w;
    }
}
void Sprite::setHeight(int h) {
    if(dst == NULL) {
        setDestinationRect(h, 0, 0, 0);
    }
    else {
        dst->h = h;
    }
}

void Sprite::setAlpha(uint8_t alpha) {
    this->alpha = alpha;
}

std::string Sprite::getImageId() const { return this->id; }
int Sprite::getX() const { return dst == NULL ? 0 : dst->x; }
int Sprite::getY() const { return dst == NULL ? 0 : dst->y; }
int Sprite::getWidth() const { return dst == NULL ? 0 : dst->w; }
int Sprite::getHeight() const { return dst == NULL ? 0 : dst->h; }

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
