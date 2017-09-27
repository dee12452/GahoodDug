#ifndef MAP_SCREEN_HPP
#define MAP_SCREEN_HPP

#include "BaseScreen.hpp"

class Map;

class MapScreen : public BaseScreen {
public:
    MapScreen();
    ~MapScreen() override;

protected:
	void onDraw(Window *) override;
    void onStart() override;
    void onStop() override;
    void onUpdate() override;
    void onInput(Gahoodmon *, const SDL_Event &) override;
	void handleKeyboard(const uint8_t *) override;
    void onUpdateInBackground() override;

private:
	Map *test;
};

#endif
