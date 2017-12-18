#include "World.hpp"

#include <algorithm>
#include <SDL2/SDL_render.h>
#include "../game/Game.hpp"
#include "../map/Maps.hpp"
#include "../map/MapLoader.hpp"
#include "../sprite/Sprites.hpp"
#include "../util/Utils.hpp"
#include "WorldCharacter.hpp"

World::World(Game *game) : map(NULL), mapTexture(NULL), player(NULL) {
    changeMap(game, Constants::MAP_TEST_3);
} 

World::~World() { 
    map = NULL;
    if(player != NULL) {
        delete player;
        player = NULL;
    }
    if(mapTexture != NULL) {
        SDL_DestroyTexture(mapTexture);
        mapTexture = NULL;
    }
}

void World::drawWorld(Window *win) {
    drawMap(win);
}

void World::drawMap(Window *win) {
	int drawWidth = Constants::WORLD_DRAW_WIDTH * map->getTileWidth();
	int drawHeight = Constants::WORLD_DRAW_HEIGHT * map->getTileHeight();
	win->setRenderTarget(mapTexture);
    win->clearRenderTarget();

	SDL_Rect mapSrc = Util::createRect(player->getPositionX(), player->getPositionY(),  drawWidth, drawHeight);
	SDL_Rect mapDst = Util::createRect(drawWidth / 2, drawHeight / 2, drawWidth, drawHeight);

	//Deal with x < 0
	int targetX = mapSrc.x - drawWidth / 2 + map->getTileWidth() / 2;
	if (targetX < 0) {
		mapSrc.x = 0;
		mapDst.x -= player->getPositionX() - drawWidth / 2 + map->getTileWidth() / 2;
	}

	//Deal with x > map width
	else if (targetX > (map->getWidth() * map->getTileWidth()) - drawWidth) {
		mapSrc.x = map->getWidth() * map->getTileWidth() - drawWidth;
		mapDst.x += (map->getWidth() * map->getTileWidth())
			- player->getPositionX() - drawWidth / 2 - map->getTileWidth() / 2;
	}

	//No issues on x axis
	else {
		mapSrc.x = targetX;
	}

	//Deal with y < 0
	int targetY = mapSrc.y - drawHeight / 2 + map->getTileHeight() / 2;
	if (targetY < 0) {
		mapSrc.y = 0;
		mapDst.y -= player->getPositionY() - drawHeight / 2 + map->getTileHeight() / 2;
	}

	//Deal with y > map height
	else if (targetY > (map->getHeight() * map->getTileHeight()) - drawHeight) {
		mapSrc.y = (map->getHeight() * map->getTileHeight()) - drawHeight;
		mapDst.y += (map->getHeight() * map->getTileHeight()) 
			- player->getPositionY() - drawHeight / 2 - map->getTileHeight() / 2;
	}

	//No issues on y axis
	else {
		mapSrc.y = targetY;
	}

    //Draw the map
	for (unsigned int i = 0; i < map->getNumberOfLayers(); i++) {
		win->drawTexture(map->getLayer(i), &mapSrc, &mapDst);
		if (i == static_cast<unsigned int> (player->getLayer() + 1)) {
			player->getSprite()->setDstX(drawWidth - player->getSprite()->getDstW() / 2);
			player->getSprite()->setDstY(drawHeight - player->getSprite()->getDstH() / 2 + Constants::CHARACTER_TILE_OFFSET_Y);
			player->getSprite()->draw(win->getWindowRenderer());
		}
	}

	mapSrc = Util::createRect(drawWidth / 2, drawHeight / 2, drawWidth, drawHeight);

	win->resetRenderTarget();
	win->drawTexture(mapTexture, &mapSrc, NULL);
}

void World::changeMap(Game *game, const char * const mapFile) {
    map = MapLoader::getInstance()->getMap(mapFile);
    if(player != NULL) delete player;
    player = new WorldCharacter(this, game->getSpriteSheet("NPC 07.png"), Constants::CHARACTER_WALK_TIMER, Constants::CHARACTER_WALK_SPEED);
    if(mapTexture == NULL) SDL_DestroyTexture(mapTexture);
	int drawWidth = Constants::WORLD_DRAW_WIDTH * map->getTileWidth();
	int drawHeight = Constants::WORLD_DRAW_HEIGHT * map->getTileHeight();
	mapTexture = game->getWindow()->createTexture(drawWidth * 2, drawHeight * 2);
}

Map * World::getMap() const { return map; }
int World::getTileWidth() const { return map->getTileWidth(); }
int World::getTileHeight() const { return map->getTileHeight(); }
WorldCharacter * World::getPlayer() const { return player; }
