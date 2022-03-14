/*
	Task:		Finding most common n-th bits in 1000piece 12bit binary number list.
				Final 12 bit binary number from the most common bits is gamma.
				Final 12 bit binary number from the least common bits is epsilon.
	Input file:	%CD\inputs\day3.txt
	Solution: 	2595824 (784*3311)
	Author:		Molnar Mate
	Date:		2022.03.14.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NUM_OF_BITS		12
#define NUM_OF_INPUTS	1000


int main()
{	
	int gamma_dec = 0;
	int epsilon_dec = 0;

	int gamma[12];
	int epsilon[12];
	int bitfield [NUM_OF_INPUTS][NUM_OF_BITS];


	// OPEN INPUT FILE
	FILE *file = fopen("inputs\\day3.txt", "r");
	if (file == 0)
	{
		printf("Could not find input file.\n");
		return 1;
	}


	// LOAD VALUES INTO "bitfield" MATRIX (line-by-line)
	int row_cnt = 0;
	char line[NUM_OF_BITS];
	while(fgets(line, sizeof(line), file))
	{
		fscanf(file, "%[^\n]", line);		//read: line -> str
		//read line char-by-char
		for (int i=0; i<sizeof(line); i++)
		{
			//printf("%c", line[i]);
			int bit = line[i] - '0';		// (ASCII value of '0-9') - (ASCII value of '0' (=48))
			if(bit==-48) {bit=0;}			// TODO - weird bug only in first line (in char-int conversion) (-48 instead of 0)
			bitfield [row_cnt][i] = bit;
		}
		row_cnt++;
	}
	printf("\n");


	// LOOP THROUGH MATRIX COLUMNS
	for(int x=0; x<NUM_OF_INPUTS; x++)
	{
		// LOOP THROUGH MATRIX ROWS
		for(int y=0; y<NUM_OF_BITS; y++)
		{
			printf("%d", bitfield [x][y]);
		}
		printf("\n");
	}


	// LOOP THROUGH MATRIX COLUMNS
	for(int x=0; x<NUM_OF_BITS; x++)
	{
		int ones = 0;
		int zeroes = 0;

		// LOOP THROUGH MATRIX ROWS
		for(int y=0; y<NUM_OF_INPUTS; y++)
		{
			//count 1s and 0s in column
			if(bitfield [y][x] == 1) {ones++;}
			else if(bitfield [y][x] == 0) {zeroes++;}
		}

		//fill n-th bit in gamma and epsilon
		if(ones > zeroes)
		{
			gamma[x] = 1;
			epsilon[x] = 0;
		}
		else
		{
			gamma[x] = 0;
			epsilon[x] = 1;
		}
	}
	

	fclose(file);


	printf("\nGamma: ");
	for(int n=0; n<12; n++) {printf("%d", gamma[n]);}
	printf("\nEpsilon: ");
	for(int n=0; n<12; n++) {printf("%d", epsilon[n]);}


	int i = 11;
	for(int n=0; n<12; n++)
	{
		gamma_dec += gamma[n] * pow(2,i);
		epsilon_dec += epsilon[n] * pow(2,i);
		i--;
	}
	printf("\nGamma: %d", gamma_dec);
	printf("\nEpsilon: %d", epsilon_dec);


	int solution = gamma_dec * epsilon_dec;
	printf("\nSolution: %d", solution);


	return 0;
}