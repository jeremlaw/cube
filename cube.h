/**************************************************************
 *
 *                     cube.h
 *
 *     This file contains the Cube interface, which inculdes 
 *     data structure representing a 3x3x3 Rubik's Cube, as
 *     well as a cube initializer.
 *
 **************************************************************/
#ifndef CUBE_H
#define CUBE_H

typedef enum { RED, YELLOW, ORANGE, WHITE, GREEN, BLUE } Color;
typedef int Face[3][3];

typedef enum { LEFT, FRONT, RIGHT, TOP, BACK, BOTTOM } Side;

typedef Face Cube[6];

Cube *newCube();
void freeCube(Cube *cube);
void display(Cube *cube);

#endif