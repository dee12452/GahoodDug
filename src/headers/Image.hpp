#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Sprite.hpp"

class Image : public Sprite {
public:
    Image(const std::string &id);
    Image(const std::string &id, int, int, int, int, int, int, int, int);
    Image(const std::string &id, const SDL_Rect &, const SDL_Rect &);
    ~Image() override;

protected:
    void onUpdate() override;
};

#endif
