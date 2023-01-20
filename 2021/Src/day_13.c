/*
	AUTHOR:		Molnar Mate
	DATE:		2022.07.10.
	INPUT FILE:	..\txt_inputs\day_13.txt

	####################################################################################################
	AOC description
	
jobb = magasság = y
x fold = függőleges
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

#define PLANE_SIZE_X 1308
#define PLANE_SIZE_Y 895


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
		input->folds[line - 795].axis = token2[11];
		while(token2 != NULL)					//extract all other tokens in line
		{
			input->folds[line - 795].val = strtol(token2, &end, 10);
			token2 = strtok(NULL, "=");
		}	 
	}
}

void print_plane(char plane[PLANE_SIZE_Y][PLANE_SIZE_X])
{
	for (uint16_t row = 0; row < PLANE_SIZE_Y; row++)
	{
		for (uint16_t col = 0; col < PLANE_SIZE_X; col++)
		{
			printf("%c", plane[row][col]);
		}
		printf("\n");
	}
}

void create_plane(input_t *input, char plane[PLANE_SIZE_Y][PLANE_SIZE_X])
{
	for (uint16_t row = 0; row < PLANE_SIZE_Y; row++)
	{
		for (uint16_t col = 0; col < PLANE_SIZE_X; col++)
		{
			plane[row][col] = '.';
		}
	}	

	for(int i = 0; i < 794; i++)
	{
		plane[input->coordinates[i].y][input->coordinates[i].x] = '#';
		//printf("[%d,%d]\n",input->coordinates[i].y, input->coordinates[i].x);
	}
}

void fold(char plane[PLANE_SIZE_Y][PLANE_SIZE_X], input_t *input, uint8_t fold_num)
{
	char fold_axis = input->folds[fold_num].axis;
	uint16_t fold_val = input->folds[fold_num].val;

	if(fold_axis == 'x')
	{
		for (uint16_t row = 0; row < PLANE_SIZE_Y; row++)
		{
			for (uint16_t col = 0; col < PLANE_SIZE_X; col++)
			{
				// move hashes
				if(col > fold_val && plane[row][col]=='#')
				{
					plane[row][fold_val - (col - fold_val)] = '#';
				}
				// x out folded away area
				if(col >= fold_val)
				{
					plane[row][col] = 'x';
				}
			}
		}
	}

	if(fold_axis == 'y')
	{
		for (uint16_t col = 0; col < PLANE_SIZE_X; col++)
		{
			for (uint16_t row = 0; row < PLANE_SIZE_Y; row++)
			{
				// move hashes
				if(row > fold_val && plane[row][col]=='#')
				{
					plane[fold_val - (row - fold_val)][col] = '#';
				}
				// x out folded away area
				if(row >= fold_val)
				{
					plane[row][col] = 'x';
				}
			}
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

	char plane[PLANE_SIZE_Y][PLANE_SIZE_X];
	create_plane(&input, plane);
	//print_plane(plane);	

	// PART 1
	fold(plane, &input, 0);
	for (uint16_t col = 0; col < PLANE_SIZE_X; col++)
	{
		for (uint16_t row = 0; row < PLANE_SIZE_Y; row++)
		{
			if(plane[row][col] == '#')
			{
				result_1++;
			}
		}
	}
	printf("result_1 = %lu\n", result_1);

	// PART 2
	for(int i = 1; i < 12; i++)
	{
		fold(plane, &input, i);
	}
	printf("result_2 =\n");
	for (uint16_t row = 0; row < 6; row++)
	{
		for (uint16_t col = 0; col < 40; col++)
		{
			printf("%c", plane[row][col]);
		}
		printf("\n");
	}


    return E_OK;
}

/*
 * biggest headaches:
 * 		- mixed up matrix dimensions resulting in duoble markings
*/
