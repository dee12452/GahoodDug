#ifndef WORLD_HPP
#define WORLD_HPP

#include "WorldCharacter.hpp"

class Map;
class WorldTextBox;
struct SDL_Texture;
struct SDL_Rect;
enum MapDirection;

class World {
public:
    World(Game *game);
    ~World();

    void render(Window *win);

    WorldCharacter * getPlayer() const;
    Map * getMap() const;
	int getTileWidth() const;
	int getTileHeight() const;

    void changeMap(const char * const mapFile);
	void changeMap(Map *newMap);

private:
    Map *map;
    SDL_Texture *mapTexture;
    WorldCharacter *player;
	WorldTextBox *routeTextBox;

    void drawMap(Window *win);
	void drawBorderingMap(Window *win, MapDirection direction, SDL_Rect mapSrc, SDL_Rect mapDst);

	/**
	* Move listener for the player
	*/
	class PlayerMoveListener : public WorldCharacterMoveListener {
	private:
		World *world;
	public:
		PlayerMoveListener(World *w) { world = w; }
		~PlayerMoveListener() override { world = 0; }

		void onMoveStart(FacingDirection direction, int tileX, int tileY) override;
		void onMove(FacingDirection direction, float percentToNextTile, int positionX, int positionY) override;
		void onMoveEnd(FacingDirection direction, int tileX, int tileY) override;
	};
};

#endif
