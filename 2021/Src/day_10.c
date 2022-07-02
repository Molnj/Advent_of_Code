/*
	AUTHOR:		Molnar Mate
	DATE:		2022.07.01.
	INPUT FILE:	..\txt_inputs\day_10.txt

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

#define INPUT_FILE			"..\\txt_inputs\\day_10.txt"
#define NUMBER_OF_LINES		94		//number of rows in input txt 
#define LENGTH_OF_LINES		130		//max line length in input txt
char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt

#define PARANTHESES_POINTS	3
#define SQUARE_POINTS		57
#define CURLY_POINTS		1197
#define ANGLE_POINTS		25137

char stack[4096];
uint16_t stack_cnt = 0;

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

void push(char c)
{
	if(stack_cnt == 4096)
	{
		fprintf(stderr, "Stack overflow.\n");
		return;
	}
	stack[stack_cnt] = c;
	stack_cnt++;
}

char pop()
{
	if(stack_cnt == 0)
	{
		fprintf(stderr, "Stack underflow.\n");
		return -1;
	}

	char c = stack[stack_cnt - 1];
	stack_cnt--;
	return c;
}

void empty()
{
	while(stack_cnt > 0)
	{
		pop();
	}
}

void print_stack()
{
	for(int i = 0; i < stack_cnt; i++)
	{
		printf("%c",stack[i]);
	}
	printf("\n");
}

uint32_t count_corruption_score()
{
	uint32_t corruption_score = 0;
	uint16_t idx = 0;
	bool corrupted = false;
	empty();
	for(uint16_t line = 0; line < NUMBER_OF_LINES; line++)
	{
		corrupted = false;
		for(idx = 0; idx < LENGTH_OF_LINES; idx++)
		{
			if(	txt[line][idx] == '(' ||
				txt[line][idx] == '[' ||
				txt[line][idx] == '{' ||
				txt[line][idx] == '<')
			{
				push(txt[line][idx]);
			}
			else
			{
				switch(txt[line][idx])
				{
					case ')':
						corrupted = pop() != '(' ? true : false;
						break;
					case ']':
						corrupted = pop() != '[' ? true : false;
						break;
					case '}':
						corrupted = pop() != '{' ? true : false;
						break;
					case '>':
						corrupted = pop() != '<' ? true : false;
						break;
					default:
						break;
				}
			}
			
			//print_stack();

			if(corrupted)
			{
				char corrupt_char = txt[line][idx];
				switch(corrupt_char)
				{
					case ')':
						corruption_score += PARANTHESES_POINTS;
						break;
					case ']':
						corruption_score += SQUARE_POINTS;
						break;
					case '}':
						corruption_score += CURLY_POINTS;
						break;
					case '>':
						corruption_score += ANGLE_POINTS;
						break;
					default:
						break;
				}

				break;
			}
		}
	}

	return corruption_score;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint32_t result_2 = 0;

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}

	result_1 = count_corruption_score();

	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- ...
*/