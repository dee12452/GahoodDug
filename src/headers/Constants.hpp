#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <stdint.h>
#include <string>

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
    static const uint8_t GAME_LOOP_DELAY;
    static const uint8_t RENDER_LOOP_DELAY;
    static const uint8_t TARGET_FPS;
    static const char * const GAME_THREAD_NAME;
    static const char * const GAME_IMAGE_FOLDER;
	static const char * const GAME_TILESET_FOLDER;
    /******************
     ******************/

    
    /*
     **********************************
     * Image Ids
     **********************************
     */
    static const std::string IMAGE_ID_TEST;
	static const std::string IMAGE_TILESET_UNDERWATER;
	static const std::string IMAGE_CHARACTER_1;
    
    /*
     **********************************
     * Sprite Constants
     **********************************
     */
	//Alpha constants for the sprite
    static const uint8_t SPRITE_ALPHA_FULL;
    static const uint8_t SPRITE_ALPHA_NONE;
	//Width of characters in the texture sheets
	static const uint8_t SPRITE_CHARACTER_WIDTH;
	static const uint8_t SPRITE_CHARACTER_HEIGHT;
	//Character texture sheets rows of facing
	static const uint8_t SPRITE_CHARACTER_FACE_DOWN;
	static const uint8_t SPRITE_CHARACTER_FACE_UP;
	static const uint8_t SPRITE_CHARACTER_FACE_LEFT;
	static const uint8_t SPRITE_CHARACTER_FACE_RIGHT;

    /*
     **********************************
     * Sprite Constants
     **********************************
     */
    static const int TILE_WIDTH;
    static const int TILE_HEIGHT;

	/*
	**********************************
	* Map File Constants
	**********************************
	*/
	static const char * const MAP_FILE_TEST;
	
	/*
	**********************************
	* Map Constants
	**********************************
	*/
	static const uint8_t MAP_MAX_LAYERS;
	static const uint8_t MAP_NUM_TILES_WIDTH;
	static const uint8_t MAP_NUM_TILES_HEIGHT;

private:
	Constants() {}
	~Constants() {}
};

#endif
