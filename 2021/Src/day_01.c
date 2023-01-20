/*
	AUTHOR:		Molnar Mate
	DATE:		2022.03.13.
	INPUT FILE: ..\txt_inputs\day_01.txt

	####################################################################################################
	--- Day 1: Sonar Sweep ---
	You're minding your own business on a ship at sea when the overboard alarm goes off! You rush to see if you can help. Apparently, one of the Elves tripped and accidentally sent the sleigh keys flying into the ocean!

	Before you know it, you're inside a submarine the Elves keep ready for situations like this. It's covered in Christmas lights (because of course it is), and it even has an experimental antenna that should be able to track the keys if you can boost its signal strength high enough; there's a little meter that indicates the antenna's signal strength by displaying 0-50 stars.

	Your instincts tell you that in order to save Christmas, you'll need to get all fifty stars by December 25th.

	Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

	As the submarine drops below the surface of the ocean, it automatically performs a sonar sweep of the nearby sea floor. On a small screen, the sonar sweep report (your puzzle input) appears: each line is a measurement of the sea floor depth as the sweep looks further and further away from the submarine.

	For example, suppose you had the following report:

	199
	200
	208
	210
	200
	207
	240
	269
	260
	263
	This report indicates that, scanning outward from the submarine, the sonar sweep found depths of 199, 200, 208, 210, and so on.

	The first order of business is to figure out how quickly the depth increases, just so you know what you're dealing with - you never know if the keys will get carried into deeper water by an ocean current or a fish or something.

	To do this, count the number of times a depth measurement increases from the previous measurement. (There is no measurement before the first measurement.) In the example above, the changes are as follows:

	199 (N/A - no previous measurement)
	200 (increased)
	208 (increased)
	210 (increased)
	200 (decreased)
	207 (increased)
	240 (increased)
	269 (increased)
	260 (decreased)
	263 (increased)
	In this example, there are 7 measurements that are larger than the previous measurement.

	How many measurements are larger than the previous measurement?

	Your puzzle answer was 1548.

	--- Part Two ---
	Considering every single measurement isn't as useful as you expected: there's just too much noise in the data.

	Instead, consider sums of a three-measurement sliding window. Again considering the above example:

	199  A      
	200  A B    
	208  A B C  
	210    B C D
	200  E   C D
	207  E F   D
	240  E F G  
	269    F G H
	260      G H
	263        H
	Start by comparing the first and second three-measurement windows. The measurements in the first window are marked A (199, 200, 208); their sum is 199 + 200 + 208 = 607. The second window is marked B (200, 208, 210); its sum is 618. The sum of measurements in the second window is larger than the sum of the first, so this first comparison increased.

	Your goal now is to count the number of times the sum of measurements in this sliding window increases from the previous sum. So, compare A with B, then compare B with C, then C with D, and so on. Stop when there aren't enough measurements left to create a new three-measurement sum.

	In the above example, the sum of each three-measurement window is as follows:

	A: 607 (N/A - no previous sum)
	B: 618 (increased)
	C: 618 (no change)
	D: 617 (decreased)
	E: 647 (increased)
	F: 716 (increased)
	G: 769 (increased)
	H: 792 (increased)
	In this example, there are 5 sums that are larger than the previous sum.

	Consider sums of a three-measurement sliding window. How many sums are larger than the previous sum?

	Your puzzle answer was 1589.

	Both parts of this puzzle are complete! They provide two gold stars: **
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define PT1 1
#define PT2 2

#define INPUT_FILE		"..\\txt_inputs\\day_01.txt"
#define NUMBER_OF_LINES	2000
#define LENGTH_OF_LINES	4

int values[NUMBER_OF_LINES];


bool read_input(char *fileName, int *values);
int count_increments(int* values, int partNo);



bool read_input(char *fileName, int *values)
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


int count_increments(int *values, int partNo)
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



int main()
{	
	if (! read_input(INPUT_FILE, values))
	{
		return E_NOT_OK;
	}

	int result1 = count_increments(values, PT1);
	int result2 = count_increments(values, PT2);
	printf("RESULT1 = %d (Number of times the [single] value incremented)\n", result1);
	printf("RESULT2 = %d (Number of times the [sliding window] value incremented)\n", result2);
	return E_OK;
}