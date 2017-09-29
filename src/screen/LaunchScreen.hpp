#ifndef LAUNCH_SCREEN_HPP
#define LAUNCH_SCREEN_HPP

#include "BaseScreen.hpp"

class LaunchScreen : public BaseScreen {
public:
    LaunchScreen();
    ~LaunchScreen() override;

protected:
    void onDraw(Window *win) override;
    void onStart() override;
    void onStop() override;
    void onUpdate() override;
    void onInput(Game *game, const SDL_Event &event) override;
    void onKeyInput(const uint8_t *keys) override;
    void onUpdateInBackground() override;
};

#endif
