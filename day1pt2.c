/*
	Task:		day1ot1, but put input measurements into 3item sliding (by1) windows.
				How many windows' sum are greater than the preivous'?
	Input file:	%CD\inputs\day1.txt 	(contains 2000 lines of int values)
	Solution: 	1589
	Author:		Molnar Mate
	Date:		2022.03.13.
*/

#include <stdlib.h>
#include <stdio.h>

#define INPUT_FILE		"inputs\\day1.txt"
#define LINE_LEN		4
#define LINE_NUM		2000


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
	while(fgets(line, LINE_LEN, pFile))
	{
		fscanf(pFile, "%[^\n]", line);		//line -> str
		values[value_index] = atoi(line);	//str  -> int
		//printf("Value: %i\n", values[value_index]);
		value_index++;
	}
	fclose(pFile);


	//CHECK IF SUM OF WINDOW INCREMENTED
	int increments = 0;
	for(int index = 1 ; index < LINE_NUM-2 ; index++)
	{
		int recent_window = values[index] + values[index+1] +values[index+2];
		int previous_window = values[index-1] + values[index] +values[index+1];
		if(recent_window > previous_window)
		{	
			increments++;
		}
	}


	printf("Number of times the value incremented: %i", increments);
	return 0;
}