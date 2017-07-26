#include "../headers/Constants.hpp"
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

/*
 * IMAGE IDS */
const std::string Constants::IMAGE_ID_TEST = "sprite/test.png";

/*
 * SPRITE CONST */
const uint8_t Constants::SPRITE_ALPHA_FULL = 255;
const uint8_t Constants::SPRITE_ALPHA_NONE = 0;

/*
 * TILE CONST */
const int Constants::TILE_WIDTH = 32;
const int Constants::TILE_HEIGHT = 32;

/*
 * MAP CONST */
const char * const Constants::MAP_FILE_TEST = "../res/map/test_map.tmx";
const uint8_t Constants::MAP_MAX_LAYERS = 5;
