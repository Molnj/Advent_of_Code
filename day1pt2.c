/*
	Task:		Put input measurements into 3item sliding (by1) windows. How many windows' sum are greater than the preivous'?
	Input file:	%CD\inputs\day1.txt 	(contains 2000 lines of int values)
	Solution: 	1589
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
	FILE *file = fopen("inputs\\day1.txt", "r");
	if (file == 0)
	{
		printf("Could not find input file.\n");
		return 1;
	}

	//LOAD VALUES INTO BUFFER (LINE-BY-LINE)
	while(fgets(line ,MAX_LINE_LENGTH, file))
	{
		fscanf(file, "%[^\n]", line);		//line -> str
		values[value_index] = atoi(line);	//str  -> int
		//printf("Value: %i\n", values[value_index]);
		value_index++;
	}

	//CHECK IF SUM OF WINDOW INCREMENTED
	for(int index = 1 ; index < NUM_OF_INPUTS-2 ; index++)
	{
		int recent_window = values[index] + values[index+1] +values[index+2];
		int previous_window = values[index-1] + values[index] +values[index+1];
		if(recent_window > previous_window)
		{	
			increments++;
		}
	}

	printf("Number of times the value incremented: %i", increments-1); //random 6422280 at the end, thus -1 
	
	fclose(file);
	return 0;
}