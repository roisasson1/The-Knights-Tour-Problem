#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 4

typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;

typedef struct _treeNodeListCell {
	struct _treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

typedef struct _treeNodeList {
	treeNodeListCell* head;
	treeNodeListCell* tail;
}treeNodeList;

typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions;
} treeNode;

typedef struct _pathTree {
	treeNode* root;
} pathTree;


chessPosArray*** validKnightMoves();
chessPosArray* insertCoord(int row, int col);

void display(chessPosList* lst);
void freeDup(chessPosCell* dup, chessPosCell* prev);
void locatePos(chessPosCell* head);
void tableX(char arr[][SIZE]);
void makeDisplay(char arr[][SIZE]);

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* findAllPossibleKnightPathsHelper(chessPos pos, chessPosArray*** mat, bool hasBeenTable[][SIZE]);
void initBoolTable(bool arr[][SIZE]);
treeNode* createNewTNode(chessPos startingPos);

void makeEmptyList(treeNodeList* lst);
bool isEmptyList(treeNodeList* lst);
void insertDataToStartList(treeNodeList* lst, treeNode* data);
treeNodeListCell* createNewListNode(treeNode* data, treeNodeListCell* next);
void insertNodeToStartList(treeNodeList* lst, treeNodeListCell* head);

void checkMemory1(chessPosArray* arr);
void checkMemory2(chessPosArray** arr);
void checkMemory3(chessPosArray*** arr);
void checkMemory4(chessPos* arr);

void main()
{
	// ex2
	/*
	chessPosList l;
	chessPosCell* n1, * n2, * n3, * n4;

	n4 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n4->position[0] = 'D';
	n4->position[1] = '8';
	n4->next = NULL;

	n3 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n3->position[0] = 'H';
	n3->position[1] = '5';
	n3->next = n4;

	n2 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n2->position[0] = 'H';
	n2->position[1] = '5';
	n2->next = n3;

	n1 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n1->position[0] = 'A';
	n1->position[1] = '4';
	n1->next = n2;

	l.head = (chessPosCell*)malloc(sizeof(chessPosCell));
	l.head = n1;
	l.tail = n4->next;
	display(&l);

	/*chessPosCell n4 = { {'D','8'} , NULL };
	chessPosCell n3 = { {'H','5'} , &n4 };
	chessPosCell n2 = { {'H','5'} , &n3 };
	chessPosCell n1 = { {'A','4'} , &n2 };

	//chessPosList l = { &n1, &n4 };*/

	// ex3:

	pathTree path;
	chessPos start;

	start[0] = 'A';
	start[1] = '2';
	path = findAllPossibleKnightPaths(start);

	// ex 1:
	// chessPosArray*** mat = validKnightMoves();


}

chessPosArray*** validKnightMoves()
{
	chessPosArray*** arr = (chessPosArray***)malloc(SIZE * sizeof(chessPosArray**));
	chessPosArray** inArr;
	chessPosArray* cell;
	checkMemory3(arr);

	for (int row = 0; row < SIZE; row++)
	{
		inArr = (chessPosArray**)malloc(SIZE * sizeof(chessPosArray*));
		checkMemory2(inArr);

		for (int col = 0; col < SIZE; col++)
		{
			cell = insertCoord(row, col);
			inArr[col] = cell;
		}
		arr[row] = inArr;
	}
	return arr;
}

chessPosArray* insertCoord(int row, int col)
{
	chessPosArray* newCell = (chessPosArray*)malloc(sizeof(chessPosArray));
	checkMemory1(newCell);
	newCell->positions = (chessPos*)malloc(SIZE * sizeof(chessPos));
	checkMemory4(newCell->positions);
	int count = 0;
	if (row - 2 >= 0 && col - 1 >= 0)
	{
		newCell->positions[count][0] = row - 2 + 'A';
		newCell->positions[count][1] = col - 1 + '1';
		count++;
	}

	if (row - 2 >= 0 && col + 1 < SIZE)
	{
		newCell->positions[count][0] = row - 2 + 'A';
		newCell->positions[count][1] = col + 1 + '1';
		count++;
	}

	if (row - 1 >= 0 && col + 2 < SIZE)
	{
		newCell->positions[count][0] = row - 1 + 'A';
		newCell->positions[count][1] = col + 2 + '1';
		count++;
	}

	if (row + 1 < SIZE && col + 2 < SIZE)
	{
		newCell->positions[count][0] = row + 1 + 'A';
		newCell->positions[count][1] = col + 2 + '1';
		count++;
	}

	if (row + 2 < SIZE && col + 1 < SIZE)
	{
		newCell->positions[count][0] = row + 2 + 'A';
		newCell->positions[count][1] = col + 1 + '1';
		count++;
	}

	if (row + 2 < SIZE && col - 1 >= 0)
	{
		newCell->positions[count][0] = row + 2 + 'A';
		newCell->positions[count][1] = col - 1 + '1';
		count++;
	}

	if (row + 1 < SIZE && col - 2 >= 0)
	{
		newCell->positions[count][0] = row + 1 + 'A';
		newCell->positions[count][1] = col - 2 + '1';
		count++;
	}

	if (row - 1 >= 0 && col - 2 >= 0)
	{
		newCell->positions[count][0] = row - 1 + 'A';
		newCell->positions[count][1] = col - 2 + '1';
		count++;
	}
	newCell->positions = (chessPos*)realloc(newCell->positions, count * sizeof(chessPos));
	checkMemory4(newCell->positions);
	newCell->size = count;
	return newCell;
}

void display(chessPosList* lst)
{
	chessPosCell* curr, * saver, * dup;
	chessPosCell* prev = lst->head;
	curr = lst->head;
	saver = lst->head->next;

	//TODO emptyList (?)

	while (curr != NULL)
	{
		while (saver != NULL)
		{
			if (curr->position[0] == saver->position[0] && curr->position[1] == saver->position[1])
			{
				dup = saver;
				saver = saver->next;
				freeDup(dup, prev);
			}
			prev = saver;
			saver = saver->next;
		}
		curr = curr->next;
		if (curr != NULL)
			saver = curr->next;
		prev = curr;
	}
	locatePos(lst->head);
}

void freeDup(chessPosCell* dup, chessPosCell* prev)
{
	chessPosCell* tmp;

	tmp = dup;
	dup = dup->next;
	prev->next = dup;
	//tmp->position[0] = NULL;
	//tmp->position[1] = NULL;
	free(tmp);
}

void locatePos(chessPosCell* head)
{
	chessPosCell* curr;
	char table[SIZE][SIZE];
	int row, col, location = 1;

	curr = head;
	tableX(table);

	while (curr != NULL)
	{
		row = curr->position[0] - 'A';
		col = curr->position[1] - '1';

		table[row][col] = location + '0';
		location++;
		curr = curr->next;
	}
	makeDisplay(table);
}

// this function prints the table with X in any cell and print it with the frame
void tableX(char arr[][SIZE])
{
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			arr[i][j] = ' ';
	}
}

// this function prints the frame of the table
void makeDisplay(char arr[][SIZE])
{
	int i, j;

	printf("\n\n    ");
	for (i = 0; i < SIZE; i++) {// print the num of any col.
		printf("%4d", i + 1);
	}
	printf("\n   ");
	for (j = 0; j < SIZE + 1; j++)  // print frame
		printf("____");
	printf("\n");

	for (i = 0; i < SIZE; i++) { //print the num of any row
		printf("%4c |", i + 'A');
		for (j = 0; j < SIZE; j++) {
			printf(" %c |", arr[i][j]);
		}
		printf("\n");
	}
	printf("   ");
	for (j = 0; j < SIZE + 1; j++) // print frame
		printf("____");
}

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	pathTree tr;
	chessPosArray*** mat;
	bool hasBeenTable[SIZE][SIZE];

	mat = validKnightMoves(); // create mat

	initBoolTable(hasBeenTable); // create path
	tr.root = findAllPossibleKnightPathsHelper(startingPosition, mat, hasBeenTable);

	return tr;

}

treeNode* findAllPossibleKnightPathsHelper(chessPos pos, chessPosArray*** mat, bool hasBeenTable[][SIZE])
{
	pathTree tr;
	treeNodeList lst;
	makeEmptyList(&lst);
	int i = pos[0] - 'A';
	int j = pos[1] - '1';
	int row, col;
	int size;
	bool check = true;
	int count = 0;

	tr.root = createNewTNode(pos); // create root
	if (hasBeenTable[i][j] == false)
		hasBeenTable[i][j] = true;

	size = mat[i][j]->size;
	for (int t = 0; t < size; t++)
	{
		row = mat[i][j]->positions[t][0] - 'A';
		col = mat[i][j]->positions[t][1] - '1';
		if (hasBeenTable[row][col] == true)
		{
			count++;
			check = false;
			break;
		}
		else
			break;
	}

	if (check == true) // rec stop
	{
		tr.root->next_possible_positions = lst.head;
		return tr.root;
	}
	else
	{
		for (int kids = 0; kids < size; kids++)
		{
			int rowK = mat[i][j]->positions[kids][0] - 'A';
			int colK = mat[i][j]->positions[kids][1] - '1';
			if (hasBeenTable[rowK][colK] == false)
			{
				tr.root = findAllPossibleKnightPathsHelper(mat[i][j]->positions[kids], mat, hasBeenTable);
				treeNode* tmp = createNewTNode(mat[i][j]->positions[kids]);
				insertDataToStartList(&lst, tmp);
			}
		}
		hasBeenTable[i][j] = false;
	}

	return tr.root;
}

// if all true - return
// else
// create A1 - add node to start list
// if path[i][j] of the kid is false - call 
// add A1 to path - make true
// for (...... < size)
// call fh(c2, mat, path);
// call fh(b3, ma, path);
// change back A1 to false

// ex4 - check if 64's path is exist
// get tree, search for the longest path
// and also get size
// take the longer sub-tree - and free the other sub-tree
// search max of all the kids path
// if the sub-trees are in the same size - return one of them
// add root - size + 1
// if 64 - return it (on the maatefet)
// else - free and return null

/*chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	chessPosList* longest;
	chessPosArray*** mat;
	bool hasBeenTable[SIZE][SIZE];
	int size;

	mat = validKnightMoves();
	initBoolTable(hasBeenTable); // create path

	longest = findKnightPathCoveringAllBoardHelper(path_tree->root, &size, mat, hasBeenTable);
	if (longest == 64)
		return longest;
	else
	{
		freeTree(longest);
		return NULL;
	}
}
*/

/*chessPosList* findKnightPathCoveringAllBoardHelper(treeNode* root, int* size, chessPosArray*** mat, bool hasBeenTable[][SIZE])
{
	chessPosList* lst;
	int i = root->position[0] - 'A';
	int j = root->position[1] - '1';
	int row, col;
	bool check = true;

	if (hasBeenTable[i][j] == false)
		hasBeenTable[i][j] = true;

	*size = mat[i][j]->size;

	for (int t = 0; t < size; t++)
	{
		row = mat[i][j]->positions[0] - 'A';
		col = mat[i][j]->positions[1] - '1';
		if (hasBeenTable[row][col] == false)
		{
			check = false;
			break;
		}
	}

	if (check == true) // rec stop
	{
		*size += 1;
		return lst->head;
	}
}*/

void initBoolTable(bool arr[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			arr[i][j] = false;
	}
}

treeNode* createNewTNode(chessPos startingPos)
{
	treeNode* res;

	res = (treeNode*)malloc(sizeof(treeNode));
	if (res == NULL)
		exit(1);
	res->position[0] = startingPos[0];
	res->position[1] = startingPos[1];
	//makeEmptyList(lst);
	res->next_possible_positions = NULL;

	return res;
}

void makeEmptyList(treeNodeList* lst)
{
	lst->head = lst->tail = NULL;
}

bool isEmptyList(treeNodeList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

void insertDataToStartList(treeNodeList* lst, treeNode* data)
{
	treeNodeListCell* newHead;
	newHead = createNewListNode(data, NULL);
	insertNodeToStartList(lst, newHead);
}

treeNodeListCell* createNewListNode(treeNode* data, treeNodeListCell* next)
{
	treeNodeListCell* res;
	res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	if (res == NULL)
		exit(3);
	res->node = data;
	res->next = next;
	return res;
}

void insertNodeToStartList(treeNodeList* lst, treeNodeListCell* head)
{
	if (isEmptyList(lst) == true)
	{
		head->next = NULL;
		lst->head = lst->tail = head;
	}
	else
	{
		head->next = lst->head;
		lst->head = head;
	}
}


void checkMemory3(chessPosArray*** arr)
{
	if (arr == NULL)
	{
		printf("Memory allocation failed");
		exit(1);
	}
}

void checkMemory2(chessPosArray** arr)
{
	if (arr == NULL)
	{
		printf("Memory allocation failed");
		exit(1);
	}
}

void checkMemory1(chessPosArray* arr)
{
	if (arr == NULL)
	{
		printf("Memory allocation failed");
		exit(1);
	}
}

void checkMemory4(chessPos* arr)
{
	if (arr == NULL)
	{
		printf("Memory allocation failed");
		exit(1);
	}
}