#ifndef GAHOOD_UTIL_H
#define GAHOOD_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <pthread.h>

/* *************************
 * Util macros
 * *************************
 */

/* Delays in milliseconds */
#define DELAY_GAME_LOOP 10
#define DELAY_RENDER_LOOP 10

/* Window information */
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "GahoodTanks"

/* Colors and Alpha */
#define FULL_ALPHA 255
#define NO_ALPHA 0

/* *************************
 * Util consts and enums 
 * *************************
 */

/* The Window Flags */
extern const uint32_t WINDOW_FLAGS;

/* Game States */
typedef enum GameState { 
    GAME_STATE_PLAY, 
    GAME_STATE_EXIT,
    GAME_STATE_MENU
} GameState;


/* *************************
 * Util methods 
 * *************************
 */
void gahood_utilFatalError(const char *);
void gahood_utilFatalSDLError(const char *);

#endif
