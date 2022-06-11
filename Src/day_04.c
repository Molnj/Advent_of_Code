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
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define PT1 1
#define PT2 2

#define INPUT_FILE			"inputs\\day_04.txt"
#define NUMBER_OF_LINES		601		//number of rows in input txt 
#define LENGTH_OF_LINES		300		//max line length in input txt

#define BOARD_WIDTH			5
#define BOARD_HEIGHT		5
#define BOARD_SIZE			BOARD_HEIGHT * BOARD_WIDTH
#define NUM_OF_BOARDS		100		//number of boards

#define NUM_OF_DRAWS		100		// list of drawn numbers (1st line) contains 100 numbers	//bingo numbers here range 1-99 (in reality 1-75 or 1-90)


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
	int drawn_numbers[NUM_OF_DRAWS];
	uint32_t draw_count;
	int number_of_winning_boards;
} bingo_game_t;


int main()
{	
	bingo_game_t bingo;

	int
	if (read_first_line_into_number_list(INPUT_FILE, bingo.))
	{

	}
	char line[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt
	int numbers_drawn [INPUT_NUM];			//number of drawn characters (1st line)
	int bingo_boards [BOARD_NUMBER][BOARD_HEIGHT][BOARD_WIDTH];				//100 pieces of 5x5 bingo boards, stacked

	int cnt = 0;
	char *token;

	int win_cnt = 0;


	// OPEN INPUT FILE
	FILE *pFile = fopen(INPUT_FILE, "r");
	if (pFile == 0)
	{
		printf("Could not find input file.\n");
		return 1;
	}


	// TXT --> CHAR[row][column]
	int i = 0;
	int total = 0;
	while(fgets(line[i], LENGTH_OF_LINES, pFile))
	{
		line[i][strlen(line[i]) - 1] = '\0';
		i++;
	}
	total = i;
	fclose(pFile);


	// CREATE NUMBERS TO BE DRAWN --- CHAR --> INT ("," delimiter)
	cnt = 0;
	token = strtok(line[0], ",");
	while( token != NULL )
	{
		numbers_drawn[cnt] = atoi(token);
		token = strtok(NULL, ",");
		cnt++;
	}


	//CREATE BINGO CARD STACK
	int x = 0;
	int y = 0;
	int z = 0;	// int x, y, z = 0; not working - TODO ?
	cnt = 0;

	for(int i=2 ; i<NUMBER_OF_LINES ; i++)
	{
		if(cnt != 5)
		{
			x = 0;
			token = strtok(line[i], " ");
			while( token != NULL )
			{
				bingo_boards [z][y][x] = atoi(token);
				token = strtok(NULL, " ");
				x++;
			}
			y++;
			cnt++;
		}
		else
		{
			cnt = 0;
			x = 0;
			y = 0;
			z++;
		}
	}

	// START DRAWING NUMBERS
	for(i=0; i<INPUT_NUM; i++)
	{
		printf("\nNumber drawn: %d ",numbers_drawn[i]);
		
		//MARK CARDS
		for(z=0 ; z<100 ; z++)
		{
			for(y=0 ; y<5 ; y++)
			{
				for(x=0 ; x<5 ; x++)
				{
					if (bingo_boards[z][y][x] == numbers_drawn[i])
					{
						bingo_boards[z][y][x] = -1;
					}
				}
			}
		}


		//CHECK CARDS
		for(z=0 ; z<100 ; z++)
		{
			for(y=0 ; y<5 ; y++)
			{
				win_cnt = 0;
				for(x=0 ; x<5 ; x++)
				{
					if (bingo_boards[z][y][x] == -1) {win_cnt++;}
					if (win_cnt == 5)
					{
						printf("WINNING CARD (vertical): %d", z);
						//CALCULATE POINTS
						int unmarked_sum = 0;
						for(y=0 ; y<5 ; y++)
						{
							for(x=0 ; x<5 ; x++)
							{
								if (bingo_boards[z][y][x] != -1) {unmarked_sum += bingo_boards[z][y][x];}
							}

						}
						int result = unmarked_sum * numbers_drawn[i];
						printf("\nRESULT: %d", result);
						exit(0);
					}
				}
			}
			for(x=0 ; x<5 ; x++)
			{
				win_cnt = 0;
				for(y=0 ; y<5 ; y++)
				{
					if (bingo_boards[z][y][x] == -1) {win_cnt++;}
					if (win_cnt == 5)
					{
						printf("WINNING CARD (horizontal): %d", z);
						//CALCULATE POINTS
						int unmarked_sum = 0;
						for(y=0 ; y<5 ; y++)
						{
							for(x=0 ; x<5 ; x++)
							{
								if (bingo_boards[z][y][x] != -1) {unmarked_sum += bingo_boards[z][y][x];}
							}

						}
						int result = unmarked_sum * numbers_drawn[i];
						printf("\nRESULT: %d", result);
						exit(0);
					}
				}
			}
		}
	}

	
}




