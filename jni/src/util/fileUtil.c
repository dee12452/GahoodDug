#include "../headers/fileUtil.h"

#include <SDL.h>
#include <string.h>
#include <stdbool.h>
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
    char buffer[2];
    memset(buffer, 0, 1);
    SDL_RWread(in, buffer, sizeof(buffer), 1);
    buffer[1] = '\0';
    int read = 1;
    while(read != 0 && buffer[0] != '\n' && buffer[0] != '\0' && buffer[0] != EOF) {
        if(line == NULL) {
            line = (char *) malloc(sizeof(char) * maxLineSize);
            strcpy(line, "");
        }
        strcat(line, buffer);
        memset(buffer, 0, 1);
        read = SDL_RWread(in, buffer, sizeof(buffer) / 2, 1);
        buffer[1] = '\0';
    }
    return line;
}

char *
gahood_fileUtilGetWordFromLine(char *line, int index) {
    const uint8_t maxWordSize = 150;
    int currIndex = 0;
    bool foundIndex = false;
    int i = 0;
    while(line[i] != '\n' && line[i] != '\0') {
        if(currIndex == index) {
            foundIndex = true;
            break;
        }
        if(line[i] == ' ') {
            currIndex++;
        }
        i++;
    }
    if(!foundIndex)
        return NULL;
    char *word = (char *) malloc(sizeof(char) * maxWordSize);
    strcpy(word, "");
    while(line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && line[i] != EOF) {
        char buffer[2];
        buffer[0] = line[i];
        buffer[1] = '\0';
        strcat(word, buffer);
        i++;
    }
    return word;
}
