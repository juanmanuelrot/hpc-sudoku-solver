#ifndef solver
#define solver
#include "board.h"

int finished(Board*);  
int isValidRow(Board* board, int row, int col, int value);
int isValidColumn(Board* board, int row, int col, int value);
int isValidSquare(Board* board, int row, int col, int value);
int isValidBoard(Board* board, int row, int col, int value);
int find_empty(Board* board, int* row, int* col);
int* findPossibleValues(Board* board, int row, int column);
int is_resolved(Board* board);
#endif