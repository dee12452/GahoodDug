#ifndef GAHOOD_GAME_H
#define GAHOOD_GAME_H

void gahood_gameRun(int, char **);
enum GameState gahood_gameGetGameState();
void gahood_gameSetGameState(enum GameState);

#endif
