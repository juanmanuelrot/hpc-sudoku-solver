#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "board.h"
#include "sequential.h"
#include "parallel.h"

int main(int argc, char *argv[]){
    if(argc<3 || argc>3){
        printf("Error: Missing arguments\n");
        printf("Run as: ./myproject <input_file> <mode>\n");
        printf("MODE: 0 for sequential, 1 for parallel\n");
        return 1;
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
            if (solved) { printf("Board solved\n"); }
            else { printf("Board not solved\n"); }
            printBoard(board);
            printf("Elapsed time: %f seconds\n", elapsed_time);
        }
        else if(strcmp(argv[2],"1")==0){
            printf("Running parallel mode\n");
        }
        else{
            printf("Error: Invalid mode\n");
            printf("MODE: 0 for sequential, 1 for parallel\n");
            return 1;
        }
    }
}