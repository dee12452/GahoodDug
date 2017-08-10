#include "../headers/Image.hpp"

Image::Image(const std::string &id) : Sprite(id) {}

Image::Image(const std::string &id, 
        int sX, 
        int sY, 
        int sW, 
        int sH, 
        int dX, 
        int dY, 
        int dW, 
        int dH) : Sprite(id, sX, sY, sW, sH, dX, dY, dW, dH) {}

Image::Image(const std::string &id, 
        const SDL_Rect &s, 
        const SDL_Rect &d) : Sprite(id, s, d) {}

Image::~Image() {}

void Image::onUpdate() {}
