#include "../headers/BaseGahoodGame.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <pthread.h>
#include "../headers/GahoodWindow.hpp"
#include "../headers/GahoodUtil.hpp"

#define DEFAULT_GAME_DELAY 5
#define DEFAULT_RENDER_DELAY 5
#define DEFAULT_FPS 30

static void * runGameThread(void *); 

BaseGahoodGame::BaseGahoodGame() {
    window = NULL;
    gameThread = NULL;
    running = false;
    didExit = false;
    gameLoopDelay = DEFAULT_GAME_DELAY;
    renderLoopDelay = DEFAULT_RENDER_DELAY;
}

BaseGahoodGame::~BaseGahoodGame() {}

void BaseGahoodGame::start(const char *gameTitle,
        int width,
        int height,
        uint32_t settings) {
    
    init(gameTitle, width, height, settings);
    run();
    exit();
}

void BaseGahoodGame::init(const char *gameTitle,
        int width,
        int height,
        uint32_t settings) {
    SDL_Init(settings);
    IMG_Init(IMG_INIT_PNG);
    running = true;
    window = new GahoodWindow(gameTitle,
            width,
            height,
            settings,
            DEFAULT_FPS);
    pthread_create(gameThread, NULL, runGameThread, this);
    if(gameThread == NULL) {
        GahoodUtil::fatalError("Failed to create the game thread");
    }
}

void BaseGahoodGame::run() {
    while(isRendering() && !didExit) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                didExit = true;
                break;
            }
            onPollEvent(e);
        }
        if(window->shouldRender()) {
            window->initRender();
            onDraw(window->getRenderer());
            window->draw();
        }
        SDL_Delay(renderLoopDelay);
    }
}

void BaseGahoodGame::exit() {
    running = false;
    if(gameThread != NULL) {
        free(gameThread);
        gameThread = NULL;
    }
    if(window != NULL) {
        delete window;
        window = NULL;
    }
    IMG_Quit();
    SDL_Quit();
}

void BaseGahoodGame::update() {
    onUpdate();
}

void * runGameThread(void *data) {
    BaseGahoodGame *game = static_cast<BaseGahoodGame *> (data);
    while(game->isRunning()) {
        game->update();
        SDL_Delay(game->getGameLoopDelayMs());
    }
    return NULL;
}

void BaseGahoodGame::setGameLoopDelayMs(uint32_t ms) {
    gameLoopDelay = ms;
}

void BaseGahoodGame::setRenderLoopDelayMs(uint32_t ms) {
    renderLoopDelay = ms;
}

uint32_t BaseGahoodGame::getGameLoopDelayMs() const {
    return gameLoopDelay;
}

uint32_t BaseGahoodGame::getRenderLoopDelayMs() const {
    return renderLoopDelay;
}

bool BaseGahoodGame::isRunning() const {
    return running;
}

GahoodWindow * BaseGahoodGame::getGameWindow() const  {
    return window;
}
