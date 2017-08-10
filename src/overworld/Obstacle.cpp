#include "../headers/Obstacle.hpp"

Obstacle::Obstacle(const std::string &id, 
	int sX, 
	int sY, 
	int sW, 
	int sH, 
	int dX,
	int dY, 
	int dW, 
	int dH,
	const std::string &type) 
	: Sprite(id, 
		sX, sY, sW, sH,
		dX, dY, dW, dH) {
	obstacleType = type;
}

Obstacle::~Obstacle() {
}

std::string Obstacle::getObstacleType() const {
	return obstacleType;
}