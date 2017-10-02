#include "FontSprite.hpp"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "Sprite.hpp"

FontSprite::FontSprite(SDL_Renderer *renderer, TTF_Font *targetFont, const std::string &newText, const SDL_Color &color) {
    font = targetFont;
    text = newText;
    textColor = new SDL_Color;
    *textColor = color;
    texture = NULL;
    sprite = NULL;
    createNewFontTexture(renderer);
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

void FontSprite::createNewFontTexture(SDL_Renderer *renderer) {
    if(texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    SDL_Surface *tempSurface = TTF_RenderUTF8_Solid(font, text.c_str(), *textColor);
    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    tempSurface = NULL;
    if(sprite != NULL) {
        delete sprite;
    } 
    sprite = new Sprite(texture);
}

void FontSprite::changeText(SDL_Renderer *renderer, const std::string &newText) {
    text = newText;
    createNewFontTexture(renderer);
}

void FontSprite::changeColor(SDL_Renderer *renderer, const SDL_Color &color) {
    *textColor = color;
    createNewFontTexture(renderer);
}

void FontSprite::draw(SDL_Renderer *renderer) {
    if(sprite != NULL) {
        sprite->draw(renderer);
    }
}

Sprite * FontSprite::getSprite() const { return sprite; }
std::string FontSprite::getText() const { return text; }
SDL_Color FontSprite::getColor() const  { return *textColor; }
