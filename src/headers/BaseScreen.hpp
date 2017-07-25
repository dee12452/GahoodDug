#ifndef BASE_SCREEN_HPP
#define BASE_SCREEN_HPP

#include <vector>

class Sprite;
class Gahoodmon;
struct SDL_Renderer;
union SDL_Event;

class BaseScreen {
public:
    BaseScreen();
    virtual ~BaseScreen();
    void update();
    void updateInBackground();
    void handleInput(Gahoodmon *, const SDL_Event &);
    std::vector<Sprite *> getSprites() const;
	void draw(SDL_Renderer *);
    void start();
    void stop();

protected:
	virtual void onDraw(SDL_Renderer *) = 0;
    virtual void onStart() = 0;
    virtual void onStop() = 0;
    virtual void onUpdate() = 0;
    virtual void onInput(Gahoodmon *, const SDL_Event &) = 0;
    virtual void onUpdateInBackground() = 0;

    void addSprite(Sprite *);
    void removeSprite(Sprite *);

private:
    std::vector<Sprite *> sprites;
};

#endif
