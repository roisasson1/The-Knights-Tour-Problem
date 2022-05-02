#ifndef HQ6_H
#define HQ6_H

#include "Header.h"


int checkAndDisplayPathFromFile(char* file_name);
/*This func check the list that got from the file and return number due to the options*/

chessPosList createChessPosList(BYTE* bytesArr, int sizeArr, int sizeOfPos);
/*This func create list from the array we read*/

bool isPathLegal(chessPosList lst);
/*This func checks if the path of positions is leagl*/

bool checkNextMoveLegality(int row, int col, chessPosCell* next);
/*This func check the legality from the current pos to the next one*/

int resultOfLegality(bool legalPath, chessPosList* lst);
/*This func returning the options according to the path*/

#endif