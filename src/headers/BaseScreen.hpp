#ifndef BASE_SCREEN_HPP
#define BASE_SCREEN_HPP

#include <vector>

class Sprite;
class Gahoodmon;
struct SDL_Renderer;
union SDL_Event;

class BaseScreen {
public:
    BaseScreen();
    virtual ~BaseScreen();
    void update();
    void updateInBackground();
    void handleInput(Gahoodmon *, const SDL_Event &);
    std::vector<Sprite *> getSprites() const;
    virtual void stop() = 0;

protected:
    virtual void onUpdate() = 0;
    virtual void onInput(Gahoodmon *, const SDL_Event &) = 0;
    virtual void onUpdateInBackground() = 0;

    std::vector<Sprite *> sprites;
};

#endif
