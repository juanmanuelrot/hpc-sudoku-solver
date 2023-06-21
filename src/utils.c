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
            if(fscanf(file, "%d ", &read) != 1) {
                printf("Error al leer celda [%d][%d]", i, j);
                fclose(file);
                for (int k = 0; k <= i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                return NULL;
            }
            matrix[i][j] = read;
        }
    }

    Board* board = (Board*) malloc(sizeof(Board));
    board->size = size;
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
