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
    void updateInBackground();
    std::vector<Sprite *> getSprites() const;

protected:
    virtual void onUpdate() = 0;
    virtual void onUpdateInBackground() = 0;

    std::vector<Sprite *> sprites;
};

#endif
