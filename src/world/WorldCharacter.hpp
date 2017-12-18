#ifndef WORLD_CHARACTER_HPP
#define WORLD_CHARACTER_HPP

#include "BaseWorldMover.hpp"

class Timer;

class WorldCharacter : public BaseWorldMover {
public:
    WorldCharacter(World *world, SpriteSheet *sheet, int movementUpdateTime, int movementSpeed);
    ~WorldCharacter() override;

protected:
	void onTickInBackground() override;
	void onMoveStart(FacingDirection direction) override;
	void onMove(float percentToNextTile) override;
	void onMoveEnd(FacingDirection direction) override;
	void onChangeDirection(FacingDirection direction) override;

private:
    bool checkForObstacles(int tileX, int tileY) const;
};

#endif
