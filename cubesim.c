/**************************************************************
 *
 *                     cubesim.c
 *
 *     Program that simulates a Rubik's Cube, allowing the user
 *     to interact and perform a variety of turns. These include:
 *     R, R', R2, L, L', L2, U, U', U2, D, D', D2, F, F', F2,
 *     B, B', B2, M, M', and M2. Also allows user to solve the
 *     cube in its current state.
 * 
 *     Note: Currently only supports solving the white cross.
 *           Other stages are in progress.
 *
 **************************************************************/
#include <stdio.h>
#include <string.h>
#include "cube.h"
#include "moves.h"
#include "white_cross.h"

int main()
{   
    printf("\n");
    Cube *cube = newCube();
    printf("Welcome to the cube simulator! This is your cube:\n\n");
    display(cube);
    printf("Enter any move or sequence of moves\n");
    printf("or type h for help, or q to quit.\n");
    char s[] = "     ";
    while (strcmp(s, "q") != 0) {
        scanf("%s", s);
        if (strcmp(s, "q") == 0) {
            printf("Thanks for cubing. Have a nice day!\n");
            freeCube(cube);
            return 0;
        }
        /* In Progress */
        else if (strcmp(s, "h") == 0) {
            printf("\n\033[32m");
            printf("----------------- Help Center -----------------\n\n");
            printf("Sorry, we are currently busy. Please leave a\n");
            printf("message and we be with you as soon as possible.\n\n");
            printf("-----------------------------------------------\n");
            printf("\033[0m");
        }
        else {
            if (strcmp(s, "R") == 0) {
            R(cube);
            }
            else if (strcmp(s, "R'") == 0) {
                Rp(cube);
            }
            else if (strcmp(s, "R2") == 0) {
                R2(cube);
            }
            else if (strcmp(s, "L") == 0) {
                L(cube);
            }
            else if (strcmp(s, "L'") == 0) {
                Lp(cube);
            }
            else if (strcmp(s, "L2") == 0) {
                L2(cube);
            }
            else if (strcmp(s, "U") == 0) {
                U(cube);
            }
            else if (strcmp(s, "U'") == 0) {
                Up(cube);
            }
            else if (strcmp(s, "U2") == 0) {
                U2(cube);
            }
            else if (strcmp(s, "D") == 0) {
                D(cube);
            }
            else if (strcmp(s, "D'") == 0) {
                Dp(cube);
            }
            else if (strcmp(s, "D2") == 0) {
                D2(cube);
            }
            else if (strcmp(s, "F") == 0) {
                F(cube);
            }
            else if (strcmp(s, "F'") == 0) {
                Fp(cube);
            }
            else if (strcmp(s, "F2") == 0) {
                F2(cube);
            }
            else if (strcmp(s, "B") == 0) {
                B(cube);
            }
            else if (strcmp(s, "B'") == 0) {
                Bp(cube);
            }
            else if (strcmp(s, "B2") == 0) {
                B2(cube);
            }
            else if (strcmp(s, "M") == 0) {
                M(cube);
            }
            else if (strcmp(s, "M'") == 0) {
                Mp(cube);
            }
            else if (strcmp(s, "M2") == 0) {
                M2(cube);
            }
            else if (strcmp(s, "solve") == 0) {
                daisy(cube);
                white_cross(cube);
            }
            else {
                printf("\n\033[31m");
                printf("Oops! Invalid turn. Choose from the following turns:");
                printf("\n\n\033[0m");
                printf("\033[32m");
                printf("R R' R2 L L' L2 U U' U2 D D' D2 F F' F2 B B' B2 M M' M2");
                printf("\n\n\033[0m");
                printf("Your current cube:\n\n");
            }
            display(cube);
        }
    }
    freeCube(cube);
}
