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
#include <stdlib.h>
#include <stdio.h>
#include "white_cross.h"
#include "moves.h"

typedef struct {
    int row, col;
    bool valid;
} Petal;

/********** numPetals ********
 *
 *      Returns the number of white edges around the yellow center
 *  
 ******************************/
static int numPetals(Cube *cube)
{   
    int petalCount = 0;
    Face *top = &((*cube)[TOP]);
    for (int i = 0; i < 2; i++) {
        if ((*top)[i][i + 1] == WHITE) {
            petalCount++;
        }
        if ((*top)[i + 1][i] == WHITE) {
            petalCount++;
        }
    }
    return petalCount;
}

static Petal getPetal(Cube *cube, Side side)
{
    /* Check for petals in (1,0) and (1,2) */
    for (int i = 0; i < 3; i += 2) {
        if ((*cube)[side][1][i] == WHITE) {
            Petal p = { 1, i, true };
            return p;
        }
    }
    /* Check for petals in (0,1) and (2,1) */
    for (int i = 0; i < 3; i += 2) {
        if ((*cube)[side][i][1] == WHITE) {
            Petal p = { i, 1, true };
            return p;
        }
    }
    /* If no petal found, return invalid petal */
    Petal p = { 0, 0, false };
    return p;
}

static void moveDaisy(Cube *cube, int row, int col)
{  
    while ((*cube)[TOP][row][col] == WHITE) {
        U(cube);
        display(cube);
    }
}

static void placePetal(Petal *petal, Side side, Cube *cube)
{
    /* Petals in col 1 need to be moved to col 0 or 2 */
    if (petal->col == 1) {

        if (side == FRONT) {
            moveDaisy(cube, 2, 1);
            F(cube);
            display(cube);
        }
        else if (side == LEFT) {
            moveDaisy(cube, 1, 0);
            L(cube);
            display(cube);
        }
        else if (side == RIGHT) {
            moveDaisy(cube, 1, 2);
            R(cube);
            display(cube);
        }
        else if (side == BACK) {
            moveDaisy(cube, 0, 1);
            B(cube);
            display(cube);
        }
    }

    /* Special case: bottom petals can be moved in one move
     * after moving the daisy */
    if (side == BOTTOM) {
        moveDaisy(cube, petal->row, petal->col);
        if (petal->row == 0) {
            F2(cube);
            display(cube);
        }
        else if (petal->row == 2) {
            B2(cube);
            display(cube);
        }
        else if (petal->col == 0) {
            L2(cube);
            display(cube);
        }
        else if (petal->col == 2) {
            R2(cube);
            display(cube);
        }
        return;
    }
    
    if (side == FRONT) {
        moveDaisy(cube, 1, petal->col);
        if (petal->col == 0) {
            Lp(cube);
            display(cube);
        } else {
            R(cube);
            display(cube);
        }
        return;
    }
    if (side == LEFT) {
        moveDaisy(cube, petal->col, 1);
        if (petal->col == 0) {
            Bp(cube);
            display(cube);
        } else {
            F(cube);
            display(cube);
        }
        return;
    }
    if (side == RIGHT) {
        moveDaisy(cube, 2 - petal->col, 1);
        if (petal->col == 0) {
            Fp(cube);
            display(cube);
        } else {
            B(cube);
            display(cube);
        }
        return;
    }
    if (side == BACK) {
        moveDaisy(cube, 1, petal->col);
        if (petal->col == 0) {
            L(cube);
            display(cube);
        } else {
            Rp(cube);
            display(cube);
        }
        return;
    }
}

static void findPetal(Cube *cube)
{
    Petal petal;
    int iter = 0;
    while (numPetals(cube) < 4) {
        for (Side side = LEFT; side <= BOTTOM; side++) {
            if (side != TOP) {
                petal = getPetal(cube, side);

                if (petal.valid) {
                    iter++;
                    placePetal(&petal, side, cube);
                    //display(cube);
                }
            }
        }
        if (iter == 100) {
            break;
        }
    }
}

void daisy(Cube *cube)
{
    findPetal(cube);
}

void white_cross(Cube *cube)
{
    while ((*cube)[LEFT][0][1] != (*cube)[LEFT][1][1]) {
        U(cube);
        display(cube);
    }
    L2(cube);
    display(cube);

    while ((*cube)[FRONT][0][1] != (*cube)[FRONT][1][1] &&
           (*cube)[TOP][2][1] != WHITE) {
        U(cube);
        display(cube);
    }
    F2(cube);
    display(cube);

    while ((*cube)[RIGHT][0][1] != (*cube)[RIGHT][1][1] &&
           (*cube)[TOP][1][2] != WHITE) {
        U(cube);
        display(cube);
    }
    R2(cube);
    display(cube);

    while ((*cube)[BACK][2][1] != (*cube)[BACK][1][1] &&
           (*cube)[TOP][0][1] != WHITE) {
        U(cube);
        display(cube);
    }
    B2(cube);
    display(cube);
}