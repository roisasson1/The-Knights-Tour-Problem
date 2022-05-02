#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 5
#define MAX_POSITION 8

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

bool isEmptyList(treeNodeListCell* head);
void insertTDataToStartList(treeNode* root, treeNode* data);
treeNodeListCell* createNewListNode(treeNode* data);
void insertTNodeToStartList(treeNode* root, treeNodeListCell* node);

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
void findKnightPathCoveringAllBoardHelper(treeNode* root, int* sizeOfList, chessPosList* longest);
void makeEmptyChessPosList(chessPosList* lst);
bool isEmptyChessPosList(chessPosList* lst);
void insertDataToStartChessPosList(chessPosList* lst, treeNode* node);
chessPosCell* createNewChessPosCell(treeNode* data);
void insertNodeToStartChessPosList(chessPosList* lst, chessPosCell* head);
void freeList(chessPosList* lst);

void printList(chessPosList* lst);

void saveListToBinFile(char* file_name, chessPosList* pos_list);

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
	chessPosList* lst;

	start[0] = 'C';
	start[1] = '3';
	path = findAllPossibleKnightPaths(start);

	lst = findKnightPathCoveringAllBoard(&path);
	// ex 1:
	// chessPosArray*** mat = validKnightMoves();

	printList(lst);

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
	newCell->positions = (chessPos*)malloc(MAX_POSITION * sizeof(chessPos));
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
	tr.root = findAllPossibleKnightPathsHelper(*startingPosition, mat, hasBeenTable);

	return tr;

}

treeNode* findAllPossibleKnightPathsHelper(chessPos pos, chessPosArray*** mat, bool hasBeenTable[][SIZE])
{
	int i = pos[0] - 'A';
	int j = pos[1] - '1';

	//bool check = true;

	if (hasBeenTable[i][j] == true)
		return NULL;
	else
	{
		int row, col;
		int size = mat[i][j]->size;
		treeNode* root = createNewTNode(pos); // create root
		hasBeenTable[i][j] = true;

		for (int kids = 0; kids < size; kids++)
		{
			row = mat[i][j]->positions[kids][0] - 'A';
			col = mat[i][j]->positions[kids][1] - '1';
			if (hasBeenTable[row][col] == false)
			{
				treeNode* tmp = findAllPossibleKnightPathsHelper(mat[i][j]->positions[kids], mat, hasBeenTable);
				insertTDataToStartList(root, tmp);
			}
		}
		hasBeenTable[i][j] = false;
		return root;
	}

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

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	chessPosList* longest;
	int sizeOfList = 0;

	longest = (chessPosList*)malloc(sizeof(chessPosList));
	findKnightPathCoveringAllBoardHelper(path_tree->root, &sizeOfList, longest);
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

	//longest = (chessPosList*)malloc(sizeof(chessPosList));
	makeEmptyChessPosList(longest);

	if (root == NULL)
	{
		*sizeOfList = 0;
		//currList = (chessPosList*)malloc(sizeof(chessPosList));
		makeEmptyChessPosList(&currList);
		*longest = currList;
		return;
	}
	else
	{
		curr = root->next_possible_positions;
		while (curr != NULL)
		{
			findKnightPathCoveringAllBoardHelper(curr->node, &sizeOfKids, &currList);
			if (sizeOfKids > maxSize)
			{
				freeList(longest);
				maxSize = sizeOfKids;
				*longest = currList;
			}
			else
				freeList(&currList);
			// if the size of the next kid is bigger - make him max
			curr = curr->next;
		}
		insertDataToStartChessPosList(longest, root); //to do - convert the nodeTo to chessPosCell and insert to the list
		//to do - change root to root -> positions
		maxSize++;
		*sizeOfList = maxSize;

		return;
	}
}

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	short int sizeOfPos;
	FILE* fp = fopen(file_name, "wb");
	sizeOfPos = countPos(pos_list);
	chessPosCell* curr = pos_list->head;
	fwrite(&sizeOfPos, sizeof(short int), 1, fp);
	int i, j;
	for (i = 0; i < sizeOfPos; i++)
	{
		int row = curr->position[0] - 'A';
		int col = curr->position[1] - '1';

		int d = intToBin(row); // 010

		curr = curr->next;
	}
}


void makeEmptyChessPosList(chessPosList* lst)
{
	lst->head = lst->tail = NULL;
}

bool isEmptyChessPosList(chessPosList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

void insertDataToStartChessPosList(chessPosList* lst, treeNode* node)
{
	chessPosCell* newHead;
	newHead = createNewChessPosCell(node);
	insertNodeToStartChessPosList(lst, newHead);
}

chessPosCell* createNewChessPosCell(treeNode* data)
{
	chessPosCell* res;
	res = (chessPosCell*)malloc(sizeof(chessPosCell));
	if (res == NULL)
		exit(3);
	res->position[0] = data->position[0];
	res->position[1] = data->position[1];
	res->next = NULL;
	return res;
}

void insertNodeToStartChessPosList(chessPosList* lst, chessPosCell* head)
{
	if (isEmptyChessPosList(lst))
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


void freeList(chessPosList* lst)
{
	chessPosCell* curr, * saver;
	curr = lst->head;
	while (curr != NULL)
	{
		saver = curr;
		curr = curr->next;
		lst->head = curr;
		free(saver);
	}
}

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


bool isEmptyList(treeNodeListCell* head)
{
	if (head == NULL)
		return true;
	else
		return false;
}

void insertTDataToStartList(treeNode* root, treeNode* data)
{
	treeNodeListCell* newHead;
	newHead = createNewListNode(data, NULL);
	insertTNodeToStartList(root, newHead);
}

treeNodeListCell* createNewListNode(treeNode* data)
{
	treeNodeListCell* res;
	res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	if (res == NULL)
		exit(3);
	res->node = data;
	res->next = NULL;
	return res;
}

void insertTNodeToStartList(treeNode* root, treeNodeListCell* node)
{
	if (isEmptyList(root->next_possible_positions))
	{
		root->next_possible_positions = node;
		node->next = NULL;
	}
	else
	{
		node->next = root->next_possible_positions;
		root->next_possible_positions = node;
	}
}

void printList(chessPosList* lst)
{
	if (isEmptyList(lst))
	{
		return;
	}
	chessPosCell* curr;
	curr = lst->head;
	while (curr != NULL)
	{
		printf("%c%c ", curr->position[0], curr->position[1]);
		curr = curr->next;
	}
	printf("\n");
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