#ifndef SPRITE_HPP
#define SPRITE_HPP

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Texture;
class Timer;

#include <string>

class Sprite {
public:
    Sprite(const std::string &id);
    Sprite(const std::string &id, int, int, int, int, int, int, int, int);
    Sprite(const std::string &id, const SDL_Rect &, const SDL_Rect &);
    virtual ~Sprite();

    virtual void draw(SDL_Renderer *);
    void update();

    SDL_Rect * getSourceRect() const;
    SDL_Rect * getDestinationRect() const;
    void setSourceRect(int, int, int, int);
    void setDestinationRect(int, int, int, int);
    void setSourceRect(const SDL_Rect &);
    void setDestinationRect(const SDL_Rect &);

    void setUpdateTimer(unsigned int);
    void setImageId(const std::string &);
    void setX(int);
    void setY(int);
    void setWidth(int);
    void setHeight(int);

    std::string getImageId() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

protected:
    virtual void onUpdate() = 0;

private:
    Timer *timer;
    std::string id;
    SDL_Rect *src;
    SDL_Rect *dst;
};

#endif
