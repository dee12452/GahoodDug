#include "MapScreen.hpp"

MapScreen::MapScreen() : currentMap(NULL) {}

MapScreen::~MapScreen() {}

void MapScreen::onStart(Game *) {}

void MapScreen::onStop() {}

void MapScreen::onDraw(Window *) {}

void MapScreen::onUpdate(Game *) {}

void MapScreen::onUpdateInBackground(Game *) {}

void MapScreen::onInput(Game *, const SDL_Event &) {}

void MapScreen::onKeyInput(Game *, const uint8_t *) {}
