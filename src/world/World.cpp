#include "World.hpp"

#include <algorithm>
#include <SDL2/SDL_render.h>
#include "../game/Game.hpp"
#include "../map/Maps.hpp"
#include "../map/MapLoader.hpp"
#include "../sprite/Sprites.hpp"
#include "../util/Utils.hpp"
#include "Character.hpp"

World::World(Game *game) : currentMap(NULL), mapTexture(NULL), player(NULL) {
    changeMap(game, Constants::MAP_TEST_3);
} 

World::~World() { 
    currentMap = NULL;
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
	int drawWidth = Constants::WORLD_DRAW_WIDTH * currentMap->getTileWidth();
	int drawHeight = Constants::WORLD_DRAW_HEIGHT * currentMap->getTileHeight();
	win->setRenderTarget(mapTexture);
    win->clearRenderTarget();

	SDL_Rect mapSrc = Util::createRect(player->getPositionX(), player->getPositionY(),  drawWidth, drawHeight);
	SDL_Rect mapDst = Util::createRect(drawWidth / 2, drawHeight / 2, drawWidth, drawHeight);

	//Deal with x < 0
	int targetX = mapSrc.x - drawWidth / 2 + currentMap->getTileWidth() / 2;
	if (targetX < 0) {
		mapSrc.x = 0;
		mapDst.x -= player->getPositionX() - drawWidth / 2 + currentMap->getTileWidth() / 2;
	}

	//Deal with x > map width
	else if (targetX > (currentMap->getWidth() * currentMap->getTileWidth()) - drawWidth) {
		mapSrc.x = currentMap->getWidth() * currentMap->getTileWidth() - drawWidth;
		mapDst.x += (currentMap->getWidth() * currentMap->getTileWidth())
			- player->getPositionX() - drawWidth / 2 - currentMap->getTileWidth() / 2;
	}

	//No issues on x axis
	else {
		mapSrc.x = targetX;
	}

	//Deal with y < 0
	int targetY = mapSrc.y - drawHeight / 2 + currentMap->getTileHeight() / 2;
	if (targetY < 0) {
		mapSrc.y = 0;
		mapDst.y -= player->getPositionY() - drawHeight / 2 + currentMap->getTileHeight() / 2;
	}

	//Deal with y > map height
	else if (targetY > (currentMap->getHeight() * currentMap->getTileHeight()) - drawHeight) {
		mapSrc.y = (currentMap->getHeight() * currentMap->getTileHeight()) - drawHeight;
		mapDst.y += (currentMap->getHeight() * currentMap->getTileHeight()) 
			- player->getPositionY() - drawHeight / 2 - currentMap->getTileHeight() / 2;
	}

	//No issues on y axis
	else {
		mapSrc.y = targetY;
	}

    //Draw the map
	for (unsigned int i = 0; i < currentMap->getNumberOfLayers(); i++) {
		win->drawTexture(currentMap->getLayer(i), &mapSrc, &mapDst);
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
    currentMap = MapLoader::getInstance()->getMap(mapFile);
    if(player != NULL) delete player;
    player = new Character(currentMap, game->getSpriteSheet("NPC 07.png"), Constants::CHARACTER_WALK_TIMER, Constants::CHARACTER_WALK_SPEED);
    if(mapTexture == NULL) SDL_DestroyTexture(mapTexture);
	int drawWidth = Constants::WORLD_DRAW_WIDTH * currentMap->getTileWidth();
	int drawHeight = Constants::WORLD_DRAW_HEIGHT * currentMap->getTileHeight();
	mapTexture = game->getWindow()->createTexture(drawWidth * 2, drawHeight * 2);
}

int World::getTileWidth() const { return currentMap->getTileWidth(); }
int World::getTileHeight() const { return currentMap->getTileHeight(); }
Character * World::getPlayer() const { return player; }
