/**************************************************************
 *
 *                     moves.c
 *
 *     This file contains the implementation for all the legal
 *     moves that can be performed on a Rubik's Cube.
 *     
 **************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "moves.h"

static void swap(Face *face, int i, int j)
{
    Color temp = (*face)[i][j];
    (*face)[i][j] = (*face)[2 - i][2 - j];
    (*face)[2 - i][2 - j] = temp;
}

/********** rotateFace90 ********
 *
 *      Rotates the given face by 90 degrees in the specified direction
 * 
 *      Used U, U', D, D', R, R', L, L', F, F', B, and B'.
 *      
 ******************************/
static void rotateFace90(Face *face, bool cw)
{
    Color temp1 = (*face)[0][0];
    Color temp2 = (*face)[0][1];

    if (cw) {
        (*face)[0][0] = (*face)[2][0];
        (*face)[0][1] = (*face)[1][0];
        (*face)[2][0] = (*face)[2][2];
        (*face)[1][0] = (*face)[2][1];
        (*face)[2][2] = (*face)[0][2];
        (*face)[2][1] = (*face)[1][2];
        (*face)[0][2] = temp1;
        (*face)[1][2] = temp2;
    } else {
        (*face)[0][0] = (*face)[0][2];
        (*face)[0][1] = (*face)[1][2];
        (*face)[0][2] = (*face)[2][2];
        (*face)[1][2] = (*face)[2][1];
        (*face)[2][2] = (*face)[2][0];
        (*face)[2][1] = (*face)[1][0];
        (*face)[2][0] = temp1;
        (*face)[1][0] = temp2;
    }
}

/********** rotateFace180 ********
 *
 *      Rotates the given face by 180 degrees in the specified direction
 * 
 *      Used U2, D2, R2, L2, F2, and B2.
 *      
 ******************************/
static void rotateFace180(Face *face)
{
    swap(face, 0, 0);
    swap(face, 0, 1);
    swap(face, 0, 2);
    swap(face, 1, 2);
}

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
    Color temp1[3];

    for (int col = 0; col < 3; col++) {
        temp1[col] = (*f1)[row][col];
        (*f1)[row][col] = (*f2)[row][col];
    }
    for (int col = 0; col < 3; col++) {
        (*f2)[row][col] = (*f3)[2 - row][2 - col];
    }
    for (int col = 0; col < 3; col++) {
        (*f3)[2 - row][col] = (*f4)[row][2 - col];
    }
    for (int col = 0; col < 3; col++) {
        (*f4)[row][col] = temp1[col];
    }
}

/********** turnLayer180H ********
 *
 *      Turns the given horizontal layer 90 degrees
 * 
 *      A layer is specified by 4 faces and the row index.
 *      
 *      The turning direction is irrelevant.
 *  
 ******************************/
static void turnLayer180H(Face *f1, Face *f2, Face *f3, Face *f4, int row)
{
    Color temp[3];

    /* Swap rows in front and back faces */
    for (int col = 0; col < 3; col++) {
        temp[col] = (*f1)[row][col];
        (*f1)[row][col] = (*f3)[2 - row][2 - col];
        (*f3)[2 - row][2 - col] = temp[col];
    }

    /* Swap rows in right and left faces */
    for (int col = 0; col < 3; col++) {
        temp[col] = (*f2)[row][col];
        (*f2)[row][col] = (*f4)[row][col];
        (*f4)[row][col] = temp[col];
    }
}

/**************************** U Moves ******************************/

void U(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *l = &(cube->Left);
    Face *r = &(cube->Right);
    Face *b = &(cube->Back);
    turnLayer90H(f, r, b, l, 0);
    rotateFace90(&(cube->Top), true);
}

void Up(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *l = &(cube->Left);
    Face *r = &(cube->Right);
    Face *b = &(cube->Back);
    turnLayer90H(f, l, b, r, 0);
    rotateFace90(&(cube->Top), false);
}

void U2(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *l = &(cube->Left);
    Face *r = &(cube->Right);
    Face *b = &(cube->Back);
    turnLayer180H(f, r, b, l, 0);
    rotateFace180(&(cube->Top));
}

/**************************** D Moves ******************************/

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
 *      Will perform an R/L move OR an F/B move depending
 *      on the first and third specified faces.
 *      
 *      f2 and f4 must be the top and bottom faces, while f1 and f3
 *      can be either the right/left faces or the front/back faces.
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
        temp[row] = (*f1)[row][col];
    }

    for (int row = 0; row < 3; row++) {
        (*f1)[row][col] = (*f2)[row][col];
        (*f2)[row][col] = (*f3)[row][col];
        (*f3)[row][col] = (*f4)[row][col];
        (*f4)[row][col] = temp[row];
    }
}

/********** turnLayer180V ********
 *
 *      Turns the given vertical layer 90 degrees
 *      
 *      Will perform an R2/L2 move OR an F2/B2 move
 *      depending on the last two faces specified.
 * 
 *      f1 and f2 must be the top and bottom faces, while f3 and f4
 *      can be either the right/left faces or the front/back faces.
 *      right/left faces are changed  
 * 
 *      A layer is specified by 4 faces and the column index.
 *      
 *      The turning direction is irrelevant.
 *  
 ******************************/
static void turnLayer180V(Face *f1, Face *f2, Face *f3, Face *f4, int col)
{
    Color temp[3];

    /* Swap columns in top and bottom faces */
    for (int row = 0; row < 3; row++) {
        temp[col] = (*f1)[row][col];
        (*f1)[row][col] = (*f3)[row][col];
        (*f3)[row][col] = temp[col];
    }

    /* Swap columns in left/right OR front/back faces */
    for (int row = 0; row < 3; row++) {
        temp[col] = (*f2)[row][col];
        (*f2)[row][col] = (*f4)[row][col];
        (*f4)[row][col] = temp[col];
    }    
}

/**************************** R Moves ******************************/

void R(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer90V(f, d, b, u, 2);
    rotateFace90(&(cube->Right), true);
}

void Rp(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer90V(f, u, b, d, 2);
    rotateFace90(&(cube->Right), false);
}

void R2(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer180V(f, d, b, u, 2);
    rotateFace180(&(cube->Right));
}

/**************************** L Moves ******************************/

void L(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer90V(f, u, b, d, 0);
    rotateFace90(&(cube->Left), true);
}

void Lp(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer90V(f, d, b, u, 0);
    rotateFace90(&(cube->Left), false);
}

void L2(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer180V(f, u, b, d, 0);
    rotateFace180(&(cube->Left));
}

/**************************** M Moves ******************************/

void M(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer90V(f, d, b, u, 1);
}

void Mp(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer90V(f, u, b, d, 1);
}

void M2(Cube *cube)
{
    Face *f = &(cube->Front);
    Face *u = &(cube->Top);
    Face *b = &(cube->Back);
    Face *d = &(cube->Bottom);
    turnLayer180V(f, d, b, u, 1);
}

/**************************** F Moves ******************************/

void F(Cube *cube)
{
    Face *r = &(cube->Right);
    Face *u = &(cube->Top);
    Face *l = &(cube->Left);
    Face *d = &(cube->Bottom);
    turnLayer90V(r, u, l, d, 2);
    rotateFace90(&(cube->Front), true);
}

void Fp(Cube *cube)
{
    Face *r = &(cube->Right);
    Face *u = &(cube->Top);
    Face *l = &(cube->Left);
    Face *d = &(cube->Bottom);
    turnLayer90V(r, d, l, d, 2);
    rotateFace90(&(cube->Front), false);
}

void F2(Cube *cube)
{
    Face *r = &(cube->Right);
    Face *u = &(cube->Top);
    Face *l = &(cube->Left);
    Face *d = &(cube->Bottom);
    turnLayer180V(r, u, l, d, 0);
    rotateFace180(&(cube->Front));;
}