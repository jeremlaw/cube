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

static Color CWPetal(Face *top, int row, int col)
{
    if (col == 1) {
        return (*top)[col][2 - row];
    }
    return (*top)[2 - col][row];
}

static void moveDaisy(Cube *cube, int row, int col)
{
    Face *top = &(*cube)[TOP];
    if ((*top)[row][col] != WHITE) {
        return;
    }
    if (CWPetal(top, row, col) != WHITE) {
        Up(cube);
        return;
    }
    if ((*top)[2 - row][2 - col] != WHITE) {
        U2(cube);
        return;
    }
    U(cube);
}

static void placePetal(Petal *petal, Side side, Cube *cube)
{
    /* Petals in col 1 need to be moved to col 0 or 2 */
    if (petal->col == 1) {

        if (side == LEFT) {
            moveDaisy(cube, 1, 0);
            L(cube);
        }
        else if (side == FRONT) {
            moveDaisy(cube, 2, 1);
            F(cube);
        } 
        else if (side == RIGHT) {
            moveDaisy(cube, 1, 2);
            R(cube);
        }
        else if (side == BACK) {
            moveDaisy(cube, 0, 1);
            B(cube);
        }
        if (petal->row == 0) {
            petal->row++;
            petal->col++;
        } else {
            petal->row--;
            petal->col--;
        }
    }

    if (side == LEFT) {
        moveDaisy(cube, petal->col, 1);
        if (petal->col == 0) {
            Bp(cube);
        } else if (petal->col == 2) {
            F(cube);
        }
        return;
    }

    if (side == FRONT) {
        moveDaisy(cube, 1, petal->col);
        if (petal->col == 0) {
            Lp(cube);
        } else if (petal->col == 2) {
            R(cube);
        }
        return;
    }

    if (side == RIGHT) {
        moveDaisy(cube, 2 - petal->col, 1);
        if (petal->col == 0) {
            Fp(cube);
        } else if (petal->col == 2) {
            B(cube);
        }
        return;
    }

    if (side == BACK) {
        moveDaisy(cube, 1, petal->col);
        if (petal->col == 0) {
            L(cube);
        } else if (petal->col == 2) {
            Rp(cube);
        }
        return;
    }

    /* Special case: bottom petals can be moved in one move
     * after moving the daisy */
    if (side == BOTTOM) {
        moveDaisy(cube, 2 - petal->row, petal->col);
        if (petal->row == 0) {
            F2(cube);
        }
        else if (petal->row == 2) {
            B2(cube);
        }
        else if (petal->col == 0) {
            L2(cube);
        }
        else if (petal->col == 2) {
            R2(cube);
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
    display(cube);
}

void white_cross(Cube *cube)
{
    int iter = 0;
    while (numPetals(cube) != 0 && iter < 50) {
        Face *left = &(*cube)[LEFT];
        Face *front = &(*cube)[FRONT];
        Face *right = &(*cube)[RIGHT];
        Face *top = &(*cube)[TOP];
        Face *back = &(*cube)[BACK];

        if ((*left)[0][1] == (*left)[1][1] && (*top)[1][0] == WHITE) {
            L2(cube);
        }
        if ((*front)[0][1] == (*front)[1][1] && (*top)[2][1] == WHITE) {
            F2(cube);
        }
        if ((*right)[0][1] == (*right)[1][1] && (*top)[1][2] == WHITE) {
            R2(cube);
        }
        if ((*back)[2][1] == (*back)[1][1] && (*top)[0][1] == WHITE) {
            B2(cube);
        }
        if (numPetals(cube) != 0) {
            U(cube);
        }
        iter++;
    }
}