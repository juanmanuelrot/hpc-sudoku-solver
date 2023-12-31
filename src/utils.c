#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/board.h"
#include "../include/utils.h"

Board* readBoard(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    int miniGridSize;
    fscanf(file, "%d", &miniGridSize);  // Leemos el tamaño de minigrid de la primera fila

    if(miniGridSize < 3){
        printf("Tamaño de minigrid inválido.\n");
        fclose(file);
        return NULL;
    }

    int size = pow(miniGridSize, 2);

    int** matrix = (int**)malloc(size * sizeof(int*));
    if (matrix == NULL) {
        printf("Falló la reserva de memoria.\n");
        fclose(file);
        return NULL;
    }
    int solved=1;
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Falló la reserva de memoria.\n");
            fclose(file);
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return NULL;
        }

        for (int j = 0; j < size; j++){
            int read;
            if(fscanf(file, "%d ", &read) != 1 || read<0 || read>size) {
                if (read<0) {
                    printf("Celda tiene que ser mayor que 0");
                }
                else if(read>size) {
                    printf("Celda tiene que ser menor que %d.\n", size);
                }
                printf("Error al leer celda [%d][%d]\n", i, j);
                fclose(file);
                for (int k = 0; k < i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                return NULL;
            }
            matrix[i][j] = read;
            if(read==0 && solved==1){
                solved=0;
            }
        }
    }

    Board* board = (Board*) malloc(sizeof(Board));
    board->size = size;
    board->n = miniGridSize;
    board->solved = solved;
    board->boardArray = matrix;
    
    fclose(file);  // Close the file
    return board;
}

void printBoard(Board* board){
    int size = (*board).size;

    for(int i=0; i < size; i++){
        for(int j=0; j<size; j++){
            printf("%d ", (*board).boardArray[i][j]);
        }
        printf("\n");
    }
}

Board* copyBoard(Board* board){
    int size = board->size;
    int** matrix = (int**)malloc(size * sizeof(int*));
    if (matrix == NULL) {
        printf("Falló la reserva de memoria.\n");
        return NULL;
    }
    
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Falló la reserva de memoria.\n");
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return NULL;
        }

        for (int j = 0; j < size; j++){
            matrix[i][j] = board->boardArray[i][j];
        }
    }

    Board* newBoard = (Board*) malloc(sizeof(Board));
    newBoard->size = size;
    newBoard->n = board->n;
    newBoard->solved = board->solved;
    newBoard->boardArray = matrix;
    newBoard->boardSolved = NULL;

    if(board->solved){
        int** solvedMatrix = (int**)malloc(size * sizeof(int*));
        if (solvedMatrix == NULL) {
            printf("Falló la reserva de memoria.\n");
            return NULL;
        }
        
        for (int i = 0; i < size; i++) {
            solvedMatrix[i] = (int*)malloc(size * sizeof(int));
            if (solvedMatrix[i] == NULL) {
                printf("Falló la reserva de memoria.\n");
                for (int k = 0; k < i; k++) {
                    free(solvedMatrix[k]);
                }
                free(solvedMatrix);
                return NULL;
            }

            for (int j = 0; j < size; j++){
                solvedMatrix[i][j] = board->boardSolved[i][j];
            }
        }

        board->boardSolved = solvedMatrix;
    }
    
    return newBoard;
}

void deleteBoard(Board* board){
    int size = board->size;

    for(int i=0; i<size; i++){
        free(board->boardArray[i]);

        if(board->boardSolved != NULL){
            free(board->boardSolved[i]);
        }
    }

    free(board->boardArray);
    if(board->boardSolved != NULL){
        free(board->boardSolved);
    }
    free(board);
}

