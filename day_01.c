/*
	AUTHOR:		Molnar Mate
	DATE:		2022.03.13

	INPUT FILE:	%CD\inputs\day_01.txt
				(contains 2000 lines of int values (max 4 character long))

	TASK-1:		How many [SINGLE VALUE] measurements are larger than the previous measurement?
	TASK-2:		How many [3-ITEM SLIDING WINDOW SUM] measurements are larger than the previous measurement?

	SOLUTION-1: 1548
	SOLUTION-2: 1589
*/


#include <stdlib.h>
#include <stdio.h>

#define INPUT_FILE	"inputs\\day_01.txt"
#define NUMBER_OF_LINES	2000
#define LENGTH_OF_LINES	4


int main()
{	
	//OPEN INPUT FILE
	FILE *pFile = fopen(INPUT_FILE, "r");
	if (pFile == 0)
	{
		printf("Could not find input file: %s\n", INPUT_FILE);
		return 1;
	}


	//LOAD VALUES INTO BUFFER (LINE-BY-LINE)
	char line[LENGTH_OF_LINES];
	int values[NUMBER_OF_LINES];
	int value_index = 0;
	while(fgets(line ,LENGTH_OF_LINES, pFile))
	{
		fscanf(pFile, "%[^\n]", line);		//line -> str
		values[value_index] = atoi(line);	//str  -> int
		//printf("Value: %i\n", values[value_index]);
		value_index++;
	}
	fclose(pFile);


	//COUNT INCREMENTS OF [SINGLE VALUE]
	int single_increments = 0;
	for(int index = 1 ; index < NUMBER_OF_LINES ; index++)
	{
		int recent_value = values[index];
		int previous_value = values[index-1];
		if(recent_value > previous_value)
		{	
			single_increments++;
		}
	}

	
	//COUNT INCREMENTS OF [SLIDING WINDOW'S SUM]
	int window_increments = 0;
	for(int index = 1 ; index < NUMBER_OF_LINES-2 ; index++)
	{
		int recent_window = 	values[index] 	+ values[index+1] 	+ values[index+2];
		int previous_window = 	values[index-1]	+ values[index] 	+ values[index+1];
		if(recent_window > previous_window)
		{	
			window_increments++;
		}
	}


	printf("RESULT1 = %i (Number of times the *single* value incremented)\n", single_increments);
	printf("RESULT2 = %i (Number of times the *sliding window* value incremented)\n", window_increments);
	return 0;
}