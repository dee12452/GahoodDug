#include "../headers/IntroScreen.hpp"
#include "../headers/Image.hpp"
#include "../headers/Constants.hpp"

IntroScreen::IntroScreen() : BaseScreen() {}

IntroScreen::~IntroScreen() {}

void IntroScreen::onDraw(Window *r) {}

void IntroScreen::onStart() {
    addSprite(new Image(Constants::IMAGE_ID_TEST));
}

void IntroScreen::onStop() {}

void IntroScreen::onUpdate() {}

void IntroScreen::onUpdateInBackground() {}

void IntroScreen::onInput(Gahoodmon *, const SDL_Event &) {
}
