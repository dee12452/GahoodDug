#include "LaunchScreen.hpp"

#include <SDL2/SDL_ttf.h>
#include "../game/Game.hpp"
#include "../game/Window.hpp"
#include "../util/Util.hpp"
#include "../util/FileUtil.hpp"
#include "../util/Constants.hpp"

LaunchScreen::LaunchScreen() : currentImageFile(0) {}

LaunchScreen::~LaunchScreen() {}

void LaunchScreen::onDraw(Window *) {
}

void LaunchScreen::onStart() {
    imageFilePaths = FileUtil::getFilesRecursively(Constants::GAME_RES_FOLDER, Constants::IMAGE_FILE_EXTENSION);
}

void LaunchScreen::onStop() {}

void LaunchScreen::onUpdate(Game *game) {
    if(isLoading()) {
        Util::log("Loading image " + imageFilePaths[currentImageFile]);
        game->loadSpriteSheet(imageFilePaths[currentImageFile].c_str());
        currentImageFile++;
    }
}

void LaunchScreen::onUpdateInBackground(Game *) {}

void LaunchScreen::onInput(Game *, const SDL_Event &) {}

void LaunchScreen::onKeyInput(Game *, const uint8_t *) {}

bool LaunchScreen::isLoading() const {
    return currentImageFile < imageFilePaths.size();
}
