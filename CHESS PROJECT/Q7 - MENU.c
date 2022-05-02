#include "Header.h"
#include "Hq3.h"
#include "Hq4.h"
#include "Hq5.h"
#include "Hq6.h"
#include "Hq7.h"

void printMenu()
{
	int choice;
	chessPos position;
	pathTree tr;
	chessPosList lst;
	makeEmptyChessPosList(&lst);
	char* name = { NULL };
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
			while (!flag1) /* repeat until the user insert valid pos*/
			{
				getchar();  /*for "\n"*/
				printf("Please enter row and col: \n");
				scanf("%c%c", &position[0], &position[1]);
				if (checkValid(position))
				{
					flag1 = true; /*indication for valid pos*/
					printf("The position initialized. Please continue...\n");
					selectOptions();
				}
				else
					printf("The position is not valid!!! Please try again\n");
			}
		}
		else if (choice == 2)
			choice2(&tr, &position, flag1, &flag2);  /*calling for operate this choice*/
		else if (choice == 3)
			choice3(&tr, &lst, &position, flag1, flag2, &flag3); 
		else if (choice == 4)
		{
			if (flag1)  /*checks if the user inserts position*/
			{
				if (!flag3) /*if he did - checks if choice3 operated*/
					choice3(&tr, &lst, &position, flag1, flag2, &flag3); /*if not - operate coice 3*/
				name = inputName(&lst);
				saveListToBinFile(name, &lst);
				printf("The file created. Please continue...\n");
				selectOptions();
			}
			else
				errorMessage();
		}
		else if (choice == 5)
		{
			if (!flag1) /*gets "\n"*/
				getchar();
			name = inputName(&lst);
			int result = checkAndDisplayPathFromFile(name);
			options5(result);  /*printing message according to the result*/
			finished = true;  /*finishing the rutine*/
		}
		else
			printf("Please enter valid number (1-6) !!!!!\n");

		if (finished)
		{
			ending(name, &lst, &tr);
			flag1 = flag2 = flag3 = finished = false;  /*reboots parameters*/
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
	/*row between A to H and col between 1 to 8*/
	if ((position[0] >= 'A') && (position[0] <= 'H') && (position[1] >= '1') && (position[1] <= '8'))
		return true;
	return false;

}

void choice2(pathTree* tr, chessPos* position, bool flag1, bool* flag2)
{
	if (flag1) /*checks  if the user insert pos*/
	{
		*tr = findAllPossibleKnightPaths(position);
		*flag2 = true;
		printf("The path has created. Please continue...\n");
		selectOptions();
	}
	else
		errorMessage();
}

void choice3(pathTree* tr, chessPosList* lst, chessPos* position, bool flag1, bool flag2, bool* flag3)
{
	chessPosList* tmpList = NULL;
	if (flag1)
	{
		if (flag2) /*check is the user create a path*/
		{
			tmpList = findKnightPathCoveringAllBoard(tr);
		}
		else
		{
			/*if not - create path from choice 2*/
			choice2(tr, position, flag1, &flag2);
			tmpList = findKnightPathCoveringAllBoard(tr);
		}
		freeTree(*tr);

		if (tmpList == NULL)
			printf("The path does not cover all the board!!!\n");
		else
		{
			printf("This path is covering all the board :)\n Please continue...\n");
			*lst = *tmpList;
		}
		selectOptions();
		*flag3 = true;  /*choice 3 is operated*/
	}
	else
		errorMessage();
}

char* inputName()
{
	char* name = (char*)malloc(sizeof(char));
	checkMemory(name);
	int lsize = 1, psize = 0;
	printf("Please enter name of file: \n");
	char ch = getchar();
	while (ch != '\n')
	{
		if (lsize == psize)
		{
			lsize *= 2;
			name = (char*)realloc(name, (lsize + 1) * sizeof(char));
		}
		name[psize] = ch;
		psize++;

		ch = getchar();
	}
	name[psize] = '\0';
	name = (char*)realloc(name, (psize + 6) * sizeof(char));
	name[psize + 5] = '\0';
	sprintf(name, "%s%s", name, ".bin"); // adding .bin to the end
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

void ending(char* name, chessPosList* lst)
{
	free(name);
	freeList(lst);
	printf("Please enter a key to return the menu!\n");
	getchar();
	system("cls");
	message();
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

void selectOptions()
{
	printf("Select one of the menu options: \n");
}