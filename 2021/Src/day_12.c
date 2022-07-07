/*
	AUTHOR:		Molnar Mate
	DATE:		2022.07.05.
	INPUT FILE:	..\txt_inputs\day_12.txt

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

#define INPUT_FILE			"..\\txt_inputs\\day_12.txt"
#define LINES		25		//number of rows in input txt 
#define COLS		10		//max line length in input txt
char txt[LINES][COLS+2];	//+2 for read input()'s +'\0'


//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	char start[5];
	char end[5];
} way_t;

typedef struct
{
	way_t ways[25];
} cave_t;

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

void process_input(cave_t *cave)//ADD PARAM
{
	char *token = NULL;
	char delim[] = "-";

	for(int line = 0; line < LINES; line++)
	{
		token = strtok(txt[line], delim);
		uint8_t cnt = 0;
		while( token != NULL )
		{
			switch(cnt)
			{
				case 0:
					strcpy(cave->ways[line].start, token);
					break;
				case 1:
					strcpy(cave->ways[line].end, token);
					break;
				default:
					break;
			}
			token = strtok(NULL, delim);
			cnt++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint32_t result_2 = 0;

	cave_t cave = {{0,0}};

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_input(&cave);//ADD PARAM

	for (int i = 0; i < 25; i++)
	{
		printf("-%s", cave.ways[i].start);
		printf(" %s\n", cave.ways[i].end);
	}

	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);


    return E_OK;
}

/*
 * biggest headaches:
 * 		- ...
*/
