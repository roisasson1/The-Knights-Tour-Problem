#include "Header.h"
#include "Hq5.h"

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
	unsigned int sizeArr = calcSize(sizeOfPos); /*calculating size arr*/
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
	int size = 6 * sizeOfPos; /* the position catch 6 bits. 3 for the row, 3 for the col*/
	if (size % 8 != 0) /*check if all bits positions are devided to 8. if not devided - adding 1 more cell in in the array.*/
		return size / 8 + 1;
	else  /* if devided - return this size*/
		return size / 8;
}

BYTE* createBytesArr(int sizeArr, chessPosList* lst)
{
	chessPosCell* curr = lst->head;
	BYTE saver = 0x00, saverLeft = 0x00, saverRight = 0x00, row, col, endByte = 0x00;
	BYTE* bytesArr = (BYTE*)malloc(sizeArr * sizeof(BYTE));
	checkMemory(bytesArr);
	int i;

	for (i = 0; i < sizeArr; i++) /*insert positions bits to array*/
	{
		BYTE val = 0x00;
		/*inserting to row and col current position*/
		row = curr->position[0] - 'A'; 
		col = curr->position[1] - '1';

		/*the algorithm is made of 3 parts in repeat. every 3 indices and 4 pos, the proccess starts over*/
		if ((i + 1) % 3 == 1)
		{
			/*the first part
			  byte that built in shape of b7b6b5 b4b3b2 b1b0*/
			if (i != 0)  /*this condition happen after the first iteration for taking the next pos*/
			{
				curr = curr->next;
				row = curr->position[0] - 'A';
				col = curr->position[1] - '1';
			}
			val |= row << 5;  /*position represented by 3 right bits. we shift them 5 left*/
			val |= col << 2;  /*placing the 3 bits of the col after the row*/
			if (curr->next != NULL) /*check if there is another pos to insert*/
			{
				/* if there is - we deviding the new row pos for 2*/
				saver = curr->next->position[0] - 'A'; //if is a - 0000 0001
				saverLeft = saver >> 1;     /*for saving the 2 left bits of the pos*/
				saverRight = saver << 7;   /*for saving the right bit that left for next iteration*/
				val |= saverLeft;         /*placing the left part of the bit in the end and complete a byte*/
			}
			else /*placing 0's in the end of the byte*/
				val |= endByte;
		}
		else if ((i + 1) % 3 == 2)
		{
			/*the second part
			  byte that built in shape of b7 b6b5b4 b3b2b1 b0*/
			val |= saverRight;    /*inerrt the right part of the current row*/
			val |= col << 4;      /*placing the col*/
			if (curr->next != NULL)
			{
				/*if there is  - placing the next row and dividing the next col*/
				row = curr->next->position[0] - 'A'; 
				val |= row << 1;     
				saver = curr->next->position[1] - '1';  
				saverLeft = saver >> 2;    /*in the left we save the left bit of the pos*/
				saverRight = saver << 6;   /* the right contains the other bits*/
				val |= saverLeft; // 0011 0010
			}
			else
				val |= endByte;
		}
		else if ((i + 1) % 3 == 0)
		{
			/*the third part
			  byte that built in shape of b7b6 b5b4b3 b2b1b0*/
			val |= saverRight; /*placing the rest of the current col*/
			if (curr->next != NULL)
			{
				/*if there is - insert the next pos to row and col and placing them*/
				row = curr->next->position[0] - 'A';
				col = curr->next->position[1] - '1';
				val |= row << 3;
				val |= col;
			}
			else
				val |= endByte;
		}

		bytesArr[i] = val; /*insert the value of the combined byte to the array*/
		curr = curr->next;
	}
	return bytesArr;
}