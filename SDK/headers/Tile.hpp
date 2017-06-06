#ifndef TILE_HPP
#define TILE_HPP

#include "GahoodSprite.hpp"

class Object;

class Tile : public GahoodSprite {
public:
    Tile(int, bool);
    virtual ~Tile();

    enum TileType { NONE, CAVE, GRASS, WATER };

    int getLevel() const; 
    bool isWalkable() const;

    void setOccupant(Object *);
    Object * getOccupant() const;
    bool getOccupied(bool) const;
private:
    int level;
    bool walkable;
    bool occupied;
    Object *occupant;
};

#endif
