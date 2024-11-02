/**************************************************************
 *
 *                     white_cross.c
 *
 *     This file contains the implementation of the white_cross
 *     interface, which consists of the daisy and white_cross
 *     functions.
 *
 **************************************************************/
#include <stdbool.h>
#include "white_cross.h"
#include "moves.h"

/********** numPetals ********
 *
 *      Returns the number of white edges around the yellow center
 *  
 ******************************/
static int numPetals(Cube *cube)
{   
    int petalCount = 0;
    Face top = cube->Top;
    for (int i = 0; i < 2; i++) {
        if (top[i][i + 1] == WHITE) {
            petalCount++;
        }
        if (top[i + 1][i] == WHITE) {
            petalCount++;
        }
    }
    return petalCount;
}

static void placePetal1(Cube *cube)
{
    
}