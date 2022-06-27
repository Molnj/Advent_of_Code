/*
	AUTHOR:		Molnar Mate
	DATE:		2022.06.22.
	INPUT FILE:	..\txt_inputs\day_05.txt

	####################################################################################################
	--- Day 5: Hydrothermal Venture ---
	You come across a field of hydrothermal vents on the ocean floor! These vents constantly produce large, opaque clouds, so it would be best to avoid them if possible.

	They tend to form in lines; the submarine helpfully produces a list of nearby lines of vents (your puzzle input) for you to review. For example:

	0,9 -> 5,9
	8,0 -> 0,8
	9,4 -> 3,4
	2,2 -> 2,1
	7,0 -> 7,4
	6,4 -> 2,0
	0,9 -> 2,9
	3,4 -> 1,4
	0,0 -> 8,8
	5,5 -> 8,2
	Each line of vents is given as a line segment in the format x1,y1 -> x2,y2 where x1,y1 are the coordinates of one end the line segment and x2,y2 are the coordinates of the other end. These line segments include the points at both ends. In other words:

	An entry like 1,1 -> 1,3 covers points 1,1, 1,2, and 1,3.
	An entry like 9,7 -> 7,7 covers points 9,7, 8,7, and 7,7.
	For now, only consider horizontal and vertical lines: lines where either x1 = x2 or y1 = y2.

	So, the horizontal and vertical lines from the above list would produce the following diagram:

	.......1..
	..1....1..
	..1....1..
	.......1..
	.112111211
	..........
	..........
	..........
	..........
	222111....
	In this diagram, the top left corner is 0,0 and the bottom right corner is 9,9. Each position is shown as the number of lines which cover that point or . if no line covers that point. The top-left pair of 1s, for example, comes from 2,2 -> 2,1; the very bottom row is formed by the overlapping lines 0,9 -> 5,9 and 0,9 -> 2,9.

	To avoid the most dangerous areas, you need to determine the number of points where at least two lines overlap. In the above example, this is anywhere in the diagram with a 2 or larger - a total of 5 points.

	Consider only horizontal and vertical lines. At how many points do at least two lines overlap?

	Your puzzle answer was 5442.

	--- Part Two ---
	Unfortunately, considering only horizontal and vertical lines doesn't give you the full picture; you need to also consider diagonal lines.

	Because of the limits of the hydrothermal vent mapping system, the lines in your list will only ever be horizontal, vertical, or a diagonal line at exactly 45 degrees. In other words:

	An entry like 1,1 -> 3,3 covers points 1,1, 2,2, and 3,3.
	An entry like 9,7 -> 7,9 covers points 9,7, 8,8, and 7,9.
	Considering all lines from the above example would now produce the following diagram:

	1.1....11.
	.111...2..
	..2.1.111.
	...1.2.2..
	.112313211
	...1.2....
	..1...1...
	.1.....1..
	1.......1.
	222111....
	You still need to determine the number of points where at least two lines overlap. In the above example, this is still anywhere in the diagram with a 2 or larger - now a total of 12 points.

	Consider all of the lines. At how many points do at least two lines overlap?

	Your puzzle answer was 19571.

	Both parts of this puzzle are complete! They provide two gold stars: **
//////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define INPUT_FILE			"..\\txt_inputs\\day_05.txt"
#define NUMBER_OF_LINES		500		//number of rows in input txt 
#define LENGTH_OF_LINES		20		//max line length in input txt
char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt

#define FIELD_HEIGTH        1000
#define FIELD_WIDTH         1000
#define NO_OF_VENTS         500

//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct __attribute__((packed))
{
	uint16_t x1;
    uint16_t y1;
    uint16_t x2;
    uint16_t y2;
} hydro_vent_t;

typedef struct __attribute__((packed))
{
	uint16_t field_matrix[FIELD_HEIGTH][FIELD_WIDTH];
    hydro_vent_t vents[NO_OF_VENTS];
    uint16_t vent_cnt;
} field_t;

//////////////////////////////////////////////////////////////////////////////////////////////////

bool read_input(char* fileName) 
{
	FILE *pFile = fopen(fileName, "r");
	if (pFile == 0)
	{
		printf("Could not find input file: %s.\n", fileName);
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


void process_readings(field_t *field)
{
	char *pToken = NULL;
	char *pEnd = NULL;
	char segment_start[20];
	char segment_end[20];

	for(int i = 0; i < NUMBER_OF_LINES; i++)
	{
		pToken = strtok(txt[i], " -> ");

		if(pToken != NULL)
		{
			strcpy(segment_start, pToken);
			pToken = strtok(NULL, " -> ");
			if (pToken != NULL)
			{
				strcpy(segment_end, pToken);	
			}
		}

		pToken = strtok(segment_start, ",");
		if (pToken != NULL)
		{
			field->vents[i].x1 = strtol(pToken, &pEnd, 10);
			pToken = strtok(NULL, ",");
			if (pToken != NULL)
			{
				field->vents[i].y1 = strtol(pToken, &pEnd, 10);
			}
		}

		pToken = strtok(segment_end, ",");
		if (pToken != NULL)
		{
			field->vents[i].x2 = strtol(pToken, &pEnd, 10);
			pToken = strtok(NULL, ",");
			if (pToken != NULL)
			{
				field->vents[i].y2 = strtol(pToken, &pEnd, 10);
			}
		}
		//printf("%d, %d --> %d, %d\n", field->vents[i].x1, field->vents[i].y1, field->vents[i].x2, field->vents[i].y2);
	}
}


void null_field(field_t *field)
{
	for(int i = 0; i < FIELD_HEIGTH; i++)
	{
		for(int j = 0; j < FIELD_WIDTH; j++)
		{
			field->field_matrix[i][j] = 0;
		}
	}
}


int abs_diff(int a, int b)
{
	int min = (a > b) ? b : a;
	int max = (a > b) ? a : b;
	return (max - min);
}


void mark_vents_non_diagonal(field_t *field)
{
	for(int i = 0; i < NUMBER_OF_LINES; i++)
	{
		//VERTICAL VENT
		if (field->vents[i].x1 == field->vents[i].x2)
		{
			if (field->vents[i].y1 >= field->vents[i].y2)
			{
				for (uint16_t y = field->vents[i].y2; y <= field->vents[i].y1; y++) 
				{
					field->field_matrix[field->vents[i].x1][y]++;			
				}
			} 
			else
			{
				for (uint16_t y = field->vents[i].y1; y <= field->vents[i].y2; y++)
				{
					field->field_matrix[field->vents[i].x1][y]++;				
				}
			}
		}

		//HORIZONTAL VENT
		else if (field->vents[i].y1 == field->vents[i].y2)
		{
			if (field->vents[i].x1 >= field->vents[i].x2)
			{
				for (uint16_t x = field->vents[i].x2; x <= field->vents[i].x1; x++)
				{
					field->field_matrix[x][field->vents[i].y1]++;			
				}
			} 
			else
			{
				for (uint16_t x = field->vents[i].x1; x <= field->vents[i].x2; x++)
				{
					field->field_matrix[x][field->vents[i].y1]++;			
				}
			}
		}
	}
}


void mark_vents_diagonal(field_t *field)
{
	for(int i = 0; i < NUMBER_OF_LINES; i++)
	{
		int absdiff_x = abs_diff(field->vents[i].x1, field->vents[i].x2);
		int absdiff_y = abs_diff(field->vents[i].y1, field->vents[i].y2);
		if(absdiff_x == absdiff_y)
		{
			if (field->vents[i].x1 < field->vents[i].x2 && field->vents[i].y1 < field->vents[i].y2)
			{
				uint16_t y = field->vents[i].y1;
				for (uint16_t x = field->vents[i].x1; x <= field->vents[i].x2 ; x++) {
					field->field_matrix[x][y]++;
					y++;
				}
			}
			if (field->vents[i].x1 < field->vents[i].x2 && field->vents[i].y1 > field->vents[i].y2)
			{
				uint16_t y = field->vents[i].y1;
				for (uint16_t x = field->vents[i].x1; x <= field->vents[i].x2 ; x++) {
					field->field_matrix[x][y]++;
					y--;
				}
			}
			if (field->vents[i].x1 > field->vents[i].x2 && field->vents[i].y1 < field->vents[i].y2)
			{
				uint16_t y = field->vents[i].y2;
				for (uint16_t x = field->vents[i].x2; x <= field->vents[i].x1 ; x++) {
					field->field_matrix[x][y]++;
					y--;
				}
			}
			if (field->vents[i].x1 > field->vents[i].x2 && field->vents[i].y1 > field->vents[i].y2)
			{
				uint16_t y = field->vents[i].y2;
				for (uint16_t x = field->vents[i].x2; x <= field->vents[i].x1 ; x++) {
					field->field_matrix[x][y]++;
					y++;
				}
			}
		}
	}
}


void print_field(field_t *field)
{
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			printf("%d\t", field->field_matrix[i][j]);
		}
	}
}

int count_danger(field_t *field)
{
	int cnt = 0;
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			if(field->field_matrix[i][j] > 1)
			{
				cnt++;
			}
		}
	}
	return cnt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	field_t field;
	null_field(&field);

	if(read_input(INPUT_FILE))
	{
		return E_NOT_OK;
	}
	process_readings(&field);

	mark_vents_non_diagonal(&field);
	int result_1 = count_danger(&field);

	mark_vents_diagonal(&field);
	int result_2 = count_danger(&field);

	printf("result_1: %d\n", result_1);
	printf("result_2: %d\n", result_2);

	//print_field(&field);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- matrix in structure was not initialized -- random values
 * 		- accidental infinite loop ending in code=3221225477
*/