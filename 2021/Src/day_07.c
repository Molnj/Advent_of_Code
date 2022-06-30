/*
	AUTHOR:		Molnar Mate
	DATE:		2022.06.27.
	INPUT FILE:	..\txt_inputs\day_07.txt

	####################################################################################################

	--- Day 7: The Treachery of Whales ---
	A giant whale has decided your submarine is its next meal, and it's much faster than you are. There's nowhere to run!

	Suddenly, a swarm of crabs (each in its own tiny submarine - it's too deep for them otherwise) zooms in to rescue you! They seem to be preparing to blast a hole in the ocean floor; sensors indicate a massive underground cave system just beyond where they're aiming!

	The crab submarines all need to be aligned before they'll have enough power to blast a large enough hole for your submarine to get through. However, it doesn't look like they'll be aligned before the whale catches you! Maybe you can help?

	There's one major catch - crab submarines can only move horizontally.

	You quickly make a list of the horizontal position of each crab (your puzzle input). Crab submarines have limited fuel, so you need to find a way to make all of their horizontal positions match while requiring them to spend as little fuel as possible.

	For example, consider the following horizontal positions:

	16,1,2,0,4,2,7,1,2,14
	This means there's a crab with horizontal position 16, a crab with horizontal position 1, and so on.

	Each change of 1 step in horizontal position of a single crab costs 1 fuel. You could choose any horizontal position to align them all on, but the one that costs the least fuel is horizontal position 2:

	Move from 16 to 2: 14 fuel
	Move from 1 to 2: 1 fuel
	Move from 2 to 2: 0 fuel
	Move from 0 to 2: 2 fuel
	Move from 4 to 2: 2 fuel
	Move from 2 to 2: 0 fuel
	Move from 7 to 2: 5 fuel
	Move from 1 to 2: 1 fuel
	Move from 2 to 2: 0 fuel
	Move from 14 to 2: 12 fuel
	This costs a total of 37 fuel. This is the cheapest possible outcome; more expensive outcomes include aligning at position 1 (41 fuel), position 3 (39 fuel), or position 10 (71 fuel).

	Determine the horizontal position that the crabs can align to using the least fuel possible. How much fuel must they spend to align to that position?

	Your puzzle answer was 348664.

	--- Part Two ---
	The crabs don't seem interested in your proposed solution. Perhaps you misunderstand crab engineering?

	As it turns out, crab submarine engines don't burn fuel at a constant rate. Instead, each change of 1 step in horizontal position costs 1 more unit of fuel than the last: the first step costs 1, the second step costs 2, the third step costs 3, and so on.

	As each crab moves, moving further becomes more expensive. This changes the best horizontal position to align them all on; in the example above, this becomes 5:

	Move from 16 to 5: 66 fuel
	Move from 1 to 5: 10 fuel
	Move from 2 to 5: 6 fuel
	Move from 0 to 5: 15 fuel
	Move from 4 to 5: 1 fuel
	Move from 2 to 5: 6 fuel
	Move from 7 to 5: 3 fuel
	Move from 1 to 5: 10 fuel
	Move from 2 to 5: 6 fuel
	Move from 14 to 5: 45 fuel
	This costs a total of 168 fuel. This is the new cheapest possible outcome; the old alignment position (2) now costs 206 fuel instead.

	Determine the horizontal position that the crabs can align to using the least fuel possible so they can make you an escape route! How much fuel must they spend to align to that position?

	Your puzzle answer was 100220525.

	Both parts of this puzzle are complete! They provide two gold stars: **
//////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define INPUT_FILE			"..\\txt_inputs\\day_07.txt"
#define NUMBER_OF_LINES		1		//number of rows in input txt 
#define LENGTH_OF_LINES		4000	//max line length in input txt
#define MAX_CRABS			1000	//max number of crabs
char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt


//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	uint16_t x_pos[MAX_CRABS];
	uint16_t x_pos_max;
	uint16_t count;
} crab_subs_t;

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

void process_input(crab_subs_t *crabs)
{
	char *token = NULL;
	char *end = NULL;
	int idx = 0;

	token = strtok(txt[0], ",");
	while( token != NULL )
	{
		uint16_t x_pos = strtol(token, &end, 10);
		crabs->x_pos[idx] = x_pos;
		crabs->x_pos_max = (x_pos > crabs->x_pos_max) ? x_pos : crabs->x_pos_max;
		crabs->count++;
		token = strtok(NULL, ",");
		idx++;
	}
}

uint32_t calculate_optimal_allignment(crab_subs_t *crabs, char x)
{
	uint32_t fuel_needed = UINT32_MAX;
	uint32_t temp = 0;
	uint32_t dist = 0;
	for(uint16_t i = 0; i <= crabs->x_pos_max; i++) //trying all possible positions
	{
		temp = 0;
		for(uint16_t j = 0; j < crabs->count; j++)	//distance from all the crabs
		{
			dist = (i > crabs->x_pos[j]) ? (i - crabs->x_pos[j]) : (crabs->x_pos[j] - i);
			if(x == 'h') 	//fuel consumption - linear human math
			{
				temp += dist;
			}
			if(x == 's')	//fuel consumption - exponential shrimp math
			{
				for(uint16_t k = 1; k <= dist; k++)
				{
					temp += k;
				}
			}
		}
		fuel_needed = (fuel_needed > temp) ? temp : fuel_needed;
	}

	return fuel_needed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	crab_subs_t crabs = {{0},0,0};
	uint32_t fuel_needed = 0;

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_input(&crabs);

	fuel_needed = calculate_optimal_allignment(&crabs, 'h');	//solution with human math
	printf("result_1 = %lu\n", fuel_needed);

	fuel_needed = calculate_optimal_allignment(&crabs, 's');	//solution with shrimp math
	printf("result_2 = %lu\n", fuel_needed);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- none
*/