/*
	AUTHOR:		Molnar Mate
	DATE:		2022.06.22

	INPUT FILE:	..\txt_inputs\day_05.txt
				500 lines of (x1,y1) --> (x2,y2) vektor-like values representing streams

	TASK-1:		There is a field (seems to be) of 1000 × 1000 in size.
                the input vektor represent "hydrotermal vents" - dangerous lines
                The program most count at how many point these vents overlap
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

void mark_vents(field_t *field)
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
		if (field->vents[i].y1 == field->vents[i].y2)
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
	mark_vents(&field);
	print_field(&field);
	int danger = count_danger(&field);
	printf("result-1: %d", danger);

    return E_OK;
}

/*
 * biggest headaches:
 * 		- ...
*/