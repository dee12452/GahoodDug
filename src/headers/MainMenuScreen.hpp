#ifndef MAIN_MENU_SCREEN_HPP
#define MAIN_MENU_SCREEN_HPP

#include "BaseScreen.hpp"

class MainMenuScreen : public BaseScreen {
public:
    MainMenuScreen();
    ~MainMenuScreen() override;

protected:
	void onDraw(SDL_Renderer *) override;
    void onStart() override;
    void onStop() override;
    void onUpdate() override;
    void onInput(Gahoodmon *, const SDL_Event &) override;
    void onUpdateInBackground() override;
};

#endif
