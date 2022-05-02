#include "Header.h"
#include "Hq2.h"

void display(chessPosList* lst)
{
	chessPosCell* curr, * dup;
	chessPosCell* prev = NULL;
	curr = lst->head;
	bool hasBeenTable[SIZE][SIZE];

	initBoolTable(hasBeenTable); /* initializing array with FALSE in any cell */

	/* searching for duplications and remove them from the list */
	while (curr != NULL)
	{
		int row = curr->position[0] - 'A';
		int col = curr->position[1] - '1';

		/* if the position was not "activated" before - activate it */
		if (hasBeenTable[row][col] == false)
			hasBeenTable[row][col] = true;
		else
		{
			dup = curr;
			curr = curr->next;
			freeDup(dup, prev);
		}

		/* borders of list */
		if (curr == lst->head)
			prev = lst->head;
		else
			prev = prev->next;

		if (curr != NULL)
			curr = curr->next;
	}
	locatePos(lst->head); /* inputing numbers in order of any position */
}

void freeDup(chessPosCell* dup, chessPosCell* prev)
{
	/* removing duplications in the list */
	chessPosCell* tmp;
	tmp = dup;
	dup = dup->next;
	prev->next = dup;
	free(tmp);
}

void locatePos(chessPosCell* head)
{
	chessPosCell* curr;
	chessPos table[SIZE][SIZE];
	int row, col, location = 1;

	curr = head;
	createEmptyTable(table);

	/* inputing numbers in order of any position */
	while (curr != NULL)
	{
		row = curr->position[0] - 'A';
		col = curr->position[1] - '1';

		if (location <= 9)
		{
			table[row][col][0] = ' ';
			table[row][col][1] = location + '0';
		}
		/* if the number is more than one digit */
		else if (location >= 10 && location <= (SIZE * SIZE))
		{
			table[row][col][0] = (location / 10) + '0';
			table[row][col][1] = (location % 10) + '0';
		}
		location++;
		curr = curr->next;
	}
	makeDisplay(table); /* creating the table borders */
}

void createEmptyTable(chessPos arr[][SIZE])
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

void makeDisplay(chessPos arr[][SIZE])
{
	int i, j;

	printf("\n\n    ");
	for (i = 0; i < SIZE; i++) /* print the num of any col */
		printf("%5d", i + 1);
	printf("\n   ");
	for (j = 0; j < SIZE + 2; j++)  /* print frame */
		printf("____");
	printf("\n");

	for (i = 0; i < SIZE; i++) { /*print the num of any row */
		printf("%4c |", i + 'A');
		for (j = 0; j < SIZE; j++) {
			printf(" %c%c |", arr[i][j][0], arr[i][j][1]);
		}
		printf("\n");
	}
	printf("   ");
	for (j = 0; j < SIZE + 2; j++) /* print frame */
		printf("____");
	printf("\n\n");
}