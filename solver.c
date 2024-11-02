/**************************************************************
 *
 *                     solver.c
 *
 *     Rubik's Cube solving program, using the CFOP method.
 *
 **************************************************************/
#include <stdio.h>
#include "cube.h"
#include "moves.h"

int main()
{   
    printf("\n");
    Cube *cube = newCube();
    //display(cube);
    printf("R\n");
    R(cube);
    display(cube);
    printf("L'\n");
    Lp(cube);
    display(cube);
    printf("B2\n");
    B2(cube);
    display(cube);
    printf("L'\n");
    Lp(cube);
    display(cube);
    printf("B'\n");
    Bp(cube);
    display(cube);
    printf("D\n");
    D(cube);
    display(cube);
    printf("U'\n");
    Up(cube);
    display(cube);
    printf("L2\n");
    L2(cube);
    display(cube);
    printf("B2\n");
    B2(cube);
    display(cube);
    printf("D2\n");
    D2(cube);
    display(cube);
    printf("U'\n");
    Up(cube);
    display(cube);
    printf("B'\n");
    Bp(cube);
    display(cube);
    printf("L2\n");
    L2(cube);
    display(cube);
    printf("B\n");
    B(cube);
    display(cube);
    printf("D'\n");
    Dp(cube);
    display(cube);
    printf("L2\n");
    L2(cube);
    display(cube);
    printf("R2\n");
    R2(cube);
    display(cube);
    printf("F'\n");
    Fp(cube);
    display(cube);
    printf("B'\n");
    Bp(cube);
    display(cube);
    printf("L2\n");
    L2(cube);
    display(cube);
    printf("U2\n");
    U2(cube);
    display(cube);
    printf("D'\n");
    Dp(cube);
    display(cube);
    printf("F2\n");
    F2(cube);
    display(cube);
    printf("D\n");
    D(cube);
    display(cube);
    printf("L2\n");
    L2(cube);
    
    display(cube);
    freeCube(cube);
}
