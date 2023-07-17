#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "../include/parallel.h"
#include "../include/trivialSimplify.h"

void solve_parallel(Board* board, Board* solvedBoard, int* found_solution, int num_threads, int num_tasks) {
    // while(applyElimination(board));
    // printf("Funcion\n");
    if(*found_solution){
        deleteBoard(board);
        return;
    }

    if(finished(board)){
        if(is_resolved(board)){
            printf("Encontramos");
            solvedBoard->solved = 1;
            solvedBoard->n = board->n;
            solvedBoard->size = board->size;
            solvedBoard->boardSolved = board->boardArray;
            solvedBoard->boardArray = board->boardArray;
            free(board);

            *found_solution = 1;
            return;

        } else {
            deleteBoard(board);
            return;
        }
        
    }

    if(*found_solution){
        deleteBoard(board);
        return;
    }

    int i;
    int j;
    find_empty(board, &i, &j);

    // printf("Found empty %d %d\n", i, j);

    int* possibleValues = findPossibleValues(board, i, j);

    if(*found_solution){
        deleteBoard(board);
        return;
    }
    for(int k=1; k <= board->size; k++){
        // printf("k %d %d\n", k, possibleValues[k]);
        if(possibleValues[k] == 1){
            Board* boardCopy = copyBoard(board);
            boardCopy->boardArray[i][j] = k;
            if (num_tasks < num_threads) {
                #pragma omp atomic update
                num_tasks++;
                #pragma omp task 
                solve_parallel(boardCopy, solvedBoard, found_solution, num_threads, num_tasks);
                #pragma omp atomic update
                num_tasks--;
            }else{
                solve_parallel(boardCopy, solvedBoard, found_solution, num_threads, num_tasks);
            }
        }
    } 
    free(possibleValues);
    deleteBoard(board);
}