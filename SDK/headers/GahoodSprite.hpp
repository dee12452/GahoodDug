#ifndef GAHOOD_SPRITE_HPP
#define GAHOOD_SPRITE_HPP

#include <string>

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Texture;

class GahoodSprite {
public:
    GahoodSprite();
    GahoodSprite(const std::string &);
    GahoodSprite(int, int, int, int, int, int, int, int);
    GahoodSprite(const std::string &, int, int, int, int, int, int, int, int);
    virtual ~GahoodSprite();

    void setTextureId(const std::string &);
    void setSourceDimensions(int, int, int, int);
    void setSourceDimensions(SDL_Rect *);
    void setDestinationDimensions(int, int, int, int);
    void setDestinationDimensions(SDL_Rect *);
    SDL_Rect * getSourceDimensions() const;
    SDL_Rect * getDestinationDimensions() const;

    virtual void draw(SDL_Renderer *);
private:
    std::string textureId;
    SDL_Rect *srcDimensions;
    SDL_Rect *dstDimensions;
};

#endif
