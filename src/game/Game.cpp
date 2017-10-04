#include "Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Window.hpp"
#include "SpriteSheet.hpp"
#include "Font.hpp"
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
        SDL_Delay(Constants::RENDER_LOOP_DELAY);
    }
    deinit();
}

void Game::runInBackground() {
    if(currentScreen != NULL) {
        currentScreen->updateInBackground(this);
    }
}

void Game::init() {
    Util::log("Started Initialization");
    
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
  
    //Create the window
    int msPerFrame = 1000 / Constants::TARGET_FPS;
    fpsTimer = new Timer(msPerFrame);
    window = new Window();
    running = true;

    //Load the fonts
    std::vector<std::string> fontFiles = FileUtil::getFilesRecursively(Constants::GAME_RES_FOLDER, Constants::FONT_FILE_EXTENSION);
    Util::log("Loading fonts.");
    for(size_t i = 0; i < fontFiles.size(); i++) {
        Util::log("Loading font " + fontFiles[i]);
        std::string fName = FileUtil::getFileName(fontFiles[i].c_str());
        fonts.insert(std::pair<std::string, Font *> (fName, new Font(fontFiles[i].c_str())));
    }
    Util::log("Loaded all fonts!");
    
    //Load the tilesets and maps
    Util::log("Loading maps and tilesets.");
    MapLoader::getInstance()->loadAll(Constants::GAME_RES_FOLDER);
    Util::log("Finished loading maps and tilesets!");
    
    //Create the background thread
    backgroundThread = SDL_CreateThread(runInBackgroundThread, Constants::GAME_THREAD_NAME, this);
    if(backgroundThread == NULL) {
        Util::fatalSDLError("Could not create the background thread");
    }
    
    //Start the first screen
    requestNewScreen(new LaunchScreen(this));
    
    Util::log("Initialized game successfully");
}

void Game::update() {
   
    /* Check to see if there's a screen change
     * Will not change unless there was a request to */
    changeScreens();

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
        currentScreen->update(this);
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
    Util::log("Exiting game.");
	
    //Stop the screen
    Util::log("Stopping the current screen.");
    if (currentScreen != NULL) {
		delete currentScreen;
		currentScreen = NULL;
	}
    if (nextScreen != NULL) {
		delete nextScreen;
		currentScreen = NULL;
	}
    Util::log("Successfully stopped the current screen!");
    
    //Stop background thread
    int threadRetVal;
    Util::log("Stopping background thread.");
    SDL_WaitThread(backgroundThread, &threadRetVal);
    backgroundThread = NULL;
    if(threadRetVal != 0) {
        char val = '0' + threadRetVal;
        std::string message = "Warning: Background thread returned with an invalid value of ";
        message += val;
        Util::log(message);
    }
    Util::log("Successfully stopped background thread!");

    //Free the fps timer
    if(fpsTimer != NULL) {
        delete fpsTimer;
        fpsTimer = NULL;
    }

    //Destroy the window
    Util::log("Closing the window.");
    if(window != NULL) {
        delete window;
        window = NULL;
    }
    Util::log("Successfully closed the window!");
    
    //Delete the map loader and it's data
    Util::log("Deleting maps and tilesets...");
    MapLoader::getInstance()->deleteInstance();
    Util::log("Successfully deleted maps and tilesets");
    
    Util::log("Deleting fonts and sprites...");
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
    Util::log("Successfully deleted sprites and fonts!");

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    Util::log("Closing Game.");
}

void Game::quit() { running = false; }

int runInBackgroundThread(void *gahoodmon) {
    Game *game = static_cast<Game *> (gahoodmon);
    while(game->isRunning()) {
        game->runInBackground();
        SDL_Delay(Constants::GAME_LOOP_DELAY);
    }
    return 0;
}
