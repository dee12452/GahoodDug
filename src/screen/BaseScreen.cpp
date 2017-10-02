#include "BaseScreen.hpp"
#include <SDL2/SDL.h>
#include "../game/Game.hpp"
#include "../game/Window.hpp"
#include "../game/Sprite.hpp"

BaseScreen::BaseScreen() {}

BaseScreen::~BaseScreen() {}

void BaseScreen::start(Game *game) {
    onStart(game);
}

void BaseScreen::stop() {
    onStop();
}

void BaseScreen::update(Game *game) {
    onUpdate(game);
}

void BaseScreen::updateInBackground(Game *game) { 
    onUpdateInBackground(game);
}

void BaseScreen::handleInput(Game *game) {
    //Game handles quit event//
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
	onKeyInput(game, keyboard);
}

void BaseScreen::draw(Window *win) {
	onDraw(win);
}
