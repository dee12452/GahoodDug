#ifndef GAHOOD_WINDOW_HPP
#define GAHOOD_WINDOW_HPP

#include <stdint.h>

//Forward Declatations//
class GahoodTimer;

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
////////////////////////

class GahoodWindow {
public:
    GahoodWindow(const char *, int, int, uint32_t, int);
    ~GahoodWindow();
    
    void setFramesPerSecond(int) const;
    bool shouldRender() const;
    void initRender() const;
    void draw() const;
    SDL_Renderer * getRenderer() const;
    SDL_Window * getWindow() const;
    SDL_Texture * getTexture() const;
private:
    GahoodTimer *fpsTimer;
    SDL_Window *win;
    SDL_Renderer *winRenderer;
    SDL_Texture *winTexture;
};

#endif
