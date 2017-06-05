#include "../headers/SpriteManager.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/GahoodUtil.hpp"

SpriteManager * SpriteManager::instance = NULL;

SpriteManager::SpriteManager() {}

SpriteManager::~SpriteManager() {
    std::map<std::string, SDL_Texture *>::iterator iterator;
    for(iterator = textures.begin(); iterator != textures.end(); ++iterator) {
        SDL_DestroyTexture(iterator->second);
        iterator->second = NULL;
        textures.erase(iterator);
    }
    textures.clear();
}

SpriteManager * SpriteManager::getInstance() {
    if(instance == NULL) {
        instance = new SpriteManager();
    }
    return instance;
}

void SpriteManager::destroyInstance() {
    if(instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

void SpriteManager::loadTexture(SDL_Renderer *r, const std::string &file) {
    SDL_Texture *texture = IMG_LoadTexture(r, file.c_str());
    if(texture == NULL) {
        GahoodUtil::fatalSDLError("Failed to load texture: " + file);
    }
    textures.insert(std::pair<std::string, SDL_Texture *> (file, texture));
}

void SpriteManager::unloadTexture(const std::string &file) {
    std::map<std::string, SDL_Texture *>::const_iterator iterator = textures.find(file);
    if(iterator != textures.end()) {
        SDL_DestroyTexture(iterator->second);
        textures.erase(iterator);
    }
}

SDL_Texture * SpriteManager::getTexture(const std::string &file) const {
    std::map<std::string, SDL_Texture *>::const_iterator iterator = textures.find(file);
    if(iterator != textures.end()) {
        return iterator->second;
    }
    return NULL;
}
