/*
	Task:		Finding most common n-th bits in 1000piece 12bit binary number list.
				Final 12 bit binary number from the most common bits is gamma.
				Final 12 bit binary number from the least common bits is epsilon.
	Input file:	%CD\inputs\day3.txt
	Solution: 	2135254 (781*2734)
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
	int bitfield [NUM_OF_INPUTS][NUM_OF_BITS];

	int bitfield_oxygen [NUM_OF_INPUTS][NUM_OF_BITS];
	int bitfield_co2 [NUM_OF_INPUTS][NUM_OF_BITS];

	int oxygen_b[NUM_OF_BITS];
	int co2_b[NUM_OF_BITS];

	int oxygen_dec = 0;
	int co2_dec = 0;


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
	fclose(file);


	// COPY BITFIELD INTO "OXIGEN" AND "CO2" MATRICES
	for(int row=0; row<NUM_OF_INPUTS; row++)
	{
		for(int col=0; col<NUM_OF_BITS; col++)
		{
			bitfield_oxygen [row][col] = bitfield [row][col];
			bitfield_co2 [row][col] = bitfield [row][col];
		}
	}


	// OXYGEN - COUNT 1S AND 0S, THEN DELETE ROWS WITH LESS FREQUENT BITS AT X-TH BIT POSITION
	for(int x=0; x<NUM_OF_BITS; x++)
	{
		int ones = 0;
		int zeroes = 0;

		//counting part
		for(int y=0; y<NUM_OF_INPUTS; y++)
		{
			if(bitfield_oxygen [y][x] == 1) {ones++;}
			else if(bitfield_oxygen [y][x] == 0) {zeroes++;}
		}

		//"deleting" part (-1)
		for(int row=0; row<NUM_OF_INPUTS; row++)
		{
			if(ones >= zeroes)
			{
				if(bitfield_oxygen [row][x] == 0)
				{
					for(int col=0; col<NUM_OF_BITS; col++)
					{
						bitfield_oxygen [row][col] = -1;
					}
				}
			}
			else
			{
				if(bitfield_oxygen [row][x] == 1)
				{
					for(int col=0; col<NUM_OF_BITS; col++)
					{
						bitfield_oxygen [row][col] = -1;
					}
				}
			}
		}
	}
	//find oxygen_b array in matrix
	for(int row=0; row<NUM_OF_INPUTS; row++)
	{
		if(bitfield_oxygen [row][0] != -1)
		{
			for(int col=0; col<NUM_OF_BITS; col++)
			{
				oxygen_b[col] = bitfield_oxygen [row][col];
			}
		}
	}
	printf("\nOxygen_b: ");
	for (int i=0; i<NUM_OF_BITS; i++) {printf("%d", oxygen_b[i]);}


	// CO2 - COUNT 1S AND 0S, THEN DELETE ROWS WITH LESS FREQUENT BITS AT X-TH BIT POSITION
	for(int x=0; x<NUM_OF_BITS; x++)
	{
		int ones = 0;
		int zeroes = 0;

		//counting part
		for(int y=0; y<NUM_OF_INPUTS; y++)
		{
			if(bitfield_co2 [y][x] == 1) {ones++;}
			else if(bitfield_co2 [y][x] == 0) {zeroes++;}
		}

		//"deleting" part (-1)
		for(int row=0; row<NUM_OF_INPUTS; row++)
		{
			if(ones > 0 && zeroes > 0)	//removing the less frequent parts repeatedly could delete the last remaining option 
			{
				if(ones >= zeroes)
				{
					if(bitfield_co2 [row][x] == 1)
					{
						for(int col=0; col<NUM_OF_BITS; col++)
						{
							bitfield_co2 [row][col] = -1;
						}
					}
				}
				else
				{
					if(bitfield_co2 [row][x] == 0)
					{
						for(int col=0; col<NUM_OF_BITS; col++)
						{
							bitfield_co2 [row][col] = -1;
						}
					}
				}
			}
		}
	}
	//find co2_b array in matrix
	for(int row=0; row<NUM_OF_INPUTS; row++)
	{
		if(bitfield_co2 [row][0] != -1)
		{
			for(int col=0; col<NUM_OF_BITS; col++)
			{
				co2_b[col] = bitfield_co2 [row][col];
			}
		}
	}
	printf("\nCO2_b: ");
	for (int i=0; i<NUM_OF_BITS; i++) {printf("%d", co2_b[i]);}



	//bin -> dec conversion
	int i = 11;
	for(int n=0; n<12; n++)
	{
		oxygen_dec += oxygen_b[n] * pow(2,i);
		co2_dec += co2_b[n] * pow(2,i);
		i--;
	}
	printf("\nOyxgen: %d", oxygen_dec);
	printf("\nCO2: %d", co2_dec);


	//solution
	int solution = oxygen_dec * co2_dec;
	printf("\nSOLUTION: %d", solution);


	return 0;
}