/**************************************************************
 *
 *                     moves.co
 *
 *     This file contains the implementation for all the legal
 *     moves that can be performed on a Rubik's Cube.
 *     
 **************************************************************/
#include <stdio.h>
#include "moves.h"

void U(Cube *cube)
{
    Color temp[3];
    for (int col = 0; col < 3; col++) {
        temp[col] = cube->Front[0][col];
    }

    for (int col = 0; col < 3; col++) {
        cube->Front[0][col] = cube->Right[0][col];
        cube->Right[0][col] = cube->Back[0][col];
        cube->Back[0][col] = cube->Left[0][col];
        cube->Left[0][col] = temp[col];
    }
}