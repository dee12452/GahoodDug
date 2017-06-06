#include "../headers/Object.hpp"

#include <SDL2/SDL.h> 

Object::Object(const std::string &tId, const SDL_Rect &src, const SDL_Rect &dst) : GahoodSprite(tId) {
    setSourceDimensions(src.x, src.y, src.w, src.h);
    setDestinationDimensions(dst.x, dst.y, dst.w, dst.h);
}

void Object::update() { onUpdate(); }
