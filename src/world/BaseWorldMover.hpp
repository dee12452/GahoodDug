#ifndef BASE_WORLD_MOVER
#define BASE_WORLD_MOVER

#include "BaseWorldObject.hpp"

class Timer;

typedef enum FacingDirection { NONE = 4, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 0 } FacingDirection;

class BaseWorldMover : public BaseWorldObject {
public:
	BaseWorldMover(World *world, SpriteSheet *spriteSheet, int movementUpdateTime, int movementSpeed);
	virtual ~BaseWorldMover() override;

	void move(FacingDirection direction);
	void changeDirection(FacingDirection direction);
	void cancelNextMove();

	bool isMoving() const;
    FacingDirection getCurrentDirection() const;
	FacingDirection getNextDirection() const;
    int getMoveSpeed() const;
    void setMoveSpeed(int speed);

protected:

    void stopNextMovement();
    bool isWalkingLeft() const;
	void onTick(Game *game) override;

	virtual void onMoveStart(FacingDirection direction) = 0;
    virtual void onMove(float percentToNextTile) = 0;
	virtual void onMoveEnd(FacingDirection direction) = 0;
	virtual void onChangeDirection(FacingDirection direction) = 0;

private:
	int displacement, moveSpeed, nextMoveSpeed;
	FacingDirection currentDirection, nextDirection;
	Timer *movementTimer;
	bool moving, canMove, walkLeft;
};

#endif
