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
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_DOWN) {
				if (!test->getPlayer()->move(CH_DOWN, 500)) {
				}
			}
			else if (e.key.keysym.sym == SDLK_UP) {
				if (!test->getPlayer()->move(CH_UP, 500)) {
				}
			}
			else if (e.key.keysym.sym == SDLK_LEFT) {
				if (!test->getPlayer()->move(CH_LEFT, 500)) {
				}
			}
			else if (e.key.keysym.sym == SDLK_RIGHT) {
				if (!test->getPlayer()->move(CH_RIGHT, 500)) {
				}
			}
		}
	}
}
