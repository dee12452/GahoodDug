#include "LaunchScreen.hpp"

#include <SDL2/SDL_ttf.h>
#include "WorldScreen.hpp"
#include "../game/Game.hpp"
#include "../sprite/Sprites.hpp"
#include "../util/Utils.hpp"
#include "../map/MapLoader.hpp"

LaunchScreen::LaunchScreen() : BaseScreen(), loadingText(NULL), hasDrawn(false) {}

LaunchScreen::~LaunchScreen() {
    if(loadingText != NULL) {
        delete loadingText;
        loadingText = NULL;
    }
}

void LaunchScreen::start(Game *game) {
	game->schedule(this);
	loadingText = game->getFont(Constants::FONT_JOYSTIX)->createFontSprite(game->getWindow(), "Loading");
	loadingText->setColor(game->getWindow(), Constants::COLOR_WHITE);
	loadingText->getSprite()->setDstRect(Util::createRectCenteredHorizontally(450, 150, 25));
}

void LaunchScreen::stop(Game *game) {
	game->unschedule(this);
}

void LaunchScreen::render(Window *win) {
    loadingText->draw(win);
	hasDrawn = true;
}

void LaunchScreen::onInput(Game *, const SDL_Event &) {}

void LaunchScreen::onKeyInput(Game *, const uint8_t *) {}

void LaunchScreen::onGameTick(Game *game) {
	if (!hasDrawn) return;
	std::vector<std::string> imageFiles = FileUtil::getFilesRecursively(Constants::GAME_RES_FOLDER, Constants::IMAGE_FILE_EXTENSION);
	for (unsigned int i = 0; i < imageFiles.size(); i++) game->loadSpriteSheet(imageFiles[i].c_str());
	MapLoader::getInstance()->loadAll(game, Constants::GAME_RES_FOLDER);
	game->unschedule(this);
	game->requestNewScreen(new WorldScreen());
}
