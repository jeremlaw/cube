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
    Cube *cube = newCube();
    printCube(cube);
    U(cube);
    printCube(cube);
    freeCube(cube);
}
