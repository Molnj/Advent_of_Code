/*
	AUTHOR:		Molnar Mate
	DATE:		2022.06.28.
	INPUT FILE:	..\txt_inputs\day_08.txt

	####################################################################################################
	--- Day 8: Seven Segment Search ---
	You barely reach the safety of the cave when the whale smashes into the cave mouth, collapsing it. Sensors indicate another exit to this cave at a much greater depth, so you have no choice but to press on.

	As your submarine slowly makes its way through the cave system, you notice that the four-digit seven-segment displays in your submarine are malfunctioning; they must have been damaged during the escape. You'll be in a lot of trouble without them, so you'd better figure out what's wrong.

	Each digit of a seven-segment display is rendered by turning on or off any of seven segments named a through g:

	0:      1:      2:      3:      4:
	aaaa    ....    aaaa    aaaa    ....
	b    c  .    c  .    c  .    c  b    c
	b    c  .    c  .    c  .    c  b    c
	....    ....    dddd    dddd    dddd
	e    f  .    f  e    .  .    f  .    f
	e    f  .    f  e    .  .    f  .    f
	gggg    ....    gggg    gggg    ....

	5:      6:      7:      8:      9:
	aaaa    aaaa    aaaa    aaaa    aaaa
	b    .  b    .  .    c  b    c  b    c
	b    .  b    .  .    c  b    c  b    c
	dddd    dddd    ....    dddd    dddd
	.    f  e    f  .    f  e    f  .    f
	.    f  e    f  .    f  e    f  .    f
	gggg    gggg    ....    gggg    gggg
	So, to render a 1, only segments c and f would be turned on; the rest would be off. To render a 7, only segments a, c, and f would be turned on.

	The problem is that the signals which control the segments have been mixed up on each display. The submarine is still trying to display numbers by producing output on signal wires a through g, but those wires are connected to segments randomly. Worse, the wire/segment connections are mixed up separately for each four-digit display! (All of the digits within a display use the same connections, though.)

	So, you might know that only signal wires b and g are turned on, but that doesn't mean segments b and g are turned on: the only digit that uses two segments is 1, so it must mean segments c and f are meant to be on. With just that information, you still can't tell which wire (b/g) goes to which segment (c/f). For that, you'll need to collect more information.

	For each display, you watch the changing signals for a while, make a note of all ten unique signal patterns you see, and then write down a single four digit output value (your puzzle input). Using the signal patterns, you should be able to work out which pattern corresponds to which digit.

	For example, here is what you might see in a single entry in your notes:

	acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab |
	cdfeb fcadb cdfeb cdbaf
	(The entry is wrapped here to two lines so it fits; in your notes, it will all be on a single line.)

	Each entry consists of ten unique signal patterns, a | delimiter, and finally the four digit output value. Within an entry, the same wire/segment connections are used (but you don't know what the connections actually are). The unique signal patterns correspond to the ten different ways the submarine tries to render a digit using the current wire/segment connections. Because 7 is the only digit that uses three segments, dab in the above example means that to render a 7, signal lines d, a, and b are on. Because 4 is the only digit that uses four segments, eafb means that to render a 4, signal lines e, a, f, and b are on.

	Using this information, you should be able to work out which combination of signal wires corresponds to each of the ten digits. Then, you can decode the four digit output value. Unfortunately, in the above example, all of the digits in the output value (cdfeb fcadb cdfeb cdbaf) use five segments and are more difficult to deduce.

	For now, focus on the easy digits. Consider this larger example:

	be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb |
	fdgacbe cefdb cefbgd gcbe
	edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec |
	fcgedb cgb dgebacf gc
	fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef |
	cg cg fdcagb cbg
	fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega |
	efabcd cedba gadfec cb
	aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga |
	gecf egdcabf bgf bfgea
	fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf |
	gebdcfa ecba ca fadegcb
	dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf |
	cefg dcbef fcge gbcadfe
	bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd |
	ed bcgafe cdgba cbgef
	egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg |
	gbdfcae bgc cg cgb
	gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc |
	fgae cfgab fg bagce
	Because the digits 1, 4, 7, and 8 each use a unique number of segments, you should be able to tell which combinations of signals correspond to those digits. Counting only digits in the output values (the part after | on each line), in the above example, there are 26 instances of digits that use a unique number of segments (highlighted above).

	In the output values, how many times do digits 1, 4, 7, or 8 appear?

	Your puzzle answer was 416.

	--- Part Two ---
	Through a little deduction, you should now be able to determine the remaining digits. Consider again the first example above:

	acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab |
	cdfeb fcadb cdfeb cdbaf
	After some careful analysis, the mapping between signal wires and segments only make sense in the following configuration:

	dddd
	e    a
	e    a
	ffff
	g    b
	g    b
	cccc
	So, the unique signal patterns would correspond to the following digits:

	acedgfb: 8
	cdfbe: 5
	gcdfa: 2
	fbcad: 3
	dab: 7
	cefabd: 9
	cdfgeb: 6
	eafb: 4
	cagedb: 0
	ab: 1
	Then, the four digits of the output value can be decoded:

	cdfeb: 5
	fcadb: 3
	cdfeb: 5
	cdbaf: 3
	Therefore, the output value for this entry is 5353.

	Following this same process for each entry in the second, larger example above, the output value of each entry can be determined:

	fdgacbe cefdb cefbgd gcbe: 8394
	fcgedb cgb dgebacf gc: 9781
	cg cg fdcagb cbg: 1197
	efabcd cedba gadfec cb: 9361
	gecf egdcabf bgf bfgea: 4873
	gebdcfa ecba ca fadegcb: 8418
	cefg dcbef fcge gbcadfe: 4548
	ed bcgafe cdgba cbgef: 1625
	gbdfcae bgc cg cgb: 8717
	fgae cfgab fg bagce: 4315
	Adding all of the output values in this larger example produces 61229.

	For each entry, determine all of the wire/segment connections and decode the four-digit output values. What do you get if you add up all of the output values?

	Your puzzle answer was 1043697.

	Both parts of this puzzle are complete! They provide two gold stars: **
//////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define INPUT_FILE			"..\\txt_inputs\\day_08.txt"
#define NUMBER_OF_LINES		200		//number of rows in input txt 
#define LENGTH_OF_LINES		100		//max line length in input txt
char txt[NUMBER_OF_LINES][LENGTH_OF_LINES];	//character matrix - to be filled up with input txt

#define INPUT_CNT	10
#define	INPUT_LEN	(7+1)	// max: abcdefg + \0

#define OUTPUT_CNT	4
#define	OUTPUT_LEN	(7+1)	// max: abcdefg + \0

#define DIGIT_0		"abcefg"
#define DIGIT_1		"cf"
#define DIGIT_2		"acdeg"
#define DIGIT_3		"abdfg"
#define DIGIT_4		"bcdf"
#define DIGIT_5		"abdfg"
#define DIGIT_6		"abdefg"
#define DIGIT_7		"acf"
#define DIGIT_8		"abcdefg"
#define DIGIT_9		"abcdfg"

//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
	char input[INPUT_CNT][INPUT_LEN];
	char output[OUTPUT_CNT][OUTPUT_LEN];
} combination_t;

typedef struct 
{
	combination_t list[NUMBER_OF_LINES];
} list_t;

//////////////////////////////////////////////////////////////////////////////////////////////////

bool read_input(char* fileName) 
{
	FILE *pFile = fopen(fileName, "r");
	if (pFile == 0)
	{
		return E_NOT_OK;
	}

	// .TXT --> CHAR[row][column]
	int i = 0;
	while(fgets(txt[i], LENGTH_OF_LINES, pFile))
	{
		txt[i][strlen(txt[i]) - 1] = '\0';
		i++;
	}

	fclose(pFile);
	return E_OK;
}

void process_input(list_t *myList)
{
	char character = '0';
	uint8_t element_num = 0;
	uint8_t element_idx = 0;

	//inputs
	for(int line = 0; line < NUMBER_OF_LINES; line++)
	{
		character = '0';
		element_num = 0;
		element_idx = 0;
		for(int idx = 0; idx < 61; idx++)//LENGTH_OF_LINES
		{
			character = txt[line][idx];
			printf("%c", character);
			if(character == ' ')
			{
				element_num++;
				element_idx = 0;
			}
			else
			{
				myList->list[line].input[element_num][element_idx] = character;
				element_idx++;
			}
		}

		element_num = 0;
		element_idx = 0;
		for(int idx = 61; idx < strlen(txt[line]); idx++)
		{
			character = txt[line][idx];
			printf("%c", character);
			if(character == ' ')
			{
				element_num++;
				element_idx = 0;
			}
			else
			{
				myList->list[line].output[element_num][element_idx] = character;
				element_idx++;
			}
		}
		printf("\n");
	}
}

uint32_t count_1478_outputs(list_t *myList)
{
	uint8_t length = 0;
	uint32_t cnt = 0;
	for(int i = 0; i < NUMBER_OF_LINES; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			length = strlen(myList->list[i].output[j]);
			if(length == 2 || length == 4 || length == 3 || length == 7)
			{
				cnt ++;
			}
		}
	}
	return cnt;
}

uint32_t sum_outputs(list_t *myList)
{
	// 1,4,7,8 have unique number of segments, thus they are identifiable
	// 2,3,5 all have 5 segments, but only 3 contains both 1 segments, and only 2 contains 2 segments of 4 (instead of 3)
	// 0,6,9 have 6 segments, but the are also identifiable using 1 and 4.
	// multiplier needed for handling decimal places
	uint8_t length = 0;
	uint16_t multiplier = 1000;
	uint32_t sum = 0;

	char segments_in_1[2];
	uint8_t segment_match_with_1 = 0;
	char segments_in_4[4];
	uint8_t segment_match_with_4 = 0;

	for(int line = 0; line < NUMBER_OF_LINES; line++)
	{
		//finding 1 and 4 in from the inputs
		for(uint8_t in_idx = 0; in_idx < 10; in_idx++)
		{
			if(strlen(myList->list[line].input[in_idx]) == 2)
			{
				segments_in_1[0] = myList->list[line].input[in_idx][0];
				segments_in_1[1] = myList->list[line].input[in_idx][1];
			}
			if(strlen(myList->list[line].input[in_idx]) == 4)
			{
				segments_in_4[0] = myList->list[line].input[in_idx][0];
				segments_in_4[1] = myList->list[line].input[in_idx][1];
				segments_in_4[2] = myList->list[line].input[in_idx][2];
				segments_in_4[3] = myList->list[line].input[in_idx][3];
			}
		}

		//decoding output based on length and 1+4 inputs
		multiplier = 1000;
		for(int out_idx = 0; out_idx < 4; out_idx++)
		{
			segment_match_with_1 = 0;
			segment_match_with_4 = 0;
			length = strlen(myList->list[line].output[out_idx]);
			if(length == 2)
			{
				sum += 1 * multiplier;
			}
			if(length == 3)
			{
				sum += 7 * multiplier;
			}
			if(length == 4)
			{
				sum += 4 * multiplier;
			}
			if(length == 5)
			{
				for (int x1 = 0; x1 < length; x1++)
				{
					for (int x2 = 0; x2 < 2; x2++)
					{
						if(segments_in_1[x2] == myList->list[line].output[out_idx][x1])
						{
							segment_match_with_1++;
						}
					}
					for (int x2 = 0; x2 < 4; x2++)
					{
						if(segments_in_4[x2] == myList->list[line].output[out_idx][x1])
						{
							segment_match_with_4++;
						}
					}
				}
				if(segment_match_with_1 == 2)
				{
					sum += 3 * multiplier;
				}
				else if(segment_match_with_4 == 2)
				{
					sum += 2 * multiplier;
				}
				else
				{
					sum += 5 * multiplier;
				}
			}
			if(length == 6)
			{
				for (int x1 = 0; x1 < length; x1++)
				{
					for (int x2 = 0; x2 < 2; x2++)
					{
						if(segments_in_1[x2] == myList->list[line].output[out_idx][x1])
						{
							segment_match_with_1++;
						}
					}
					for (int x2 = 0; x2 < 4; x2++)
					{
						if(segments_in_4[x2] == myList->list[line].output[out_idx][x1])
						{
							segment_match_with_4++;
						}
					}
				}
				if(segment_match_with_1 == 1)
				{
					sum += 6 * multiplier;
				}
				else if(segment_match_with_4 == 4)
				{
					sum += 9 * multiplier;
				}
				else
				{
					sum += 0 * multiplier;
				}
			}
			if(length == 7)
			{
				sum += 8 * multiplier;
			}

			multiplier /= 10;
		}
	}
	return sum;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint32_t result_2 = 0;

	list_t myList = {{0}};

	if(read_input(INPUT_FILE))
	{
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_input(&myList);

	result_1 = count_1478_outputs(&myList);
	result_2 = sum_outputs(&myList);


	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);


    return E_OK;
}

/*
 * biggest headaches:
 * 		- reading input :(
 * 1041715 low
*/