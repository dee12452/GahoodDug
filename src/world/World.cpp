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
	SDL_Texture *mapTexture = win->createTexture(currentMap->getTileWidth() * Constants::WORLD_DRAW_WIDTH, 
            currentMap->getTileHeight() * Constants::WORLD_DRAW_HEIGHT);
	win->setRenderTarget(mapTexture);
	
    //srcRect for the map
	SDL_Rect mapSrcRect = Util::createRect(player->getPositionX(), 
            player->getPositionY(), 
            currentMap->getTileWidth() * Constants::WORLD_DRAW_WIDTH,
            currentMap->getTileHeight() * Constants::WORLD_DRAW_HEIGHT);

	for (unsigned int layer = 0; layer < currentMap->getNumberOfLayers(); layer++) {
		win->drawTexture(currentMap->getLayer(layer), &mapSrcRect, NULL);
		if (player->getLayer() == static_cast<int>(layer)) {
			player->getSprite()->draw(win->getWindowRenderer());
		}
	}

	win->resetRenderTarget();
	win->drawTexture(mapTexture, NULL, NULL);
	SDL_DestroyTexture(mapTexture);
	mapTexture = NULL;
}

int World::getTileWidth() const { return currentMap->getTileWidth(); }
int World::getTileHeight() const { return currentMap->getTileHeight(); }
Character * World::getPlayer() const { return player; }
