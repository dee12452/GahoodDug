#ifndef GAHOODMON_HPP
#define GAHOODMON_HPP

class Window;
class Timer;

class Gahoodmon {
public:
    Gahoodmon();
    ~Gahoodmon();

    void run();
    bool isRunning() const;

private:
    //Member variables//
    bool running;
    Window *window;
    Timer *fpsTimer;

    //Member functions//
    void init();
    void update();
    void deinit();
};

#endif
