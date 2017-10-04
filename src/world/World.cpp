#include "World.hpp"

#include <SDL2/SDL_render.h>
#include "../game/Game.hpp"
#include "../map/Maps.hpp"
#include "../map/MapLoader.hpp"
#include "../game/Sprites.hpp"
#include "../util/Utils.hpp"

World::World(Game *game) : 
    currentMap(MapLoader::getInstance()->getMap(Constants::MAP_TEST)),
    tilesetSprite(game->getSpriteSheet(currentMap->getTileset()->getImagePath())->createSprite()) {
}

World::~World() { 
    currentMap = NULL;
    if(tilesetSprite != NULL) {
        delete tilesetSprite;
        tilesetSprite = NULL;
    }
}

void World::draw(Window *win) {
    /* For each layer, create a transparent texture
     * Then copy each tile to the transparent texture 
     * Lastly, draw the layers to the window */ 
    for(size_t layer = 0; layer < currentMap->getLayers().size(); layer++) {
        SDL_Texture *texture = win->createTransparentTexture(Constants::WORLD_DRAW_WIDTH * currentMap->getTileWidth(), 
                Constants::WORLD_DRAW_HEIGHT * currentMap->getTileHeight());
        win->setRenderTarget(texture);
        for(int y = 0; y < Constants::WORLD_DRAW_HEIGHT && y < currentMap->getHeight(); y++) {
            for(int x = 0; x < Constants::WORLD_DRAW_WIDTH && x < currentMap->getWidth(); x++) {
                if(currentMap->getLayers()[layer][x][y] - 1 < 0) continue;
                Tile *currTile = currentMap->getTileset()->getTile(currentMap->getLayers()[layer][x][y] - 1);
                SDL_Rect src = Util::createRect(currTile->getRow() * currentMap->getTileWidth(), 
                        currTile->getColumn() * currentMap->getTileHeight(), 
                        currentMap->getTileWidth(), 
                        currentMap->getTileHeight());
                SDL_Rect dst = Util::createRect(x * currentMap->getTileWidth(),
                        y * currentMap->getTileHeight(),
                        currentMap->getTileWidth(),
                        currentMap->getTileHeight());
                tilesetSprite->setSrcRect(src);
                tilesetSprite->setDstRect(dst);
                tilesetSprite->draw(win->getWindowRenderer());
                currTile = NULL;
            }
        }
        win->resetRenderTarget();
        win->drawTexture(texture, NULL, NULL);
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void World::update(Game *) {}
