#!/bin/bash
#SBATCH --job-name=sudoku-solve
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=80
#SBATCH --mem=4096
#SBATCH --time=2:00:00
#SBATCH --partition=normal
#SBATCH --qos=normal
#SBATCH --mail-type=ALL
#SBATCH --mail-user=jmlolo00@gmail.com

source /etc/profile.d/modules.sh

cd ~/hpc-sudoku-solver
./sudoku_solver boards/hard16x16.txt 1 75