#include "Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Window.hpp"
#include "SpriteSheet.hpp"
#include "../util/Constants.hpp"
#include "../util/Timer.hpp"
#include "../util/Util.hpp"
#include "../util/FileUtil.hpp"
#include "../screen/LaunchScreen.hpp"
#include "../map/MapLoader.hpp"

static int runInBackgroundThread(void *gahoodmon);

Game::Game() {
    window = NULL;
    fpsTimer = NULL;
    backgroundThread = NULL;
    currentScreen = NULL;
}

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
        currentScreen->updateInBackground();
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
   
    int msPerFrame = 1000 / Constants::TARGET_FPS;
    fpsTimer = new Timer(msPerFrame);
    window = new Window(this);
    running = true;

    backgroundThread = SDL_CreateThread(runInBackgroundThread, Constants::GAME_THREAD_NAME, this);
    if(backgroundThread == NULL) {
        Util::fatalSDLError("Could not create the background thread");
    }
    
    //Start the first screen
    requestNewScreen(new LaunchScreen());
    
    //Load the tilesets and maps
    MapLoader::getInstance()->loadAll(Constants::GAME_RES_FOLDER);
    Util::log("Initialized game successfully");
}

void Game::update() {
    
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
        currentScreen->update();
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

bool Game::isRunning() const {
    return running;
}

void Game::loadSpriteSheet(const char *path) {
    spriteSheets.insert(std::pair<std::string, SpriteSheet *>(FileUtil::getFileName(path), new SpriteSheet(window->getWindowRenderer(), path)));
}

void Game::deinit() {
    int threadRetVal;
    SDL_WaitThread(backgroundThread, &threadRetVal);
    backgroundThread = NULL;
    if(threadRetVal != 0) {
        char val = '0' + threadRetVal;
        std::string message = "Warning: Background thread returned with an invalid value of ";
        message += val;
        Util::log(message);
    }
	if (currentScreen != NULL) {
		currentScreen->stop();
		delete currentScreen;
		currentScreen = NULL;
	}
    if(fpsTimer != NULL) {
        delete fpsTimer;
        fpsTimer = NULL;
    }
    if(window != NULL) {
        delete window;
        window = NULL;
    }
    MapLoader::getInstance()->deleteInstance();
    for(std::map<std::string, SpriteSheet *>::const_iterator iterator = spriteSheets.begin(); iterator != spriteSheets.end(); ++iterator) {
        if(iterator->second != NULL) {
            delete iterator->second;
        }
    }
    spriteSheets.clear();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::requestNewScreen(BaseScreen *screen) {
    if(currentScreen == NULL) {
        currentScreen = screen;
    }
    else {
        currentScreen->stop();
        delete currentScreen;
        currentScreen = screen;
    }
    currentScreen->start();
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
