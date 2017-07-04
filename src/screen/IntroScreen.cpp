#include "../headers/IntroScreen.hpp"
#include "../headers/Image.hpp"
#include "../headers/Constants.hpp"

IntroScreen::IntroScreen() : BaseScreen() {
    sprites.push_back(new Image(Constants::IMAGE_ID_TEST));
}

IntroScreen::~IntroScreen() {

}

void IntroScreen::onUpdate() {}

void IntroScreen::onUpdateInBackground() {}

void IntroScreen::stop() {}

void IntroScreen::onInput(Gahoodmon *, const SDL_Event &) {
}
