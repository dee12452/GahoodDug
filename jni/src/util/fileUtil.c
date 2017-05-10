#include "../headers/fileUtil.h"

#include <SDL.h>
#include "../headers/sprite.h"
#include "../headers/util.h"

Sprite ** 
gahood_fileUtilLoadSprites(const char *file) {
    Sprite **sprites = NULL;
    SDL_RWops *in = SDL_RWFromFile(file, "rt");
    if(!in) {
        char buffer[500];
        strcpy(buffer, "Failed to load file ");
        strcat(buffer, file);
        gahood_utilFatalSDLError(buffer);
    }
    
    return sprites;
}
