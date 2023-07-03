#include <stdio.h>
#include <stdlib.h>
#include "../include/solver.h"

int finished(Board* board){
    int size = (*board).size;
    for(int i=0; i < size; i++){
        for(int j=0; j<size; j++){
            if((*board).boardArray[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}
int isValidRow(Board* board, int row, int col, int value){
    for(int j=0; j<(*board).size; j++){
        if((*board).boardArray[row][j] == value && j != col){
            return 0;
        }
    }
    return 1;
}
int isValidColumn(Board* board, int row, int col, int value){
    for(int i=0; i<(*board).size; i++){
        if((*board).boardArray[i][col] == value  && i != row){
            return 0;
        }
    }
    return 1;
}
int isValidSquare(Board* board, int row, int col, int value){
    int n = (*board).n;
    int rowStart = row - row % n;
    int colStart = col - col % n;
    for(int i=rowStart; i<rowStart+n; i++){
        for(int j=colStart; j<colStart+n; j++){
            if((*board).boardArray[i][j] == value && i != row && j != col){
                return 0;
            }
        }
    }
    return 1;
}
int isValidBoard(Board* board, int row, int col, int value){
    return isValidRow(board, row, col, value) && isValidColumn(board, row, col, value) && isValidSquare(board, row, col, value);
}

int find_empty(Board* board, int* row, int* col){
	for (int i = 0; i < board->size; ++i)
	{
		for (int j = 0; j < board->size; ++j)
		{
			if ((*board).boardArray[i][j] == 0)
			{
				*row = i;
                *col = j;
				return 0;
			}
		}
	}
	return 1;
	
}

int* findPossibleValues(Board* board, int row, int column){
    int* array = (int*) malloc((board->size + 1) * sizeof(int));

    for(int k=1; k <= board->size; k++){
        array[k] = 1;
    }

    for(int k=0; k<board->size; k++){
        if(board->boardArray[k][column] != 0){
            array[board->boardArray[k][column]] = 0;
        }

        if(board->boardArray[row][k] != 0){
            array[board->boardArray[row][k]] = 0;
        }
    }

    int miniGridRowNumber = (row/board->n)*board->n;
    int miniGridColumnNumber = (column/board->n)*board->n;

    for(int i=miniGridRowNumber; i<miniGridRowNumber+board->n; i++){
        for(int j=miniGridColumnNumber; j<miniGridColumnNumber+board->n; j++){
            if(board->boardArray[i][j] != 0){
                array[board->boardArray[i][j]] = 0;
            }
        }
    }

    return array;
}

int is_resolved(Board* board){
    int size = (*board).size;
    for(int i=0; i < size; i++){
        for(int j=0; j<size; j++){
            if((*board).boardArray[i][j] == 0 || !isValidBoard(board, i, j, (*board).boardArray[i][j])){
                return 0;
            }
        }
    }
    return 1;
}