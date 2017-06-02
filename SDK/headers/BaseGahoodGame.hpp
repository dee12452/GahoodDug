#ifndef BASE_GAHOOD_GAME_HPP
#define BASE_GAHOOD_GAME_HPP

class Window;

class BaseGahoodGame {
public:
    BaseGahoodGame();
    ~BaseGahoodGame();
    
    virtual void start();
protected:
    int gameState;

private:
    Window *window;
};

#endif
