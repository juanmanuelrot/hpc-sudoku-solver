#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "../include/board.h"

int main(int argc, char *argv[]){
    Board* board = readBoard(argv[1]);
    printBoard(board);
}