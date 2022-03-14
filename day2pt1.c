/*
	Task:		Each input line has a direction (forward, up, down) and a distance (1-9)
				Calculate final destination by multiplying final vertival and horizontal distance 
	Input file:	%CD\inputs\day2.txt
	Solution: 	1250395 (1909*655)
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
				if(line[0] == 'f') 		{ horizontal = horizontal + dist; }
				else if(line[0] == 'u')	{ vertical = vertical - dist; }
				else if(line[0] == 'd')	{ vertical = vertical + dist; }
				break;	// break after getting the number, to avoid mess in next 16-? characters
			}
		}
	}	
	fclose(file);


	int solution = horizontal * vertical;
	printf("Horizontal: %d\n", horizontal);
	printf("Vertical: %d\n", vertical);
	printf("Solution: %d\n", solution);

	return 0;
}