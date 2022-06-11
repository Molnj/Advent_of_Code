/*
	AUTHOR:		Molnar Mate
	DATE:		2022.03.14

	INPUT FILE:	%CD\inputs\day_02.txt
				(contains 1000 lines of [direction + distance] combinations

	TASK-1:		Each input line has a direction (forward, up, down) and a distance (1-9)
				Calculate final destination by multiplying final vertival and horizontal distance
	TASK-2:		Same as previously, but now with aim --> up and down modifies aim, instead of moving
				forward still moves horizontally, but now changes vertically too based on current aim

	SOLUTION-1: 1250395 (1909*655)
	SOLUTION-2: 1451210346 (h-1909, v-760194, a-655)
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define PT1 1
#define PT2 2

#define INPUT_FILE			"..\\txt_inputs\\day_02.txt"
#define NUMBER_OF_LINES		1000
#define LENGTH_OF_LINES		16

typedef enum
{
	FORWARD	= 0,
	UP 		= 1,
	DOWN 	= 2
} direction_en;

typedef struct __attribute__((packed))
{
	direction_en direction;
	int distance;
} instruction_t;

typedef struct __attribute__((packed))
{
	int horizontal;
	int vertical;
	int aim;
} submarinePosition_t;


bool read_input_into_instruction_list(char *fileName, instruction_t *instructions);
unsigned int measure_submarine_path(instruction_t *instruction_list, int partNo);


int main()
{	
	instruction_t instruction_list[NUMBER_OF_LINES];
	if (read_input_into_instruction_list(INPUT_FILE, instruction_list))
	{
        unsigned int result1 = measure_submarine_path(instruction_list, PT1);
		unsigned int result2 = measure_submarine_path(instruction_list, PT2);
		printf("RESULT1 = %u\n", result1);
		printf("RESULT2 = %u\n", result2);
	}
	else {return 1;}

	return 0;
} 


bool read_input_into_instruction_list(char *fileName, instruction_t *instructions)
{
	//OPEN INPUT FILE
	FILE *pFile = fopen(fileName, "r");
	if (pFile == 0)
	{
		printf("Could not find input file: %s.\n", fileName);
		return false;
	}
    
	//READ TXT LINE-BY-LINE
    char dir_str[16];
    int dist = 0;
    int idx = 0;
    while (!feof(pFile))
    {
        fscanf(pFile, "%s %d\n", dir_str, &dist);
        direction_en dir;

        if 		(strcmp(dir_str, "forward") == 0)	{dir = FORWARD;}
        else if	(strcmp(dir_str, "up") == 0)		{dir = UP;}
        else if	(strcmp(dir_str, "down") == 0)		{dir = DOWN;}
        else 										{printf("Unknown token: %s.\n", dir_str);}

        instructions[idx].direction = dir;
        instructions[idx].distance = dist;
		//printf("%d %d \n", instructions[idx].direction, instructions[idx].distance);
        idx++;
    }

    fclose(pFile);
    return true;
}


unsigned int measure_submarine_path(instruction_t* instruction_list, int partNo)
{
    submarinePosition_t position;
    position.vertical = 0;
    position.horizontal = 0;
    position.aim = 0;

    for (int idx = 0; idx < NUMBER_OF_LINES; idx++)
    {
        instruction_t instruction = instruction_list[idx];
		if(partNo == 1) //not using aim
		{
			switch(instruction.direction)
			{
				case FORWARD:
					position.horizontal += instruction.distance;
					break;
				case UP:
					position.vertical -= instruction.distance;
					break;
				case DOWN:
					position.vertical += instruction.distance;
					break;
				default:
					//do nothing
					break; 
			}
		}
		else if(partNo == 2) //using aim
		{
			switch(instruction.direction)
			{
				case FORWARD:
					position.horizontal += instruction.distance;
					position.vertical += (position.aim * instruction.distance);
					break;
				case UP:
					position.aim -= instruction.distance;
					break;
				case DOWN:
					position.aim += instruction.distance;
					break;
				default:
					//do nothing
					break; 
			}
		}
    }
    unsigned int result = position.horizontal * position.vertical;
    return result;
}