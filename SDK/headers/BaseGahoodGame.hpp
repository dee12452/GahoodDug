#ifndef BASE_GAHOOD_GAME_HPP
#define BASE_GAHOOD_GAME_HPP

#include <stdint.h>

//Forward Declarations//
class GahoodWindow;

struct SDL_Renderer;
union SDL_Event;
////////////////////////

class BaseGahoodGame {
public:
    BaseGahoodGame();
    virtual ~BaseGahoodGame();
    
    virtual void start(const char *, int, int, uint32_t);

    GahoodWindow * getGameWindow() const;
    void update();
    void setGameLoopDelayMs(uint32_t);
    void setRenderLoopDelayMs(uint32_t);
    uint32_t getGameLoopDelayMs() const;
    uint32_t getRenderLoopDelayMs() const;
    bool isRunning() const;

protected:
    int gameState;
    virtual void onUpdate() = 0;
    virtual void onPollEvent(SDL_Event) = 0;
    virtual void onDraw(SDL_Renderer *) = 0;
    virtual bool isRendering() const = 0;

private:
    void init(const char *, int, int, uint32_t);
    void run();
    void exit();

    bool running, didExit;
    long unsigned int *gameThread;
    GahoodWindow *window;
    uint32_t gameLoopDelay;
    uint32_t renderLoopDelay;
};

#endif
