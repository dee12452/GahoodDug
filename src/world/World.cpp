#include "World.hpp"
#include "../map/Maps.hpp"

#ifndef NULL
#define NULL 0
#endif

World::World(Map *firstMap) : currentMap(firstMap) {}

World::~World() { currentMap = NULL; }

void World::draw(Window *) {}

void World::update() {}
