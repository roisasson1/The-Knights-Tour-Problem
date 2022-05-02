#ifndef HQ1_H
#define HQ1_H

#include "Header.h"

/* this function creating the table
and put in every cell the position and an array of possible moves the knight can make */
chessPosArray*** validKnightMoves();

/* this function checks all the possible moves the knight can make */
chessPosArray* insertCoord(int row, int col);

#endif