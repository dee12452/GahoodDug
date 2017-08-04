#ifndef MAP_SCREEN_HPP
#define MAP_SCREEN_HPP

#include "BaseScreen.hpp"

class Map;

class MapScreen : public BaseScreen {
public:
    MapScreen();
    ~MapScreen() override;

protected:
	void onDraw(SDL_Renderer *) override;
    void onStart() override;
    void onStop() override;
    void onUpdate() override;
    void onInput(Gahoodmon *, const SDL_Event &) override;
    void onUpdateInBackground() override;

private:
	Map *test;
};

#endif
