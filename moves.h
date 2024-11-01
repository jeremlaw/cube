/**************************************************************
 *
 *                     moves.h
 *
 *     This file contains an interface that allows the user to
 *     perform any legal move on a Rubik's Cube. These are U, U',
 *     U2, D, D', D2, R, R', R2, L, L', L2, F, F', F2. B, B', B2.
 *     
 *     "Prime" moves denoted with p rather than ', e.g. D' = Dp.
 *
 **************************************************************/

#ifndef MOVES_H
#define MOVES_H

#include "cube.h"

/* U Moves */
void U(Cube *cube);
void Up(Cube *cube);
void U2(Cube *cube);

/* D Moves */
void D(Cube *cube);
void Dp(Cube *cube);
void D2(Cube *cube);

/* R Moves */
void R(Cube *cube);
void Rp(Cube *cube);
void R2(Cube *cube);

/* L Moves */
void L(Cube *cube);
void Lp(Cube *cube);
void L2(Cube *cube);

/* F Moves */
void F(Cube *cube);
void Fp(Cube *cube);
void F2(Cube *cube);

/* B Moves */
void B(Cube *cube);
void Bp(Cube *cube);
void B2(Cube *cube);

/* M Moves */
void M(Cube *cube);
void Mp(Cube *cube);
void M2(Cube *cube);

#endif