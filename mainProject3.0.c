#define _CRT_SECURE_NO_WARNINGS
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

typedef unsigned char BYTE;


chessPosArray*** validKnightMoves();
chessPosArray* insertCoord(int row, int col);

void display(chessPosList* lst);
void freeDup(chessPosCell* dup, chessPosCell* prev);
void locatePos(chessPosCell* head);
void tableX(chessPos arr[][SIZE]);
void makeDisplay(chessPos arr[][SIZE]);

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
int countPos(chessPosList* lst);
int calcSize(int sizeOfPos);
BYTE* createBytesArr(int sizeArr, chessPosList* lst);

int checkAndDisplayPathFromFile(char* file_name);
chessPosList createChessPosList(BYTE* bytesArr, int sizeArr, int sizeOfPos);
bool isPathLegal(chessPosList lst);
bool checkNextMoveLegality(int row, int col, chessPosCell* next);
int resultOfLegality(bool legalPath, chessPosList* lst);
void insertDataToEndChessPosList(chessPosList* lst, char row, char col);
chessPosCell* createNewChessPosListNode(char row, char col, chessPosCell* next);
void insertNodeToEndChessPosList(chessPosList* lst, chessPosCell* tail);

void printMenu();
bool checkValid(chessPos position);
void choice2(pathTree* tr, chessPos* position, bool flag1, bool* flag2);
void choice3(pathTree* tr, chessPosList* lst, chessPos* position, bool flag1, bool flag2, bool* flag3);
char* inputName(chessPosList* lst);
void options5(int result);
void message();
void errorMessage();

void checkMemory1(chessPosArray* arr);
void checkMemory2(chessPosArray** arr);
void checkMemory3(chessPosArray*** arr);
void checkMemory4(chessPos* arr);
void checkMemory(void* arr);
void checkFile(FILE* fp);

void main()
{
	// ex 1:
	// chessPosArray*** mat = validKnightMoves();

	// ex2
	/*
	chessPosList l;
	chessPosCell* n1, * n2, * n3, * n4;
	n4 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n4->position[0] = 'B';
	n4->position[1] = '2';
	n4->next = NULL;

	n3 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n3->position[0] = 'D';
	n3->position[1] = '2';
	n3->next = n4;

	n2 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n2->position[0] = 'A';
	n2->position[1] = '4';
	n2->next = n3;

	n1 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n1->position[0] = 'A';
	n1->position[1] = '4';
	n1->next = n2;

	l.head = (chessPosCell*)malloc(sizeof(chessPosCell));
	l.head = n1;
	l.tail = n4->next;
	display(&l); */
	

	// ex3: 
	/*
	pathTree path;
	chessPos start;
	chessPosList* lst;

	start[0] = 'C';
	start[1] = '3';
	path = findAllPossibleKnightPaths(start);
	*/

	// ex4: 
	/*
		lst = findKnightPathCoveringAllBoard(&path);
		printList(lst);
	*/

	// ex5: 
	/*char name[] = "binFile.bin";
	chessPosList l;
	chessPosCell* n1, * n2, * n3, * n4, *n5;

	n5 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n5->position[0] = 'E';
	n5->position[1] = '3';
	n5->next = NULL;

	n4 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n4->position[0] = 'D';
	n4->position[1] = '1';
	n4->next = n5;

	n3 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n3->position[0] = 'B';
	n3->position[1] = '3';
	n3->next = n4;

	n2 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n2->position[0] = 'A';
	n2->position[1] = '4';
	n2->next = n3;

	n1 = (chessPosCell*)malloc(sizeof(chessPosCell));
	n1->position[0] = 'C';
	n1->position[1] = '5';
	n1->next = n2;

	l.head = (chessPosCell*)malloc(sizeof(chessPosCell));
	l.head = n1;
	l.tail = n5->next;

	saveListToBinFile(name, &l);*/

	// ex 6:
	//char str[] = "binFile.bin";
	//int res = checkAndDisplayPathFromFile(str);

	printMenu();
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
	chessPosCell* curr, * dup;
	chessPosCell* prev = NULL;
	curr = lst->head;
	bool hasBeenTable[SIZE][SIZE];

	initBoolTable(hasBeenTable);

	//TODO emptyList (?)

	while (curr != NULL)
	{
		int row = curr->position[0] - 'A';
		int col = curr->position[1] - '1';

		if (hasBeenTable[row][col] == false)
			hasBeenTable[row][col] = true;
		else
		{
			dup = curr;
			curr = curr->next;
			freeDup(dup, prev);
		}

		if (curr == lst->head)
			prev = lst->head;
		else
			prev = prev->next;

		if (curr != NULL)
			curr = curr->next;
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
	chessPos table[SIZE][SIZE];
	int row, col, location = 1;

	curr = head;
	tableX(table);

	while (curr != NULL)
	{
		row = curr->position[0] - 'A';
		col = curr->position[1] - '1';

		if (location <= 9)
		{
			table[row][col][0] = ' ';
			table[row][col][1] = location + '0';
		}
		else if (location >= 10 && location <= 99)
		{
			table[row][col][0] = (location / 10) + '0';
			table[row][col][1] = (location % 10) + '0';
		}
		location++;
		curr = curr->next;
	}
	makeDisplay(table);
}

// this function prints the table with X in any cell and print it with the frame
void tableX(chessPos arr[][SIZE])
{
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
		{
		    arr[i][j][0] = ' ';
			arr[i][j][1] = ' ';
		}
	}
}

// this function prints the frame of the table
void makeDisplay(chessPos arr[][SIZE])
{
	int i, j;

	printf("\n\n    ");
	for (i = 0; i < SIZE; i++) {// print the num of any col.
		printf("%5d", i + 1);
	}
	printf("\n   ");
	for (j = 0; j < SIZE + 2; j++)  // print frame
		printf("____");
	printf("\n");

	for (i = 0; i < SIZE; i++) { //print the num of any row
		printf("%4c |", i + 'A');
		for (j = 0; j < SIZE; j++) {
			printf(" %c%c |", arr[i][j][0], arr[i][j][1]);
		}
		printf("\n");
	}
	printf("   ");
	for (j = 0; j < SIZE + 2; j++) // print frame
		printf("____");
	printf("\n\n");
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
	checkFile(fp);

	if (pos_list == NULL)
	{
		printf("The list does not exist!!!\n");
		fclose(fp);
		return;
	}

	sizeOfPos = countPos(pos_list);
	unsigned int sizeArr = calcSize(sizeOfPos);
	fwrite(&sizeOfPos, sizeof(short int), 1, fp);

	if (sizeArr != 0)
	{
		BYTE* bytesArr = (BYTE*)malloc(sizeArr * sizeof(BYTE));
		checkMemory(bytesArr);
		bytesArr = createBytesArr(sizeArr, pos_list);
		fwrite(bytesArr, sizeof(BYTE), sizeArr, fp);
		free(bytesArr);
	}

	fclose(fp);
	/*to do :
	1. ask hadar about empty list
	2. about short int - in frhed it shows 05 00 instead 00 05
	*/
}

int countPos(chessPosList* lst)
{
	chessPosCell* curr;
	int count = 0;

	curr = lst->head;

	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}

	return count;
}

int calcSize(int sizeOfPos)
{
	int size = 6 * sizeOfPos;
	if (size % 8 != 0)
		return size / 8 + 1;
	else
		return size / 8;
}

BYTE* createBytesArr(int sizeArr, chessPosList* lst)
{
	chessPosCell* curr = lst->head;
	BYTE saver = 0x00, saverLeft = 0x00, saverRight = 0x00, row, col, endByte = 0x00;
	BYTE* bytesArr = (BYTE*)malloc(sizeArr * sizeof(BYTE));
	checkMemory(bytesArr);
	int i;

	for (i = 0; i < sizeArr; i++)
	{
		BYTE val = 0x00;
		row = curr->position[0] - 'A'; // if is c - 0000 0010
		col = curr->position[1] - '1'; // if is 5 - 0000 0100

		if ((i + 1) % 3 == 1)
		{
			if (i != 0)
			{
				curr = curr->next;
				row = curr->position[0] - 'A';
				col = curr->position[1] - '1';
			}
			val |= row << 5;  //val is 0100 0000
			val |= col << 2;  //val is 0101 0000
			if (curr->next != NULL)
			{
				saver = curr->next->position[0] - 'A'; //if is a - 0000 0001
				saverLeft = saver >> 1;
				saverRight = saver << 7;
				val |= saverLeft;  // 0101 0000
			}
			else
				val |= endByte;
		}
		else if ((i + 1) % 3 == 2)
		{
			val |= saverRight;
			val |= col << 4;   // col 0000 0011 --> 0011 0000
			if (curr->next != NULL)
			{
				row = curr->next->position[0] - 'A'; //0000 0001
				val |= row << 1;     // 0011 0010
				saver = curr->next->position[1] - '1';  //0000 0010
				saverLeft = saver >> 2;
				saverRight = saver << 6;
				val |= saverLeft; // 0011 0010
			}
			else
				val |= endByte;
		}
		else if ((i + 1) % 3 == 0)
		{
			val |= saverRight;
			if (curr->next != NULL)
			{
				row = curr->next->position[0] - 'A';
				col = curr->next->position[1] - '1';
				val |= row << 3;
				val |= col;
			}
			else
				val |= endByte;
		}

		bytesArr[i] = val;
		curr = curr->next;
	}
	return bytesArr;
}


int checkAndDisplayPathFromFile(char* file_name)
{
	FILE* fp = fopen(file_name, "rb");

	if (fp == NULL)
		return -1;
	else
	{
		short int sizeOfPos;
		int result;
		chessPosList posList;

		bool legalPath;

		fread(&sizeOfPos, sizeof(short int), 1, fp);
		if (sizeOfPos == 0)
		{
			makeEmptyChessPosList(&posList);
			fclose(fp);
			return 3;
		}
		else
		{
			BYTE* bytesArr;
			int sizeArr = calcSize(sizeOfPos);
			bytesArr = (BYTE*)malloc(sizeArr * sizeof(BYTE));
			checkMemory(bytesArr);
			fread(bytesArr, sizeof(BYTE), sizeArr, fp);
			posList = createChessPosList(bytesArr, sizeArr, sizeOfPos);
			free(bytesArr);
		}

		// to do - ask how to read the position from the file:
		// option 1 - copy to bytes arr and  then convert to list 
		// option 2 - there is a way to copy dierctly to list

		fclose(fp);


		legalPath = isPathLegal(posList);
		result = resultOfLegality(legalPath, &posList);

		freeList(&posList);
		return result;
	}
}

chessPosList createChessPosList(BYTE* bytesArr, int sizeArr, int sizeOfPos)
{
	chessPosList lst;
	makeEmptyChessPosList(&lst);
	BYTE  saverLeft = 0x00, mask = 0x00;
	char row = 0, col = 0;
	int i, countPos = 0;


	for (i = 0; i < sizeArr; i++)
	{

		if ((i + 1) % 3 == 1)
		{
			row = (bytesArr[i] >> 5) + 'A'; // if is c - 0000 0010
			mask = 0x07;
			col = (mask & (bytesArr[i] >> 2)) + '1'; // if is 5 - 0000 0100
			insertDataToEndChessPosList(&lst, row, col);
			countPos++;
			if (countPos < sizeOfPos)
			{
				mask = 0x03;
				saverLeft = mask & bytesArr[i];
			}

		}
		else if ((i + 1) % 3 == 2)
		{
			row = ((bytesArr[i] >> 7) | (saverLeft << 1)) + 'A'; // if is c - 0000 0010
			mask = 0x07;
			col = (mask & (bytesArr[i] >> 4)) + '1'; // if is 5 - 0000 0100
			insertDataToEndChessPosList(&lst, row, col);
			countPos++;
			if (countPos < sizeOfPos)
			{
				row = (mask & (bytesArr[i] >> 1)) + 'A';
				mask = 0x01;
				saverLeft = mask & bytesArr[i];
			}
		}
		else if ((i + 1) % 3 == 0)
		{
			col = ((bytesArr[i] >> 6) | (saverLeft << 2)) + '1';
			insertDataToEndChessPosList(&lst, row, col);
			countPos++;
			if (countPos < sizeOfPos)
			{
				mask = 0x07;
				row = (mask & (bytesArr[i] >> 3)) + 'A';
				col = (mask & bytesArr[i]) + '1';
				insertDataToEndChessPosList(&lst, row, col);
				countPos++;
			}
		}

	}

	return lst;

}

bool isPathLegal(chessPosList lst)
{
	if (isEmptyChessPosList(&lst))
		return true;
	chessPosCell* curr = lst.head;

	while (curr->next != NULL)
	{
		int row = curr->position[0] - 'A';
		int col = curr->position[1] - '1';
		if (checkNextMoveLegality(row, col, curr->next) == false)
			return false;
		curr = curr->next;
	}
	return true;
}

bool checkNextMoveLegality(int row, int col, chessPosCell* next)
{
	int rowNext = next->position[0] - 'A';
	int colNext = next->position[1] - '1';

	if ((row - 2) == rowNext && (col + 1) == colNext)
		return true;
	else if ((row - 1) == rowNext && (col + 2) == colNext)
		return true;
	else if ((row + 1) == rowNext && (col + 2) == colNext)
		return true;
	else if ((row + 2) == rowNext && (col + 1) == colNext)
		return true;
	else if ((row + 2) == rowNext && (col - 1) == colNext)
		return true;
	else if ((row + 1) == rowNext && (col - 2) == colNext)
		return true;
	else if ((row - 1) == rowNext && (col - 2) == colNext)
		return true;
	else if ((row - 2) == rowNext && (col - 1) == colNext)
		return true;
	else
		return false;

}

int resultOfLegality(bool legalPath, chessPosList* lst)
{
	if (legalPath)
	{
		display(lst);
		int listLen = countPos(lst);
		if (listLen == (SIZE * SIZE))
			return 2;
		else
			return 3;
	}
	else
		return 1;
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

void insertDataToEndChessPosList(chessPosList* lst, char row, char col)
{
	chessPosCell* newTail;
	newTail = createNewChessPosListNode(row, col, NULL);
	insertNodeToEndChessPosList(lst, newTail);
}

chessPosCell* createNewChessPosListNode(char row, char col, chessPosCell* next)
{
	chessPosCell* newCell;
	newCell = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemory(newCell);
	newCell->position[0] = row;
	newCell->position[1] = col;
	newCell->next = next;
	return newCell;
}

void insertNodeToEndChessPosList(chessPosList* lst, chessPosCell* tail)
{
	if (isEmptyChessPosList(lst))
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
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
	newHead = createNewListNode(data);
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

void printMenu()
{
	int choice;
	chessPos position;
	pathTree tr;
	chessPosList* lst = NULL;
	//makeEmptyChessPosList(&lst);
	char* name;
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;
	bool finished = false;

	message();
	scanf("%d", &choice);
	while (choice != 6)
	{
		if (choice == 1)
		{
			while (!flag1)
			{
				getchar();
				printf("Please enter row and col: \n");
				scanf("%c%c", &position[0], &position[1]);
				if (checkValid(position))
				{
					flag1 = true;
					printf("The position initialized. Please continue...\n");
				}
				else
					printf("The position is not valid!!! Please try again\n");
			}
		}
		else if (choice == 2)
			choice2(&tr, &position, flag1, &flag2);
		else if (choice == 3)
			choice3(&tr, &lst, &position, flag1, flag2, &flag3);
		else if (choice == 4)
		{
			if (flag1)
			{
				if (!flag3)
					choice3(&tr, &lst, &position, flag1, flag2, &flag3);
				name = inputName(&lst);
				saveListToBinFile(name, &lst);
				printf("The file created. Please continue...\n");
			}
			else
				errorMessage();
		}
		else if (choice == 5)
		{
			if (!flag1)
				getchar();
			name = inputName(&lst);
			int result = checkAndDisplayPathFromFile(name);
			options5(result);
			finished = true;
		}
		else
			printf("Please enter valid number (1-6) !!!!!\n");

		if (finished)
		{
			printf("Please enter a key to return the menu!\n");
			getchar();
			flag1 = flag2 = flag3 = finished = false;
			system("cls");
			message();
		}

		scanf("%d", &choice);
		if (flag1)
		    getchar();
	}
	if (choice == 6)
		exit(1);
}

bool checkValid(chessPos position)
{
	if ((position[0] >= 'A') && (position[0] <= 'H') && (position[1] >= '1') && (position[1] <= '8'))
		return true;
	return false;

}

void choice2(pathTree* tr, chessPos* position, bool flag1, bool* flag2)
{
	if (flag1)
	{
		*tr = findAllPossibleKnightPaths(position);
		*flag2 = true;
		printf("The path has created. Please continue...\n");
	}
	else
		errorMessage();
}

void choice3(pathTree* tr, chessPosList* lst, chessPos* position, bool flag1, bool flag2, bool* flag3)
{
	chessPosList* tmpList = NULL;
	//makeEmptyChessPosList(&tmpList);
	if (flag1)
	{
		if (flag2)
		{
			tmpList = findKnightPathCoveringAllBoard(tr);
		}
		else
		{
			choice2(tr, position, flag1, &flag2);
			tmpList = findKnightPathCoveringAllBoard(tr);
		}

		if (tmpList == NULL)
			printf("The path does not cover all the board!!!\n");
		else
		{
			printf("This path is covering all the board :)\n Please continue...\n");
			*lst = *tmpList;
		}
		*flag3 = true;
	}
	else
		errorMessage();
}

char* inputName(chessPosList* lst)
{
	char* name = (char*)malloc(sizeof(char));
	int lsize = 1, psize = 0;
	printf("Please enter name of file: \n");
	char ch = getchar();
	while (ch != '\n')
	{
		if (lsize == psize)
		{
			lsize *= 2;
			name = (char*)realloc(name, (lsize+1) * sizeof(char));
		}
		name[psize] = ch;
		psize++;

		ch = getchar();
	}
	name[psize] = '\0';
	name = (char*)realloc(name, (psize + 6) * sizeof(char));
	name[psize + 5] = '\0';
	sprintf(name, "%s%s", name, ".bin"); // adding .ind to the end
	checkMemory(name);
	return name;
}

void options5(int result)
{
	if (result == -1)
		printf("The file does not exist\n");
	if (result == 1)
		printf("The path is illegal!!!\n");
	if (result == 2)
		printf("You welcome!!!\n");
	if (result == 3)
		printf("The list in file does not cover all board\n");
}

void message()
{
	printf("1. Enter a knight's starting position\n");
	printf("2. Create all possible knight paths\n");
	printf("3. Find a knight path covering all board\n");
	printf("4. Save knight path covering all board to file\n");
	printf("5. Load and display path from file\n");
	printf("6. Exit\n");
}

void errorMessage()
{
	printf("You have not entered position yet! Please enter 1\n");
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

void checkMemory(void* arr)
{
	if (arr == NULL)
	{
		printf("Memory allocation failed");
		exit(1);
	}
}

void checkFile(FILE* fp)
{
	if (fp == NULL)
	{
		printf("Failed opening the file");
		exit(2);
	}
}