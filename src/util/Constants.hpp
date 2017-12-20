#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <stdint.h>
#include <string>

struct SDL_Color;

class Constants {
public:
    /*
     **********************************
     * Window Constants
     **********************************
     */
    static const char * GAME_TITLE;
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const uint32_t WINDOW_FLAGS;
    /******************
     ******************/


    /*
     **********************************
     * Game Constants
     **********************************
     */
    static const uint8_t GAME_BACKGROUND_LOOP_DELAY;
    static const uint8_t GAME_LOOP_DELAY;
	static const uint16_t TARGET_TICKS_PER_SECOND;
    static const uint8_t TARGET_FPS;
    static const char * const GAME_THREAD_NAME;
    static const char * const GAME_RES_FOLDER;
    /******************
     ******************/


    /*
     **********************************
     * File Constants
     **********************************
     */
    //File extensions
    static const char * const IMAGE_FILE_EXTENSION;
    static const char * const TILESET_FILE_EXTENSION;
    static const char * const MAP_FILE_EXTENSION;
    static const char * const FONT_FILE_EXTENSION;
    
    //Font files
    static const char * const FONT_JOYSTIX;
    
    //Image files
    static const char * const IMAGE_TILESET_UNDERWATER;
    static const char * const IMAGE_TILESET_BOAT;
    static const char * const IMAGE_TILESET_OUTSIDE;
    /******************
     ******************/

    
    /*
     **********************************
     * Color Constants
     **********************************
     */
	static const SDL_Color COLOR_BLACK;
	static const SDL_Color COLOR_WHITE;
	static const SDL_Color COLOR_GREY;
	static const SDL_Color COLOR_RED;
	static const SDL_Color COLOR_BLUE;
	static const SDL_Color COLOR_GREEN;
	static const SDL_Color COLOR_YELLOW;
    /******************
	******************/
    
    /*
     **********************************
     * Sprite Constants
     **********************************
     */
	//Alpha constants for the sprite
    static const uint8_t SPRITE_ALPHA_FULL;
    static const uint8_t SPRITE_ALPHA_NONE;
	/******************
	******************/
    
    /*
     **********************************
     * Map Constants
     **********************************
     */
	//Maps
    static const char * const MAP_TEST;
    static const char * const MAP_TEST_2;
    static const char * const MAP_PALLET_TOWN;
	static const char * const MAP_ROUTE_1;
	//Tile types
    static const std::string TILE_TYPE_FLOOR;
    static const std::string TILE_TYPE_WALL;
	static const std::string TILE_TYPE_WATER;
	static const std::string TILE_TYPE_GRASS;
	static const std::string TILE_TYPE_FLOWER;
	static const std::string TILE_TYPE_SIGN;
	static const std::string TILE_TYPE_DOOR;
	static const std::string TILE_TYPE_CLIFF;
    /******************
	******************/
    
    /*
     **********************************
     * World Constants
     **********************************
     */
    static const int WORLD_DRAW_WIDTH;
    static const int WORLD_DRAW_HEIGHT;
	static const unsigned int WORLD_MAP_NAME_ANIM_TICK_TIME;
    /******************
	******************/
    
    /*
     **********************************
     * Character Constants
     **********************************
     */
    static const int CHARACTER_WALK_TIMER;
    static const int CHARACTER_WIDTH;
    static const int CHARACTER_HEIGHT;
    static const int CHARACTER_TILE_OFFSET_X;
    static const int CHARACTER_TILE_OFFSET_Y;
    static const int CHARACTER_WALK_SPEED;
    static const int CHARACTER_RUN_SPEED;
    /******************
	******************/

private:
	Constants() {}
	~Constants() {}

};

#endif
