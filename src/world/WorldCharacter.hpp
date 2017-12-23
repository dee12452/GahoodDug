#ifndef WORLD_CHARACTER_HPP
#define WORLD_CHARACTER_HPP

#include "BaseWorldMover.hpp"

class Timer;
class WorldCharacterMoveListener;

class WorldCharacter : public BaseWorldMover {
public:
    WorldCharacter(World *world, SpriteSheet *image, int movementUpdateTime, int movementSpeed);
    ~WorldCharacter() override;

	void setOnMoveListener(WorldCharacterMoveListener *listener);

protected:
	void onTickInBackground() override;
	void onMoveStart(FacingDirection direction) override;
	void onMove(float percentToNextTile) override;
	void onMoveEnd(FacingDirection direction) override;
	void onChangeDirection(FacingDirection direction) override;

private:
    bool checkForObstacles(int tileX, int tileY) const;
	WorldCharacterMoveListener *moveListener;
};

class WorldCharacterMoveListener {
public:
	WorldCharacterMoveListener() {}
	virtual ~WorldCharacterMoveListener() {}

	virtual void onMoveStart(FacingDirection direction, int tileX, int tileY) = 0;
	virtual void onMove(FacingDirection direction, float percentToNextTile, int positionX, int positionY) = 0;
	virtual void onMoveEnd(FacingDirection direction, int tileX, int tileY) = 0;

};

#endif
