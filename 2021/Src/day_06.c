/*
	AUTHOR:		Molnar Mate
	DATE:		2022.06.26.
	INPUT FILE:	..\txt_inputs\day_06.txt

	####################################################################################################
	--- Day 6: Lanternfish ---
	The sea floor is getting steeper. Maybe the sleigh keys got carried this way?

	A massive school of glowing lanternfish swims past. They must spawn quickly to reach such large numbers - maybe exponentially quickly? You should model their growth rate to be sure.

	Although you know nothing about this specific species of lanternfish, you make some guesses about their attributes. Surely, each lanternfish creates a new lanternfish once every 7 days.

	However, this process isn't necessarily synchronized between every lanternfish - one lanternfish might have 2 days left until it creates another lanternfish, while another might have 4. So, you can model each fish as a single number that represents the number of days until it creates a new lanternfish.

	Furthermore, you reason, a new lanternfish would surely need slightly longer before it's capable of producing more lanternfish: two more days for its first cycle.

	So, suppose you have a lanternfish with an internal timer value of 3:

	After one day, its internal timer would become 2.
	After another day, its internal timer would become 1.
	After another day, its internal timer would become 0.
	After another day, its internal timer would reset to 6, and it would create a new lanternfish with an internal timer of 8.
	After another day, the first lanternfish would have an internal timer of 5, and the second lanternfish would have an internal timer of 7.
	A lanternfish that creates a new fish resets its timer to 6, not 7 (because 0 is included as a valid timer value). The new lanternfish starts with an internal timer of 8 and does not start counting down until the next day.

	Realizing what you're trying to do, the submarine automatically produces a list of the ages of several hundred nearby lanternfish (your puzzle input). For example, suppose you were given the following list:

	3,4,3,1,2
	This list means that the first fish has an internal timer of 3, the second fish has an internal timer of 4, and so on until the fifth fish, which has an internal timer of 2. Simulating these fish over several days would proceed as follows:

	Initial state: 3,4,3,1,2
	After  1 day:  2,3,2,0,1
	After  2 days: 1,2,1,6,0,8
	After  3 days: 0,1,0,5,6,7,8
	After  4 days: 6,0,6,4,5,6,7,8,8
	After  5 days: 5,6,5,3,4,5,6,7,7,8
	After  6 days: 4,5,4,2,3,4,5,6,6,7
	After  7 days: 3,4,3,1,2,3,4,5,5,6
	After  8 days: 2,3,2,0,1,2,3,4,4,5
	After  9 days: 1,2,1,6,0,1,2,3,3,4,8
	After 10 days: 0,1,0,5,6,0,1,2,2,3,7,8
	After 11 days: 6,0,6,4,5,6,0,1,1,2,6,7,8,8,8
	After 12 days: 5,6,5,3,4,5,6,0,0,1,5,6,7,7,7,8,8
	After 13 days: 4,5,4,2,3,4,5,6,6,0,4,5,6,6,6,7,7,8,8
	After 14 days: 3,4,3,1,2,3,4,5,5,6,3,4,5,5,5,6,6,7,7,8
	After 15 days: 2,3,2,0,1,2,3,4,4,5,2,3,4,4,4,5,5,6,6,7
	After 16 days: 1,2,1,6,0,1,2,3,3,4,1,2,3,3,3,4,4,5,5,6,8
	After 17 days: 0,1,0,5,6,0,1,2,2,3,0,1,2,2,2,3,3,4,4,5,7,8
	After 18 days: 6,0,6,4,5,6,0,1,1,2,6,0,1,1,1,2,2,3,3,4,6,7,8,8,8,8
	Each day, a 0 becomes a 6 and adds a new 8 to the end of the list, while each other number decreases by 1 if it was present at the start of the day.

	In this example, after 18 days, there are a total of 26 fish. After 80 days, there would be a total of 5934.

	Find a way to simulate lanternfish. How many lanternfish would there be after 80 days?

	Your puzzle answer was 390011.

	--- Part Two ---
	Suppose the lanternfish live forever and have unlimited food and space. Would they take over the entire ocean?

	After 256 days in the example above, there would be a total of 26984457539 lanternfish!

	How many lanternfish would there be after 256 days?

	Your puzzle answer was 1746710169834.

	Both parts of this puzzle are complete! They provide two gold stars: **
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

void process_input(lanternfish_t *fishes)
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
	process_input(&fishes);

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