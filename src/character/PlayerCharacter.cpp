#include "../headers/PlayerCharacter.hpp"

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
	: BaseCharacter(id, sX, sY, sW, sH) {
	setDestinationRect(dX, dY, dW, dH);
}

PlayerCharacter::~PlayerCharacter() {}

void PlayerCharacter::onMove(const CharacterDirection &, __int64, __int64) {

}

void PlayerCharacter::onArrive(const CharacterDirection &, int, int) {

}

void PlayerCharacter::onChangeDirection(const CharacterDirection &) {

}