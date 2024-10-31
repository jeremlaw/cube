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

typedef enum { WHITE, YELLOW, RED, GREEN, ORANGE, BLUE } Color;
typedef Color Face[3][3];

typedef struct {
    Face faces[6];
} Cube;

Cube *newCube();
void freeCube(Cube *cube);

#endif