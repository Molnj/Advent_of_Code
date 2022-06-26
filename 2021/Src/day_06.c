/*
	AUTHOR:		Molnar Mate
	DATE:		2022.06.26.

	INPUT FILE:	..\txt_inputs\day_06.txt
				long line of numbers separated by colons,
				each representing a fish's days until reproduction

	TASK-1:		fish reproduction timer resets to 6, and for a newborn the first cycle is 8
				calculate the population after 40 days
    TASK-2:     calculate the population after 256 days


	SOLUTION-1: 
	SOLUTION-2: 
//////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"
#include <inttypes.h>


#define INPUT_FILE			"..\\txt_inputs\\day_06.txt"
#define NUMBER_OF_LINES		1		//number of rows in input txt 
#define LENGTH_OF_LINES		1000		//max line length in input txt
char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt

#define DAYS_TO_SIMULATE				256

uint64_t result_1 = 0;
uint64_t result_2 = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
	uint64_t fish_groups[9];	//grouping fishes based on their days untill reproduction
	uint64_t count;
} lanternfish_t;

//////////////////////////////////////////////////////////////////////////////////////////////////

bool read_input(char* fileName) 
{
	FILE *pFile = fopen(fileName, "r");
	if (pFile == 0)
	{
		return E_NOT_OK;
	}

	// .TXT --> CHAR[row][column]
	uint64_t i = 0;
	while(fgets(txt[i], LENGTH_OF_LINES, pFile))
	{
		txt[i][strlen(txt[i]) - 1] = '\0';
		i++;
	}

	fclose(pFile);
	return E_OK;
}

void process_read(lanternfish_t *fishes)
{
	char *token = NULL;
	char *end = NULL;
	int idx = 0;

	token = strtok(txt[0], ",");
	while( token != NULL )
	{
		uint8_t days_till_reproduction = strtol(token, &end, 10);
		fishes->fish_groups[days_till_reproduction]++;
		fishes->count++;
		token = strtok(NULL, ",");
		idx++;
	}
}

void reproduction(lanternfish_t *fishes)
{
	uint64_t birthing_fishes = fishes->fish_groups[0];
	fishes->count += birthing_fishes;

	fishes->fish_groups[0] = fishes->fish_groups[1];
	fishes->fish_groups[1] = fishes->fish_groups[2];
	fishes->fish_groups[2] = fishes->fish_groups[3];
	fishes->fish_groups[3] = fishes->fish_groups[4];
	fishes->fish_groups[4] = fishes->fish_groups[5];
	fishes->fish_groups[5] = fishes->fish_groups[6];
	fishes->fish_groups[6] = fishes->fish_groups[7] + birthing_fishes;
	fishes->fish_groups[7] = fishes->fish_groups[8];
	fishes->fish_groups[8] = birthing_fishes;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	lanternfish_t fishes = {{0}, 0};

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_read(&fishes);

	for(uint16_t day = 0; day < DAYS_TO_SIMULATE; day++)
	{
		reproduction(&fishes);
		printf("Num of fish at day %u: %llu.\n", day+1, fishes.count);
		if(day+1 == 80)
		{
			result_1 = fishes.count;
		}
		if(day+1 == 256)
		{
			result_2 = fishes.count;
		}
	}
	printf("result_1: %lu\n", result_1);
	printf("result_2: %" PRIu64 "\n", result_2);


    return 0;
}

/*
 * biggest headaches:
 * 		- process_read() can't handle token != NULL for some reason
* 		- used to represent each fish in an array using it's days untill reproduction
			with this method part2 would have me use millions of int values
			which was not even elegant with dinamic memory alllocation
			switched to representing fishes[10], with for example fish[3] representing number of fish with 3 days till reproduction
		- suffering with printing uint64_t
*/