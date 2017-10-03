#include "LaunchScreen.hpp"

#include <SDL2/SDL_ttf.h>
#include "MapScreen.hpp"
#include "../game/Sprites.hpp"
#include "../util/Utils.hpp"

LaunchScreen::LaunchScreen() : currentImageFile(0), loadingText(NULL) {}

LaunchScreen::~LaunchScreen() {}

void LaunchScreen::onDraw(Window *win) {
    if(!isLoading() && loadingText->getText() != "Finished") {
        loadingText->setText(win->getWindowRenderer(), "Finished");
    }
    else if(isLoading() && loadingText->getText() != "Loading " + FileUtil::getFileName(imageFilePaths[currentImageFile].c_str())) {
        loadingText->setText(win->getWindowRenderer(), "Loading " + FileUtil::getFileName(imageFilePaths[currentImageFile].c_str()));
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
    if(!isLoading()) {
        game->requestNewScreen(new MapScreen());
    }
    else {
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
