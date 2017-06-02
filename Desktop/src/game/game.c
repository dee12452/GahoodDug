#include "../headers/game.h"

#include <pthread.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../headers/util.h"
#include "../headers/window.h"
#include "../headers/screen.h"

static GameState gameState;
static pthread_t gameThread;

static void run(); 
static void init();
static void close();
static void * update(void *);

int 
main(int argc, char *argv[]) {
    for(int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    run();
    exit(EXIT_SUCCESS);
}

void
gahood_gameSetGameState(GameState newGameState) {
    gameState = newGameState;
}

GameState
gahood_gameGetGameState() {
    return gameState;
}

void
run() {
    init();
    close();
}

void
init() {
    /* Init SDL and IMG with flags in util */
    if(SDL_Init(SDL_INIT_FLAGS) < 0) {
        gahood_utilFatalSDLError("Failed to init SDL");
    }
    if(IMG_Init(IMG_INIT_FLAGS) < 0) {
        gahood_utilFatalSDLError("Failed to init SDL IMG");
    }
    gameState = GAME_STATE_MENU;
    if(pthread_create(&gameThread, NULL, update, NULL) < 0) {
        gahood_utilFatalError("Failed to create the game thread");
    }
    gahood_screenInit();
    gahood_windowStart();
}

void
close() {
    SDL_Log("****************** Joining the game thread *******************\n");
    if(pthread_join(gameThread, NULL) < 0) {
        gahood_utilFatalError("Failed to join the game thread");
    }
    SDL_Log("****************** Joined the game thread *******************\n");
    SDL_Log("****************** Closing the screen *******************\n");
    gahood_screenClose();
    SDL_Log("****************** Closed the screen *******************\n");
    IMG_Quit();
    SDL_Quit();
}

void *
update(void *ptr) {
    if(ptr) { pthread_exit(NULL); }
    while(gameState != GAME_STATE_EXIT) {
        gahood_screenUpdate(gameState); 
        SDL_Delay(DELAY_GAME_LOOP);
    }
    pthread_exit(NULL);
}
