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

void swap4cycle(Face *f1, Face *f2, Face *f3, Face *f4)
{
    Color temp[3];
    for (int col = 0; col < 3; col++) {
        temp[col] = (*f1)[0][col];
    }

    for (int col = 0; col < 3; col++) {
        (*f1)[0][col] = (*f2)[0][col];
        (*f2)[0][col] = (*f3)[0][col];
        (*f3)[0][col] = (*f4)[0][col];
        (*f4)[0][col] = temp[col];
    }
}

void U(Cube *cube)
{
    Face *f1 = &(cube->Front);
    Face *f2 = &(cube->Left);
    Face *f3 = &(cube->Right);
    Face *f4 = &(cube->Back);

    swap4cycle(f1, f2, f3, f4);
}

void Up(Cube *cube)
{
    Color temp[3];
    for (int col = 0; col < 3; col++) {
        temp[col] = cube->Front[0][col];
    }

    for (int col = 0; col < 3; col++) {
        cube->Front[0][col] = cube->Left[0][col];
        cube->Left[0][col] = cube->Back[0][col];
        cube->Back[0][col] = cube->Right[0][col];
        cube->Right[0][col] = temp[col];
    }
}

void U2(Cube *cube)
{
    Color temp[3];
    for (int col = 0; col < 3; col++) {
        temp[col] = cube->Front[0][col];
    }

    for (int col = 0; col < 3; col++) {
        cube->Front[0][col] = cube->Back[0][col];
        cube->Back[0][col] = temp[col];
    }
    for (int col = 0; col < 3; col++) {
        temp[col] = cube->Right[0][col];
    }
    for (int col = 0; col < 3; col++) {
        cube->Right[0][col] = cube->Left[0][col];
        cube->Left[0][col] = temp[col];
    }
}