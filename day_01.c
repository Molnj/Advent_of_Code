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
#include <stdbool.h>

#define PT1 1
#define PT2 2

#define INPUT_FILE	"inputs\\day_01.txt"
#define NUMBER_OF_LINES	2000
#define LENGTH_OF_LINES	4


bool read_input_into_list(char* fileName, int* values);
int count_increments(int* values, int partNo);

int main()
{	
	int values[NUMBER_OF_LINES];
	if (read_input_into_list(INPUT_FILE, values))
	{
		int result1 = count_increments(values, PT1);
		int result2 = count_increments(values, PT2);
		printf("RESULT1 = %d (Number of times the [single] value incremented)\n", result1);
		printf("RESULT2 = %d (Number of times the [sliding window] value incremented)\n", result2);
	}
	else {return 1;}

	return 0;
}


bool read_input_into_list(char* fileName, int* values)
{
	//OPEN INPUT FILE
	FILE *pFile = fopen(fileName, "r");
	if (pFile == 0)
	{
		printf("Could not find input file: %s.\n", fileName);
		return false;
	}

	//LOAD VALUES INTO BUFFER (LINE-BY-LINE)
	int idx = 0;
	int value = 0;
    while (!feof(pFile))
    {
		fscanf(pFile, "%d\n", &value);
		values[idx] = value;
		idx++;
	}
	fclose(pFile);
	return true;
}


int count_increments(int* values, int partNo)
{
	int increments = 0;

	if(partNo == 1)
	{
		//COUNT INCREMENTS OF [SINGLE VALUE]
		for(int idx = 1 ; idx < NUMBER_OF_LINES ; idx++)
		{
			int recent_value = values[idx];
			int previous_value = values[idx-1];
			if(recent_value > previous_value) {increments++;}
		}
	}
	else if(partNo == 2)
	{
		//COUNT INCREMENTS OF [SLIDING WINDOW'S SUM]
		for(int index = 1 ; index < NUMBER_OF_LINES-2 ; index++)
		{
			int recent_window = 	values[index] 	+ values[index+1] 	+ values[index+2];
			int previous_window = 	values[index-1]	+ values[index] 	+ values[index+1];
			if(recent_window > previous_window) {increments++;}
		}
	}

	return increments;
}