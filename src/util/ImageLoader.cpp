#include "../headers/ImageLoader.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/Constants.hpp"
#include "../headers/FileUtil.hpp"
#include "../headers/Util.hpp"

ImageLoader * ImageLoader::instance = NULL;

ImageLoader::ImageLoader() {
    currentImage = 0;
}

ImageLoader::~ImageLoader() {
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

ImageLoader * ImageLoader::getInstance() {
    if(instance == NULL) {
        instance = new ImageLoader();
    }
    return instance;
}

void ImageLoader::deleteInstance() {
    if(instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

void ImageLoader::setImageFolder(const char *path) {
    imageIds = FileUtil::getFiles(path);
    for(unsigned int i = 0; i < imageIds.size(); i++) {
        images.insert(std::pair<std::string, SDL_Texture *> (imageIds[i], NULL));
    }
}

bool ImageLoader::hasLoadedAllImages() const {
    if(currentImage == imageIds.size())
        return true;
    return false;
}

void ImageLoader::loadImage(SDL_Renderer *renderer, const std::string &id) {
    std::map<std::string, SDL_Texture *>::iterator it = images.find(id);
    if(it == images.end()) {
        Util::fatalError(("Failed to load image: " + id).c_str());
    }
    else {
        if(it->second == NULL) {
            it->second = IMG_LoadTexture(renderer, (Constants::GAME_IMAGE_FOLDER + it->first).c_str());
			if (it->second == NULL) {
				Util::fatalSDLError("Failed to load image!");
			}
        }
        else
            Util::log("Warning: Tried to load an image that was already loaded.");
    }
}

void ImageLoader::loadNextImage(SDL_Renderer *renderer) {
    if(currentImage == imageIds.size())
        return;
    std::map<std::string, SDL_Texture *>::iterator it = images.find(imageIds[currentImage]);
    if(it != images.end()) {
		if (it->second == NULL) {
			it->second = IMG_LoadTexture(renderer, (Constants::GAME_IMAGE_FOLDER + it->first).c_str());
			if (it->second == NULL) {
				Util::fatalSDLError("Failed to load image!");
			}
		}
        else
            Util::log("Warning: Tried to load an image that was already loaded.");
    }
    else {
        Util::fatalError(("Failed to load image: " + imageIds[currentImage]).c_str());
    }
    currentImage++;
}

SDL_Texture * ImageLoader::getImage(const std::string &id) const {
    std::map<std::string, SDL_Texture *>::const_iterator it = images.find(id);
    if(it != images.end()) {
        return it->second;
    }
    else {
        return NULL;
    }
}
