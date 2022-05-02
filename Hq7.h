#ifndef HQ7_H
#define HQ7_H

#include "Header.h"

void printMenu();
/*This func prints the menu*/

bool checkValid(chessPos position);
/*This func check the validation of the position the user insert*/

chessPos* choice1(bool* flag1);
/*This func operates choice 1 if the user choose it*/

void choice2(pathTree* tr, chessPos* position, bool flag1, bool* flag2);
/*This func operates choice 2 if the user choose it*/

void choice3(pathTree* tr, chessPosList* lst, chessPos position, bool flag1, bool flag2, bool* flag3);
/*This func operates choice 3 if the user choose it*/

char* inputName();
/*This func get name from the user and adding ".bin" for creating binary file*/

void options5(int result);
/*This func prints message according to operation of option 5*/

void message();
/*This func prints the content of the menu */

void errorMessage();
/*This func prints error message if the user insert invalid row and col*/

void selectOptions();
/*This func prints to user choose again one of the option menu*/

void ending(char* name, chessPosList* lst);
/*This func free the name & list and clear the screen for new rutine*/

#endif
