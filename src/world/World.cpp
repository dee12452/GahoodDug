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

    //Create the texture for the map to be drawn to and clear it
    SDL_Texture *mapTexture = SDL_CreateTexture(win->getWindowRenderer(),
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_TARGET, 
            (Constants::WORLD_DRAW_WIDTH + 2) * currentMap->getTileWidth(),
            (Constants::WORLD_DRAW_HEIGHT + 2)* currentMap->getTileHeight());
    win->setRenderTarget(mapTexture);
    win->clearRenderTartget();

    //player offsets
    //means how far off from the current tile they are 
    const int playerOffsetX = player->getPositionX() % currentMap->getTileWidth();
    const int playerOffsetY = player->getPositionY() % currentMap->getTileHeight();
    
    //where to start drawing the map
    //uses player position
    const int startDrawX = player->getPositionX() / currentMap->getTileWidth() - Constants::WORLD_DRAW_WIDTH / 2;
    const int startDrawY = player->getPositionY() / currentMap->getTileHeight() - Constants::WORLD_DRAW_HEIGHT / 2;
    
    for(size_t layer = 0; layer < currentMap->getLayers().size(); layer++) {
        
        //Draw the current layer using the given map
        for(int y = startDrawY; y - startDrawY < Constants::WORLD_DRAW_HEIGHT + 2 && y < currentMap->getHeight(); y++) {
            for(int x = startDrawX; x - startDrawX < Constants::WORLD_DRAW_WIDTH + 2 && x < currentMap->getWidth(); x++) {
                if(y < 0 || x < 0 || currentMap->getLayers()[layer][x][y] - 1 < 0) continue;
                Tile *currTile = currentMap->getTileset()->getTile(currentMap->getLayers()[layer][x][y] - 1);
                SDL_Rect src = Util::createRect(currTile->getRow() * currentMap->getTileWidth(), 
                        currTile->getColumn() * currentMap->getTileHeight(), 
                        currentMap->getTileWidth(), 
                        currentMap->getTileHeight());
                SDL_Rect dst = Util::createRect((x - startDrawX) * currentMap->getTileWidth() - Constants::CHARACTER_TILE_OFFSET_X,
                        (y - startDrawY) * currentMap->getTileHeight() - Constants::CHARACTER_TILE_OFFSET_Y,
                        currentMap->getTileWidth(),
                        currentMap->getTileHeight());
                tilesetSprite->setSrcRect(src);
                tilesetSprite->setDstRect(dst);
                tilesetSprite->draw(win->getWindowRenderer());
                currTile = NULL;
            }
        }

        //If the player is on this layer, draw him
        //Adding the commented section draws the character on the correct tile but puts him not in the center of the screen 
        if(player->getLayer() == static_cast<int>(layer)) {
            player->getSprite()->setDstX(((Constants::WORLD_DRAW_WIDTH) * currentMap->getTileWidth()) / 2 + playerOffsetX);
            player->getSprite()->setDstY(((Constants::WORLD_DRAW_HEIGHT)* currentMap->getTileHeight()) / 2 + playerOffsetY);
            player->draw(win);
        }
    }

    //The actual rect of what's to be drawn to the screen
    //The actual map texture is 2 tiles too long and tall
    SDL_Rect mapSrcRect = Util::createRect(currentMap->getTileWidth() + playerOffsetX,
            currentMap->getTileHeight() + playerOffsetY,
            Constants::WORLD_DRAW_WIDTH * currentMap->getTileWidth(),
            Constants::WORLD_DRAW_HEIGHT * currentMap->getTileHeight());
    win->resetRenderTarget();
    win->drawTexture(mapTexture, &mapSrcRect, NULL);

    //Clean up
    SDL_DestroyTexture(mapTexture);
    mapTexture = NULL;
}

void World::update(Game *game) { player->update(game); }

Character * World::getPlayer() const { return player; }
