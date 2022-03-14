/*
	Task:		day2pt1, but now with aim
				up and down modifies aim
				forward still moves horizontally, but now changes vertically too based on current
	Input file:	%CD\inputs\day2.txt
	Solution: 	1451210346 (h-1909, v-760194, a-655)
	Author:		Molnar Mate
	Date:		2022.03.14.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH	16
#define NUM_OF_INPUTS	1000


int main()
{	
	int horizontal = 0;
	int vertical = 0;
	int aim = 0;

	// OPEN INPUT FILE
	FILE *file = fopen("inputs\\day2.txt", "r");
	if (file == 0)
	{
		printf("Could not find input file.\n");
		return 1;
	}


	//read txt line-by-line
	char line[16];
	while(fgets(line, sizeof(line), file))
	{
		bool flag = false;
		//read line char-by-char
		for (int i = 0; i<sizeof(line); i++)
		{
			//if whitespace is found --> add the next character as distance, then break to next line
			if(line[i] == ' ') { flag = true; }
			//get distance, then add it to corresponding direction
			if(flag)
			{
				int dist = line[i+1] - '0'; 	//char -> int
				if(line[0] == 'f')
				{
					 horizontal = horizontal + dist;
					 vertical = vertical + aim * dist;
				}
				else if(line[0] == 'u')	{ aim = aim - dist; }
				else if(line[0] == 'd')	{ aim = aim + dist; }
				break;	// break after getting the number, to avoid mess in next 16-? characters
			}
		}
	}	
	fclose(file);


	int solution = horizontal * vertical;
	printf("Horizontal: %d\n", horizontal);
	printf("Vertical: %d\n", vertical);
	printf("Aim: %d\n", aim);
	printf("Solution: %d\n", solution);

	return 0;
}