#include "../headers/Gahoodmon.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/Window.hpp"
#include "../headers/Constants.hpp"
#include "../headers/Timer.hpp"
#include "../headers/Util.hpp"
#include "../headers/ImageLoader.hpp"
#include "../headers/MapLoader.hpp"
#include "../headers/MapScreen.hpp"
#include "../headers/Animator.hpp"

static int runInBackgroundThread(void *);

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
	if (!MapLoader::getInstance()->hasLoadedAllTilesets()) {
		MapLoader::getInstance()->loadNextTileset();
	}
    if(currentScreen != NULL) {
        currentScreen->updateInBackground();
    }
}

void Gahoodmon::init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
   
    int msPerFrame = 1000 / Constants::TARGET_FPS;
    fpsTimer = new Timer(msPerFrame);
    window = new Window();
	ImageLoader::getInstance()->setImageFolder(Constants::GAME_IMAGE_FOLDER);
	MapLoader::getInstance()->setTilesetFolder(Constants::GAME_TILESET_FOLDER);
    running = true;

    backgroundThread = SDL_CreateThread(runInBackgroundThread, Constants::GAME_THREAD_NAME, this);
    if(backgroundThread == NULL) {
        Util::fatalSDLError("Could not create the background thread");
    }
    requestNewScreen(new MapScreen());
}

void Gahoodmon::update() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            running = false;
        }
	}
	if (currentScreen != NULL) {
		currentScreen->handleInput(this);
	}
    Animator::getInstance()->animateAnimations();
    if(currentScreen != NULL) {
        if(fpsTimer->check()) {
            //Render to the window
            window->render(currentScreen);
        }
        currentScreen->update();
    }
}

bool Gahoodmon::isRunning() const {
    return running;
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
	Animator::deleteInstance();
	ImageLoader::deleteInstance();
	MapLoader::deleteInstance();

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

int runInBackgroundThread(void *data) {
    Gahoodmon *game = static_cast<Gahoodmon *> (data);
    while(game->isRunning()) {
        game->runInBackground();
        SDL_Delay(Constants::GAME_LOOP_DELAY);
    }
    return 0;
}
