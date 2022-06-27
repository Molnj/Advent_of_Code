/*
	AUTHOR:		Molnar Mate
	DATE:		2022.03.14.
	INPUT FILE:	..\txt_inputs\day_02.txt

	####################################################################################################
	--- Day 2: Dive! ---
	Now, you need to figure out how to pilot this thing.

	It seems like the submarine can take a series of commands like forward 1, down 2, or up 3:

	forward X increases the horizontal position by X units.
	down X increases the depth by X units.
	up X decreases the depth by X units.
	Note that since you're on a submarine, down and up affect your depth, and so they have the opposite result of what you might expect.

	The submarine seems to already have a planned course (your puzzle input). You should probably figure out where it's going. For example:

	forward 5
	down 5
	forward 8
	up 3
	down 8
	forward 2
	Your horizontal position and depth both start at 0. The steps above would then modify them as follows:

	forward 5 adds 5 to your horizontal position, a total of 5.
	down 5 adds 5 to your depth, resulting in a value of 5.
	forward 8 adds 8 to your horizontal position, a total of 13.
	up 3 decreases your depth by 3, resulting in a value of 2.
	down 8 adds 8 to your depth, resulting in a value of 10.
	forward 2 adds 2 to your horizontal position, a total of 15.
	After following these instructions, you would have a horizontal position of 15 and a depth of 10. (Multiplying these together produces 150.)

	Calculate the horizontal position and depth you would have after following the planned course. What do you get if you multiply your final horizontal position by your final depth?

	Your puzzle answer was 1250395.

	--- Part Two ---
	Based on your calculations, the planned course doesn't seem to make any sense. You find the submarine manual and discover that the process is actually slightly more complicated.

	In addition to horizontal position and depth, you'll also need to track a third value, aim, which also starts at 0. The commands also mean something entirely different than you first thought:

	down X increases your aim by X units.
	up X decreases your aim by X units.
	forward X does two things:
	It increases your horizontal position by X units.
	It increases your depth by your aim multiplied by X.
	Again note that since you're on a submarine, down and up do the opposite of what you might expect: "down" means aiming in the positive direction.

	Now, the above example does something different:

	forward 5 adds 5 to your horizontal position, a total of 5. Because your aim is 0, your depth does not change.
	down 5 adds 5 to your aim, resulting in a value of 5.
	forward 8 adds 8 to your horizontal position, a total of 13. Because your aim is 5, your depth increases by 8*5=40.
	up 3 decreases your aim by 3, resulting in a value of 2.
	down 8 adds 8 to your aim, resulting in a value of 10.
	forward 2 adds 2 to your horizontal position, a total of 15. Because your aim is 10, your depth increases by 2*10=20 to a total of 60.
	After following these new instructions, you would have a horizontal position of 15 and a depth of 60. (Multiplying these produces 900.)

	Using this new interpretation of the commands, calculate the horizontal position and depth you would have after following the planned course. What do you get if you multiply your final horizontal position by your final depth?

	Your puzzle answer was 1451210346.

	Both parts of this puzzle are complete! They provide two gold stars: **
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