/*
	AUTHOR:		Molnar Mate
	DATE:		2022.06.30.
	INPUT FILE:	..\txt_inputs\day_09.txt

	####################################################################################################
	--- Day 9: Smoke Basin ---
	These caves seem to be lava tubes. Parts are even still volcanically active; small hydrothermal vents release smoke into the caves that slowly settles like rain.

	If you can model how the smoke flows through the caves, you might be able to avoid it and be that much safer. The submarine generates a heightmap of the floor of the nearby caves for you (your puzzle input).

	Smoke flows to the lowest point of the area it's in. For example, consider the following heightmap:

	2199943210
	3987894921
	9856789892
	8767896789
	9899965678
	Each number corresponds to the height of a particular location, where 9 is the highest and 0 is the lowest a location can be.

	Your first goal is to find the low points - the locations that are lower than any of its adjacent locations. Most locations have four adjacent locations (up, down, left, and right); locations on the edge or corner of the map have three or two adjacent locations, respectively. (Diagonal locations do not count as adjacent.)

	In the above example, there are four low points, all highlighted: two are in the first row (a 1 and a 0), one is in the third row (a 5), and one is in the bottom row (also a 5). All other locations on the heightmap have some lower adjacent location, and so are not low points.

	The risk level of a low point is 1 plus its height. In the above example, the risk levels of the low points are 2, 1, 6, and 6. The sum of the risk levels of all low points in the heightmap is therefore 15.

	Find all of the low points on your heightmap. What is the sum of the risk levels of all low points on your heightmap?

	Your puzzle answer was 524.

	--- Part Two ---
	Next, you need to find the largest basins so you know what areas are most important to avoid.

	A basin is all locations that eventually flow downward to a single low point. Therefore, every low point has a basin, although some basins are very small. Locations of height 9 do not count as being in any basin, and all other locations will always be part of exactly one basin.

	The size of a basin is the number of locations within the basin, including the low point. The example above has four basins.

	The top-left basin, size 3:

	2199943210
	3987894921
	9856789892
	8767896789
	9899965678
	The top-right basin, size 9:

	2199943210
	3987894921
	9856789892
	8767896789
	9899965678
	The middle basin, size 14:

	2199943210
	3987894921
	9856789892
	8767896789
	9899965678
	The bottom-right basin, size 9:

	2199943210
	3987894921
	9856789892
	8767896789
	9899965678
	Find the three largest basins and multiply their sizes together. In the above example, this is 9 * 14 * 9 = 1134.

	What do you get if you multiply together the sizes of the three largest basins?

	Your puzzle answer was 1235430.

	Both parts of this puzzle are complete! They provide two gold stars: **
//////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define INPUT_FILE			"..\\txt_inputs\\day_09.txt"
#define NUMBER_OF_LINES		100				//number of rows in input txt 
#define LENGTH_OF_LINES		(100+2)			//max line length in input txt
#define MAP_SIZE			102				//100×100 input + frame out of 9s
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

void process_input(uint8_t value_map[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if(i == 0 || i == MAP_SIZE-1 || j == 0 || j == MAP_SIZE-1)
			{
				value_map[i][j] = 9;
			}
			else
			{
				value_map[i][j] = txt[i-1][j-1]-'0';
			}
		}
	}
}

void print_value_map(uint8_t value_map[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			printf("%d", value_map[i][j]);
		}
		printf("\n");
	}
}

uint32_t calculate_risk_level(uint8_t value_map[MAP_SIZE][MAP_SIZE])
{	
	uint32_t risk_level = 0;
	uint8_t curr_val = 0;

	//iterating through the inner values (not counting the "9 frame")
	for (int y = 1; y < MAP_SIZE-1; y++)
	{
		for (int x = 1; x < MAP_SIZE-1; x++)
		{
			uint8_t curr_val = value_map[y][x];
			if(	curr_val < value_map[y-1][x] && 
				curr_val < value_map[y+1][x] && 
				curr_val < value_map[y][x-1] && 
				curr_val < value_map[y][x+1])
				{
					risk_level += curr_val + 1;
				}
		}
	}
	return risk_level;
}

uint16_t DFS_basin_size (uint8_t y, uint8_t x, uint8_t value_map[MAP_SIZE][MAP_SIZE], uint8_t checked_map[MAP_SIZE][MAP_SIZE])
{
	//Creating basin from lowest point outward with flow fill
	//Depth First Search with recursion
	
	if(value_map[y][x] == 9)
	{
		return 0;
	}

	if(checked_map[y][x] == 1)	// is ""== 1" more readable? 
	{
		return 0;
	}

	uint16_t cnt = 1;
	checked_map[y][x] = 1;

	cnt += DFS_basin_size(y-1, x, value_map, checked_map);
  	cnt += DFS_basin_size(y+1, x, value_map, checked_map);
  	cnt += DFS_basin_size(y, x-1, value_map, checked_map);
 	cnt += DFS_basin_size(y, x+1, value_map, checked_map);

	return cnt;
}

uint32_t calculate_basins(uint8_t value_map[MAP_SIZE][MAP_SIZE])
{	
	uint32_t risk_level = 0;
	uint8_t curr_val = 0;

	uint16_t basin_size = 0;
	uint16_t top_3_basins[3] = {0};


	//iterating through the inner values (not counting the "9 frame")
	uint8_t checked_map[MAP_SIZE][MAP_SIZE] = {0};
	for (int y = 1; y < MAP_SIZE-1; y++)
	{
		for (int x = 1; x < MAP_SIZE-1; x++)
		{
			uint8_t curr_val = value_map[y][x];
			if(	curr_val < value_map[y-1][x] && 
				curr_val < value_map[y+1][x] && 
				curr_val < value_map[y][x-1] && 
				curr_val < value_map[y][x+1])
				{
					basin_size = DFS_basin_size(y, x, value_map, checked_map);

					if (basin_size > top_3_basins[2]) 
					{
						top_3_basins[2] = basin_size;
					}
          			if (top_3_basins[2] > top_3_basins[1])
					{
						int temp = top_3_basins[2];
						top_3_basins[2] = top_3_basins[1];
						top_3_basins[1] = temp;
					}
        			if (top_3_basins[1] > top_3_basins[0])
					{
						int temp = top_3_basins[1];
						top_3_basins[1] = top_3_basins[0];
						top_3_basins[0] = temp;
					}
				}
		}
	}
	//printf("%lu - %lu - %lu\n", top_3_basins[0], top_3_basins[1], top_3_basins[2]);
	return top_3_basins[0] * top_3_basins[1] * top_3_basins[2];
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint32_t result_2 = 0;

	uint8_t value_map[MAP_SIZE][MAP_SIZE] = {{0},{0}}; //100×100 initial map + 1 thick "9" frame

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_input(value_map);
	//print_value_map(value_map);

	result_1 = calculate_risk_level(value_map);
	result_2 = calculate_basins(value_map);

	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- finding a way to fluid fill the are of each basin
 * 			going outwards from the deepest spot recursively
 * 			returning when reaching walls and already checked spots
*/