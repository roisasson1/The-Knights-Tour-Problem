#include "Header.h"
#include "Hq6.h"
#include "Hq5.h"
#include "Hq2.h"

int checkAndDisplayPathFromFile(char* file_name)
{
	FILE* fp = fopen(file_name, "rb");

	if (fp == NULL)   /*file doesn't exist*/
		return -1;
	else
	{
		short int sizeOfPos;
		int result;
		chessPosList posList;

		bool legalPath;

		fread(&sizeOfPos, sizeof(short int), 1, fp);
		if (sizeOfPos == 0) /*check situation of file with 0 positions*/
		{
			makeEmptyChessPosList(&posList);
			fclose(fp);
			return 3;
		}
		else
		{ /* creating bytes array for reading data from the file*/
			BYTE* bytesArr;
			int sizeArr = calcSize(sizeOfPos);
			bytesArr = (BYTE*)malloc(sizeArr * sizeof(BYTE));
			checkMemory(bytesArr);
			fread(bytesArr, sizeof(BYTE), sizeArr, fp);
			posList = createChessPosList(bytesArr, sizeArr, sizeOfPos); /*converting the array to position list*/
			free(bytesArr);
		}

		fclose(fp);
		legalPath = isPathLegal(posList); /*chceking if path is legal*/
		result = resultOfLegality(legalPath, &posList); /*gets the result of the legality*/

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
		/*the algorithm is made of 3 parts in repeat*/
		if ((i + 1) % 3 == 1)
		{
			/*checking the indices that devided by 3*/
			row = (bytesArr[i] >> 5) + 'A'; /*placing the 3 bits that represents the row*/
			mask = 0x07;      /*initializing the mask to 0000 0111 for setting the bit*/
			col = (mask & (bytesArr[i] >> 2)) + '1';  /*placing the 3 bits of col*/
			insertDataToEndChessPosList(&lst, row, col);  /*insert the pos to the list*/
			countPos++;
			if (countPos < sizeOfPos) /*checks if we convert all positions*/
			{
				/* in case we dont convert all*/
				mask = 0x03;    /*intializing the mask to 0000 0011 for setting the rest bits*/
				saverLeft = mask & bytesArr[i]; /* saving the bits that left for next iteration*/
			}

		}
		else if ((i + 1) % 3 == 2)
		{
			row = ((bytesArr[i] >> 7) | (saverLeft << 1)) + 'A';/*creating the devided pos and inserting to row*/
			mask = 0x07;
			col = (mask & (bytesArr[i] >> 4)) + '1'; 
			insertDataToEndChessPosList(&lst, row, col);
			countPos++;
			if (countPos < sizeOfPos)
			{
				row = (mask & (bytesArr[i] >> 1)) + 'A'; /*placing the bits of the row*/
				mask = 0x01;
				saverLeft = mask & bytesArr[i]; /*saving the last bit*/
			}
		}
		else if ((i + 1) % 3 == 0)
		{
			col = ((bytesArr[i] >> 6) | (saverLeft << 2)) + '1'; /*creating the devided pos and inserting to col */
			insertDataToEndChessPosList(&lst, row, col);
			countPos++;
			if (countPos < sizeOfPos)
			{
				mask = 0x07;
				row = (mask & (bytesArr[i] >> 3)) + 'A'; /* placing the row*/
				col = (mask & bytesArr[i]) + '1';        /*placing th col*/
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

	/*checking every possible next move. if the next pos is one of them - return true*/
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
		display(lst);  /*calling to func of q2*/
		int listLen = countPos(lst);
		if (listLen == (SIZE * SIZE)) /*checks if the list covers all board*/
			return 2;
		else
			return 3;
	}
	else
		return 1;
}