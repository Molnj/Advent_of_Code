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
#define NUMBER_OF_LINES		10		//number of rows in input txt 
#define LENGTH_OF_LINES		30		//max line length in input txt
char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt

#define PARANTHESES_POINTS	3
#define SQUARE_POINTS		57
#define CURLY_POINTS		1197
#define ANGLE_POINTS		25137

typedef struct {
	char arr[4096];
	uint16_t cnt;
} char_stack_t;

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

void push(char_stack_t *stack, char c)
{
	if(stack->cnt == 4096)
	{
		fprintf(stderr, "Stack overflow.\n");
		return;
	}
	
	stack->arr[stack->cnt] = c;
	stack->cnt++;
}

char pop(char_stack_t *stack)
{
	if(stack->cnt == 0)
	{
		fprintf(stderr, "Stack underflow.\n");
		return -1;
	}

	char c = stack->arr[stack->cnt - 1];
	stack->cnt--;
	return c;
}



void print_stack(char_stack_t *stack)
{
	for(int i = 0; i < stack->cnt; i++)
	{
		printf("%c", stack->arr[i]);
	}
	printf("\n");
}

uint32_t count_corruption_score(char_stack_t *stack)
{
	uint32_t corruption_score = 0;
	bool corrupted = false;
	for(uint16_t line = 0; line < NUMBER_OF_LINES; line++)
	{
		corrupted = false;
		stack->cnt = 0;
		//printf("------------------\n");
		for(uint16_t idx = 0; idx < strlen(txt[line]); idx++)
		{
			if(	txt[line][idx] == '(' ||
				txt[line][idx] == '[' ||
				txt[line][idx] == '{' ||
				txt[line][idx] == '<')
			{
				push(stack, txt[line][idx]);
			}
			else
			{
				switch(txt[line][idx])
				{
					case ')':
						corrupted = pop(stack) != '(' ? true : false;
						break;
					case ']':
						corrupted = pop(stack) != '[' ? true : false;
						break;
					case '}':
						corrupted = pop(stack) != '{' ? true : false;
						break;
					case '>':
						corrupted = pop(stack) != '<' ? true : false;
						break;
					default:
						break;
				}
			}
			
			//print_stack(stack);

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
				//printf("XXX\n");
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

	char_stack_t stack = {{0},0};

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}

	result_1 = count_corruption_score(&stack);

	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- ...
*/