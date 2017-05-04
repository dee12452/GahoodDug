#ifndef GAHOOD_GAME_H
#define GAHOOD_GAME_H

typedef enum GameState {
    GAME_STATE_PLAY,
    GAME_STATE_EXIT
} GameState;

void gahood_gameRun(int, char **);
enum GameState gahood_gameGetGameState();
void gahood_gameSetGameState(enum GameState);

#endif
