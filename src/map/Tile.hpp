#ifndef TILE_HPP
#define TILE_HPP

#include "Sprite.hpp"
#include <vector>

class Timer;

class Tile : public Sprite {
public:
    Tile(const std::string &, 
		const std::string &,
		int, 
		int, 
		int, 
		bool);

    Tile(const std::string &, 
		const std::string &,
		int,
		const std::vector<std::pair<int, int>> &, 
		unsigned int,
		bool);

    ~Tile() override;

	int getTileId() const;
	std::string getTileType() const;

protected:
    void onUpdate() override;

private:
	int tileId;
    Timer *animTimer;
    std::vector<std::pair<int, int>> textureCoordinates;
	std::string tileType;
    int currentTexture;
    bool walkable;
};

#endif
