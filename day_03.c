/*
	AUTHOR:		Molnar Mate
	DATE:		2022.03.14

	INPUT FILE:	%CD\inputs\day_03.txt
				(contains 1000 lines of 12 bit long binary numbers)

	TASK-1:		Finding most common n-th bits in 1000piece 12bit binary number list.
				Final 12 bit binary number from the [MOST COMMON] bits is [GAMMA].
				Final 12 bit binary number from the [LEAST COMMON] bits is [EPSILON].
				Multiply together the 2 values to get the solution!
	TASK-2:		Find [OXYGEN] and [CO2] values!
				[OXYGEN]: find [MOST COMMON] n-th bit, then only keep corresponding lines. Last line remaining is [OXYGEN]
				[CO2]: find [LEAST COMMON] n-th bit, then only keep corresponding lines. Last line remaining is [CO2]
				Multiply together the 2 values to get the solution!

	SOLUTION-1: 2595824 (784*3311)
	SOLUTION-2: 2135254 (781*2734)
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INPUT_FILE		"inputs\\day_03.txt"
#define NUM_OF_BITS		12
#define LENGTH_OF_LINES	1000


int main()
{	
	int gamma_dec = 0;
	int epsilon_dec = 0;

	int gamma[12];
	int epsilon[12];
	int bitfield [LENGTH_OF_LINES][NUM_OF_BITS];


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
		for(int y=0; y<LENGTH_OF_LINES; y++)
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


/*
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INPUT_FILE		"inputs\\day3.txt"
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
			//printf("%c", line[i]);
			int bit = line[i] - '0';		// (ASCII value of '0-9') - (ASCII value of '0' (=48))
			if(bit==-48) {bit=0;}			// TODO - weird bug only in first line (in char-int conversion) (-48 instead of 0)
			bitfield [row_cnt][i] = bit;
		}
		row_cnt++;
	}
	fclose(pFile);


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
}*/