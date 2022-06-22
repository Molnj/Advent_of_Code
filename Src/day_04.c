/*
	AUTHOR:		Molnar Mate
	DATE:		2022.03.15

	INPUT FILE:	%CD\inputs\day_04.txt
				(1st line is 300 character long list of comma separated drawn numbers)
				(followed by 100 piece of 5x5 int matrices (representing bingo sheets) separated by empty lines)

	TASK-1:		100 pieces of 5×5 bingo cards are given with 100 numbers drawn (in txt)
				find which card will have a BINGO [FIRST]
				calculate final score by: recently drawn winning number value * sum of unmarked numbers on board
	TASK-2:		100 pieces of 5×5 bingo cards are given with 100 numbers drawn (in txt)
				find which card will have a BINGO [LAST]
				calculate final score by: recently drawn winning number value * sum of unmarked numbers on board

	SOLUTION-1: 6592 (12th board wins first when 8 is drawn)
	SOLUTION-2: 31755 (40th board wins last when 87 is drawn)
//////////////////////////////////////////////////////////////////////////////////////////////////
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define PT1 1
#define PT2 2

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
	while( token != NULL )
	{
		bingo->draw_list[idx] = atoi(token);
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
			char *token = strtok(txt[i], " ");
			while( token != NULL )
			{
				int placeholder_for_some_reason = atoi(token);
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
					printf("Winning board: %d\n", z+1);
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
					printf("Winning board: %d\n", z+1);
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