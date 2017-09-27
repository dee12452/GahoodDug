#ifndef SPRITE_HPP
#define SPRITE_HPP

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class Sprite {
public:
    /* Create a sprite that has NULL src and dst rects 
     * Meaning when drawn it will take the whole screen */
    Sprite(SDL_Texture *sprSheet);

    /* Create a sprite with dimensions as ints 
     * Will fill the rects with these ints */
    Sprite(SDL_Texture *sprSheet, 
            int srcX, 
            int srcY, 
            int srcW, 
            int srcH, 
            int dstX, 
            int dstY, 
            int dstW, 
            int dstH);

    /* Alternatively create a with the dimension rects */
    Sprite(SDL_Texture *sprSheet, 
            const SDL_Rect &srcRect,
            const SDL_Rect &dstRect);

    /* Destructor -> will not delete the SDL_Texture 
     * Just delete the dimension rects if they are not NULL */
    ~Sprite();

    /* Draw the Sprite to the screen */
    void draw(SDL_Renderer *renderer) const;

    /*
     * Getters and Setters for dimension rects
     * getters: if dimension rects are null, default return val is -1
     * setters: if dimension rects are null, will make a new rect but set all to 0 
     */
    int getDstX() const;
    int getDstY() const;
    int getDstW() const;
    int getDstH() const;

    void setDstX(int dstX);
    void setDstY(int dstY);
    void setDstW(int dstW);
    void setDstH(int dstH);

    int getSrcX() const;
    int getSrcY() const;
    int getSrcW() const;
    int getSrcH() const;
    
    void setSrcX(int srcX);
    void setSrcY(int srcY);
    void setSrcW(int srcW);
    void setSrcH(int srcH);

    SDL_Rect * getSrcRect() const;
    SDL_Rect * getDstRect() const;

    void setSrcRect(const SDL_Rect &srcRect);
    void setDstRect(const SDL_Rect &dstRect);

    void setSpriteSheet(SDL_Texture *newSpriteSheet);
    /*
     * End Getters and Setters
     */

private:
    void initRect(SDL_Rect *&targetRect) const;

    SDL_Texture *spriteSheet;
    SDL_Rect *sourceRect;
    SDL_Rect *destinationRect;
};

#endif
