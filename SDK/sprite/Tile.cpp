#include "../headers/Tile.hpp"

Tile::Tile(int z, bool walk) : GahoodSprite() {
    level = z;
    walkable = walk;
}

Tile::~Tile() {}

int Tile::getLevel() const {
    return level;
}

bool Tile::isWalkable() const {
    return walkable;
}

void Tile::setOccupant(Object *obj) {
    occupant = obj;
    if(obj == NULL) {
        occupied = false;
    }
    else {
        occupied = true;
    }
}
