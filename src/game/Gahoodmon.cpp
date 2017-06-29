#include "../headers/Gahoodmon.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/Window.hpp"
#include "../headers/Constants.hpp"
#include "../headers/Timer.hpp"
#include "../headers/Util.hpp"

Gahoodmon::Gahoodmon() {
    window = NULL;
    fpsTimer = NULL;
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

void Gahoodmon::init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
   
    int msPerFrame = 1000 / Constants::TARGET_FPS;
    fpsTimer = new Timer(msPerFrame);
    window = new Window();
    running = true;
}

void Gahoodmon::update() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            running = false;
        }
    }
    if(fpsTimer->check()) {
        //Render to the window
        window->render();
    }
}

void Gahoodmon::deinit() {
    if(fpsTimer != NULL) {
        delete fpsTimer;
        fpsTimer = NULL;
    }
    if(window != NULL) {
        delete window;
        window = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}
