/**************************************************************
 *
 *                     white_cross.h
 *
 *     This file contains an interface that allows the user to
 *     create a white cross. This is done in two steps:
 *          Creating the daisy: four white edges surrounding
 *          the yellow center
 *          White cross: four white edges in the correct places
 *          around the white center
 *
 **************************************************************/
#ifndef WHITE_CROSS_H
#define WHITE_CROSS_H

#include "cube.h"

void daisy(Cube *cube);

void white_cross(Cube *cube);

#endif
