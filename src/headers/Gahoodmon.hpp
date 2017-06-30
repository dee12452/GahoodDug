#ifndef GAHOODMON_HPP
#define GAHOODMON_HPP

struct SDL_Thread;
class Window;
class Timer;
class BaseScreen;

class Gahoodmon {
public:
    Gahoodmon();
    ~Gahoodmon();

    void run();
    void runInBackground();
    bool isRunning() const;

private:
    //Member variables//
    bool running;
    Window *window;
    Timer *fpsTimer;
    SDL_Thread *backgroundThread;
    BaseScreen *currentScreen;

    //Member functions//
    void init();
    void update();
    void deinit();
};

#endif
