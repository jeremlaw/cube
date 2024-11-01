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
    // R(cube);
    // U(cube);
    // Rp(cube);
    // Up(cube);
    // Rp(cube);
    // F(cube);
    // R2(cube);
    // Up(cube);
    // Rp(cube);
    // Up(cube);
    // R(cube);
    // U(cube);
    // Rp(cube);
    // Fp(cube);
    F(cube);
    

    display(cube);
    freeCube(cube);
}
