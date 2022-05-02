#ifndef HQ3_H
#define HQ3_H

#include "Header.h"

/* this function making the table of possible moves and creating tree of possible moves from the exact position */
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);

/* this function is the recursive function -
checking if the position or the possible moves have not been activated yet and creating tree node.
if it does, the tree node getting into a list of the possible moves from the node from above.
in the end, a tree of possible moves is made */
treeNode* findAllPossibleKnightPathsHelper(chessPos pos, chessPosArray*** mat, bool hasBeenTable[][SIZE]);

#endif
