#include "../headers/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

const uint32_t WINDOW_FLAGS = SDL_WINDOW_OPENGL;
const uint32_t SDL_INIT_FLAGS = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
const uint32_t IMG_INIT_FLAGS = IMG_INIT_PNG;

const uint8_t RES_FILES_SIZE = 4;
const char * RES_FILES[] = {
    "res/gahooddug_dirt.png",
    "res/gahooddug_sprites.png",
    "res/gahooddug_control_stick_bg.png",
    "res/gahooddug_control_stick.png"
};

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

int
gahood_utilStringToInt(char *str) {
    if(!str) {
        return -1;
    }
    unsigned int i = 0;
    const unsigned int ASCII_MIN = 48;
    const unsigned int ASCII_MAX = 57;
    while(str[i] != '\0') {
        if((unsigned int) str[i] < ASCII_MIN || (unsigned int) str[i] > ASCII_MAX) {
            return -1;
        }
        i++;
    }
    int ret = 0;
    i = 0;
    while(str[i] != '\0') {
        ret *= 10;
        ret += (int) (str[i] - '0');
        i++;
    }
    return ret;
}

bool
gahood_utilStringEquals(const char *str1, const char *str2) {
    if(strcmp(str1, str2) == 0)
        return true;
    return false;
}
