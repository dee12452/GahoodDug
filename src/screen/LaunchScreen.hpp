#ifndef LAUNCH_SCREEN_HPP
#define LAUNCH_SCREEN_HPP

#include "BaseScreen.hpp"
#include "../game/BaseGameObject.hpp"
#include <string>

class FontSprite;
class LaunchScreenLoader;

class LaunchScreen : public BaseScreen, public BaseGameObject {
public:
    LaunchScreen();
    ~LaunchScreen() override;

	void start(Game *game) override;
	void stop(Game *game) override;
	void render(Window *win) override;

protected:
    void onInput(Game *game, const SDL_Event &event) override;
    void onKeyInput(Game *game, const uint8_t *keys) override;
	void onGameTick(Game *game) override;

private:
	//Sprites
	FontSprite *loadingText;
	bool hasDrawn;
};

#endif
