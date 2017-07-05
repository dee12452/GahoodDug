#ifndef MAP_SCREEN_HPP
#define MAP_SCREEN_HPP

#include "BaseScreen.hpp"

class MapScreen : public BaseScreen {
public:
    MapScreen();
    ~MapScreen() override;

    void drawScreen(SDL_Renderer *) override;
protected:
    void onStart() override;
    void onStop() override;
    void onUpdate() override;
    void onInput(Gahoodmon *, const SDL_Event &) override;
    void onUpdateInBackground() override;
};

#endif
