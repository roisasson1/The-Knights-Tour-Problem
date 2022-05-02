#ifndef GENERAL_HEADER_H
#define GENERAL_HEADER_H

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


void initBoolTable(bool arr[][SIZE]);
/*This func initialize table to false*/

treeNode* createNewTNode(chessPos startingPos);
/*create tree node from data of pos*/
bool isEmptyList(treeNodeListCell* head);
/*checking if there isn't next possivle moves*/

void insertTDataToStartList(treeNode* root, treeNode* data);
/*insert data of tree node to list*/
treeNodeListCell* createNewListNode(treeNode* data);
/*create list node from data of tree node*/

void insertTNodeToStartList(treeNode* root, treeNodeListCell* node);
/* insert tree node to the beggining of the list*/

void makeEmptyChessPosList(chessPosList* lst);
bool isEmptyChessPosList(chessPosList* lst);
void insertDataToStartChessPosList(chessPosList* lst, treeNode* node);
/*insert tree node data to list*/

chessPosCell* createNewChessPosCell(treeNode* data);
/*create new chess pos cell from tree node*/

void insertNodeToStartChessPosList(chessPosList* lst, chessPosCell* head);
/*insert chess pos cell to the beginning of the chess pos list*/

void freeList(chessPosList* lst);
void insertDataToEndChessPosList(chessPosList* lst, char row, char col);
chessPosCell* createNewChessPosListNode(char row, char col, chessPosCell* next);
void insertNodeToEndChessPosList(chessPosList* lst, chessPosCell* tail);

void checkMemory(void* arr);
void checkFile(FILE* fp);
void freeTree(pathTree tr);
void freeTreeHelper(treeNode* root);

#endif

