#ifndef GAHOODMON_HPP
#define GAHOODMON_HPP

#include <map>
#include <string>

struct SDL_Thread;
class Window;
class Timer;
class SpriteSheet;
class BaseScreen;

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

private:
    //Member variables//
    bool running;
    bool newScreen;
    Window *window;
    Timer *fpsTimer;
    SDL_Thread *backgroundThread;
    BaseScreen *currentScreen;

    //Member functions//
    void init();
    void update();
    void deinit();

    std::map<std::string, SpriteSheet *> spriteSheets;
};

#endif
