/*
	AUTHOR:		Molnar Mate
	DATE:		2022.xx.xx.
	INPUT FILE:	..\txt_inputs\day_XX.txt

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

#define INPUT_FILE			"..\\txt_inputs\\day_xx.txt"
#define LINES		500		//number of rows in input txt 
#define COLS		18		//max line length in input txt
char txt[LINES][COLS+2];	//+2 for read input()'s +'\0'


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
	while(fgets(txt[i], COLS+2, pFile)) //+2 for '\0'
	{
		txt[i][strlen(txt[i]) - 1] = '\0';
		i++;
	}

	fclose(pFile);
	return E_OK;
}

void process_input()//ADD PARAM
{
	char *token = NULL;
	char *end = NULL;
/* 	
 	for(int line = 0; line < 795; line++)
	{
		char *token = strtok(txt[line], ",");	//extract first token in line
		//first token
		while(token != NULL)					//extract all other tokens in line
		{
			//next token
			token = strtok(NULL, " ");
		}
	}
 */
}


//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint32_t result_2 = 0;

	//STRUCT

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_input();//ADD PARAM

	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);


    return E_OK;
}

/*
 * biggest headaches:
 * 		- ...
*/
