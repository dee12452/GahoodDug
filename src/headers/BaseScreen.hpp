#ifndef BASE_SCREEN_HPP
#define BASE_SCREEN_HPP

#include <vector>

class Sprite;
struct SDL_Renderer;

class BaseScreen {
public:
    BaseScreen();
    virtual ~BaseScreen();
    void update();
    std::vector<Sprite *> getSprites() const;

protected:
    virtual void onUpdate();

    std::vector<Sprite *> sprites;
};

#endif
