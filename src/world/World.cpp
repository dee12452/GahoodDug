#include "World.hpp"

#include <SDL2/SDL_render.h>
#include "../game/Game.hpp"
#include "../map/Maps.hpp"
#include "../map/MapLoader.hpp"
#include "../sprite/Sprites.hpp"
#include "../util/Utils.hpp"
#include "Character.hpp"

World::World(Game *game) : 
    currentMap(MapLoader::getInstance()->getMap(Constants::MAP_TEST)),
    tilesetSprite(game->getSpriteSheet(currentMap->getTileset()->getImagePath())->createSprite()),
    player(new Character(game->getSpriteSheet("NPC 01.png"), currentMap->getTileWidth())) {
	player->getSprite()->setDstX(Constants::WINDOW_WIDTH / 2 - player->getSprite()->getDstW() / 2);
	player->getSprite()->setDstY(Constants::WINDOW_HEIGHT / 2 - player->getSprite()->getDstH() / 2);
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

void World::drawWorld(Window *win) {

    //information on drawing the map to the screen 
    int mapDrawW = currentMap->getTileWidth() * Constants::WORLD_DRAW_WIDTH;
    int mapDrawH = currentMap->getTileHeight() * Constants::WORLD_DRAW_HEIGHT;

    //check character position limits are not out of bounds
    player->setPositionX(std::max(0, player->getPositionX()));
    player->setPositionX(std::min(currentMap->getTileWidth() * currentMap->getWidth() - mapDrawW, player->getPositionX()));
    player->setPositionY(std::max(0, player->getPositionY()));
    player->setPositionY(std::min(currentMap->getTileHeight() * currentMap->getHeight() - mapDrawH, player->getPositionY()));
    int mapDrawX = player->getPositionX();
    int mapDrawY = player->getPositionY();

    //create the map texture to be drawn
    SDL_Texture *mapTexture = win->createTexture(mapDrawW, mapDrawH);
	win->setRenderTarget(mapTexture);

    //srcRect for the map
    SDL_Rect mapSrcRect = Util::createRect(mapDrawX, mapDrawY, mapDrawW, mapDrawH);

    //dstRect for the map
    mapDrawX = 0; mapDrawY = 0;
    SDL_Rect mapDstRect = Util::createRect(mapDrawX, mapDrawY, mapDrawW, mapDrawH);

	for (unsigned int layer = 0; layer < currentMap->getNumberOfLayers(); layer++) {
		win->drawTexture(currentMap->getLayer(layer), &mapSrcRect, &mapDstRect);
		if (player->getLayer() == static_cast<int>(layer)) {
			player->getSprite()->draw(win->getWindowRenderer());
		}
	}

	win->resetRenderTarget();
	win->drawTexture(mapTexture, NULL, NULL);
	SDL_DestroyTexture(mapTexture);
	mapTexture = NULL;
}

Character * World::getPlayer() const { return player; }
