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
const char * const Constants::GAME_RES_FOLDER = "../res";

/*
 * FILE EXTENSIONS CONST */
const char * const Constants::IMAGE_FILE_EXTENSION = ".png";
const char * const Constants::TILESET_FILE_EXTENSION = ".tsx";
const char * const Constants::MAP_FILE_EXTENSION = ".tmx";
const char * const Constants::FONT_FILE_EXTENSION = ".ttf";

/*
 * FONT CONST */
const char * const Constants::FONT_JOYSTIX = "joystix_monospace.ttf";

/*
 * IMAGE CONST */
const char * const Constants::IMAGES_FIRST_TO_LOAD[] = {  }; 
const int Constants::IMAGES_FIRST_TO_LOAD_COUNT = 0;

/*
 * SPRITE CONST */
const uint8_t Constants::SPRITE_ALPHA_FULL = 255;
const uint8_t Constants::SPRITE_ALPHA_NONE = 0;
