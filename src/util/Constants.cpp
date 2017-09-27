#include "Constants.hpp"
#include <SDL2/SDL.h>

/*
 * WINDOW CONST */
const char * Constants::GAME_TITLE = "Gahoodmon";
const int Constants::WINDOW_WIDTH = 500;
const int Constants::WINDOW_HEIGHT = 500;
const uint32_t Constants::WINDOW_FLAGS = SDL_WINDOW_OPENGL; 

/*
 * GAME CONST */
const uint8_t Constants::GAME_LOOP_DELAY = 5;
const uint8_t Constants::RENDER_LOOP_DELAY = 5;
const uint8_t Constants::TARGET_FPS = 60;
const char * const Constants::GAME_THREAD_NAME = "GahoodmonBackgroundThread";
const char * const Constants::GAME_IMAGE_FOLDER = "../res/image/";
const char * const Constants::GAME_TILESET_FOLDER = "../res/tileset/";

/*
 * IMAGE IDS */
const std::string Constants::IMAGE_ID_TEST = "sprite/test.png";
const std::string Constants::IMAGE_TILESET_UNDERWATER = "tile/tileset_underwater.png";
const std::string Constants::IMAGE_CHARACTER_1 = "sprite/character_1.png";

/*
 * SPRITE CONST */
const uint8_t Constants::SPRITE_ALPHA_FULL = 255;
const uint8_t Constants::SPRITE_ALPHA_NONE = 0;
const int Constants::SPRITE_TILE_WIDTH = 32;
const int Constants::SPRITE_TILE_HEIGHT = 32;
const int Constants::SPRITE_CHARACTER_WIDTH = 32;
const int Constants::SPRITE_CHARACTER_HEIGHT = 48;
const int Constants::SPRITE_CHARACTER_X = 0;
const int Constants::SPRITE_CHARACTER_Y = 0;
const uint8_t Constants::SPRITE_CHARACTER_FACE_DOWN = 0;
const uint8_t Constants::SPRITE_CHARACTER_FACE_UP = 3;
const uint8_t Constants::SPRITE_CHARACTER_FACE_LEFT = 1;
const uint8_t Constants::SPRITE_CHARACTER_FACE_RIGHT = 2;

/*
 * MAP CONST */
const char * const Constants::MAP_FILE_TEST = "../res/map/test_map.tmx";
const uint8_t Constants::MAP_MAX_LAYERS = 5;
const uint8_t Constants::MAP_NUM_TILES_WIDTH = 10;
const uint8_t Constants::MAP_NUM_TILES_HEIGHT = 9;
const std::string Constants::TILE_TYPE_WALL = "wall";
const std::string Constants::TILE_TYPE_FLOOR = "floor";

/*
 * OBJECT TYPE CONST */
const std::string Constants::OBJECT_TYPE_PLAYER = "PlayerObject";
