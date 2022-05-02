#include "Header.h"
#include "Hq3.h"
#include "Hq1.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	pathTree tr;
	chessPosArray*** mat;
	bool hasBeenTable[SIZE][SIZE];

	mat = validKnightMoves(); /* creating the table with the possible moves in each cell */

	initBoolTable(hasBeenTable); /* initializing table with FALSE in any cell */

	/* sending the root of the tree to the recursive function */
	tr.root = findAllPossibleKnightPathsHelper(*startingPosition, mat, hasBeenTable);

	return tr;
}

treeNode* findAllPossibleKnightPathsHelper(chessPos pos, chessPosArray*** mat, bool hasBeenTable[][SIZE])
{
	/* adjust to array places */
	int i = pos[0] - 'A';
	int j = pos[1] - '1';

	/* the stopping condition */
	/* if the position activated before */
	if (hasBeenTable[i][j] == true)
		return NULL;
	else
	{
		int row, col;
		int size = mat[i][j]->size; /* size of possible moves */
		treeNode* root = createNewTNode(pos); /* creating the root */
		hasBeenTable[i][j] = true;

		/* this loop checking if one of the kids was activated */
		for (int kids = 0; kids < size; kids++)
		{
			/* adjust to array places */
			row = mat[i][j]->positions[kids][0] - 'A';
			col = mat[i][j]->positions[kids][1] - '1';

			/* if the position was not "activated" before */
			if (hasBeenTable[row][col] == false)
			{
				/* the recursive step */
				treeNode* tmp = findAllPossibleKnightPathsHelper(mat[i][j]->positions[kids], mat, hasBeenTable);

				/* insert the root to the list of kids */
				insertTDataToStartList(root, tmp);
			}
		}
		hasBeenTable[i][j] = false;  /* clear the bool table from the last call */
		return root;
	}

}