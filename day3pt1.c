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

#define INPUT_FILE		"inputs\\day3.txt"
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
	FILE *pFile = fopen(INPUT_FILE, "r");
	if (pFile == 0)
	{
		printf("Could not find input file.\n");
		return 1;
	}


	// LOAD VALUES INTO "bitfield" MATRIX (line-by-line)
	int row_cnt = 0;
	char line[NUM_OF_BITS];
	while(fgets(line, sizeof(line), pFile))
	{
		fscanf(pFile, "%[^\n]", line);		//read: line -> str
		//read line char-by-char
		for (int i=0; i<sizeof(line); i++)
		{
			int bit = line[i] - '0';		// (ASCII value of '0-9') - (ASCII value of '0' (=48))
			if(bit==-48) {bit=0;}			// TODO - weird bug only in first line (in char-int conversion) (-48 instead of 0)
			bitfield [row_cnt][i] = bit;
		}
		row_cnt++;
	}
	fclose(pFile);


	//COUNT 1s and 0s in each column, based on frequency fill x-th gamma and epsilon bit positions
	for(int x=0; x<NUM_OF_BITS; x++)
	{
		int ones = 0;
		int zeroes = 0;

		//count 1s and 0s in column
		for(int y=0; y<NUM_OF_INPUTS; y++)
		{
			if(bitfield [y][x] == 1) {ones++;}
			else if(bitfield [y][x] == 0) {zeroes++;}
		}

		//fill x-th bit in gamma and epsilon
		if(ones >= zeroes)
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
	//print results (binary)
	printf("\nGamma: ");
	for(int n=0; n<12; n++) {printf("%d", gamma[n]);}
	printf("\nEpsilon: ");
	for(int n=0; n<12; n++) {printf("%d", epsilon[n]);}


	//bin -> dec conversion
	int i = 11;
	for(int n=0; n<12; n++)
	{
		gamma_dec += gamma[n] * pow(2,i);
		epsilon_dec += epsilon[n] * pow(2,i);
		i--;
	}
	//print results (decimal)
	printf("\nGamma: %d", gamma_dec);
	printf("\nEpsilon: %d", epsilon_dec);


	//solution
	int solution = gamma_dec * epsilon_dec;
	printf("\nSolution: %d", solution);
	return 0;
}