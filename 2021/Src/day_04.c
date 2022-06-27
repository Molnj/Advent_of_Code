/*
	AUTHOR:		Molnar Mate
	DATE:		2022.03.15.
	INPUT FILE:	..\txt_inputs\day_04.txt

	####################################################################################################
	--- Day 4: Giant Squid ---
	You're already almost 1.5km (almost a mile) below the surface of the ocean, already so deep that you can't see any sunlight. What you can see, however, is a giant squid that has attached itself to the outside of your submarine.

	Maybe it wants to play bingo?

	Bingo is played on a set of boards each consisting of a 5x5 grid of numbers. Numbers are chosen at random, and the chosen number is marked on all boards on which it appears. (Numbers may not appear on all boards.) If all numbers in any row or any column of a board are marked, that board wins. (Diagonals don't count.)

	The submarine has a bingo subsystem to help passengers (currently, you and the giant squid) pass the time. It automatically generates a random order in which to draw numbers and a random set of boards (your puzzle input). For example:

	7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

	22 13 17 11  0
	8  2 23  4 24
	21  9 14 16  7
	6 10  3 18  5
	1 12 20 15 19

	3 15  0  2 22
	9 18 13 17  5
	19  8  7 25 23
	20 11 10 24  4
	14 21 16 12  6

	14 21 17 24  4
	10 16 15  9 19
	18  8 23 26 20
	22 11 13  6  5
	2  0 12  3  7
	After the first five numbers are drawn (7, 4, 9, 5, and 11), there are no winners, but the boards are marked as follows (shown here adjacent to each other to save space):

	22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
	8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
	21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
	6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
	1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
	After the next six numbers are drawn (17, 23, 2, 0, 14, and 21), there are still no winners:

	22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
	8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
	21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
	6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
	1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
	Finally, 24 is drawn:

	22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
	8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
	21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
	6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
	1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
	At this point, the third board wins because it has at least one complete row or column of marked numbers (in this case, the entire top row is marked: 14 21 17 24 4).

	The score of the winning board can now be calculated. Start by finding the sum of all unmarked numbers on that board; in this case, the sum is 188. Then, multiply that sum by the number that was just called when the board won, 24, to get the final score, 188 * 24 = 4512.

	To guarantee victory against the giant squid, figure out which board will win first. What will your final score be if you choose that board?

	Your puzzle answer was 6592.

	--- Part Two ---
	On the other hand, it might be wise to try a different strategy: let the giant squid win.

	You aren't sure how many bingo boards a giant squid could play at once, so rather than waste time counting its arms, the safe thing to do is to figure out which board will win last and choose that one. That way, no matter which boards it picks, it will win for sure.

	In the above example, the second board is the last to win, which happens after 13 is eventually called and its middle column is completely marked. If you were to keep playing until this point, the second board would have a sum of unmarked numbers equal to 148 for a final score of 148 * 13 = 1924.

	Figure out which board will win last. Once it wins, what would its final score be?

	Your puzzle answer was 31755.

	Both parts of this puzzle are complete! They provide two gold stars: **
//////////////////////////////////////////////////////////////////////////////////////////////////
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define INPUT_FILE			"..\\txt_inputs\\day_04.txt"
#define NUMBER_OF_LINES		601		//number of rows in input txt 
#define LENGTH_OF_LINES		300		//max line length in input txt

char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt

#define BOARD_WIDTH			5
#define BOARD_HEIGHT		5
#define BOARD_SIZE			(BOARD_HEIGHT * BOARD_WIDTH)
#define NUM_OF_BOARDS		100		//number of boards
#define NUM_OF_DRAWS		100		// list of drawn numbers (1st line) contains 100 numbers	//bingo numbers here range 1-99 (in reality 1-75 or 1-90)

int result_1, result_2;

//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct __attribute__((packed))
{
	int value;
	bool marked;
} bingo_board_number_t;


typedef struct __attribute__((packed))
{
	bingo_board_number_t board_numbers[BOARD_HEIGHT][BOARD_WIDTH];
	bool board_won;
} bingo_board_t;


typedef struct __attribute__((packed))
{
	bingo_board_t boards[NUM_OF_BOARDS];
	int draw_list[NUM_OF_DRAWS];
	uint32_t draw_count;
	int number_of_winning_boards;
	int last_winning_board;
} bingo_game_t;

//////////////////////////////////////////////////////////////////////////////////////////////////

bool read_input(char* fileName) 
{
	FILE *pFile = fopen(fileName, "r");
	if (pFile == 0)
	{
		printf("Could not find input file: %s.\n", fileName);
		return E_NOT_OK;
	}

	// .TXT --> CHAR[row][column]
	int i = 0;
	while(fgets(txt[i], LENGTH_OF_LINES, pFile))
	{
		txt[i][strlen(txt[i]) - 1] = '\0';
		i++;
	}

	fclose(pFile);
	return E_OK;
}


void print_items(bingo_game_t *bingo)
{
	for(int i = 0; i<100; i++)
	{
		printf("%d, ", bingo->draw_list[i]);
	}
	printf("\n\n");

	for(int  z= 0; z<100; z++)
	{
		printf("%d\n", z+1);
		for(int y = 0; y<5; y++)
		{
			for(int x = 0; x<5; x++)
			{
				printf("%d\t", bingo->boards[z].board_numbers[y][x].value);
			}
			printf("\n");
		}
		printf("\n");
	}
}


void create_draw_list(bingo_game_t *bingo)
{
	int idx = 0;
	char *token = strtok(txt[0], ",");
	char *pEnd;
	while( token != NULL )
	{
		int placeholder_for_some_reason = atoi(token);//strtol(token, &pEnd, 10);
		bingo->draw_list[idx] = placeholder_for_some_reason;
		token = strtok(NULL, ",");
		idx++;
	}
}


void create_bingo_sheets(bingo_game_t *bingo)
{
	int idx = 0;
	int x, y, z;
	for(int i=2 ; i<NUMBER_OF_LINES ; i++)
	{
		if(idx != 5)
		{
			x = 0;
			char *pEnd;
			char *token = strtok(txt[i], " ");
			while( token != NULL )
			{
				int placeholder_for_some_reason = strtol(token, &pEnd, 10);
				bingo->boards[z].board_numbers[y][x].value = placeholder_for_some_reason;
				bingo->boards[z].board_numbers[y][x].marked = false;
				bingo->last_winning_board = 0;
				bingo->boards[z].board_won = false;
				token = strtok(NULL, " ");
				x++;
			}
			y++;
			idx++;
		}
		else
		{
			idx = 0;
			x = 0;
			y = 0;
			z++;
		}
	}
}


void mark_sheets(bingo_game_t *bingo, int next_draw)
{
	int x, y, z;
	for(int  z= 0; z<100; z++)
	{
		for(int y = 0; y<5; y++)
		{
			for(int x = 0; x<5; x++)
			{
				if(bingo->boards[z].board_numbers[y][x].value == next_draw)
				{
					bingo->boards[z].board_numbers[y][x].marked = true;
				}
			}
		}
	}
}


bool check_for_winner(bingo_game_t *bingo)
{
	int cnt;
	for(int z = 0; z < NUM_OF_BOARDS; z++)
	{
		//check row
		cnt = 0;
		for(int y = 0; y < BOARD_HEIGHT; y++)
		{
			for(int x = 0; x < BOARD_WIDTH; x++)
			{
				if(bingo->boards[z].board_numbers[y][x].marked)
				{
					cnt++;
				}
			}
			if(cnt == 5)
			{
				if(bingo->boards[z].board_won == false)	// need to check again, since it could have changed in row phase
				{
					//printf("Winning board: %d\n", z+1);
					bingo->boards[z].board_won = true;
					bingo->number_of_winning_boards++;
					bingo->last_winning_board = z;
					//NOTE: eredetileg itt volt return E_OK, de rontott, mert volt, hogy egyszerre több is jól lett kitöltve
				}
			}
			cnt = 0;
		}
		
		//check column
		cnt = 0;
		for(int y = 0; y < BOARD_HEIGHT; y++)
		{
			for(int x = 0; x < BOARD_WIDTH; x++)
			{
				if(bingo->boards[z].board_numbers[x][y].marked)
				{
					cnt++;
				}
			}
			if(cnt == 5)
			{
				if(bingo->boards[z].board_won == false)	// need to check again, since it could have changed in row phase
				{
					//printf("Winning board: %d\n", z+1);
					bingo->boards[z].board_won = true;
					bingo->number_of_winning_boards++;
					bingo->last_winning_board = z;
				}
			}
			cnt = 0;
		}
	}
}


int calculate_results(bingo_game_t *bingo, int winning_draw)
{
	//Result is: product of the winning drawn number and the sum of the unmarked numbers on the winning board
	int result = 0;
	int unmarked_sum = 0;
	int i = 0;

	i = bingo->last_winning_board;
 	for(int x = 0; x < BOARD_WIDTH; x++)
	{
		for(int y = 0; y < BOARD_HEIGHT; y++)
		{
			if(! bingo->boards[i].board_numbers[x][y].marked)
			{
				unmarked_sum += bingo->boards[i].board_numbers[x][y].value;
			}
		}
	}
	result = unmarked_sum * winning_draw;
	//printf("%d, %d\n", unmarked_sum, winning_draw);

	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{	
	bingo_game_t bingo;
	bingo.last_winning_board = 0;
	bingo.number_of_winning_boards = 0;

	bool win_flag = false;
	int next_draw;
	int num_of_winners;

	if(read_input(INPUT_FILE))
	{
		printf("Reading input file was not successful. Closing Application..\n");
		return E_NOT_OK;
	}

	create_draw_list(&bingo);
	create_bingo_sheets(&bingo);
	//print_items(&bingo);

	for(int i = 0; i < NUM_OF_DRAWS; i++)
	{
		next_draw = bingo.draw_list[i];
		mark_sheets(&bingo, next_draw);
		check_for_winner(&bingo);

		if(bingo.number_of_winning_boards == 1 && result_1 == 0)
		{
			result_1 = calculate_results(&bingo, next_draw);
		}
		if(bingo.number_of_winning_boards == NUM_OF_BOARDS && result_2 == 0)
		{
			result_2 = calculate_results(&bingo, next_draw);
		}
	}

	printf("Result_1: %d\n", result_1);
	printf("Result_2: %d\n", result_2);

	return E_OK;
}

/*
 * biggest headaches:
 * 		- struggles with uninitialized values in structures (34523432 instead 0)
 * 		- had to check for result == 0, otherwise condition will be fulfilled later
 * 		- check_for_winner() used to be bool and returned after finding a winner,
 *  	  this way only 66 winning board were found since simultaneous wins were not handled
 * 		- TODO - what if two or more are winning simultaneously as first/last boards?
*/