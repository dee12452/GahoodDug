#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "BaseWorldObject.hpp"

class Timer;

typedef enum FacingDirection { NONE = 4, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 0 } FacingDirection;

class Character : public BaseWorldObject {
public:
    Character(SpriteSheet *sheet, int tileWidth);
    ~Character() override;

    void update(Game *game) override;
    void draw(Window *win) override;

    void move(FacingDirection direction);
    void changeDirection(FacingDirection direction);
    void cancelNextMove();

    bool isMoving() const;
    FacingDirection getCurrentDirection() const;
    FacingDirection getNextDirection() const;

private:
    int tileWidth, displacement;
    FacingDirection currentDirection, nextDirection;
    Timer *movementTimer;
    bool moving, walkLeft;
};

#endif
