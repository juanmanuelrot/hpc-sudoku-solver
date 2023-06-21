#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "../include/board.h"
#include "../include/sequential.h"
#include "../include/parallel.h"

int main(int argc, char *argv[]){
    if(argc<3 || argc>3){
        printf("Error: Missing arguments\n");
        printf("Run as: ./myproject <input_file> <mode>\n");
        printf("MODE: 0 for sequential, 1 for parallel\n");
        return 1;
    } 
    Board* board = readBoard(argv[1]);
    printf("Board input read\n");
    printBoard(board);
    if(strcmp(argv[2],"0")==0){
        printf("Running sequential mode\n");

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