/*
	AUTHOR:		Molnar Mate
	DATE:		2022.06.30.
	INPUT FILE:	..\txt_inputs\day_09.txt

	####################################################################################################
	AOC description
	

//////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define INPUT_FILE			"..\\txt_inputs\\day_09.txt"
#define NUMBER_OF_LINES		100				//number of rows in input txt 
#define LENGTH_OF_LINES		(100+2)			//max line length in input txt
#define MAP_SIZE			102				//100×100 input + frame out of 9s
char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt


//////////////////////////////////////////////////////////////////////////////////////////////////

//structure

//////////////////////////////////////////////////////////////////////////////////////////////////

bool read_input(char* fileName) 
{
	FILE *pFile = fopen(fileName, "r");
	if (pFile == 0)
	{
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

void process_input(uint8_t value_map[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if(i == 0 || i == MAP_SIZE-1 || j == 0 || j == MAP_SIZE-1)
			{
				value_map[i][j] = 9;
			}
			else
			{
				value_map[i][j] = txt[i-1][j-1]-'0';
			}
		}
	}
}

void print_value_map(uint8_t value_map[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			printf("%d", value_map[i][j]);
		}
		printf("\n");
	}
}

uint32_t calculate_risk_level(uint8_t value_map[MAP_SIZE][MAP_SIZE])
{	
	uint32_t risk_level = 0;
	uint8_t curr_val = 0;

	//iterating through the inner values (not counting the "9 frame")
	for (int y = 1; y < MAP_SIZE-1; y++)
	{
		for (int x = 1; x < MAP_SIZE-1; x++)
		{
			uint8_t curr_val = value_map[y][x];
			if(	curr_val < value_map[y-1][x] && 
				curr_val < value_map[y+1][x] && 
				curr_val < value_map[y][x-1] && 
				curr_val < value_map[y][x+1])
				{
					risk_level += curr_val + 1;
				}
		}
	}
	return risk_level;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint32_t result_2 = 0;

	uint8_t value_map[MAP_SIZE][MAP_SIZE] = {{0},{0}}; //100×100 initial map + 1 thick "9" frame

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_input(value_map);
	//print_value_map(value_map);

	result_1 = calculate_risk_level(value_map);

	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- ...
*/