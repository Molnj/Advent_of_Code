/*
	Task:		How many measurements are larger than the previous measurement?
	Input file:	%CD\inputs\day1pt1.txt 	(contains 2000 lines of int values)
	Solution: 	1548
	Author:		Molnar Mate
	Date:		2022.03.13.
*/

#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH	8
#define NUM_OF_INPUTS	2000


int main()
{	
	char line[8];
	int values[NUM_OF_INPUTS];
	int value_index = 0;
	int increments = 0;

	// OPEN INPUT FILE
	FILE *file = fopen("inputs\\day1pt1.txt", "r");
	if (file == 0)
	{
		printf("Could not find input file.\n");
		return 1;
	}

	//LOAD VALUES INTO BUFFER (LINE-BY-LINE)
	while(fgets(line ,MAX_LINE_LENGTH, file))
	{
		fscanf(file, "%[^\n]", line);
		values[value_index] = atoi(line);
		//printf("Value: %i\n", values[value_index]);
		value_index++;
	}
	
	//CHECK IF VALUE INCREMENTED
	for(int index = 1 ; index < NUM_OF_INPUTS ; index++)
	{
		int recent_value = values[index];
		int previous_value = values[index-1];
		if(recent_value > previous_value)
		{	
			increments++;
		}
	}

	printf("Number of times the value incremented: %i", increments-1); //random 6422280 at the end, thus -1 
	
	fclose(file);
	return 0;
}