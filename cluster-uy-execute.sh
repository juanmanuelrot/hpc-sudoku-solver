#!/bin/bash
#SBATCH --job-name=sudoku-solve
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=32
#SBATCH --mem=4096
#SBATCH --time=8:00:00
#SBATCH --partition=normal
#SBATCH --qos=normal
#SBATCH --mail-type=ALL
#SBATCH --mail-user=jmlolo00@gmail.com

source /etc/profile.d/modules.sh

cd ~/hpc-sudoku-solver
chmod +x sudoku_solver
./sudoku_solver boards/hard25x25.txt 1 32