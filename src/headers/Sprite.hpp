#ifndef SPRITE_HPP
#define SPRITE_HPP

class Timer;
class Window;
struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Texture;

#include <string>
#include <stdint.h>

class Sprite {
public:
    Sprite(const std::string &id);
    Sprite(const std::string &id, int, int, int, int, int, int, int, int);
    Sprite(const std::string &id, const SDL_Rect &, const SDL_Rect &);
    virtual ~Sprite();

    virtual void draw(Window *);
    void update();
    virtual void updateInBackground() {}

    SDL_Rect * getSourceRect() const;
    SDL_Rect * getDestinationRect() const;
    void setSourceRect(int, int, int, int);
    void setDestinationRect(int, int, int, int);
    void setSourceRect(const SDL_Rect &);
    void setDestinationRect(const SDL_Rect &);

    void setUpdateTimer(unsigned int);
    void setImageId(const std::string &);
    void setAlpha(uint8_t);

    std::string getImageId() const;

protected:
    virtual void onUpdate() = 0;

private:
    Timer *updateTimer;
    std::string id;
    SDL_Rect *src;
    SDL_Rect *dst;
    uint8_t alpha;
};

#endif
