/**************************************************************
 *
 *                     solver.c
 *
 *     Rubik's Cube solving program, using the CFOP method.
 *
 **************************************************************/
#include <stdio.h>
#include "moves.h"
#include "white_cross.h"

int main()
{
    printf("Hello world!\n");
    Cube *cube = newCube();
    printf("Welcome to the cube solver! This is your cube:\n\n");
    display(cube);
    L(cube);
    R(cube);
    Dp(cube);
    F(cube);
    U2(cube);
    D2(cube);
    L2(cube);
    Rp(cube);
    Up(cube);
    L(cube);
    U(cube);
    L(cube);
    R(cube);
    B2(cube);
    Rp(cube);
    Bp(cube);
    D(cube);
    U2(cube);
    B2(cube);
    U(cube);
    D2(cube);
    F(cube);
    R2(cube);
    Up(cube);
    Bp(cube);
    display(cube);
    daisy(cube);
    white_cross(cube);
    freeCube(cube);
}