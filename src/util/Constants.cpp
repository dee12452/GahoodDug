#include "Constants.hpp"
#include "Util.hpp"
#include <SDL2/SDL.h>

/*
 * WINDOW CONST */
const char * Constants::GAME_TITLE = "Gahoodmon";
const int Constants::WINDOW_WIDTH = 500;
const int Constants::WINDOW_HEIGHT = 500;
const uint32_t Constants::WINDOW_FLAGS = SDL_WINDOW_OPENGL; 

/*
 * GAME CONST */
const uint8_t Constants::GAME_BACKGROUND_LOOP_DELAY = 25;
const uint8_t Constants::GAME_LOOP_DELAY = 5;
const uint16_t Constants::TARGET_TICKS_PER_SECOND = 120;
const uint8_t Constants::TARGET_FPS = 65;
const char * const Constants::GAME_THREAD_NAME = "GahoodmonBackgroundThread";
const char * const Constants::GAME_RES_FOLDER = "../res";

/*
 * FILE EXTENSIONS CONST */
const char * const Constants::IMAGE_FILE_EXTENSION = ".png";
const char * const Constants::TILESET_FILE_EXTENSION = ".tsx";
const char * const Constants::MAP_FILE_EXTENSION = ".tmx";
const char * const Constants::FONT_FILE_EXTENSION = ".ttf";

/*
 * COLOR CONST */
const SDL_Color Constants::COLOR_WHITE = Util::createColor(255, 255, 255, 255);
const SDL_Color Constants::COLOR_BLACK = Util::createColor(0, 0, 0, 255);
const SDL_Color Constants::COLOR_RED = Util::createColor(255, 0, 0, 255);
const SDL_Color Constants::COLOR_BLUE = Util::createColor(0, 0, 255, 255);
const SDL_Color Constants::COLOR_GREY = Util::createColor(128, 128, 128, 255);
const SDL_Color Constants::COLOR_GREEN = Util::createColor(0, 255, 0, 255);
const SDL_Color Constants::COLOR_YELLOW = Util::createColor(255, 255, 0, 255);

/*
 * FONT CONST */
const char * const Constants::FONT_JOYSTIX = "joystix_monospace.ttf";

/*
 * IMAGE CONST */
const char * const Constants::IMAGE_TILESET_UNDERWATER = "tileset_underwater.png";

/*
 * SPRITE CONST */
const uint8_t Constants::SPRITE_ALPHA_FULL = 255;
const uint8_t Constants::SPRITE_ALPHA_NONE = 0;

/*
 * MAP CONST */
const char * const Constants::MAP_TEST = "test_map.tmx";

/*
 * WORLD CONST */
const int Constants::WORLD_DRAW_WIDTH = 15;
const int Constants::WORLD_DRAW_HEIGHT = 15;

/*
 * CHARACTER CONST */
const int Constants::CHARACTER_WALK_TIMER = 15;
const int Constants::CHARACTER_WIDTH = 32;
const int Constants::CHARACTER_HEIGHT = 48;
const int Constants::CHARACTER_TILE_OFFSET_X = -16;
const int Constants::CHARACTER_TILE_OFFSET_Y = -32;
const int Constants::CHARACTER_WALK_SPEED = 2;
const int Constants::CHARACTER_RUN_SPEED = 4;
