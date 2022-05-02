#include "Header.h"

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
	checkMemory(res);
	res->position[0] = data->position[0];  /*converting tree node to chessPosCell*/
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

void initBoolTable(bool arr[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			arr[i][j] = false;  /*initialize every cell*/
	}
}

treeNode* createNewTNode(chessPos startingPos)
{
	treeNode* res;

	res = (treeNode*)malloc(sizeof(treeNode));
	if (res == NULL)
		exit(1);
	res->position[0] = startingPos[0]; /*converting the chess pos to tree node*/
	res->position[1] = startingPos[1];
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
	checkMemory(res);
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

void checkMemory(void* arr)
{
	if (arr == NULL)
	{
		printf("Memory allocation failed");
		exit(3);
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

void freeTree(pathTree tr)
{
	freeTreeHelper(tr.root);
}

void freeTreeHelper(treeNode* root)
{
	if (root == NULL)
		return;

	treeNodeListCell* curr = root->next_possible_positions, * saver;

	while (curr != NULL)
	{
		freeTreeHelper(curr->node);
		// free(curr->node);
		saver = curr;
		curr = curr->next;
		free(saver);
	}
	free(root);
}