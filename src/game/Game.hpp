#ifndef GAHOODMON_HPP
#define GAHOODMON_HPP

#include <vector>
#include <map>
#include <string>
#include "Window.hpp"

struct SDL_Thread;
class Timer;
class SpriteSheet;
class BaseScreen;
class Font;
class BaseGameObject;

class Game {
public:
    Game();
    ~Game();

    void run();
    void runInBackground();
    bool isRunning() const;
    void quit();
    void requestNewScreen(BaseScreen *newScreen);
    void loadSpriteSheet(const char *path);
	void registerGameObject(BaseGameObject *obj);
	void unregisterGameObject(BaseGameObject *obj);

    Window * getWindow() const;
    SpriteSheet * getSpriteSheet(const char *spriteSheetName) const;
    Font * getFont(const char *fontName) const;

private:
    //Member variables//
    bool running;
    Window *window;
    Timer *fpsTimer, *tickTimer;
    SDL_Thread *backgroundThread;
    BaseScreen *currentScreen, *nextScreen;

    //Member functions//
    void init();
    void update();
    void deinit();
    void changeScreens();

	std::vector<BaseGameObject *> updatables;
    std::map<std::string, SpriteSheet *> spriteSheets;
    std::map<std::string, Font *> fonts;
};

#endif
