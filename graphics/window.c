#include "../headers/window.h"

#include <SDL.h>
#include <pthread.h>
#include "../headers/util.h"
#include "../headers/timer.h"
#include "../headers/input.h"
#include "../headers/screen.h"

typedef struct Window {
    SDL_Window *win;
    SDL_Renderer *winRenderer;
    SDL_Texture *winTexture;
    int w;
    int h;
    bool running;
} Window;

static Window *window = NULL;
static Timer *timer = NULL;
static pthread_t windowThread;

static void * runWindow(void *);
static Window * createWindow();
static void destroyWindow();
static void drawWindow();

void
gahood_windowStart() {
    timer = gahood_timerCreate(1000 / WINDOW_FPS);
    if(pthread_create(&windowThread, NULL, runWindow, NULL) != 0) {
        gahood_utilFatalError("Failed to create the window thread!");
    }
}

void
gahood_windowClose() {
    if(timer) {
        gahood_timerDestroy(timer);
        timer = NULL;
    }
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
        /* Poll events */
        gahood_inputHandleEvents();

        /* Draw the screen */
        drawWindow();

        /* Delay to prevent this loop from using too much CPU */
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

static void
drawWindow() {
    if(gahood_timerCheck(timer)) {
        /* Clear the window */
        if(SDL_RenderClear(window->winRenderer) < 0) {
            gahood_utilFatalSDLError("Failed to clear the renderer");
        }

        /* Set the target to the window texture */
        if(SDL_SetRenderTarget(window->winRenderer, window->winTexture) < 0) {
            gahood_utilFatalSDLError("Failed to set the render target to the window texture");
        }

        /* Clear the window texture */
        if(SDL_RenderClear(window->winRenderer) < 0) {
            gahood_utilFatalSDLError("Failed to clear the renderer");
        }

        /* Draw the screen to the window texture */
        gahood_screenDraw(window->winRenderer);

        /* Set the target back to the window */
        if(SDL_SetRenderTarget(window->winRenderer, NULL) < 0) {
            gahood_utilFatalSDLError("Failed to set the render target back to the window");
        }

        /* Copy the window texture to the window */
        if(SDL_RenderCopy(window->winRenderer, window->winTexture, NULL, NULL) < 0) {
            gahood_utilFatalSDLError("Failed to copy the window texture to the window");
        }

        /* Show the newest window */
        SDL_RenderPresent(window->winRenderer);
    }
}
