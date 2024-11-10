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

#define CW true
#define CCW false

/********** rotateFace90 ********
 *
 *      Rotates the given face by 90 degrees in the specified direction
 * 
 *      Used by U, U', D, D', R, R', L, L', F, F', B, and B'
 * 
 *      Note: Only changes the actual face rotated, not any surrounding
 *            faces. The rest is handled by various "turn[XYZ]180" functions.
 *      
 ******************************/
static void rotateFace90(Face *face, bool cw)
{
    Color temp1 = (*face)[0][0]; /* Store the top left corner */
    Color temp2 = (*face)[0][1]; /* Store the top edge */

    if (cw) {
        /* Permute Corners */
        (*face)[0][0] = (*face)[2][0];
        (*face)[2][0] = (*face)[2][2];
        (*face)[2][2] = (*face)[0][2];
        (*face)[0][2] = temp1;

        /* Permute Edges */
        (*face)[0][1] = (*face)[1][0];
        (*face)[1][0] = (*face)[2][1];
        (*face)[2][1] = (*face)[1][2];
        (*face)[1][2] = temp2;
    } else {
        /* Permute Corners */
        (*face)[0][0] = (*face)[0][2];
        (*face)[0][2] = (*face)[2][2];
        (*face)[2][2] = (*face)[2][0];
        (*face)[2][0] = temp1;
        /* Permute Edges */
        (*face)[0][1] = (*face)[1][2];
        (*face)[1][2] = (*face)[2][1];
        (*face)[2][1] = (*face)[1][0];
        (*face)[1][0] = temp2;
    }
}

/********** rotateSquare180 ********
 *
 *      Given a faces and the position of a square within
 *      the face, rotates the square by 180 degrees and
 *      swaps it with the square at its new position 
 * 
 *      Used by rotateFace180
 *      
 ******************************/
static void rotateSquare180(Face *face, int i, int j)
{
    Color temp = (*face)[i][j];
    (*face)[i][j] = (*face)[2 - i][2 - j];
    (*face)[2 - i][2 - j] = temp;
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
    /* Rotate the upper left lower right squares */
    rotateSquare180(face, 0, 0);

    /* Rotate the upper right and lower left triangles */
    rotateSquare180(face, 0, 1);
    rotateSquare180(face, 0, 2);
    rotateSquare180(face, 1, 2);
}

/*************************************************************************
 *                 y-axis turns: U, U', U2, D, D' and D2                 *
 *************************************************************************/

/********** turnYLayer90 ********
 *
 *      Turns the given layer 90 degrees about the y-axis
 * 
 *      A layer is specified by its 4 faces and row index.
 *      Row 0 is the top layer and row 2 is the bottom layer.
 *      
 *      The turning direction is specified by the order of the faces in
 *      the layer. f1 is replaced by f2, f2 by f3, f3 by f4, and f4 by f1.
 * 
 *      Note: Does not change the face rotated. This is handled by 
 *            rotateFace90.
 *      
 ******************************/
static void turnYLayer90(Face *f1, Face *f2, Face *f3, Face *f4, int row)
{
    /* Store specified row in face f1 */
    Color temp1[3];
    for (int col = 0; col < 3; col++) {
        temp1[col] = (*f1)[row][col];
    }
    /* Replace rows in face f1 with corresponding row in f2 */
    for (int col = 0; col < 3; col++) {
        (*f1)[row][col] = (*f2)[row][col];
    }
    /* Replace row in face f2 with corresponding
     * row in f3, accounting for a flip */
    for (int col = 0; col < 3; col++) {
        (*f2)[row][col] = (*f3)[2 - row][2 - col];
    }
    /* Replace row in face f3 with corresponding
     * row in f4, accounting for a flip */
    for (int col = 0; col < 3; col++) {
        (*f3)[2 - row][col] = (*f4)[row][2 - col];
    }
    /* Replace row in face f4 with corresponding row in f1 */
    for (int col = 0; col < 3; col++) {
        (*f4)[row][col] = temp1[col];
    }
}

/********** turnYLayer180 ********
 *
 *      Turns the given layer 90 degrees about the y-axis
 * 
 *      A layer is specified by 4 faces and the row index.
 *      Row 0 is the top layer and row 2 is the bottom layer.
 * 
 *      Note: Does not change the face rotated. This is handled by 
 *            rotateFace180.
 *  
 ******************************/
static void turnYLayer180(Face *f1, Face *f2, Face *f3, Face *f4, int row)
{
    /* Swap rows in front and back faces */
    for (int col = 0; col < 3; col++) {
        Color temp = (*f1)[row][col];
        (*f1)[row][col] = (*f3)[2 - row][2 - col];
        (*f3)[2 - row][2 - col] = temp;
        // rotateSquare180(f1, f3, row, col);
    }

    /* Swap rows in right and left faces */
    for (int col = 0; col < 3; col++) {
        Color temp = (*f2)[row][col];
        (*f2)[row][col] = (*f4)[row][col];
        (*f4)[row][col] = temp;
    }
}

/**************************** U Moves ******************************/

void U(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *l = &((*cube)[LEFT]);
    Face *r = &((*cube)[RIGHT]);
    Face *b = &((*cube)[BACK]);
    turnYLayer90(f, r, b, l, 0);
    rotateFace90(&((*cube)[TOP]), CW);
    printf("U ");
}

void Up(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *l = &((*cube)[LEFT]);
    Face *r = &((*cube)[RIGHT]);
    Face *b = &((*cube)[BACK]);
    turnYLayer90(f, l, b, r, 0);
    rotateFace90(&((*cube)[TOP]), CCW);
    printf("U' ");
}

void U2(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *l = &((*cube)[LEFT]);
    Face *r = &((*cube)[RIGHT]);
    Face *b = &((*cube)[BACK]);
    turnYLayer180(f, r, b, l, 0);
    rotateFace180(&((*cube)[TOP]));
    printf("U2 ");
}

/**************************** D Moves ******************************/

void D(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *l = &((*cube)[LEFT]);
    Face *r = &((*cube)[RIGHT]);
    Face *b = &((*cube)[BACK]);
    turnYLayer90(f, l, b, r, 2);
    rotateFace90(&((*cube)[BOTTOM]), CW);
    printf("D ");
}

void Dp(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *l = &((*cube)[LEFT]);
    Face *r = &((*cube)[RIGHT]);
    Face *b = &((*cube)[BACK]);
    turnYLayer90(f, r, b, l, 2);
    rotateFace90(&((*cube)[BOTTOM]), CCW);
    printf("D' ");
}

void D2(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *l = &((*cube)[LEFT]);
    Face *r = &((*cube)[RIGHT]);
    Face *b = &((*cube)[BACK]);
    turnYLayer180(f, l, b, r, 2);
    rotateFace180(&((*cube)[BOTTOM]));
    printf("D2 ");
}

/*************************************************************************
 *           x-axis turns: R, R', R2, L, L', L2, M, M', and M2           *
 *************************************************************************/

/********** turnXLayer90 ********
 *
 *      Turns the given layer 90 degrees about the x-axis
 * 
 *      A layer is specified by its 4 faces and column index.
 *      Column 0 is the left layer, column 1 is the middle layer,
 *      and column 2 is the right layer.
 *      
 *      The turning direction is specified by the order of the faces in
 *      the layer. f1 is replaced by f2, f2 by f3, f3 by f4, and f4 by f1.
 * 
 *      Note: Does not change the face rotated. This is handled by 
 *            rotateFace90. 
 *  
 ******************************/
static void turnXLayer90(Face *f1, Face *f2, Face *f3, Face *f4, int col)
{
    /* Store the specified column in face f1 */
    Color temp[3];
    for (int row = 0; row < 3; row++) {
        temp[row] = (*f1)[row][col];
    }
    /* Permute columns in f1, f2, f3, and f4 */
    for (int row = 0; row < 3; row++) {
        (*f1)[row][col] = (*f2)[row][col];
        (*f2)[row][col] = (*f3)[row][col];
        (*f3)[row][col] = (*f4)[row][col];
        (*f4)[row][col] = temp[row];
    }
}

/********** turnXLayer180 ********
 *
 *      Turns the given layer 90 degrees about the x-axis
 * 
 *      A layer is specified by 4 faces and the column index.
 * 
 *      Note: Does not change the face rotated. This is handled
 *            by rotateFace180.
 *  
 ******************************/
static void turnXLayer180(Face *f1, Face *f2, Face *f3, Face *f4, int col)
{
    Color temp[3];

    /* Swap columns in top and bottom faces */
    for (int row = 0; row < 3; row++) {
        temp[col] = (*f1)[row][col];
        (*f1)[row][col] = (*f3)[row][col];
        (*f3)[row][col] = temp[col];
    }

    /* Swap columns in front/back faces */
    for (int row = 0; row < 3; row++) {
        temp[col] = (*f2)[row][col];
        (*f2)[row][col] = (*f4)[row][col];
        (*f4)[row][col] = temp[col];
    }    
}

/**************************** R Moves ******************************/

void R(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *u = &((*cube)[TOP]);
    Face *b = &((*cube)[BACK]);
    Face *d = &((*cube)[BOTTOM]);
    turnXLayer90(f, d, b, u, 2);
    rotateFace90(&((*cube)[RIGHT]), CW);
    printf("R ");
}

void Rp(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *u = &((*cube)[TOP]);
    Face *b = &((*cube)[BACK]);
    Face *d = &((*cube)[BOTTOM]);
    turnXLayer90(f, u, b, d, 2);
    rotateFace90(&((*cube)[RIGHT]), CCW);
    printf("R' ");
}

void R2(Cube *cube)
{   
    Face *f = &((*cube)[FRONT]);
    Face *u = &((*cube)[TOP]);
    Face *b = &((*cube)[BACK]);
    Face *d = &((*cube)[BOTTOM]);
    turnXLayer180(f, d, b, u, 2);
    rotateFace180(&((*cube)[RIGHT]));
    printf("R2 ");
}

/**************************** L Moves ******************************/

void L(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *u = &((*cube)[TOP]);
    Face *b = &((*cube)[BACK]);
    Face *d = &((*cube)[BOTTOM]);
    turnXLayer90(f, u, b, d, 0);
    rotateFace90(&((*cube)[LEFT]), CW);
    printf("L ");
}

void Lp(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *u = &((*cube)[TOP]);
    Face *b = &((*cube)[BACK]);
    Face *d = &((*cube)[BOTTOM]);
    turnXLayer90(f, d, b, u, 0);
    rotateFace90(&((*cube)[LEFT]), CCW);
    printf("L' ");
}

void L2(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *u = &((*cube)[TOP]);
    Face *b = &((*cube)[BACK]);
    Face *d = &((*cube)[BOTTOM]);
    turnXLayer180(f, u, b, d, 0);
    rotateFace180(&((*cube)[LEFT]));
    printf("L2 ");
}

/**************************** M Moves ******************************/

void M(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *u = &((*cube)[TOP]);
    Face *b = &((*cube)[BACK]);
    Face *d = &((*cube)[BOTTOM]);
    turnXLayer90(f, d, b, u, 1);
    printf("M ");
}

void Mp(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *u = &((*cube)[TOP]);
    Face *b = &((*cube)[BACK]);
    Face *d = &((*cube)[BOTTOM]);;
    turnXLayer90(f, u, b, d, 1);
    printf("M' ");
}

void M2(Cube *cube)
{
    Face *f = &((*cube)[FRONT]);
    Face *u = &((*cube)[TOP]);
    Face *b = &((*cube)[BACK]);
    Face *d = &((*cube)[BOTTOM]);
    turnXLayer180(f, d, b, u, 1);
    printf("M2 ");
}

/*************************************************************************
 *                 z-axis turns: F, F', F2, B, B', and B2                *
 *************************************************************************/

/********** turnZLayer90CW ********
 *
 *      Turns the given layer 90 degrees clockwise about the z-axis
 * 
 *      A layer is specified by its 4 faces and column index.
 *      Column 0 is the front layer and column 2 is the back layer.
 *  
 ******************************/
static void turnZLayer90CW(Face *f1, Face *f2, Face *f3, Face *f4, int col)
{
    Color temp[3];

    for (int row = 0; row < 3; row++) {
        temp[row] = (*f1)[row][col];
        if (col == 2) {
            (*f1)[row][col] = (*f2)[col][2 - row];
        } else {
            (*f1)[row][col] = (*f2)[2 - col][row];
        }
        
    }
    for (int row = 0; row < 3; row++) {
        if (col == 2) {
            (*f2)[col][row] = (*f3)[row][2 - col];
        } else {
            (*f2)[2 - col][row] = (*f3)[2 - row][2 - col];
        }
    }
    for (int row = 0; row < 3; row++) {
        if (col == 2) {
            (*f3)[row][2 - col] = (*f4)[2 - col][2 - row];
        } else {
            (*f3)[row][2 - col] = (*f4)[col][row];
        }
    }
    for (int row = 0; row < 3; row++) {
        if (col == 2) {
            (*f4)[2 - col][row] = temp[row];
        } else {
            (*f4)[col][2 - row] = temp[row];
        }
    }
}

/********** turnZLayer90CCW ********
 *
 *      Turns the given layer 90 degrees counter-clockwise about the z-axis
 * 
 *      A layer is specified by its 4 faces and column index.
 *      Column 0 is the front layer and column 2 is the back layer.
 *  
 ******************************/
static void turnZLayer90CCW(Face *f1, Face *f2, Face *f3, Face *f4, int col)
{
    Color temp[3];

    for (int row = 0; row < 3; row++) {
        temp[row] = (*f1)[row][col];
        if (col == 2) {
            (*f1)[row][col] = (*f2)[2 - col][row];
        } else {
            (*f1)[row][col] = (*f2)[col][2 - row];
        }
    }
    for (int row = 0; row < 3; row++) {
        if (col == 2) {
            (*f2)[2 - col][row] = (*f3)[2 - row][2 - col];
        } else {
            (*f2)[col][row] = (*f3)[row][2 - col];
        }   
    }
    for (int row = 0; row < 3; row++) {
        if (col == 2) {
            (*f3)[row][2 - col] = (*f4)[col][row];
        } else {
            (*f3)[row][2 - col] = (*f4)[2 - col][2 - row];
        }
    }
    for (int row = 0; row < 3; row++) {
        if (col == 2) {
            (*f4)[col][2 - row] = temp[row];
        } else {
            (*f4)[2 - col][row] = temp[row];
        }
    }       
}

/********** turnZLayer180 ********
 *
 *      Turns the given layer 180 degrees about the z-axis
 * 
 *      A layer is specified by 4 faces and the column index.
 *      Column 0 is the front layer and column 2 is the back layer.
 *  
 ******************************/
static void turnZLayer180(Face *f1, Face *f2, Face *f3, Face *f4, int col)
{
    Color temp;

    /* Swap columns in left and right faces */
    for (int row = 0; row < 3; row++) {
        temp = (*f1)[row][col];
        (*f1)[row][col] = (*f3)[2 - row][2 - col];
        (*f3)[2 - row][2 - col] = temp;
    }

    /* Swap columns in top and bottom faces */
    for (int row = 0; row < 3; row++) {
        if (col == 2) {
            temp = (*f2)[col][row];
            (*f2)[col][row] = (*f4)[2 - col][2 - row];
            (*f4)[2 - col][2 - row] = temp;
        } else {
            temp = (*f2)[2 - col][row];
            (*f2)[2 - col][row] = (*f4)[col][2 - row];
            (*f4)[col][2 - row] = temp;
        }
    }    
}

/**************************** F Moves ******************************/

void F(Cube *cube)
{
    Face *r = &((*cube)[RIGHT]);
    Face *u = &((*cube)[TOP]);
    Face *l = &((*cube)[LEFT]);
    Face *d = &((*cube)[BOTTOM]);
    turnZLayer90CW(r, u, l, d, 0);
    rotateFace90(&((*cube)[FRONT]), CW);
    printf("F ");
}

void Fp(Cube *cube)
{
    Face *r = &((*cube)[RIGHT]);
    Face *u = &((*cube)[TOP]);
    Face *l = &((*cube)[LEFT]);
    Face *d = &((*cube)[BOTTOM]);
    turnZLayer90CCW(r, d, l, u, 0);
    rotateFace90(&((*cube)[FRONT]), CCW);
    printf("F' ");
}

void F2(Cube *cube)
{
    Face *r = &((*cube)[RIGHT]);
    Face *u = &((*cube)[TOP]);
    Face *l = &((*cube)[LEFT]);
    Face *d = &((*cube)[BOTTOM]);
    turnZLayer180(r, u, l, d, 0);
    rotateFace180(&((*cube)[FRONT]));
    printf("F2 ");
}

/**************************** B Moves ******************************/

void B(Cube *cube)
{
    Face *r = &((*cube)[RIGHT]);
    Face *u = &((*cube)[TOP]);
    Face *l = &((*cube)[LEFT]);
    Face *d = &((*cube)[BOTTOM]);
    turnZLayer90CW(r, d, l, u, 2);
    rotateFace90(&((*cube)[BACK]), CW);
    printf("B ");
}

void Bp(Cube *cube)
{
    Face *r = &((*cube)[RIGHT]);
    Face *u = &((*cube)[TOP]);
    Face *l = &((*cube)[LEFT]);
    Face *d = &((*cube)[BOTTOM]);
    turnZLayer90CCW(r, u, l, d, 2);
    rotateFace90(&((*cube)[BACK]), CCW);
    printf("B' ");
}

void B2(Cube *cube)
{
    Face *r = &((*cube)[RIGHT]);
    Face *u = &((*cube)[TOP]);
    Face *l = &((*cube)[LEFT]);
    Face *d = &((*cube)[BOTTOM]);
    turnZLayer180(r, d, l, u, 2);
    rotateFace180(&((*cube)[BACK]));
    printf("B2 ");
}