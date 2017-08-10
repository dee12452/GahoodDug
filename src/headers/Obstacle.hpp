#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "Sprite.hpp"

class Obstacle : public Sprite {
public:
	Obstacle(const std::string &id, int, int, int, int, int, int, int, int, const std::string &);
	~Obstacle();

	std::string getObstacleType() const;

private:
	std::string obstacleType;
};

#endif
