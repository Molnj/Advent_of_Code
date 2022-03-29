/*
	Task:		How many measurements are larger than the previous measurement?
	Input file:	%CD\inputs\day1.txt 	(contains 2000 lines of int values)
	Solution: 	1548
	Author:		Molnar Mate
	Date:		2022.03.13.
*/

#include <stdlib.h>
#include <stdio.h>

#define INPUT_FILE	"inputs\\day1.txt"
#define LINE_LEN	4
#define LINE_NUM	2000


int main()
{	
	// OPEN INPUT FILE
	FILE *pFile = fopen(INPUT_FILE, "r");
	if (pFile == 0)
	{
		printf("Could not find input file.\n");
		return 1;
	}


	//LOAD VALUES INTO BUFFER (LINE-BY-LINE)
	char line[LINE_LEN];
	int values[LINE_NUM];
	int value_index = 0;
	while(fgets(line ,LINE_LEN, pFile))
	{
		fscanf(pFile, "%[^\n]", line);		//line -> str
		values[value_index] = atoi(line);	//str  -> int
		//printf("Value: %i\n", values[value_index]);
		value_index++;
	}
	fclose(pFile);


	//CHECK IF VALUE INCREMENTED
	int increments = 0;
	for(int index = 1 ; index < LINE_NUM ; index++)
	{
		int recent_value = values[index];
		int previous_value = values[index-1];
		if(recent_value > previous_value)
		{	
			increments++;
		}
	}


	printf("Number of times the value incremented: %i", increments);
	return 0;
}