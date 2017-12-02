#ifndef LAUNCH_SCREEN_HPP
#define LAUNCH_SCREEN_HPP

#include "BaseScreen.hpp"
#include <string>

class FontSprite;

class LaunchScreen : public BaseScreen {
public:
    LaunchScreen();
    ~LaunchScreen() override;

	void start(Game *game) override;
	void stop(Game *game) override;
	void drawScreen(Window *win) const override;

protected:
    void onInput(Game *game, const SDL_Event &event) override;
    void onKeyInput(Game *game, const uint8_t *keys) override;

private:
	//Class for loading sprites
	class LaunchScreenLoader;
	LaunchScreenLoader *loader;

	//Sprites
	FontSprite *loadingText;
};

#endif
