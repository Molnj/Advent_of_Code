/*
	AUTHOR:		Molnar Mate
	DATE:		2022.06.28.
	INPUT FILE:	..\txt_inputs\day_08.txt

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

#define INPUT_FILE			"..\\txt_inputs\\day_08.txt"
#define NUMBER_OF_LINES		200		//number of rows in input txt 
#define LENGTH_OF_LINES		100		//max line length in input txt
char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt

#define INPUT_CNT	10
#define	INPUT_LEN	(7+1)	// max: abcdefg + \0

#define OUTPUT_CNT	4
#define	OUTPUT_LEN	(7+1)	// max: abcdefg + \0

#define DIGIT_0		"abcefg"
#define DIGIT_1		"cf"
#define DIGIT_2		"acdeg"
#define DIGIT_3		"abdfg"
#define DIGIT_4		"bcdf"
#define DIGIT_5		"abdfg"
#define DIGIT_6		"abdefg"
#define DIGIT_7		"acf"
#define DIGIT_8		"abcdefg"
#define DIGIT_9		"abcdfg"

//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
	char input[INPUT_CNT][INPUT_LEN];
	char output[OUTPUT_CNT][OUTPUT_LEN];
} combination_t;

typedef struct 
{
	combination_t list[NUMBER_OF_LINES];
} list_t;

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

void process_input(list_t *myList)
{
	char character = '0';
	uint8_t element_num = 0;
	uint8_t element_idx = 0;

	//inputs
	for(int line = 0; line < NUMBER_OF_LINES; line++)
	{
		character = '0';
		element_num = 0;
		element_idx = 0;
		for(int idx = 0; idx < 61; idx++)//LENGTH_OF_LINES
		{
			character = txt[line][idx];
			printf("%c", character);
			if(character == ' ')
			{
				element_num++;
				element_idx = 0;
			}
			else
			{
				myList->list[line].input[element_num][element_idx] = character;
				element_idx++;
			}
		}

		element_num = 0;
		element_idx = 0;
		for(int idx = 61; idx < strlen(txt[line]); idx++)
		{
			character = txt[line][idx];
			printf("%c", character);
			if(character == ' ')
			{
				element_num++;
				element_idx = 0;
			}
			else
			{
				myList->list[line].output[element_num][element_idx] = character;
				element_idx++;
			}
		}
		printf("\n");
	}
}

uint32_t count_1478_inputs(list_t *myList)
{
	uint8_t length = 0;
	uint32_t cnt = 0;
	for(int i = 0; i < NUMBER_OF_LINES; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			length = strlen(myList->list[i].output[j]);
			if(length == 2 || length == 4 || length == 3 || length == 7)
			{
				cnt ++;
			}
		}
	}
	return cnt;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint32_t result_2 = 0;

	list_t myList = {{0}};

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_input(&myList);

	result_1 = count_1478_inputs(&myList);

	printf("result_1 = %lu\n", result_1);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- reading input :(
*/