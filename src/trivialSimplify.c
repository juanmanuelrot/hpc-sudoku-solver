#include <stdio.h>
#include <omp.h>
#include "../include/trivialSimplify.h"

int applyElimination(Board* board){
    const miniGridSize = board->n;
    const size = board->size;
    int changed = 0;
    int blockIter;
    // #pragma omp parallel for shared(changed) schedule(dynamic)
        for(blockIter=0; blockIter<size; blockIter++){

            int ib = (blockIter/miniGridSize) * miniGridSize; // La division es entera por lo que el resultado no es i
            int jb = (blockIter % miniGridSize) * miniGridSize;

            int missingCount = 0;
            int* missingPointer;
            int usedNumbers[size+1];
            for(int k=1; k<=size; k++){
                usedNumbers[k] = 0;
            }

            for(int i=ib; i<(ib+miniGridSize); i++){
                for(int j=jb; j<(jb+miniGridSize); j++){
                    if(board->boardArray[i][j] == 0){
                        missingCount++;
                        missingPointer = &board->boardArray[i][j];
                    } else {
                        usedNumbers[board->boardArray[i][j]] = 1;
                    }
                }
            }

            if(missingCount == 1){
                int numberToPlace;
                for(int k=1; k<=size; k++){
                    if(usedNumbers[k] == 0){
                        numberToPlace = k;
                        break;
                    }
                }
                *missingPointer = numberToPlace;
                changed = 1;
            }

            if(ib == jb){ //es un bloque de la diagonal
                //eliminamos en columnas
                for(int columnIndex=jb; columnIndex < jb + miniGridSize; columnIndex++){
                    int missingCount = 0;
                    int* missingPointer;
                    int usedNumbers[size+1];
                    for(int k=1; k<=size; k++){
                        usedNumbers[k] = 0;
                    }

                    for(int i=0; i<size; i++){
                        if(board->boardArray[i][columnIndex] == 0){
                            missingCount++;
                            missingPointer = &board->boardArray[i][columnIndex];
                        } else {
                            usedNumbers[board->boardArray[i][columnIndex]] = 1;
                        } 
                    }

                    if(missingCount == 1){
                        int numberToPlace;
                        for(int k=1; k<=size; k++){
                            if(usedNumbers[k] == 0){
                                numberToPlace = k;
                                break;
                            }
                        }
                        *missingPointer = numberToPlace;
                        changed = 1;
                    }
                }

                //eliminamos en filas
                for(int rowIndex=0; rowIndex < miniGridSize; rowIndex++){
                    int missingCount = 0;
                    int* missingPointer;
                    int usedNumbers[size+1];
                    for(int k=1; k<=size; k++){
                        usedNumbers[k] = 0;
                    }

                    for(int j=0; j<size; j++){
                        if(board->boardArray[ib+rowIndex][j] == 0){
                            missingCount++;
                            missingPointer = &board->boardArray[ib+rowIndex][j];
                        } else {
                            usedNumbers[board->boardArray[ib+rowIndex][j]] = 1;
                        } 
                    }

                    if(missingCount == 1){
                        int numberToPlace;
                        for(int k=1; k<=size; k++){
                            if(usedNumbers[k] == 0){
                                numberToPlace = k;
                                break;
                            }
                        }
                        *missingPointer = numberToPlace;
                        changed = 1;
                    }
                }
            }
        }

    return changed;
}
