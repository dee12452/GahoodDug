#ifndef INTRO_SCREEN_HPP
#define INTRO_SCREEN_HPP

#include "BaseScreen.hpp"

class IntroScreen : public BaseScreen {
public:
    IntroScreen();
    ~IntroScreen() override;

    void stop() override;

protected:
    void onUpdate() override;
    void onInput(Gahoodmon *, const SDL_Event &) override;
    void onUpdateInBackground() override;
};

#endif
