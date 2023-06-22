#include <stdio.h>
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
    for(int i=0; i<(*board).size; i++){
        if((*board).boardArray[row][i] == value){
            return 0;
        }
    }
    return 1;
}
int isValidColumn(Board* board, int row, int col, int value){
    for(int i=0; i<(*board).size; i++){
        if((*board).boardArray[i][col] == value){
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
            if((*board).boardArray[i][j] == value){
                return 0;
            }
        }
    }
    return 1;
}
int isValidBoard(Board* board, int row, int col, int value){
    return isValidRow(board, row, col, value) && isValidColumn(board, row, col, value) && isValidSquare(board, row, col, value);
}

void find_empty(Board* board, int* row, int* col){
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