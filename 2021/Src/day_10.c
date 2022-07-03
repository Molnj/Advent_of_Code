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

const char openers[4] = {'(', '[', '{', '<'};
const char closers[4] = {')', ']', '}', '>'};

uint8_t corrupted_lines[NUMBER_OF_LINES];

typedef struct {
	char arr[4096];
	uint16_t cnt;
} char_stack_t;

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

bool isOpener(char c)
{
	bool result = false;
	for(int i = 0; i < sizeof(openers)/sizeof(openers[0]); i++)
	{
		if(c == openers[i])
		{
			result = true;
		}
	}
	return result;
}

bool isCloser(char c)
{
	bool result = false;
	for(int i = 0; i < sizeof(closers)/sizeof(closers[0]); i++)
	{
		if(c == closers[i])
		{
			result = true;
		}
	}
	return result;
}

bool isCorrupted(char close, char open)
{
	bool result = false;
	switch(close)
	{
		case ')':
			result = open != '(' ? true : false;
			break;
		case ']':
			result = open != '[' ? true : false;
			break;
		case '}':
			result = open != '{' ? true : false;
			break;
		case '>':
			result = open != '<' ? true : false;
			break;
		default:
			break;
	}
	return result;
}
	//print_stack(stack);

uint16_t addPoints(char c)
{
	switch(c)
	{
		case ')':
			return PARANTHESES_POINTS;
		case ']':
			return SQUARE_POINTS;
		case '}':
			return CURLY_POINTS;
		case '>':
			return ANGLE_POINTS;
		default:
			break;
	}

	return 0;
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

	// part 1
	char_stack_t stack = {{0},0};

	for(uint16_t line = 0; line < NUMBER_OF_LINES; line++)
	{
		stack.cnt = 0;
		for(uint16_t idx = 0; idx < strlen(txt[line]); idx++)
		{
			char c_curr = txt[line][idx];
			if(isOpener(c_curr))
			{
				push(&stack, c_curr);
			}
			if(isCloser(c_curr))
			{
				char c_pair = pop(&stack);
				if(isCorrupted(c_curr, c_pair))
				{
					result_1 += addPoints(c_curr);
					//printf("xxx\n");
					break;
				}
			}
			//print_stack(&stack);
		}
		//printf("----------------\n");
	}

	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- ...
*/