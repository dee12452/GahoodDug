#include "LaunchScreen.hpp"

#include <SDL2/SDL_ttf.h>
#include "MapScreen.hpp"
#include "../game/BaseGameObject.hpp"
#include "../sprite/Sprites.hpp"
#include "../util/Utils.hpp"
#include "../map/MapLoader.hpp"

class LaunchScreen::LaunchScreenLoader : public BaseGameObject {
public:
	LaunchScreenLoader(Game *game) :
		BaseGameObject(),
		imageFilePaths(FileUtil::getFilesRecursively(Constants::GAME_RES_FOLDER, Constants::IMAGE_FILE_EXTENSION)),
		currentImageFile(0) {}
	~LaunchScreenLoader() override {}

	void onTick(Game *game) override {
		if (!isLoading()) {
			//Load the tilesets and maps
			MapLoader::getInstance()->loadAll(game, Constants::GAME_RES_FOLDER);
			Util::log(SDL_LOG_PRIORITY_INFO, "Loaded maps and tilesets!");

			game->unregisterGameObject(this);
			game->requestNewScreen(new MapScreen(game));
		}
		else {
			for (int i = 0; isLoading() && i < IMAGE_LOAD_RATE; i++) {
				game->loadSpriteSheet(imageFilePaths[currentImageFile].c_str());
				currentImageFile++;
			}
		}
	}
	void onTickInBackground() override {}
	bool isLoading() const { return currentImageFile < imageFilePaths.size(); }
	std::string getCurrentImageFileName() const {
		if (isLoading()) return imageFilePaths[currentImageFile];
		else return "Finished";
	}


private:
	static const int IMAGE_LOAD_RATE = 50;

	//Used for loading the game images
	std::vector<std::string> imageFilePaths;
	size_t currentImageFile;
};

LaunchScreen::LaunchScreen(Game *game) : 
	  BaseScreen(game), 
      loadingText(game->getFont(Constants::FONT_JOYSTIX)->createFontSprite(game->getWindow()->getWindowRenderer(), "Loading")),
      loader(new LaunchScreenLoader(game)) {
    loadingText->setColor(game->getWindow()->getWindowRenderer(), Constants::COLOR_WHITE);
    loadingText->getSprite()->setDstRect(Util::createRectCenteredHorizontally(450, 150, 25));
	game->registerGameObject(loader);
}

LaunchScreen::~LaunchScreen() {
	if (loader != NULL) {
		delete loader;
		loader = NULL;
	}
    if(loadingText != NULL) {
        delete loadingText;
        loadingText = NULL;
    }
}

void LaunchScreen::drawScreen(Window *win) const {
	if (loader != NULL) {
		loadingText->setText(win->getWindowRenderer(), loader->getCurrentImageFileName());
	}
    loadingText->draw(win->getWindowRenderer());
}

void LaunchScreen::onInput(Game *, const SDL_Event &) {}

void LaunchScreen::onKeyInput(Game *, const uint8_t *) {}
