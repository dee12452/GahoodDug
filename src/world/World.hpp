#ifndef WORLD_HPP
#define WORLD_HPP

class Game;
class Window;
class Map;
class BaseWorldObject;
struct SDL_Texture;
struct SDL_Rect;
enum MapDirection;

class World {
public:
    World();
    ~World();

	void start(Game *game);
	void stop(Game *game);
    void render(Window *win);

	BaseWorldObject * getPlayer() const;
    Map * getMap() const;

    void changeMap(const char * const mapFile);
	void changeMap(Map *newMap);

private:
    Map *map;
    SDL_Texture *mapTexture;
	BaseWorldObject *player, *routeTextBox;

    void drawMap(Window *win);
	void drawBorderingMap(Window *win, MapDirection direction, SDL_Rect mapSrc, SDL_Rect mapDst);
};

#endif
