# Makefile for Rubik's Cube Simulator and Solver
#
# Created October 31, 2024

############## Variables ###############

CC = gcc # The compiler being used
CFLAGS = -g # Compiler flags
RM = rm -f # Command to remove files

TARGET1 = cubesim # Target executable 1
TARGET2 = solver # Target executable 2
OBJS1 = cube.o moves.o cubesim.o white_cross.o # Object files needed for target 1
OBJS2 = cube.o moves.o white_cross.o solver.o  # Object files needed for target 2

############### Rules ###############

all: cubesim solver

## Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


## Linking step (.o -> executable program)

$(TARGET1): $(OBJS1) 
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET2): $(OBJS2) 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJS1) $(OBJS2)