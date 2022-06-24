/*
	AUTHOR:		Molnar Mate
	DATE:		2022.

	INPUT FILE:	..\txt_inputs\day_XX.txt
				(description of txt)

	TASK-1:		
    TASK-2:     


	SOLUTION-1: 
	SOLUTION-2: 
//////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define INPUT_FILE			"..\\txt_inputs\\day_04.txt"
#define NUMBER_OF_LINES		500		//number of rows in input txt 
#define LENGTH_OF_LINES		18		//max line length in input txt
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

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}

    return 0;
}

/*
 * biggest headaches:
 * 		- ...
*/