#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include <string>
#include <map>
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;

class ImageLoader {
public:
    static ImageLoader * getInstance();
    static void deleteInstance();

    void setImageFolder(const char *);
    void loadNextImage(SDL_Renderer *);
    void loadImage(SDL_Renderer *, const std::string &);
    bool hasLoadedAllImages() const;
    SDL_Texture * getImage(const std::string &) const;

private:
    unsigned int currentImage;
    std::vector<std::string> imageIds;
    std::map<std::string, SDL_Texture *> images;

    static ImageLoader *instance;
    ImageLoader();
    ~ImageLoader();
};

#endif
