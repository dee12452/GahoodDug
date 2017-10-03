#include "LaunchScreen.hpp"

#include <SDL2/SDL_ttf.h>
#include "../game/Game.hpp"
#include "../game/Window.hpp"
#include "../util/Util.hpp"
#include "../util/FileUtil.hpp"
#include "../util/Constants.hpp"
#include "../game/Font.hpp"
#include "../game/FontSprite.hpp"

LaunchScreen::LaunchScreen() : currentImageFile(0), disclaimer(NULL) {}

LaunchScreen::~LaunchScreen() {}

void LaunchScreen::onDraw(Window *win) {
    disclaimer->draw(win->getWindowRenderer());
}

void LaunchScreen::onStart(Game *game) {
    imageFilePaths = FileUtil::getFilesRecursively(Constants::GAME_RES_FOLDER, Constants::IMAGE_FILE_EXTENSION);
    disclaimer = game->getFont(Constants::FONT_JOYSTIX)->createFontSprite(game->getWindow()->getWindowRenderer(), "Test", 12);
    SDL_Color white;
    white.a = Constants::SPRITE_ALPHA_FULL;
    white.r = Constants::SPRITE_ALPHA_FULL;
    white.g = Constants::SPRITE_ALPHA_FULL;
    white.b = Constants::SPRITE_ALPHA_FULL;
    disclaimer->changeColor(game->getWindow()->getWindowRenderer(), white);
}

void LaunchScreen::onStop() {
    if(disclaimer != NULL) {
        delete disclaimer;
        disclaimer = NULL;
    }
}

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
