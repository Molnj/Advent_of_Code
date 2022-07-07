/*
	AUTHOR:		Molnar Mate
	DATE:		2022.xx.xx.
	INPUT FILE:	..\txt_inputs\day_13.txt

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

#define INPUT_FILE			"..\\txt_inputs\\day_13.txt"
#define LINES		807		//number of rows in input txt 
#define COLS		20		//max line length in input txt
char txt[LINES][COLS+2];	//+2 for read input()'s +'\0'


//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	uint16_t x;
	uint16_t y;
} coord_t;

typedef struct
{
	char axis;
	uint16_t val;
} fold_t;

typedef struct 
{
	coord_t coordinates[795];
	fold_t folds[12];
} input_t;


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
	while(fgets(txt[i], COLS+2, pFile)) //+2 for '\0'
	{
		txt[i][strlen(txt[i]) - 1] = '\0';
		i++;
	}

	fclose(pFile);
	return E_OK;
}

void process_input(input_t *input)
{
	char *token = NULL;
	char *end = NULL;

	//get coordinates
 	for(int line = 0; line < 795; line++)
	{
		char *token = strtok(txt[line], ",");	//extract first token in line
		input->coordinates[line].x = strtol(token, &end, 10);
		while(token != NULL)					//extract all other tokens in line
		{
			input->coordinates[line].y = strtol(token, &end, 10);
			token = strtok(NULL, ",");
		}	
	}

	//get folds
	char *token2 = NULL;
 	for(int line = 795; line < LINES; line++)
	{
		char *token2 = strtok(txt[line], "=");	//extract first token in line
		input->folds[line-795].axis = token2[11];
		while(token != NULL)					//extract all other tokens in line
		{
			input->folds[line-795].val = strtol(token2, &end, 10);
			token2 = strtok(NULL, "=");
		}	
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint32_t result_2 = 0;

	input_t input = {{0,0},{0,0}};

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_input(&input);


	printf("%c---", input.folds[11].axis);

	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);


    return E_OK;
}

/*
 * biggest headaches:
 * 		- ...
*/
