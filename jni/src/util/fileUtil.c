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
    char *line = NULL;
    const uint8_t maxLineSize = 250;
    char buffer[1];
    SDL_RWread(in, buffer, 1, 1);
    while(buffer[0] != '\n' && buffer[0] != '\0') {
        if(line == NULL) {
            line = (char *) malloc(sizeof(char) * maxLineSize);
            strcpy(line, buffer);
            continue;
        }
        strcat(line, buffer);
        memset(buffer, 0, 1);
        SDL_RWread(in, buffer, 1, 1);
    }
    return line;
}
