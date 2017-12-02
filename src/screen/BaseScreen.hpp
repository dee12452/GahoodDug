#ifndef BASE_SCREEN_HPP
#define BASE_SCREEN_HPP

#include <vector>
#include "../game/Game.hpp"

class Sprite;
struct SDL_Renderer;
union SDL_Event;

class BaseScreen {
public:
    BaseScreen();
    virtual ~BaseScreen();
    
	//Screen Lifecycle
	virtual void start(Game *game);
	virtual void pause(Game *game);
	virtual void resume(Game *game);
	virtual void stop(Game *game);
	virtual void drawScreen(Window *win) const = 0;

	void handleInput(Game *game);

protected:

    virtual void onInput(Game *game, const SDL_Event &event) = 0;
	virtual void onKeyInput(Game *game, const uint8_t *keys) = 0;
};

#endif
