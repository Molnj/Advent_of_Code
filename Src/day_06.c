/*
	AUTHOR:		Molnar Mate
	DATE:		2022.

	INPUT FILE:	..\txt_inputs\day_06.txt
				(description of txt)

	TASK-1:		txt input shows how many days until each lantern fish reproduces
				this timer resets to 6, and for a newborn the first cycle is 8
				calculate the population after 40 days
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

#define INPUT_FILE			"..\\txt_inputs\\day_06.txt"
#define NUMBER_OF_LINES		1		//number of rows in input txt 
#define LENGTH_OF_LINES		1000		//max line length in input txt
char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt

#define REPRODUCTION_TIME				6
#define REPRODUCTION_TIME_NEWBORN		(REPRODUCTION_TIME + 2)
#define DAYS_TO_SIMULATE				80

//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
	uint8_t timers[1000000];
	uint32_t count;
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
	uint32_t i = 0;
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
		fishes->timers[idx] = strtol(token, &end, 10);
		fishes->count++;
		token = strtok(NULL, ",");
		idx++;
	}
}

void init_fishes(lanternfish_t *fishes)
{
	fishes->count = 0;
	for (uint32_t i = 0; i < sizeof(fishes->timers); i++)
	{
		fishes->timers[i] = 0;
	}
}

void print_fish(lanternfish_t *fishes)
{
	for (uint32_t i = 0; i < fishes->count; i++)
	{
		printf("%d,", fishes->timers[i]);
	}
	printf("\n\n");
}


void reproduction(lanternfish_t *fishes)
{
	uint32_t fish_cnt = fishes->count;
	for(uint32_t i = 0; i < fish_cnt; i++)
	{
		fishes->timers[i]--;
		if(fishes->timers[i] == 255)
		{
			fishes->timers[i] = REPRODUCTION_TIME;
			fishes->count++;
			fishes->timers[fishes->count-1] = REPRODUCTION_TIME_NEWBORN;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	lanternfish_t fishes;
	init_fishes(&fishes);

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_read(&fishes);

	for(uint8_t i = 0; i < DAYS_TO_SIMULATE; i++)
	{
		//print_fish(&fishes);
		reproduction(&fishes);
		printf("# of fish at day %d: %d.\n", i+1, fishes.count);
	}

    return 0;
}

/*
 * biggest headaches:
 * 		- process_read() can't handle token != NULL for some reason
*/

// 388820 too low