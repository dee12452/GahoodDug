#ifndef WINDOW_HPP
#define WINDOW_HPP

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;
class BaseScreen;
class Game;

class Window {
public:
    Window();
    ~Window();

    //Draw the current screen
    //Should ONLY be called by the Game object's update
    void render(BaseScreen *screen);

    //Getters for the SDL information if needed
	SDL_Window * getWindow() const;
	SDL_Renderer * getWindowRenderer() const;
	SDL_Texture * getWindowTexture() const;

    //Set the render target to a different texture
	void setRenderTarget(SDL_Texture *targetTexture) const;
	
    //Reset the render target back to the original window texture
    void resetRenderTarget() const;

    //Erase the current render target (paint it black)
	void clearRenderTarget() const;

    //Draw a texture to the current render target
    void drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect) const;
	
    //Create a new transparent texture
    SDL_Texture * createTransparentTexture(int width, int height) const;
	
    //Create a new blank (all black) texture
    SDL_Texture * createTexture(int width, int height) const;

private:
    SDL_Window *win;
    SDL_Renderer *winRenderer;
    SDL_Texture *winTexture;
};

#endif
