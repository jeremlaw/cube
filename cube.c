/**************************************************************
 *
 *                     cube.c
 *
 *     This file contains the implementation of the cube
 *     initializer in cube.h.
 *
 **************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "cube.h"

/********** newCube ********
 *
 *      Creates and initializes a new cube
 *
 *      Notes: 
 *          Allocates memory on the heap
 *          Throws runtime error if malloc fails
 *      
 ******************************/
Cube *newCube()
{
    Cube *cube = malloc(sizeof(Cube));
    assert(cube);

    for (Color face = WHITE; face <= ORANGE; face++) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                cube->faces[face][row][col] = face;
            }
        }
    }
    return cube;
}

/********** freeCube ********
 *
 *      Frees heap memory allocated by newCube
 *
 *      Note:
 *          Given cube becomes NULL when freeCube is called
 *          Throws runtime error if given cube pointer is NULL
 *      
 ******************************/
void freeCube(Cube *cube)
{
    assert(cube);
    free(cube);
}