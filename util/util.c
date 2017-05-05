#include "../headers/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

const uint32_t WINDOW_FLAGS = SDL_WINDOW_OPENGL;

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
