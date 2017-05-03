#include "../headers/window.h"
#include "../headers/input.h"

static Window *window;
static pthread_t windowThread;

static void * runWindow(void *);
static Window * createWindow();
static void destroyWindow();

void
gahood_windowStart() {
    if(pthread_create(&windowThread, NULL, runWindow, NULL) != 0) {
        gahood_utilFatalError("Failed to create the window thread!");
    }
}

void
gahood_windowClose() {
    if(window) {
        window->running = false;
        pthread_join(windowThread, NULL);
    }
}

bool
gahood_isWindowRunning() {
    if(!window)
        return false;
    return window->running;
}

static void *
runWindow(void *ptr) {
    window = createWindow();
    while(window->running) {
        gahood_inputHandleEvents();
        SDL_Delay(DELAY_RENDER_LOOP);
    }
    destroyWindow(window);
    return ptr;
}

static Window *
createWindow() {
    /* Create the window */
    window = (Window *) malloc(sizeof(Window));
    window->win = SDL_CreateWindow(
            WINDOW_NAME,
            WINDOW_X,
            WINDOW_Y,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            WINDOW_FLAGS);
    if(!window->win) {
        gahood_utilFatalSDLError("Failed to create the window");
    }

    /* Create the window renderer*/
    window->winRenderer = SDL_CreateRenderer(window->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(!window->winRenderer) {
        gahood_utilFatalSDLError("Failed to create a window renderer");
    }

    /* Create the window texture */
    window->winTexture = SDL_CreateTexture(window->winRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    if(!window->winTexture) {
        gahood_utilFatalSDLError("Failed to create the window texture");
    }

    /* Draw a black screen */
    if(SDL_SetRenderDrawColor(window->winRenderer, 0, 0, 0, FULL_ALPHA) < 0) {
        gahood_utilFatalSDLError("Failed to change the renderer color");
    }
    if(SDL_RenderClear(window->winRenderer) < 0) {
        gahood_utilFatalSDLError("Failed to clear the renderer");
    }
    SDL_RenderPresent(window->winRenderer);
    window->w = WINDOW_WIDTH;
    window->h = WINDOW_HEIGHT;
    window->running = true;
    return window;
}

static void
destroyWindow() {
    if(window != NULL) {
        if(window->winTexture != NULL) {
            SDL_DestroyTexture(window->winTexture);
            window->winTexture = NULL;
        }
        if(window->winRenderer != NULL) {
            SDL_DestroyRenderer(window->winRenderer);
            window->winRenderer = NULL;
        }
        if(window->win != NULL) {
            SDL_DestroyWindow(window->win);
            window->win = NULL;
        }
        free(window);
        window = NULL;
    }
}
