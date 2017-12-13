#ifndef MAP_SCREEN_HPP
#define MAP_SCREEN_HPP

#include "BaseScreen.hpp"

class World;

class WorldScreen : public BaseScreen {
public:
	WorldScreen();
    ~WorldScreen() override;

	void start(Game *game) override;
	void stop(Game *game) override;
	void drawScreen(Window *win) const override;

protected:
    void onInput(Game *game, const SDL_Event &event) override;
    void onKeyInput(Game *game, const uint8_t *keyboard) override;

private:
    World *world;
};

#endif
