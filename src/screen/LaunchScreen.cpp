#include "LaunchScreen.hpp"

#include <SDL2/SDL_ttf.h>
#include "../game/Game.hpp"
#include "../game/Window.hpp"
#include "../util/Util.hpp"
#include "../util/FileUtil.hpp"
#include "../util/Constants.hpp"
#include "../game/Font.hpp"
#include "../game/FontSprite.hpp"
#include "../game/Sprite.hpp"

LaunchScreen::LaunchScreen() : currentImageFile(0), loadingText(NULL) {}

LaunchScreen::~LaunchScreen() {}

void LaunchScreen::onDraw(Window *win) {
    if(!isLoading() && loadingText->getText() != "Finished") {
        loadingText->setText(win->getWindowRenderer(), "Finished");
    }
    else if(isLoading() && loadingText->getText() != "Loading " + imageFilePaths[currentImageFile]) {
        loadingText->setText(win->getWindowRenderer(), "Loading " + imageFilePaths[currentImageFile]);
    }
    loadingText->draw(win->getWindowRenderer());
}

void LaunchScreen::onStart(Game *game) {
    imageFilePaths = FileUtil::getFilesRecursively(Constants::GAME_RES_FOLDER, Constants::IMAGE_FILE_EXTENSION);
    loadingText = game->getFont(Constants::FONT_JOYSTIX)->createFontSprite(game->getWindow()->getWindowRenderer(), "Loading");
    loadingText->setColor(game->getWindow()->getWindowRenderer(), Constants::COLOR_WHITE);
    loadingText->getSprite()->setDstRect(Util::createRectCenteredHorizontally(450, 150, 25));
}

void LaunchScreen::onStop() {
    if(loadingText != NULL) {
        delete loadingText;
        loadingText = NULL;
    }
}

void LaunchScreen::onUpdate(Game *game) {
    if(isLoading()) {
        for(int i = 0; isLoading() && i < LaunchScreen::IMAGE_LOAD_RATE; i++) {
            game->loadSpriteSheet(imageFilePaths[currentImageFile].c_str());
            currentImageFile++;
        }
    }
}

void LaunchScreen::onUpdateInBackground(Game *) {}

void LaunchScreen::onInput(Game *, const SDL_Event &) {}

void LaunchScreen::onKeyInput(Game *, const uint8_t *) {}

bool LaunchScreen::isLoading() const {
    return currentImageFile < imageFilePaths.size();
}
