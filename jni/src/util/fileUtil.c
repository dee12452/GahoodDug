#include "../headers/fileUtil.h"

#include <SDL.h>
#include <string.h>
#include "../headers/util.h"

SDL_RWops * 
gahood_fileUtilOpenFile(const char *file) {
    SDL_RWops *in = SDL_RWFromFile(file, "rb");
    if(!in) {
        char message[500];
        strcpy(message, "Failed to load file: ");
        strcat(message, file);
        gahood_utilFatalSDLError(message);
    }
    return in;
}

char *
gahood_fileUtilReadLine(SDL_RWops *in) {
    char *line;
    const uint8_t maxLineSize = 250;
    return line;
}
