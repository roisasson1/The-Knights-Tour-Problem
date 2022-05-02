#include "Header.h"
#include "Hq4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	chessPosList* longest;
	int sizeOfList = 0;
	longest = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemory(longest);

	/* sending the root of the tree to the recursive function */
	findKnightPathCoveringAllBoardHelper(path_tree->root, &sizeOfList, longest);

	/* if the size of list is equal to the num of elements in the table -
	the path is covering all the board */
	if (sizeOfList == (SIZE * SIZE))
		return longest;
	else
	{
		freeList(longest);
		return NULL;
	}
}


void findKnightPathCoveringAllBoardHelper(treeNode* root, int* sizeOfList, chessPosList* longest)
{
	int sizeOfKids = 0, maxSize = 0;
	treeNodeListCell* curr;
	chessPosList currList;
	makeEmptyChessPosList(longest);

	/* stop condition */
	/* bottom of the tree */
	if (root == NULL)
	{
		*sizeOfList = 0;
		makeEmptyChessPosList(&currList);
		*longest = currList;
		return;
	}
	else
	{
		/* finding the biggest path in the kids's list */
		curr = root->next_possible_positions;
		while (curr != NULL)
		{
			findKnightPathCoveringAllBoardHelper(curr->node, &sizeOfKids, &currList);
			/* if the path's size of the next kid is bigger - make him max */
			if (sizeOfKids > maxSize)
			{
				freeList(longest);
				maxSize = sizeOfKids;
				*longest = currList;
			}
			else
				freeList(&currList);

			curr = curr->next;
		}
		/* adding the tree nodes to the new list */
		insertDataToStartChessPosList(longest, root);
		maxSize++;
		*sizeOfList = maxSize;

		return;
	}
}