#ifndef BASE_SCREEN_HPP
#define BASE_SCREEN_HPP

#include <vector>
#include <stdint.h>

class Sprite;
class Game;
class Window;
struct SDL_Renderer;
union SDL_Event;

class BaseScreen {
public:
    BaseScreen();
    virtual ~BaseScreen();
    void update();
    void updateInBackground();
    void handleInput(Game *);
	void draw(Window *);
    void start();
    void stop();

protected:
	virtual void onDraw(Window *win) = 0;
    virtual void onStart() = 0;
    virtual void onStop() = 0;
    virtual void onUpdate() = 0;
    virtual void onInput(Game *game, const SDL_Event &event) = 0;
	virtual void onKeyInput(const uint8_t *keys) = 0;
    virtual void onUpdateInBackground() = 0;
};

#endif
