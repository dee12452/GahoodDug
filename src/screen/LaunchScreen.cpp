#include "LaunchScreen.hpp"

#include <SDL2/SDL_ttf.h>
#include "MapScreen.hpp"
#include "../game/Sprites.hpp"
#include "../util/Utils.hpp"
#include "../map/MapLoader.hpp"

LaunchScreen::LaunchScreen(Game *game) 
    : BaseScreen(game), 
      imageFilePaths(FileUtil::getFilesRecursively(Constants::GAME_RES_FOLDER, Constants::IMAGE_FILE_EXTENSION)),
      currentImageFile(0), 
      loadingText(game->getFont(Constants::FONT_JOYSTIX)->createFontSprite(game->getWindow()->getWindowRenderer(), "Loading")) {
    loadingText->setColor(game->getWindow()->getWindowRenderer(), Constants::COLOR_WHITE);
    loadingText->getSprite()->setDstRect(Util::createRectCenteredHorizontally(450, 150, 25));
}

LaunchScreen::~LaunchScreen() {
    if(loadingText != NULL) {
        delete loadingText;
        loadingText = NULL;
    }
}

void LaunchScreen::onDraw(Window *win) {
    if(!isLoading() && loadingText->getText() != "Finished") {
        loadingText->setText(win->getWindowRenderer(), "Finished");
    }
    else if(isLoading() && loadingText->getText() != "Loading " + FileUtil::getFileName(imageFilePaths[currentImageFile].c_str())) {
        loadingText->setText(win->getWindowRenderer(), "Loading " + FileUtil::getFileName(imageFilePaths[currentImageFile].c_str()));
    }
    loadingText->draw(win->getWindowRenderer());
}

void LaunchScreen::onUpdate(Game *game) {
    if(!isLoading()) {
		//Load the tilesets and maps
		MapLoader::getInstance()->loadAll(game, Constants::GAME_RES_FOLDER);
		Util::log(SDL_LOG_PRIORITY_INFO, "Loaded maps and tilesets!");

        game->requestNewScreen(new MapScreen(game));
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
