#include <stdio.h>
#include <stdlib.h>
#include "../include/parallel.h"
#include "../include/trivialSimplify.h"

void solve_parallel(Board* board, Board* solvedBoard) {
    while(applyElimination(board));

    if(finished(board)){
        if(is_resolved(board)){
            solvedBoard->solved = 1;
            solvedBoard->n = board->n;
            solvedBoard->size = board->size;
            solvedBoard->boardSolved = board->boardArray;
            solvedBoard->boardArray = board->boardArray;
            free(board);
            return;
        } else {
            deleteBoard(board);
            return;
        }
        
    }

    int i;
    int j;
    find_empty(board, &i, &j);

    // printf("Found empty %d %d\n", i, j);

    int* possibleValues = findPossibleValues(board, i, j);

    for(int k=1; k <= board->size; k++){
        // printf("k %d %d\n", k, possibleValues[k]);
        if(possibleValues[k] == 1){
            Board* boardCopy = copyBoard(board);
            boardCopy->boardArray[i][j] = k;
            #pragma omp task untied
                solve_parallel(boardCopy, solvedBoard);
        }
    } 
    free(possibleValues);
    deleteBoard(board);
}