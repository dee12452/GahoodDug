#include "../headers/MapScreen.hpp"
#include "../headers/Tile.hpp"
#include "../headers/Constants.hpp"
#include "../headers/Image.hpp"
#include "../headers/ImageLoader.hpp"
#include "../headers/MapLoader.hpp"
#include "../headers/Map.hpp"
#include "../headers/BaseCharacter.hpp"
#include <SDL2/SDL.h>

MapScreen::MapScreen() {
	test = NULL;
}

MapScreen::~MapScreen() {}

void MapScreen::onDraw(Window *win) {
	test->draw(win);
}

void MapScreen::onStart() {
	test = MapLoader::getInstance()->loadMap(Constants::MAP_FILE_TEST);
}

void MapScreen::onStop() {
	if (test != NULL) {
		delete test;
		test = NULL;
	}
}

void MapScreen::onUpdate() {
	if (test != NULL) {
		test->update();
	}
}

void MapScreen::onUpdateInBackground() {
}

void MapScreen::onInput(Gahoodmon *, const SDL_Event &e) {
	if (test != NULL) {
		const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
		switch (e.type) {
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_DOWN) {
				test->getPlayer()->move(CH_DOWN);
			}
			else if (e.key.keysym.sym == SDLK_UP) {
				test->getPlayer()->move(CH_UP);
			}
			else if (e.key.keysym.sym == SDLK_LEFT) {
				test->getPlayer()->move(CH_LEFT);
			}
			else if (e.key.keysym.sym == SDLK_RIGHT) {
				test->getPlayer()->move(CH_RIGHT);
			}
		}
	}
}
