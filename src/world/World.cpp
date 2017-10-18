#include "World.hpp"

#include <SDL2/SDL_render.h>
#include "../game/Game.hpp"
#include "../map/Maps.hpp"
#include "../map/MapLoader.hpp"
#include "../game/Sprites.hpp"
#include "../util/Utils.hpp"
#include "Character.hpp"

World::World(Game *game) : 
    currentMap(MapLoader::getInstance()->getMap(Constants::MAP_TEST)),
    tilesetSprite(game->getSpriteSheet(currentMap->getTileset()->getImagePath())->createSprite()),
    player(new Character(game->getSpriteSheet("NPC 01.png"), currentMap->getTileWidth())) {
}

World::~World() { 
    currentMap = NULL;
    if(tilesetSprite != NULL) {
        delete tilesetSprite;
        tilesetSprite = NULL;
    }
    if(player != NULL) {
        delete player;
        player = NULL;
    }
}

void World::draw(Window *win) {
    SDL_Texture *mapTexture = SDL_CreateTexture(win->getWindowRenderer(), 
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_TARGET, 
            Constants::WORLD_DRAW_WIDTH * currentMap->getTileWidth(),
            Constants::WORLD_DRAW_HEIGHT * currentMap->getTileHeight());
    win->setRenderTarget(mapTexture);
    int startDrawX = player->getPositionX() / currentMap->getTileWidth() - Constants::WORLD_DRAW_WIDTH / 2;
    int startDrawY = player->getPositionY() / currentMap->getTileHeight() - Constants::WORLD_DRAW_HEIGHT / 2;
    for(size_t layer = 0; layer < currentMap->getLayers().size(); layer++) {
        for(int y = startDrawY; y - startDrawY < Constants::WORLD_DRAW_HEIGHT && y < currentMap->getHeight(); y++) {
            for(int x = startDrawX; x - startDrawX < Constants::WORLD_DRAW_WIDTH && x < currentMap->getWidth(); x++) {
                if(y < 0 || x < 0 || currentMap->getLayers()[layer][x][y] - 1 < 0) continue;
                Tile *currTile = currentMap->getTileset()->getTile(currentMap->getLayers()[layer][x][y] - 1);
                SDL_Rect src = Util::createRect(currTile->getRow() * currentMap->getTileWidth(), 
                        currTile->getColumn() * currentMap->getTileHeight(), 
                        currentMap->getTileWidth(), 
                        currentMap->getTileHeight());
                SDL_Rect dst = Util::createRect((x - startDrawX) * currentMap->getTileWidth(),
                        (y - startDrawY) * currentMap->getTileHeight(),
                        currentMap->getTileWidth(),
                        currentMap->getTileHeight());
                tilesetSprite->setSrcRect(src);
                tilesetSprite->setDstRect(dst);
                tilesetSprite->draw(win->getWindowRenderer());
                currTile = NULL;
            }
        }
    }
    win->resetRenderTarget();
    win->drawTexture(mapTexture, NULL, NULL);
    SDL_DestroyTexture(mapTexture);
    mapTexture = NULL;
    player->move(DOWN);
}

void World::update(Game *game) { player->update(game); }
