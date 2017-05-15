#include "../headers/fileUtil.h"

#include <SDL.h>
#include <stdio.h>
#include "../headers/util.h"

typedef enum LineParse {
    LINE_NONE,
    LINE_SPRITE,
    LINE_CONTROL_STICK
} LineParse;

typedef struct LineObject {
    LineParse type;
    int x;
    int y;
    const char *spriteFile;
} LineObject;

static LineObject parseLine(const char *line);

void gahood_fileUtilLoadScreen(const char *file) {
    const int maxLineSize = 250;
    char buffer[1], line[maxLineSize + 1];
    int currentChar = 0;
    SDL_RWops *in = SDL_RWFromFile(file, "rb");
    if(!in) {
        gahood_utilFatalSDLError("Failed to load file");
    }
    strcpy(line, "");
    while(SDL_RWread(in, buffer, 1, 1) > 0) {
        currentChar++;
        if(currentChar > maxLineSize) {
            char *message = "Failed to parse file ";
            strcat(message, file);
            strcat(message, ". Line was too long.");
            gahood_utilFatalError(message);
        }
        strcat(line, buffer);
        if(line[currentChar] == '\n') {
            /* Parse the line! */
            memset(line, 0, maxLineSize + 1);
        }
        memset(buffer, 0, 1);
    }
    if(currentChar < maxLineSize) {
        strcat(line, "\n");
    }
    /* Parse the last line! */
    memset(line, 0, maxLineSize + 1);
    SDL_RWclose(in);
    in = NULL;
}

LineObject parseLine(const char *line) {
    const int maxTypeSize = 50;
    char type[maxTypeSize + 1];
    int i = 0;
    strcpy(type, "");
    while(line[i] != '\n' && line[i] != '\0' && line[i] != ' ') {   
        char temp[2];
        temp[1] = '\n';
        temp[0] = line[i];
        strcat(type, temp);
    }
    LineObject obj;
    obj.type = LINE_NONE;
    if(strcmp(type, "Sprite")) {

    }
    else if(strcmp(type, "ControlStick")) {

    }
    else {
        char *message = "Error parsing the text file in the line: ";
        strcat(message, line);
        gahood_utilFatalError(message);
    }
    return obj;
}
