#ifndef UTILS_H
#define UTILS_H

#include "board.h"

Board* readBoard(char*);
void printBoard(Board*);
Board* copyBoard(Board*);
void deleteBoard(Board*);

#endif