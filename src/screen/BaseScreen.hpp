#ifndef BASE_SCREEN_HPP
#define BASE_SCREEN_HPP

#include <vector>
#include "../game/Game.hpp"

class Sprite;
struct SDL_Renderer;
union SDL_Event;

class BaseScreen {
public:
    BaseScreen(Game *game);
    virtual ~BaseScreen();
    void update(Game *game);
    void updateInBackground(Game *game);
    void handleInput(Game *game);
	void draw(Window *win);

protected:
	virtual void onDraw(Window *win) = 0;
    virtual void onUpdate(Game *game) = 0;
    virtual void onInput(Game *game, const SDL_Event &event) = 0;
	virtual void onKeyInput(Game *game, const uint8_t *keys) = 0;
    virtual void onUpdateInBackground(Game *game) = 0;
};

#endif
