#ifndef SPRITE_HPP
#define SPRITE_HPP

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Texture;

class Sprite {
public:
    Sprite();
    Sprite(int, int, int, int, int, int, int, int);
    Sprite(const SDL_Rect &, const SDL_Rect &);
    virtual ~Sprite();

    virtual void draw(SDL_Renderer *);

    SDL_Rect * getSourceRect() const;
    SDL_Rect * getDestinationRect() const;
    void setSourceRect(int, int, int, int);
    void setDestinationRect(int, int, int, int);
    void setSourceRect(const SDL_Rect &);
    void setDestinationRect(const SDL_Rect &);

    void setX(int);
    void setY(int);
    void setWidth(int);
    void setHeight(int);

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

private:
    SDL_Rect *src;
    SDL_Rect *dst;
};

#endif
