#ifndef BASE_CHARACTER_HPP
#define BASE_CHARACTER_HPP

#include "BaseOverworldObject.hpp"

enum CharacterDirection { CH_UP, CH_DOWN, CH_LEFT, CH_RIGHT, CH_NONE };

class BaseCharacter : public BaseOverworldObject {
public:
	BaseCharacter(const std::string &id, int, int, int, int);
	virtual ~BaseCharacter() override;

	CharacterDirection getFacingDirection() const;
	bool isMoving() const;

	bool move(const CharacterDirection &);
	bool move(const CharacterDirection &, unsigned int);
	void cancelNextMove();
	void changeFacingDirection(const CharacterDirection &);
	uint8_t getCurrentMapLayer() const;
	void setCurrentMapLayer(uint8_t);

protected:
	void onUpdate() override;
	virtual void onMoveStart(const CharacterDirection &);
	virtual void onMove(const CharacterDirection &, __int64, __int64);
	virtual void onMoveEnd(const CharacterDirection &, int, int);
	virtual void onChangeDirection(const CharacterDirection &);

private:
	static const __int64 updateTime, defaultMoveTime;
	CharacterDirection currentDirection, nextDirection;
	bool moving, walkLeft;
	__int64 startMove, walkDuration;
	uint8_t currentLayer;
};

#endif