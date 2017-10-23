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
            (Constants::WORLD_DRAW_WIDTH + 2) * currentMap->getTileWidth(),
            (Constants::WORLD_DRAW_HEIGHT + 2)* currentMap->getTileHeight());
    win->setRenderTarget(mapTexture);
    win->clearRenderTartget();
    int startDrawX = player->getPositionX() / currentMap->getTileWidth() - Constants::WORLD_DRAW_WIDTH / 2;
    int startDrawY = player->getPositionY() / currentMap->getTileHeight() - Constants::WORLD_DRAW_HEIGHT / 2;
    for(size_t layer = 0; layer < currentMap->getLayers().size(); layer++) {
        for(int y = startDrawY; y - startDrawY < Constants::WORLD_DRAW_HEIGHT + 2 && y < currentMap->getHeight(); y++) {
            for(int x = startDrawX; x - startDrawX < Constants::WORLD_DRAW_WIDTH + 2 && x < currentMap->getWidth(); x++) {
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
        if(player->getLayer() == static_cast<int>(layer)) {
            player->getSprite()->setDstX(100);
            player->getSprite()->setDstY(100);
            player->draw(win);
        }
    }
    SDL_Rect mapSrcRect = Util::createRect(currentMap->getTileWidth() + player->getPositionX() % currentMap->getTileWidth(),
            currentMap->getTileHeight() + player->getPositionY() % currentMap->getTileHeight(),
            Constants::WORLD_DRAW_WIDTH * currentMap->getTileWidth(),
            Constants::WORLD_DRAW_HEIGHT * currentMap->getTileHeight());
    win->resetRenderTarget();
    win->drawTexture(mapTexture, &mapSrcRect, NULL);
    SDL_DestroyTexture(mapTexture);
    mapTexture = NULL;
}

void World::update(Game *game) { player->update(game); }

Character * World::getPlayer() const { return player; }
