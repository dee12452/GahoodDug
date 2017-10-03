#ifndef MAP_SCREEN_HPP
#define MAP_SCREEN_HPP

#include "BaseScreen.hpp"

class MapScreen : public BaseScreen {
public:
    MapScreen();
    ~MapScreen() override;

protected:
    void onDraw(Window *win) override;
    void onStart(Game *game) override;
    void onStop() override;
    void onUpdate(Game *game) override;
    void onUpdateInBackground(Game *game) override;
    void onInput(Game *game, const SDL_Event &event) override;
    void onKeyInput(Game *game, const uint8_t *keyboard) override;
};

#endif
