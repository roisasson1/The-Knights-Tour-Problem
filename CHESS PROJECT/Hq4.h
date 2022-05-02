#ifndef HQ4_H
#define HQ4_H
#include "Header.h"

/* this function getting a tree, and return a list -
if the size of list is equal to the num of elements in the table -
the path is covering all the board */
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);

/* this function checking which path is the longest in every step and put it in a list */
void findKnightPathCoveringAllBoardHelper(treeNode* root, int* sizeOfList, chessPosList* longest);

#endif