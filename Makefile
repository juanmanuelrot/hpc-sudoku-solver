CC = gcc
CFLAGS = -Wall -Iinclude
LDLIBS = -lm
OBJ_DIR = obj
SRC_DIR = src
INCLUDE_DIR = include

# List your source files here (excluding main.c)
SRC_FILES = utils.c main.c sequential.c solver.c

# Create the corresponding object file names
OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Main target
all: sudoku_solver

# Rule to build the executable
sudoku_solver: $(OBJ_DIR)/main.o $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for main.o (located in the source directory)
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Create the obj directory if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

# Clean rule to remove object files and the executable
clean:
	rm -rf $(OBJ_DIR) sudoku_solver