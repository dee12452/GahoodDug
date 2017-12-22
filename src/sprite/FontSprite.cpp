#include "FontSprite.hpp"

#include <SDL2/SDL_ttf.h>
#include "../game/Window.hpp"
#include "Sprite.hpp"
#include "../util/Constants.hpp"
#include "../util/Util.hpp"

FontSprite::FontSprite(Window *win, TTF_Font *targetFont, const std::string &newText, const SDL_Color &color) {
    font = targetFont;
    text = newText;
    textColor = new SDL_Color;
    *textColor = color;
    texture = NULL;
    sprite = NULL;
    createNewFontTexture(win);
}

FontSprite::~FontSprite() {
    if(textColor != NULL) {
        delete textColor;
        textColor = NULL;
    }
    if(texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    if(sprite != NULL) {
        delete sprite;
        sprite = NULL;
    }
    if(font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }
}

void FontSprite::createNewFontTexture(Window *win) {
    if(texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    SDL_Surface *tempSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), *textColor, Constants::WINDOW_WIDTH);
    texture = SDL_CreateTextureFromSurface(win->getWindowRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
    tempSurface = NULL;
    if(sprite != NULL) {
        if(sprite->getDstRect() != NULL) {
            SDL_Rect dstR = *sprite->getDstRect();
            delete sprite;
            sprite = new Sprite(texture);
            sprite->setDstRect(dstR);
        }
        else {
            delete sprite;
            sprite = new Sprite(texture);
        }
    }
    else {
        sprite = new Sprite(texture);
    }
}

void FontSprite::setText(Window *win, const std::string &newText) {
    text = newText;
    createNewFontTexture(win);
}

void FontSprite::setColor(Window *win, const SDL_Color &color) {
    *textColor = color;
    createNewFontTexture(win);
}

void FontSprite::draw(Window *win) const {
    if(sprite != NULL) {
        sprite->draw(win);
    }
}

Sprite * FontSprite::getSprite() const { return sprite; }
std::string FontSprite::getText() const { return text; }
SDL_Color FontSprite::getColor() const  { return *textColor; }
