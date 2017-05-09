#include "../headers/window.h"

#include "SDL.h"
#include "../headers/timer.h"
#include "../headers/util.h"
#include "../headers/input.h"
#include "../headers/screen.h"

typedef struct Window {
    SDL_Window *win;
    SDL_Renderer *winRenderer;
    SDL_Texture *winTexture;
    int width;
    int height;
    Timer *fpsTimer;
    bool running;
} Window;

static Window * createWindow();
static void destroyWindow(Window *);
static void runWindow(Window *);
static void render(Window *);

void 
gahood_windowStart() {
    SDL_Log("*************** CREATE THE WINDOW **************\n");
    Window *window = createWindow();
    
    SDL_Log("*************** RUN WINDOW **************\n");
    runWindow(window);
    SDL_Log("*************** WINDOW FINISHED RUNNING **************\n");
    destroyWindow(window);
    window = NULL;
}

void
runWindow(Window *w) {
    while(w->running) {
        w->running = gahood_inputPollEvents();
        if(gahood_timerCheck(w->fpsTimer)) {
            render(w);
        }
        SDL_Delay(DELAY_RENDER_LOOP);
    }
}

void
render(Window *w) {
    /* Clear the current window */
    if(SDL_RenderClear(w->winRenderer) < 0) {
        gahood_utilFatalSDLError("Failed to clear the renderer");
    }
    
    /* Set the target to the window texture */
    if(SDL_SetRenderTarget(w->winRenderer, w->winTexture) < 0) {
        gahood_utilFatalSDLError("Failed to set render target to window texture");
    }
    
    /* Clear the window texture */
    if(SDL_RenderClear(w->winRenderer) < 0) {
        gahood_utilFatalSDLError("Failed to clear the renderer");
    }
    
    /* Draw things to the texture */
    gahood_screenDraw(w->winRenderer);
    
    /* Set the target back to the window, copy the texture to the window, and present it */
    if(SDL_SetRenderTarget(w->winRenderer, NULL) < 0) {
        gahood_utilFatalSDLError("Failed to set render target to window texture");
    }
    if(SDL_RenderCopy(w->winRenderer, w->winTexture, NULL, NULL) < 0) {
        gahood_utilFatalSDLError("Failed to render the window texture to the window");
    }
    SDL_RenderPresent(w->winRenderer);
}

Window * 
createWindow() {
    Window *window = malloc(sizeof(Window));
    
    window->win = SDL_CreateWindow(WINDOW_NAME,
            WINDOW_X,
            WINDOW_Y,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            WINDOW_FLAGS);
    if(!window->win) {
        gahood_utilFatalSDLError("Failed to create the window");
    }
    window->width = WINDOW_WIDTH;
    window->height = WINDOW_HEIGHT;

    window->winRenderer = SDL_CreateRenderer(window->win, 
            -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(!window->winRenderer) {
        gahood_utilFatalSDLError("Failed to create the window renderer");
    }
    if(SDL_SetRenderDrawColor(window->winRenderer, 0, 0, 0, FULL_ALPHA) < 0) {
        gahood_utilFatalSDLError("Failed to change render color");
    }

    window->winTexture = SDL_CreateTexture(window->winRenderer, 
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_TARGET, 
            window->width,
            window->height);
    if(!window->winTexture) {
        gahood_utilFatalSDLError("Failed to create window texture");
    }
    
    window->running = true;
    window->fpsTimer = gahood_timerCreate(1000 / WINDOW_FPS);

    return window;
}

void
destroyWindow(Window *w) {
    if(w) {
        if(w->fpsTimer) {
            gahood_timerDestroy(w->fpsTimer);
            w->fpsTimer = NULL;
        }
        if(w->winTexture) {
            SDL_DestroyTexture(w->winTexture);
            w->winTexture = NULL;
        }
        if(w->winRenderer) {
            SDL_DestroyRenderer(w->winRenderer);
            w->winRenderer = NULL;
        }
        if(w->win) {
            SDL_DestroyWindow(w->win);
            w->win = NULL;
        }
        free(w);
    }
}
