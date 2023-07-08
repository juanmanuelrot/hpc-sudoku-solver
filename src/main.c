#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "board.h"
#include "sequential.h"
#include "parallel.h"
#include "trivialSimplify.h"
#include <limits.h>
#include <omp.h>

int main(int argc, char *argv[]){
    if(argc<3 || argc>4 || (argc == 3 && (*argv[2]) == '1')){
        printf("Error: Missing arguments\n");
        printf("Run as: ./sudoku_solver <input_file> <mode> [num_threads]\n");
        printf("MODE: 0 for sequential, 1 for parallel\n");
        exit(1);
    } 
    Board* board = readBoard(argv[1]);
    if (board!=NULL){
        printf("Board input read\n");
        printBoard(board);
        if(board->solved==1){
            printf("Board is already solved\n");
            return 0;
        }
        if(strcmp(argv[2],"0")==0){
            printf("Running sequential mode\n");

            clock_t start = clock();
            int solved = solve_sequential(board);
            clock_t end = clock();
            
            double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
            if (solved) { printf("Board solved\n"); printf("Is valid? %d\n", is_resolved(board));}
            else { printf("Board not solved\n"); }
            printBoard(board);
            printf("Elapsed time: %f seconds\n", elapsed_time);
        }
        else if(strcmp(argv[2],"1")==0){
            printf("Running parallel mode\n");
            char* p;
            long arg = strtol(argv[3], &p, 10);
            if (*p != '\0' || arg < INT_MIN || arg > INT_MAX) {
                printf("Invalid number of threads");
                return 1; // In main(), returning non-zero means failure
            }

            int numThreads = arg;
            printf("Num threads %d\n", numThreads);
            omp_set_num_threads(numThreads);
            printf("Llegamos a aca");
            Board* solvedBoard = (Board*) malloc(sizeof(Board));
            solvedBoard->solved = 0;
            double elapsed_time;
            int found_solution = 0;

            #pragma omp parallel firstprivate(board, solvedBoard) shared(elapsed_time, found_solution)
            {
                #pragma omp master
                {
                    clock_t start = clock();
                    
                    #pragma omp taskgroup
                    {
                        #pragma omp task
                            solve_parallel(board, solvedBoard, 10, &found_solution);
                    }
                    clock_t end = clock();
                    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
                }
            }

            if(solvedBoard->solved){
                printf("Board solved\n");
                printBoard(solvedBoard);
                printf("Is valid? %d", is_resolved(solvedBoard));
                printf("Elapsed time: %f seconds\n", elapsed_time);
            } else {
                printf("Board not solved\n");
            }
        }
        else{
            printf("Error: Invalid mode\n");
            printf("MODE: 0 for sequential, 1 for parallel\n");
            exit(1);
        }
    }
}