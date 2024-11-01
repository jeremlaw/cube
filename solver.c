/**************************************************************
 *
 *                     solver.c
 *
 *     Rubik's Cube solving program, using the CFOP method.
 *
 **************************************************************/
#include <stdio.h>
#include "cube.h"
#include "moves.h"

int main()
{   
    printf("\n");
    Cube *cube = newCube();
    display(cube);
    freeCube(cube);
}
