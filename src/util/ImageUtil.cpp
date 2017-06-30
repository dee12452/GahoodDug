#include "../headers/ImageUtil.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/FileUtil.hpp"
#include "../headers/Util.hpp"

ImageUtil * ImageUtil::instance = NULL;

ImageUtil::ImageUtil() {
    currentImage = 0;
}

ImageUtil::~ImageUtil() {
    std::map<std::string, SDL_Texture *>::iterator it;
    for(unsigned int i = 0; i < imageIds.size(); i++) {
        it = images.find(imageIds[i]);
        if(it != images.end()) {
            SDL_DestroyTexture(it->second);
            it->second = NULL;
        }
    }
    images.clear();
    imageIds.clear();
}

ImageUtil * ImageUtil::getInstance() {
    if(instance == NULL) {
        instance = new ImageUtil();
    }
    return instance;
}

void ImageUtil::deleteInstance() {
    if(instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

void ImageUtil::setImageFolder(const char *path) {
    imageIds = FileUtil::getImageFiles(path);
    for(unsigned int i = 0; i < imageIds.size(); i++) {
        images.insert(std::pair<std::string, SDL_Texture *> (imageIds[i], NULL));
    }
    imagePath = path;
}

bool ImageUtil::hasLoadedAllImages() const {
    if(currentImage == imageIds.size())
        return true;
    return false;
}

void ImageUtil::loadImage(SDL_Renderer *renderer, const std::string &id) {
    std::map<std::string, SDL_Texture *>::iterator it = images.find(id);
    if(it == images.end()) {
        Util::fatalError(("Failed to load image: " + id).c_str());
    }
    else {
        if(it->second == NULL) {
            it->second = IMG_LoadTexture(renderer, (imagePath + it->first).c_str());
        }
        else
            Util::log("Warning: Tried to load an image that was already loaded.");
    }
}

void ImageUtil::loadNextImage(SDL_Renderer *renderer) {
    if(currentImage == imageIds.size())
        return;
    std::map<std::string, SDL_Texture *>::iterator it = images.find(imageIds[currentImage]);
    if(it != images.end()) {
        if(it->second == NULL)
            it->second = IMG_LoadTexture(renderer, (imagePath + it->first).c_str());
        else
            Util::log("Warning: Tried to load an image that was already loaded.");
    }
    else {
        Util::fatalError(("Failed to load image: " + imageIds[currentImage]).c_str());
    }
    currentImage++;
}

SDL_Texture * ImageUtil::getImage(const std::string &id) const {
    std::map<std::string, SDL_Texture *>::const_iterator it = images.find(id);
    if(it != images.end()) {
        return it->second;
    }
    else {
        return NULL;
    }
}
