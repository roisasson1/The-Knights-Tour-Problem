#ifndef HQ5_H
#define HQ5_H

#include "Header.h"

void saveListToBinFile(char* file_name, chessPosList* pos_list);
/*This func gets name of file and list, and creating a binary file of the positions list*/

int countPos(chessPosList* lst);
/*This func counts how many positions the list has*/

int calcSize(int sizeOfPos);
/*This func calculate the size of the bytes array that we want creating.*/

BYTE* createBytesArr(int sizeArr, chessPosList* lst);
/* this func creates the bytes array of the positins. We gets the position from the list*/

#endif