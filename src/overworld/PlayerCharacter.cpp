#include "../headers/PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(const std::string &id) 
	: BaseCharacter(id) {
}

PlayerCharacter::PlayerCharacter(const std::string &id, int x, int y, int w, int h) 
	: BaseCharacter(id, x, y, w, h) {
}

PlayerCharacter::PlayerCharacter(const std::string &id, 
	int sX, 
	int sY, 
	int sW, 
	int sH,
	int dX,
	int dY,
	int dW,
	int dH)
	: BaseCharacter(id, sX, sY, sW, sH, dX, dY, dW, dH) {
}

PlayerCharacter::~PlayerCharacter() {}

void PlayerCharacter::onMove(const CharacterDirection &dir, __int64 curr, __int64 total) {
	BaseCharacter::onMove(dir, curr, total);
}

void PlayerCharacter::onMoveEnd(const CharacterDirection &dir, int x, int y) {
	BaseCharacter::onMoveEnd(dir, x, y);
}

void PlayerCharacter::onMoveStart(const CharacterDirection &dir) {
	BaseCharacter::onMoveStart(dir);
}

void PlayerCharacter::onChangeDirection(const CharacterDirection &) {
}