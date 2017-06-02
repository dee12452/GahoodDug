#ifndef GAHOOD_FILE_UTIL_H
#define GAHOOD_FILE_UTIL_H

struct SDL_RWops;

struct SDL_RWops * gahood_fileUtilOpenFile(const char *);
char * gahood_fileUtilReadLine(struct SDL_RWops *);
char * gahood_fileUtilGetWordFromLine(char *, int);

#endif
