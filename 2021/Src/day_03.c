/*
	AUTHOR:		Molnar Mate
	DATE:		2022.03.14.
	INPUT FILE:	..\txt_inputs\day_03.txt

	####################################################################################################
	--- Day 3: Binary Diagnostic ---
	The submarine has been making some odd creaking noises, so you ask it to produce a diagnostic report just in case.

	The diagnostic report (your puzzle input) consists of a list of binary numbers which, when decoded properly, can tell you many useful things about the conditions of the submarine. The first parameter to check is the power consumption.

	You need to use the binary numbers in the diagnostic report to generate two new binary numbers (called the gamma rate and the epsilon rate). The power consumption can then be found by multiplying the gamma rate by the epsilon rate.

	Each bit in the gamma rate can be determined by finding the most common bit in the corresponding position of all numbers in the diagnostic report. For example, given the following diagnostic report:

	00100
	11110
	10110
	10111
	10101
	01111
	00111
	11100
	10000
	11001
	00010
	01010
	Considering only the first bit of each number, there are five 0 bits and seven 1 bits. Since the most common bit is 1, the first bit of the gamma rate is 1.

	The most common second bit of the numbers in the diagnostic report is 0, so the second bit of the gamma rate is 0.

	The most common value of the third, fourth, and fifth bits are 1, 1, and 0, respectively, and so the final three bits of the gamma rate are 110.

	So, the gamma rate is the binary number 10110, or 22 in decimal.

	The epsilon rate is calculated in a similar way; rather than use the most common bit, the least common bit from each position is used. So, the epsilon rate is 01001, or 9 in decimal. Multiplying the gamma rate (22) by the epsilon rate (9) produces the power consumption, 198.

	Use the binary numbers in your diagnostic report to calculate the gamma rate and epsilon rate, then multiply them together. What is the power consumption of the submarine? (Be sure to represent your answer in decimal, not binary.)

	Your puzzle answer was 2595824.

	--- Part Two ---
	Next, you should verify the life support rating, which can be determined by multiplying the oxygen generator rating by the CO2 scrubber rating.

	Both the oxygen generator rating and the CO2 scrubber rating are values that can be found in your diagnostic report - finding them is the tricky part. Both values are located using a similar process that involves filtering out values until only one remains. Before searching for either rating value, start with the full list of binary numbers from your diagnostic report and consider just the first bit of those numbers. Then:

	Keep only numbers selected by the bit criteria for the type of rating value for which you are searching. Discard numbers which do not match the bit criteria.
	If you only have one number left, stop; this is the rating value for which you are searching.
	Otherwise, repeat the process, considering the next bit to the right.
	The bit criteria depends on which type of rating value you want to find:

	To find oxygen generator rating, determine the most common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 1 in the position being considered.
	To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 0 in the position being considered.
	For example, to determine the oxygen generator rating value using the same example diagnostic report from above:

	Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.
	Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
	In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
	In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
	In the fifth position, there are an equal number of 0 bits and 1 bits (one each). So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
	As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.
	Then, to determine the CO2 scrubber rating value from the same example above:

	Start again with all 12 numbers and consider only the first bit of each number. There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
	Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
	In the third position, there are an equal number of 0 bits and 1 bits (one each). So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
	As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.
	Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.

	Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together. What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)

	Your puzzle answer was 2135254.

	Both parts of this puzzle are complete! They provide two gold stars: **
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define INPUT_FILE		"..\\txt_inputs\\day_03.txt"
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
	else {return E_NOT_OK;}

	return E_OK;
}


bool read_input_into_bit_matrix(char *fileName, int bit_matrix[NUMBER_OF_LINES][LENGTH_OF_LINES])
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