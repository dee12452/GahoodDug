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
    Window(Game *game);
    ~Window();

    void render(BaseScreen *currentScreen);
	SDL_Window * getWindow() const;
	SDL_Renderer * getWindowRenderer() const;
	SDL_Texture * getWindowTexture() const;

	void setRenderTarget(SDL_Texture *targetTexture) const;
	void resetRenderTarget() const;
	void drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect) const;
	SDL_Texture * createTransparentTexture(int width, int height) const;
private:
    SDL_Window *win;
    SDL_Renderer *winRenderer;
    SDL_Texture *winTexture;
};

#endif
