#include "Gahoodmon.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Window.hpp"
#include "SpriteSheet.hpp"
#include "../util/Constants.hpp"
#include "../util/Timer.hpp"
#include "../util/Util.hpp"
#include "../util/FileUtil.hpp"
#include "../screen/LaunchScreen.hpp"
#include "../map/MapLoader.hpp"

static int runInBackgroundThread(void *gahoodmon);

Gahoodmon::Gahoodmon() {
    window = NULL;
    fpsTimer = NULL;
    backgroundThread = NULL;
    currentScreen = NULL;
}

Gahoodmon::~Gahoodmon() {}

void Gahoodmon::run() {
    init();
    while(running) {
        update();
        SDL_Delay(Constants::RENDER_LOOP_DELAY);
    }
    deinit();
}

void Gahoodmon::runInBackground() {
    if(currentScreen != NULL) {
        currentScreen->updateInBackground();
    }
}

void Gahoodmon::init() {
    Util::log("Started Initialization");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
   
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

void Gahoodmon::update() {
    
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

bool Gahoodmon::isRunning() const {
    return running;
}

void Gahoodmon::loadSpriteSheet(const char *path) {
    spriteSheets.insert(std::pair<std::string, SpriteSheet *>(FileUtil::getFileName(path), new SpriteSheet(window->getWindowRenderer(), path)));
}

void Gahoodmon::deinit() {
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

    IMG_Quit();
    SDL_Quit();
}

void Gahoodmon::requestNewScreen(BaseScreen *screen) {
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

void Gahoodmon::quit() { running = false; }

int runInBackgroundThread(void *gahoodmon) {
    Gahoodmon *game = static_cast<Gahoodmon *> (gahoodmon);
    while(game->isRunning()) {
        game->runInBackground();
        SDL_Delay(Constants::GAME_LOOP_DELAY);
    }
    return 0;
}
