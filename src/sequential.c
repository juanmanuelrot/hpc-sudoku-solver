#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/sequential.h"

int solve_sequential(Board* board)
{
	if (board->solved) { return 1; }

	if (finished(board)){   // base case
        board->solved = 1;
		board->boardSolved = board->boardArray;
		return 1;
    }
    
	int row;
	int col;
	find_empty(board, &row, &col);
    int value;
	for (value=1; value <= board->size; ++value){
		if (isValidBoard(board, row, col, value))
		{
			board->boardArray[row][col]=value;

			if (solve_sequential(board)) { return 1; }
			else { board->boardArray[row][col]=0; }   // Backtrack to the most recently filled cell
		}
	}
	return 0;
}