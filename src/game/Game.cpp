#include "Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "BaseGameObject.hpp"
#include "../sprite/SpriteSheet.hpp"
#include "../sprite/Font.hpp"
#include "../util/Constants.hpp"
#include "../util/Timer.hpp"
#include "../util/Util.hpp"
#include "../util/FileUtil.hpp"
#include "../screen/LaunchScreen.hpp"
#include "../map/MapLoader.hpp"

static int runInBackgroundThread(void *gahoodmon);

Game::Game() 
    : running(false), 
      window(NULL), 
      fpsTimer(NULL), 
      backgroundThread(NULL), 
      currentScreen(NULL), 
      nextScreen(NULL) {}

Game::~Game() {}

void Game::run() {
    init();
    while(running) {
        update();
        Util::sleep(Constants::RENDER_LOOP_DELAY);
    }
    deinit();
}

void Game::runInBackground() {
	for (unsigned int i = 0; i < updatables.size(); i++) {
		updatables[i]->tickInBackground();
	}
}

void Game::init() {
    
    //Init SDL2
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        Util::fatalSDLError("Failed to initialize SDL2");
    }
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        Util::fatalSDLError("Failed to initialize SDL2 Image");
    }
    if(TTF_Init() != 0) {
        Util::fatalSDLError("Failed to initialize SDL2 TTF");
    }

	//Create the timers
	const int MILLISECONDS_PER_SECOND = 1000;
	int msPerFrame = MILLISECONDS_PER_SECOND / Constants::TARGET_FPS;
	fpsTimer = new Timer(msPerFrame);
	int msPerTick = MILLISECONDS_PER_SECOND / Constants::TARGET_TICKS_PER_SECOND;
	tickTimer = new Timer(msPerTick);
  
    //Create the window
    window = new Window();
    running = true;

    //Load the fonts
    std::vector<std::string> fontFiles = FileUtil::getFilesRecursively(Constants::GAME_RES_FOLDER, Constants::FONT_FILE_EXTENSION);
    for(size_t i = 0; i < fontFiles.size(); i++) {
        std::string fName = FileUtil::getFileName(fontFiles[i].c_str());
        fonts.insert(std::pair<std::string, Font *> (fName, new Font(fontFiles[i].c_str())));
    }
    Util::log(SDL_LOG_PRIORITY_INFO, "Loaded all fonts!");
    
    //Create the background thread
    backgroundThread = SDL_CreateThread(runInBackgroundThread, Constants::GAME_THREAD_NAME, this);
    if(backgroundThread == NULL) {
        Util::fatalSDLError("Could not create the background thread");
    }
    
    //Start the first screen
    requestNewScreen(new LaunchScreen(this));
}

void Game::update() {
   
    /* Check to see if there's a screen change
     * Will not change unless there was a request to */
    changeScreens();

	/* Update every registered game object */
	if (tickTimer->check()) {
		for (unsigned int i = 0; i < updatables.size(); i++) {
			updatables[i]->tick(this);
		}
	}

    /* If current screen exists 
     * Have it handle input 
     * check to see if it needs to be drawn 
     * and update the screen as well */
    if(currentScreen != NULL) {
		currentScreen->handleInput(this);
        if(fpsTimer->check()) {
            //Render to the window
            window->render(currentScreen);
        }
    }

    /* If current screen does not exist
     * handle the input of quitting
     */
    else {
        window->render(NULL);
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                quit();
        }
    }
}

void Game::registerGameObject(BaseGameObject *obj) {
	if (obj != NULL) updatables.push_back(obj);
}

void Game::unregisterGameObject(BaseGameObject *obj) {
	if (obj != NULL) {
		for (unsigned int i = 0; i < updatables.size(); i++) {
			//Remove the object from the list of updatables
			if (updatables[i] == obj) {
				updatables.erase(updatables.begin() + i);
				break;
			}
		}
	}
}

void Game::changeScreens() {
    if(nextScreen != NULL) {
        if(currentScreen == NULL) {
            currentScreen = nextScreen;
        }
        else {
            delete currentScreen;
            currentScreen = nextScreen;
        }
        nextScreen = NULL;
    }
}

void Game::requestNewScreen(BaseScreen *screen) {
    nextScreen = screen;
}

bool Game::isRunning() const {
    return running;
}

Window * Game::getWindow() const {
    return window;
}

void Game::loadSpriteSheet(const char *path) {
    spriteSheets.insert(std::pair<std::string, SpriteSheet *>(FileUtil::getFileName(path), new SpriteSheet(window->getWindowRenderer(), path)));
}

SpriteSheet * Game::getSpriteSheet(const char *spriteSheetName) const {
    SpriteSheet *sheet = NULL;
    std::string fileName(spriteSheetName);
    std::map<std::string, SpriteSheet *>::const_iterator iterator = spriteSheets.find(fileName);
    if(iterator != spriteSheets.end()) {
        sheet = iterator->second;
    }
    return sheet;
}

Font * Game::getFont(const char *fontName) const {
    Font *font = NULL;
    std::string fileName(fontName);
    std::map<std::string, Font *>::const_iterator iterator = fonts.find(fileName);
    if(iterator != fonts.end()) {
        font = iterator->second;
    }
    return font;
}

void Game::deinit() {

	//All unregistered game objects will be destroyed here
	for (unsigned int i = 0; i < updatables.size(); i++) {
		if (updatables[i] == NULL) continue;
		delete updatables[i];
		updatables[i] = NULL;
	}
	updatables.clear();
	
    //Stop the screen
    if (currentScreen != NULL) {
		delete currentScreen;
		currentScreen = NULL;
	}
    if (nextScreen != NULL) {
		delete nextScreen;
		currentScreen = NULL;
	}
    Util::log(SDL_LOG_PRIORITY_INFO, "Successfully stopped the current screen!");
    
    //Stop background thread
    int threadRetVal;
    SDL_WaitThread(backgroundThread, &threadRetVal);
    backgroundThread = NULL;
    if(threadRetVal != 0) {
        char val = '0' + threadRetVal;
        std::string message = "Warning: Background thread returned with an invalid value of ";
        message += val;
        Util::log(SDL_LOG_PRIORITY_WARN, message);
    }
    Util::log(SDL_LOG_PRIORITY_INFO, "Successfully stopped background thread!");

    //Free the timers
    if(fpsTimer != NULL) {
        delete fpsTimer;
        fpsTimer = NULL;
    }
	if (tickTimer != NULL) {
		delete tickTimer;
		tickTimer = NULL;
	}

    //Destroy the window
    if(window != NULL) {
        delete window;
        window = NULL;
    }
    Util::log(SDL_LOG_PRIORITY_INFO, "Successfully closed the window!");
    
    //Delete the map loader and it's data
    MapLoader::getInstance()->deleteInstance();
    Util::log(SDL_LOG_PRIORITY_INFO, "Successfully deleted maps and tilesets");
    
    //Delete all of the fonts
    for(std::map<std::string, Font *>::const_iterator iterator = fonts.begin(); iterator != fonts.end(); ++iterator) {
        if(iterator->second != NULL) {
            delete iterator->second;
        }
    }

    //Delete all of the spritesheets
    for(std::map<std::string, SpriteSheet *>::const_iterator iterator = spriteSheets.begin(); iterator != spriteSheets.end(); ++iterator) {
        if(iterator->second != NULL) {
            delete iterator->second;
        }
    }
    spriteSheets.clear();
    Util::log(SDL_LOG_PRIORITY_INFO, "Successfully deleted sprites and fonts!");

	//Deinit SDL
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::quit() { running = false; }

int runInBackgroundThread(void *gahoodmon) {
    Game *game = static_cast<Game *> (gahoodmon);
    while(game->isRunning()) {
        game->runInBackground();
        Util::sleep(Constants::GAME_BACKGROUND_LOOP_DELAY);
    }
    return 0;
}
