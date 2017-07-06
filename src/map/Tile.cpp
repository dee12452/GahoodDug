#include "../headers/Tile.hpp"

#include "../headers/Constants.hpp"
#include "../headers/Timer.hpp"

Tile::Tile(const std::string &id, 
        int x, 
        int y,
        bool isWalkable) : Sprite (id) {
    setSourceRect(x, y, Constants::TILE_WIDTH, Constants::TILE_HEIGHT);
    animTimer = NULL;
    currentTexture = 0;
    walkable = isWalkable;
}

Tile::Tile(const std::string &id,
        const std::vector<std::pair<int, int>> &coords,
        unsigned int animTimeMs,
        bool isWalkable) : Tile(id, 
            coords[0].first, 
            coords[0].second,
            isWalkable) {
    animTimer = new Timer(animTimeMs);
    textureCoordinates = coords;
}

Tile::~Tile() {
    if(animTimer != NULL) {
        delete animTimer;
        animTimer = NULL;
    }
    textureCoordinates.clear();
}

void Tile::onUpdate() {
    if(animTimer != NULL && textureCoordinates.size() > 1) {
        if(animTimer->check()) {
            currentTexture++;
            if(currentTexture == static_cast<int> (textureCoordinates.size())) {
                currentTexture = 0;
            }
            setSourceRect(textureCoordinates[currentTexture].first,
                    textureCoordinates[currentTexture].second,
                    getWidth(), getHeight());
        }
    }
}
