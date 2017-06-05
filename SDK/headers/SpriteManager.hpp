#ifndef SPRITE_MANAGER_HPP
#define SPRITE_MANAGER_HPP

#include <map>

struct SDL_Renderer;
struct SDL_Texture;

class SpriteManager {    
public:
    static SpriteManager * getInstance();
    static void destroyInstance();
    
    void loadTexture(SDL_Renderer *, const std::string &);
    void unloadTexture(const std::string &);
    SDL_Texture * getTexture(const std::string &) const;
private:
    SpriteManager();
    ~SpriteManager();
    static SpriteManager *instance;

    std::map<std::string, SDL_Texture *> textures;
};

#endif
