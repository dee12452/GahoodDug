#ifndef PLAYER_CHARACTER_HPP
#define PLAYER_CHARACTER_HPP

#include "../headers/BaseCharacter.hpp"

class PlayerCharacter : public BaseCharacter {
public:
	PlayerCharacter(const std::string &id);
	PlayerCharacter(const std::string &id, int, int, int, int);
	PlayerCharacter(const std::string &id, int, int, int, int, int, int, int, int);
	~PlayerCharacter() override;

protected:
	void onMove(const CharacterDirection &, int64_t, int64_t) override;
	void onMoveEnd(const CharacterDirection &, int, int) override;
	void onMoveStart(const CharacterDirection &) override;
	void onChangeDirection(const CharacterDirection &) override;
};

#endif
