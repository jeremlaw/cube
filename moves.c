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

/*************************************************************************
 *                        U, U', U2, D, D' and D2                        *
 *************************************************************************/

/********** turnLayer90H ********
 *
 *      Turns the given horizontal layer 90 degrees
 * 
 *      A layer is specified by its 4 faces and row index.
 *      Row 0 is the top layer and row 2 is the bottom layer.
 *      
 *      The turning direction is specified by the order of the faces in
 *      the layer. f1 is replaced by f2, f2 by f3, f3 by f4, and f4 by f1.
 *      
 ******************************/
static void turnLayer90H(Face *f1, Face *f2, Face *f3, Face *f4, int row)
{
    Color temp[3];
    for (int col = 0; col < 3; col++) {
        temp[col] = (*f1)[row][col];
    }

    for (int col = 0; col < 3; col++) {
        (*f1)[row][col] = (*f2)[row][col];
        (*f2)[row][col] = (*f3)[row][col];
        (*f3)[row][col] = (*f4)[row][col];
        (*f4)[row][col] = temp[col];
    }
}

/********** turnLayer180 ********
 *
 *      Turns the given horizontal layer 90 degrees
 * 
 *      A layer is specified by its 4 faces and row index.
 *      
 *      The turning direction is irrelevant.
 *  
 ******************************/
static void turnLayer180H(Face *f1, Face *f2, Face *f3, Face *f4, int row)
{
    /* Swap rows in front and back faces */
    Color temp[3];
    for (int col = 0; col < 3; col++) {
        temp[col] = (*f1)[row][col];
    }

    for (int col = 0; col < 3; col++) {
        (*f1)[row][col] = (*f3)[row][col];
        (*f3)[row][col] = temp[col];
    }

    /* Swap rows in right and left faces */
    for (int col = 0; col < 3; col++) {
        temp[col] = (*f2)[row][col];
    }

    for (int col = 0; col < 3; col++) {
        (*f2)[row][col] = (*f4)[row][col];
        (*f4)[row][col] = temp[col];
    }
}

void U(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *l = &(cube->Left);
    Face *r = &(cube->Right);
    Face *b = &(cube->Back);
    turnLayer90H(f, r, b, l, 0);
}

void Up(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *l = &(cube->Left);
    Face *r = &(cube->Right);
    Face *b = &(cube->Back);
    turnLayer90H(f, l, b, r, 0);
}

void U2(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *l = &(cube->Left);
    Face *r = &(cube->Right);
    Face *b = &(cube->Back);
    turnLayer180H(f, r, b, l, 0);
}

void D(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *l = &(cube->Left);
    Face *r = &(cube->Right);
    Face *b = &(cube->Back);
    turnLayer90H(f, l, b, r, 2);
}

void Dp(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *l = &(cube->Left);
    Face *r = &(cube->Right);
    Face *b = &(cube->Back);
    turnLayer90H(f, r, b, l, 2);
}

void D2(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *l = &(cube->Left);
    Face *r = &(cube->Right);
    Face *b = &(cube->Back);
    turnLayer180H(f, l, b, r, 2);
}

/*************************************************************************
 *         R, R', R2, L, L', L2, M, M', F, F', F2, B, B', and B2         *
 *************************************************************************/

/********** turnLayer90V ********
 *
 *      Turns the given vertical layer 90 degrees
 * 
 *      A layer is specified by its 4 faces and column index.
 *      Column 0 is the left layer, column 1 is the middle layer,
 *      and column 2 is the right layer.
 *      
 *      The turning direction is specified by the order of the faces in
 *      the layer. f1 is replaced by f2, f2 by f3, f3 by f4, and f4 by f1.
 *  
 *      
 ******************************/
static void turnLayer90V(Face *f1, Face *f2, Face *f3, Face *f4, int col)
{
    Color temp[3];
    for (int row = 0; row < 3; row++) {
        temp[col] = (*f1)[row][col];
    }

    for (int row = 0; row < 3; row++) {
        (*f1)[row][col] = (*f2)[row][col];
        (*f2)[row][col] = (*f3)[row][col];
        (*f3)[row][col] = (*f4)[row][col];
        (*f4)[row][col] = temp[col];
    }
}

void R(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer90V(f, d, b, u, 2);
}