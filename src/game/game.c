#include "../headers/game.h"

#include <SDL2/SDL_image.h>
#include "../headers/window.h"
#include "../headers/screen.h"
#include "../headers/util.h"

static void init();
static void update();
static void close();

static GameState gameState = GAME_STATE_PLAY;

//Main game loop
void 
gahood_gameRun(int argc, char **argv) {
    if(argc > 1) {
        for(int i = 0; i < argc; i++) {
            printf("%s\n", argv[i]);
            printf("No extra arguments are needed at this time\n");
        }
    }
    init();
    while(gameState != GAME_STATE_EXIT) {
        update();
        SDL_Delay(DELAY_GAME_LOOP);
    }
    close();
}

GameState
gahood_gameGetGameState() {
    return gameState;
}

void
gahood_gameSetGameState(GameState state) {
    gameState = state;
}

static void 
init() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        gahood_utilFatalSDLError("Failed to initialize SDL.");
    }
    if(IMG_Init(IMG_INIT_PNG) < 0) {
        gahood_utilFatalSDLError("Failed to initialize SDL_image.");
    }
    gahood_screenInit(gameState);
    gahood_windowStart();
}

static void
update() {
    gahood_screenUpdate(gameState);
}

static void
close() {
    /* Close the window before the screen to avoid mutex handling */
    gahood_windowClose();
    gahood_screenClose();
    IMG_Quit();
    SDL_Quit();
}
