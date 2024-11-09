/**************************************************************
 *
 *                     solver.c
 *
 *     Rubik's Cube solving program, using the CFOP method.
 *
 **************************************************************/
#include <stdio.h>
#include "moves.h"
#include "white_cross.h"

int main()
{
    printf("Hello world!\n");
    Cube *cube = newCube();
    printf("Welcome to the cube solver! This is your cube:\n\n");
    
    display(cube);
    daisy(cube);
    display(cube);
    white_cross(cube);
    display(cube);
    freeCube(cube);
}