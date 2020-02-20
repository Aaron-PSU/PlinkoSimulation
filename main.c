/*Aaron dawson
Plinko: a simulation of the game plinko
*/

#include "hw1given.h"
#include <stdio.h>


int main()
{

	char ** board;
	int * stats;
	int i, j, width, height, n, index, LoR, selection;
	float num, total;
	char junk;
	FILE * plinkoFile;

	InitRandom();

/*
	selecting the board
*/
	printf("which plinko board would you like to use: 1, 2, or 3?\n");
	scanf("%i", &selection);

	if(selection == 1)
		plinkoFile = fopen("plinko1.txt", "r");
	else if(selection == 2)
		plinkoFile = fopen("plinko2.txt", "r");
	else if(selection == 3)
		plinkoFile = fopen("plinko3.txt", "r");
	else{
		printf("error: selection is not 1, 2, or 3.  Using the default, board1\n");
		plinkoFile = fopen("plinko1.txt", "r");
	}
/*
	this section reads in the plinko board from the .txt file
*/
	if(plinkoFile != NULL)
		fscanf(plinkoFile, "%i" "%c" "%i", &width, &junk, &height);
	else
		printf("sorry, file could not be opened");

	board = (char**)malloc(sizeof(char*) * (height+1));
	printf("\nwidth:%i height:%i\n\n", width, height);	
	for( i=0 ; i<height ; ++i){
		board[i] = (char*) malloc(sizeof(char) * (width+1));
		fscanf(plinkoFile, "%s", board[i]);
		board[i][width] = '\0';
		printf("%s\n", board[i]);
	}
	
	stats = (int*) malloc(sizeof(int) *(width));	
	fclose(plinkoFile);

/*
	this srction repeats the simulation the number of times specified
*/
	printf("\nHow many times would you like to run this simulation?\n");
	scanf("%i", &n);

	for( i=0 ; i < n ; ++i){
		index = GetRandom(1, (width-1));
		for( j=0 ; j<height ; ++j){
			if(board[j][index] == 'X'){
				LoR = GetRandom(1,2);	
				if(LoR == 1){
					--index;
					if(board[j][index] == 'X')
						index += 2;
				}
				else{
					++index;
					if(board[j][index] == 'X')
						index -=2;
				}
			}
		}
		++stats[index];	
	}
/*
	this section prints out the results
*/
	printf("\n\n**************************************************************************\n");
	printf("Read from left to right. The first column is column 0 because it is all 'X'\n\n");

	for( i=0 ; i < width ; ++i){
		if(stats[i] != 0)		{
			num = stats[i];
			total = n;
			total = (num/total)*100;
			printf("the disc landed in column %i: %f percent of the time.\n",i, total);
		}
	}

	for( i=1 ; i<height ; ++i)
		free(board[i]);
	free(board);
	free(stats);
	
	return 0;
}
