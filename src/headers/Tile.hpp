#ifndef TILE_HPP
#define TILE_HPP

#include "Sprite.hpp"
#include <vector>

class Timer;

class Tile : public Sprite {
public:
    Tile(const std::string &, int, int, bool);
    Tile(const std::string &, 
            const std::vector<std::pair<int, int>> &, 
            unsigned int,
            bool);
    ~Tile() override;

protected:
    void onUpdate() override;

private:
    Timer *animTimer;
    std::vector<std::pair<int, int>> textureCoordinates;
    int currentTexture;
    bool walkable;
};

#endif
