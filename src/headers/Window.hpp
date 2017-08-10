#ifndef WINDOW_HPP
#define WINDOW_HPP

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;
class BaseScreen;

class Window {
public:
    Window();
    ~Window();

    void render(BaseScreen *);
	SDL_Window * getWindow() const;
	SDL_Renderer * getWindowRenderer() const;
	SDL_Texture * getWindowTexture() const;

	void setRenderTarget(SDL_Texture *) const;
	void resetRenderTarget() const;
	void drawTexture(SDL_Texture *, SDL_Rect *, SDL_Rect *) const;
	SDL_Texture * createTransparentTexture(int, int) const;
private:
    bool loadImages;
    SDL_Window *win;
    SDL_Renderer *winRenderer;
    SDL_Texture *winTexture;
};

#endif
