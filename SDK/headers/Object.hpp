#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "GahoodSprite.hpp"

class Object : public GahoodSprite {
public:
    Object(const std::string &, const SDL_Rect &, const SDL_Rect &);
    virtual ~Object();

    void update();

    virtual std::string getObjectId() = 0;

protected:
    virtual void onUpdate() = 0;
};

#endif
