#include "Header.h"
#include "Hq1.h"

chessPosArray*** validKnightMoves()
{
	/* creating SIZE*SIZE array */
	chessPosArray*** arr = (chessPosArray***)malloc(SIZE * sizeof(chessPosArray**));
	checkMemory(arr);
	chessPosArray** inArr;
	chessPosArray* cell;

	/* creating positions's array in any cell of the 8x8 array */
	for (int row = 0; row < SIZE; row++)
	{
		inArr = (chessPosArray**)malloc(SIZE * sizeof(chessPosArray*));
		checkMemory(inArr);

		for (int col = 0; col < SIZE; col++)
		{
			cell = insertCoord(row, col); /* checking array limits */
			inArr[col] = cell;
		}
		arr[row] = inArr;
	}
	return arr;
}

chessPosArray* insertCoord(int row, int col)
{
	chessPosArray* newCell = (chessPosArray*)malloc(sizeof(chessPosArray));
	checkMemory(newCell);
	newCell->positions = (chessPos*)malloc(MAX_POSITION * sizeof(chessPos));
	checkMemory(newCell->positions);
	int count = 0;

	/* checking all the possible moves in the array */
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
	checkMemory(newCell->positions);
	newCell->size = count;
	return newCell;
}