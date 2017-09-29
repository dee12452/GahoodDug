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
    static const char * const GAME_RES_FOLDER;
    static const char * const GAME_IMAGE_FOLDER;
	static const char * const GAME_TILESET_FOLDER;
    /******************
     ******************/


    /*
     **********************************
     * Game Constants
     **********************************
     */
    static const char * const IMAGE_FILE_EXTENSION;
    static const char * const TILESET_FILE_EXTENSION;
    static const char * const MAP_FILE_EXTENSION;
    /******************
     ******************/

    
    /*
     **********************************
     * Image Constants
     **********************************
     */
    //First images to be loaded when the game launches
    static const char * const IMAGES_FIRST_TO_LOAD[];
    static const int IMAGES_FIRST_TO_LOAD_COUNT;
    
    //Image Ids for the sprite sheet map
    static const std::string IMAGE_ID_TEST;
	static const std::string IMAGE_TILESET_UNDERWATER;
	static const std::string IMAGE_CHARACTER_1;
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
	
    //Dimensions of sprites in the texture sheets
	static const int SPRITE_TILE_WIDTH;
	static const int SPRITE_TILE_HEIGHT;
	static const int SPRITE_CHARACTER_WIDTH;
	static const int SPRITE_CHARACTER_HEIGHT;
	static const int SPRITE_CHARACTER_X;
	static const int SPRITE_CHARACTER_Y;
	
    //Character texture sheets rows of facing
	static const uint8_t SPRITE_CHARACTER_FACE_DOWN;
	static const uint8_t SPRITE_CHARACTER_FACE_UP;
	static const uint8_t SPRITE_CHARACTER_FACE_LEFT;
	static const uint8_t SPRITE_CHARACTER_FACE_RIGHT;
	/******************
	******************/

	/*
	**********************************
	* Map File Constants
	**********************************
	*/
	static const char * const MAP_FILE_TEST;
	/******************
	******************/
	
	/*
	**********************************
	* Map Constants
	**********************************
	*/
	//Layers
	static const uint8_t MAP_MAX_LAYERS;
	
    //Tile constants
	static const uint8_t MAP_NUM_TILES_WIDTH;
	static const uint8_t MAP_NUM_TILES_HEIGHT;
	static const std::string TILE_TYPE_WALL;
	static const std::string TILE_TYPE_FLOOR;
	/******************
	******************/

	/*
	**********************************
	* Game Object Types
	**********************************
	*/
	static const std::string OBJECT_TYPE_PLAYER;
	/******************
	******************/

private:
	Constants() {}
	~Constants() {}
};

#endif
