/*
	AUTHOR:		Molnar Mate
	DATE:		2022.07.01.
	INPUT FILE:	..\txt_inputs\day_10.txt

	####################################################################################################
	--- Day 10: Syntax Scoring ---
	You ask the submarine to determine the best route out of the deep-sea cave, but it only replies:

	Syntax error in navigation subsystem on line: all of them
	All of them?! The damage is worse than you thought. You bring up a copy of the navigation subsystem (your puzzle input).

	The navigation subsystem syntax is made of several lines containing chunks. There are one or more chunks on each line, and chunks contain zero or more other chunks. Adjacent chunks are not separated by any delimiter; if one chunk stops, the next chunk (if any) can immediately start. Every chunk must open and close with one of four legal pairs of matching characters:

	If a chunk opens with (, it must close with ).
	If a chunk opens with [, it must close with ].
	If a chunk opens with {, it must close with }.
	If a chunk opens with <, it must close with >.
	So, () is a legal chunk that contains no other chunks, as is []. More complex but valid chunks include ([]), {()()()}, <([{}])>, [<>({}){}[([])<>]], and even (((((((((()))))))))).

	Some lines are incomplete, but others are corrupted. Find and discard the corrupted lines first.

	A corrupted line is one where a chunk closes with the wrong character - that is, where the characters it opens and closes with do not form one of the four legal pairs listed above.

	Examples of corrupted chunks include (], {()()()>, (((()))}, and <([]){()}[{}]). Such a chunk can appear anywhere within a line, and its presence causes the whole line to be considered corrupted.

	For example, consider the following navigation subsystem:

	[({(<(())[]>[[{[]{<()<>>
	[(()[<>])]({[<{<<[]>>(
	{([(<{}[<>[]}>{[]{[(<()>
	(((({<>}<{<{<>}{[]{[]{}
	[[<[([]))<([[{}[[()]]]
	[{[{({}]{}}([{[{{{}}([]
	{<[[]]>}<{[{[{[]{()[[[]
	[<(<(<(<{}))><([]([]()
	<{([([[(<>()){}]>(<<{{
	<{([{{}}[<[[[<>{}]]]>[]]
	Some of the lines aren't corrupted, just incomplete; you can ignore these lines for now. The remaining five lines are corrupted:

	{([(<{}[<>[]}>{[]{[(<()> - Expected ], but found } instead.
	[[<[([]))<([[{}[[()]]] - Expected ], but found ) instead.
	[{[{({}]{}}([{[{{{}}([] - Expected ), but found ] instead.
	[<(<(<(<{}))><([]([]() - Expected >, but found ) instead.
	<{([([[(<>()){}]>(<<{{ - Expected ], but found > instead.
	Stop at the first incorrect closing character on each corrupted line.

	Did you know that syntax checkers actually have contests to see who can get the high score for syntax errors in a file? It's true! To calculate the syntax error score for a line, take the first illegal character on the line and look it up in the following table:

	): 3 points.
	]: 57 points.
	}: 1197 points.
	>: 25137 points.
	In the above example, an illegal ) was found twice (2*3 = 6 points), an illegal ] was found once (57 points), an illegal } was found once (1197 points), and an illegal > was found once (25137 points). So, the total syntax error score for this file is 6+57+1197+25137 = 26397 points!

	Find the first illegal character in each corrupted line of the navigation subsystem. What is the total syntax error score for those errors?

	Your puzzle answer was 294195.

	--- Part Two ---
	Now, discard the corrupted lines. The remaining lines are incomplete.

	Incomplete lines don't have any incorrect characters - instead, they're missing some closing characters at the end of the line. To repair the navigation subsystem, you just need to figure out the sequence of closing characters that complete all open chunks in the line.

	You can only use closing characters (), ], }, or >), and you must add them in the correct order so that only legal pairs are formed and all chunks end up closed.

	In the example above, there are five incomplete lines:

	[({(<(())[]>[[{[]{<()<>> - Complete by adding }}]])})].
	[(()[<>])]({[<{<<[]>>( - Complete by adding )}>]}).
	(((({<>}<{<{<>}{[]{[]{} - Complete by adding }}>}>)))).
	{<[[]]>}<{[{[{[]{()[[[] - Complete by adding ]]}}]}]}>.
	<{([{{}}[<[[[<>{}]]]>[]] - Complete by adding ])}>.
	Did you know that autocomplete tools also have contests? It's true! The score is determined by considering the completion string character-by-character. Start with a total score of 0. Then, for each character, multiply the total score by 5 and then increase the total score by the point value given for the character in the following table:

	): 1 point.
	]: 2 points.
	}: 3 points.
	>: 4 points.
	So, the last completion string above - ])}> - would be scored as follows:

	Start with a total score of 0.
	Multiply the total score by 5 to get 0, then add the value of ] (2) to get a new total score of 2.
	Multiply the total score by 5 to get 10, then add the value of ) (1) to get a new total score of 11.
	Multiply the total score by 5 to get 55, then add the value of } (3) to get a new total score of 58.
	Multiply the total score by 5 to get 290, then add the value of > (4) to get a new total score of 294.
	The five lines' completion strings have total scores as follows:

	}}]])})] - 288957 total points.
	)}>]}) - 5566 total points.
	}}>}>)))) - 1480781 total points.
	]]}}]}]}> - 995444 total points.
	])}> - 294 total points.
	Autocomplete tools are an odd bunch: the winner is found by sorting all of the scores and then taking the middle score. (There will always be an odd number of scores to consider.) In this example, the middle score is 288957 because there are the same number of scores smaller and larger than it.

	Find the completion string for each incomplete line, score the completion strings, and sort the scores. What is the middle score?

	Your puzzle answer was 3490802734.

	Both parts of this puzzle are complete! They provide two gold stars: **
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

uint64_t calculate_autocomplete_score(char_stack_t *stack)
{
	uint64_t result = 0;
	while(stack->cnt > 0)
	{
		result *= 5;
		char c = pop(stack);
		switch(c)
		{
			case '(':
				result += 1;
				break;
			case '[':
				result += 2;
				break;
			case '{':
				result += 3;
				break;
			case '<':
				result += 4;
				break;
			default:
				break;
		}
	}
	return result;
}

void swap(uint64_t* xp, uint64_t* yp)
{
    uint64_t temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// Function to perform Selection Sort
void selectionSort(uint64_t arr[], uint8_t n)
{
    uint8_t i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
 
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
 
        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint64_t result_2 = 0;

	char_stack_t stack = {{0},0};

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}

	// PART 1
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
					break;
				}
			}
			//print_stack(&stack);
		}
	}
	printf("result_1 = %lu\n", result_1);

	// PART 2
	uint64_t autocorrect_values[NUMBER_OF_LINES] = {0};
	uint8_t autocorrect_idx = 0;
	for(uint16_t line = 0; line < NUMBER_OF_LINES; line++)
	{
		bool line_corrupted = false;
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
					line_corrupted = true;
					break;
				}
			}
			//print_stack(&stack);
		}
		if(! line_corrupted)
		{
			autocorrect_values[autocorrect_idx] = calculate_autocomplete_score(&stack);
			autocorrect_idx++;
		}
	}

	selectionSort(autocorrect_values, autocorrect_idx);

	int mid_idx = autocorrect_idx / 2;
	result_2 = autocorrect_values[mid_idx];
	printf("result_2 = %llu\n", result_2);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- figuring out stack solution
*/