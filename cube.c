/**************************************************************
 *
 *                     cube.c
 *
 *     This file contains the implementation of the cube
 *     initializer in cube.h.
 *
 **************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "cube.h"

#define red_square    "\033[31m\u25A0\033[0m"
#define yellow_square   "\033[33m\u25A0\033[0m"
#define orange_square   "\033[38;5;208m\u25A0\033[0m"
#define white_square    "\033[37m\u25A0\033[0m"
#define green_square    "\033[32m\u25A0\033[0m"
#define blue_square     "\033[34m\u25A0\033[0m"
#define reset   "\x1B[0m"

/********** newCube ********
 *
 *      Creates and initializes a new cube
 *
 *      Notes: 
 *          Allocates memory on the heap
 *          Throws runtime error if malloc fails
 *      
 ******************************/
Cube *newCube()
{
    Cube *cube = malloc(sizeof(Cube));
    assert(cube);

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            (*cube)[LEFT][row][col] = BLUE;
            (*cube)[FRONT][row][col] = RED;
            (*cube)[RIGHT][row][col] = GREEN;
            (*cube)[TOP][row][col] = YELLOW;
            (*cube)[BACK][row][col] = ORANGE;
            (*cube)[BOTTOM][row][col] = WHITE;
        }
    }
    return cube;
}

/********** freeCube ********
 *
 *      Frees heap memory allocated by newCube
 *
 *      Note: Throws runtime error if given cube pointer is NULL
 *      
 ******************************/
void freeCube(Cube *cube)
{
    assert(cube);
    free(cube);
}

/********** printRow ********
 *
 *      Displays a row of the given cube face     
 *      
 ******************************/
static void printRow(Face *face, int row)
{
    for (int col = 0; col < 3; col++) {
        switch ((*face)[row][col]) {
            case RED:
                printf(red_square " ");
                break;
            case YELLOW:
                printf(yellow_square " ");
                break;
            case ORANGE:
                printf(orange_square " ");
                break;
            case WHITE:
                printf(white_square " ");
                break;
            case GREEN:
                printf(green_square " ");
                break;
            case BLUE:
                printf(blue_square " ");
                break;
            default:
                break;
        }
        printf(reset);
    }
    printf("  ");
}

/********** display ********
 *
 *      Displays the given cube
 *
 *      Note: Throws runtime error if given cube pointer is NULL
 *      
 ******************************/
void display(Cube *cube)
{
    printf("\nLeft    Front   Right    Top    Back    Bottom\n");
    for (int row = 0; row < 3; row++) {
        for (Side side = LEFT; side <= BOTTOM; side++) {
            printRow(&((*cube)[side]), row);
        }
        printf("\n");
    }
    printf("\n");
}
