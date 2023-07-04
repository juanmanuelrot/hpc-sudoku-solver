#ifndef PARALLEL_H
#define PARALLEL_H

#include "board.h"
#include "utils.h"
#include "solver.h"

void solve_parallel(Board* board, Board* solvedBoard, int priority, int* found_solution);

#endif;