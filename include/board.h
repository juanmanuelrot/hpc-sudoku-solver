#ifndef BOARD_H
#define BOARD_H

typedef struct {
    int size;
    int n;
    int** boardArray;
    int** boardSolved;
    int solved;
} Board;

#endif