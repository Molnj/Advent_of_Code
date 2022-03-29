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
#include <stdbool.h>

#define INPUT_FILE		"inputs\\day_03.txt"
#define NUMBER_OF_LINES	1000
#define LENGTH_OF_LINES	12

bool read_input_into_bit_matrix(char* fileName, int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES]);
int compute_power_consumption(int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES]);
int compute_oxygen_rating(int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES]);
int compute_co2_rating(int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES]);


int main()
{	
	int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES];
	if (read_input_into_bit_matrix(INPUT_FILE, bit_matrix))
	{
		int result1 = compute_power_consumption(bit_matrix);
		int result2 = compute_oxygen_rating(bit_matrix) * compute_co2_rating(bit_matrix);
		printf("\nRESULT1 = %d (power rating)", result1);
		printf("\nRESULT2 = %d (life support rating)\n", result2);
	}
	else {return 1;}

	return 0;
}


bool read_input_into_bit_matrix(char* fileName, int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES])
{
	// OPEN INPUT FILE
	FILE *pFile = fopen(fileName, "r");
	if (pFile == 0)
	{
		printf("Could not find input file: %s.\n", fileName);
		return false;
	}

	// LOAD VALUES INTO "bitfield" MATRIX (line-by-line)
	int row_cnt = 0;
	char line[LENGTH_OF_LINES];
	int value = 0;
    while (!feof(pFile))
    {
		fscanf(pFile, "%s\n", &line);
		//printf("%s\n", line);
		//read line char-by-char
		for (int i=0; i<sizeof(line); i++)
		{
			int bit = line[i] - '0';		// (ASCII value of '0-9') - (ASCII value of '0' (=48))
			if(bit==-48) {bit=0;}
			else if(bit==-47) {bit=1;}
			bit_matrix [row_cnt][i] = bit;
		}
		row_cnt++;
	}
	fclose(pFile);
	return true;
}


int compute_power_consumption(int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES])
{
	int gamma[12];
	int epsilon[12];

	int gamma_dec = 0;
	int epsilon_dec = 0;

	//COUNT 1s and 0s in each column, based on frequency fill x-th gamma and epsilon bit positions
	for(int x=0; x<LENGTH_OF_LINES; x++)
	{
		int ones = 0;
		int zeroes = 0;

		//count 1s and 0s in column
		for(int y=0; y<NUMBER_OF_LINES; y++)
		{
			if(bit_matrix [y][x] == 1) {ones++;}
			else if(bit_matrix [y][x] == 0) {zeroes++;}
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
	printf("\nGamma: %d\n", gamma_dec);
	printf("Epsilon: %d\n", epsilon_dec);


	//solution
	int solution1 = gamma_dec * epsilon_dec;
	return solution1;
}


int compute_oxygen_rating(int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES])
{
	int oxygen_b[LENGTH_OF_LINES];
	int oxygen_dec = 0;

	// COPY BIT_MATRIX INTO "OXIGEN" MATRIX
	int bit_matrix_oxygen [NUMBER_OF_LINES][LENGTH_OF_LINES];
	for(int row=0; row<NUMBER_OF_LINES; row++)
	{
		for(int col=0; col<LENGTH_OF_LINES; col++)
		{
			bit_matrix_oxygen [row][col] = bit_matrix [row][col];
		}
	}

	// OXYGEN - COUNT 1S AND 0S, THEN DELETE ROWS WITH LESS FREQUENT BITS AT X-TH BIT POSITION
	for(int x=0; x<LENGTH_OF_LINES; x++)
	{
		int ones = 0;
		int zeroes = 0;

		//counting part
		for(int y=0; y<NUMBER_OF_LINES; y++)
		{
			if(bit_matrix_oxygen [y][x] == 1) {ones++;}
			else if(bit_matrix_oxygen [y][x] == 0) {zeroes++;}
		}

		//"deleting" part (-1)
		for(int row=0; row<NUMBER_OF_LINES; row++)
		{
			if(ones >= zeroes)
			{
				if(bit_matrix_oxygen [row][x] == 0)
				{
					for(int col=0; col<LENGTH_OF_LINES; col++)
					{
						bit_matrix_oxygen [row][col] = -1;
					}
				}
			}
			else
			{
				if(bit_matrix_oxygen [row][x] == 1)
				{
					for(int col=0; col<LENGTH_OF_LINES; col++)
					{
						bit_matrix_oxygen [row][col] = -1;
					}
				}
			}
		}
	}

	//find oxygen_b array in matrix
	for(int row=0; row<NUMBER_OF_LINES; row++)
	{
		if(bit_matrix_oxygen [row][0] != -1)
		{
			for(int col=0; col<LENGTH_OF_LINES; col++)
			{
				oxygen_b[col] = bit_matrix_oxygen [row][col];
			}
		}
	}
	printf("\nOxygen_b: ");
	for (int i=0; i<LENGTH_OF_LINES; i++) {printf("%d", oxygen_b[i]);}

	//bin -> dec conversion
	int i = 11;
	for(int n=0; n<12; n++)
	{
		oxygen_dec += oxygen_b[n] * pow(2,i);
		i--;
	}
	printf("\nOyxgen: %d\n", oxygen_dec);

	return oxygen_dec;
}


int compute_co2_rating(int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES])
{
	int co2_b[LENGTH_OF_LINES];
	int co2_dec = 0;

	// COPY BIT_MATRIX INTO "CO2" MATRIX
	int bit_matrix_co2 [NUMBER_OF_LINES][LENGTH_OF_LINES];
	for(int row=0; row<NUMBER_OF_LINES; row++)
	{
		for(int col=0; col<LENGTH_OF_LINES; col++)
		{
			bit_matrix_co2 [row][col] = bit_matrix [row][col];
		}
	}

	// CO2 - COUNT 1S AND 0S, THEN DELETE ROWS WITH LESS FREQUENT BITS AT X-TH BIT POSITION
	for(int x=0; x<LENGTH_OF_LINES; x++)
	{
		int ones = 0;
		int zeroes = 0;

		//counting part
		for(int y=0; y<NUMBER_OF_LINES; y++)
		{
			if(bit_matrix_co2 [y][x] == 1) {ones++;}
			else if(bit_matrix_co2 [y][x] == 0) {zeroes++;}
		}

		//"deleting" part (-1)
		for(int row=0; row<NUMBER_OF_LINES; row++)
		{
			if(ones > 0 && zeroes > 0)	//removing the less frequent parts repeatedly could delete the last remaining option 
			{
				if(ones >= zeroes)
				{
					if(bit_matrix_co2 [row][x] == 1)
					{
						for(int col=0; col<LENGTH_OF_LINES; col++)
						{
							bit_matrix_co2 [row][col] = -1;
						}
					}
				}
				else
				{
					if(bit_matrix_co2 [row][x] == 0)
					{
						for(int col=0; col<LENGTH_OF_LINES; col++)
						{
							bit_matrix_co2 [row][col] = -1;
						}
					}
				}
			}
		}
	}
	//find co2_b array in matrix
	for(int row=0; row<NUMBER_OF_LINES; row++)
	{
		if(bit_matrix_co2 [row][0] != -1)
		{
			for(int col=0; col<LENGTH_OF_LINES; col++)
			{
				co2_b[col] = bit_matrix_co2 [row][col];
			}
		}
	}
	printf("CO2_b: ");
	for (int i=0; i<LENGTH_OF_LINES; i++) {printf("%d", co2_b[i]);}

	//bin -> dec conversion
	int i = 11;
	for(int n=0; n<12; n++)
	{
		co2_dec += co2_b[n] * pow(2,i);
		i--;
	}
	printf("\nCO2: %d\n", co2_dec);

	return co2_dec;
}