#ifndef HQ2_H
#define HQ2_H

#include "Header.h"

/* this functions getting a list of positions and updating the list if there are any duplications,
and than printing the table. in each cell will be numbered in order the way to the positions*/
void display(chessPosList* lst);

/* this function removing duplications from the list */
void freeDup(chessPosCell* dup, chessPosCell* prev);

/* this function inputing the numbers in the cells */
void locatePos(chessPosCell* head);

/* this function creating the empty table and print it with the frame */
void createEmptyTable(chessPos arr[][SIZE]);

/* this function prints the frame of the table */
void makeDisplay(chessPos arr[][SIZE]);

#endif
