#include "BaseScreen.hpp"
#include <SDL2/SDL.h>
#include "../game/Gahoodmon.hpp"
#include "../game/Window.hpp"
#include "../game/Sprite.hpp"

BaseScreen::BaseScreen() {}

BaseScreen::~BaseScreen() {}

void BaseScreen::start() {
    onStart();
}

void BaseScreen::stop() {
    onStop();
}

void BaseScreen::update() {
    onUpdate();
}

void BaseScreen::updateInBackground() { 
    onUpdateInBackground();
}

void BaseScreen::handleInput(Gahoodmon *game) {
    //Gahoodmon handles quit event//
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			game->quit();
		}
		else {
			onInput(game, e);
		}
	}
	const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
	onKeyInput(keyboard);
}

void BaseScreen::draw(Window *win) {
	onDraw(win);
}
