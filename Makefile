# Makefile for Rubik's Cube Simulator and Solver
#
# Created October 31, 2024

############## Variables ###############

CC = gcc # The compiler being used
CFLAGS = -g # Compiler flags
RM = rm -f # Command to remove files

TARGET = cubesim # Target executable
OBJS = cube.o cubesim.o moves.o # Object files needed for target 

############### Rules ###############

all: cubesim

## Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


## Linking step (.o -> executable program)

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJS)