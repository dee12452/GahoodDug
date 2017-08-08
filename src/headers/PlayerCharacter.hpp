#ifndef PLAYER_CHARACTER_HPP
#define PLAYER_CHARACTER_HPP

#include "../headers/BaseCharacter.hpp"

class PlayerCharacter : public BaseCharacter {
public:
	PlayerCharacter(const std::string &id, int, int, int, int);
	PlayerCharacter(const std::string &id, int, int, int, int, int, int, int, int);
	~PlayerCharacter() override;

protected:
	void onMove(const CharacterDirection &, __int64, __int64) override;
	void onMoveEnd(const CharacterDirection &, int, int) override;
	void onMoveStart(const CharacterDirection &) override;
	void onChangeDirection(const CharacterDirection &) override;
};

#endif