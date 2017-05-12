#include "../headers/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

const uint32_t WINDOW_FLAGS = SDL_WINDOW_OPENGL;
const uint32_t SDL_INIT_FLAGS = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
const uint32_t IMG_INIT_FLAGS = IMG_INIT_PNG;

void 
gahood_utilFatalError(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

void 
gahood_utilFatalSDLError(const char *message) {
    printf("%s\n", SDL_GetError());
    gahood_utilFatalError(message);
}