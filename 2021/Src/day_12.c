/*
	AUTHOR:		Molnar Mate
	DATE:		2022.07.05.
	INPUT FILE:	..\txt_inputs\day_12.txt

	####################################################################################################
	AOC description
	

//////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/std_types.h"

#define INPUT_FILE			"..\\txt_inputs\\day_12.txt"
#define LINES		25		// number of rows in input txt 
#define COLS		10		// max line length in input txt
char txt[LINES][COLS+2];	// +2 for read input()'s +'\0'

#define START 	"start"
#define END 	"end"


//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct node_t node_t;s
struct node_t {
	int val;
	node_t *next;
};

typedef struct {
	int adjacency[LINES]		// adjacency matrix
	char names[LINES][COLS];	// name of cave chambers
	int cnt;					// num of cave chambers
} cave_t;

//////////////////////////////////////////////////////////////////////////////////////////////////

bool read_input(char* fileName) {
	FILE *pFile = fopen(fileName, "r");
	if (pFile == 0) {
		return E_NOT_OK;
	}

	// .TXT --> CHAR[row][column]
	int i = 0;
	while(fgets(txt[i], COLS+2, pFile)) {	//+2 for '\0'
		txt[i][strlen(txt[i]) - 1] = '\0';
		i++;
	}

	fclose(pFile);
	return E_OK;
}

// fills up cave struct from txt file data
void process_input(cave_t *cave) {
	char *token = NULL;
	char delim[] = "-";

	for(int line = 0; line < LINES; line++) {
		token = strtok(txt[line], delim);
		uint8_t cnt = 0;
		while( token != NULL ) {
			switch(cnt) {
				case 0: ;
				case 1: ;
					//printf("%s\n", token);
					bool flag = false;
					for (int i = 0; i < cave->cnt; i++) {
						if(strcmp(token,cave->names[i]) == 0) { flag = true; }
					}
					if(!flag) {
						strcpy(cave->names[cave->cnt], token);
						//printf("--->%s\n",cave->names[cave->cnt]);
						cave->cnt++;
					}
					break;
				default:
					break;
			}
			token = strtok(NULL, delim);
			cnt++;
		}
	}
}

void create_adjacency_matrix(cave_t *cave) {
	for (int i = 0; i < cave->cnt; i++) {
		
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	uint32_t result_1 = 0;
	uint32_t result_2 = 0;

	cave_t cave = {{{0,0}},0};

	if(read_input(INPUT_FILE)) {
		printf("Error: could not find input file: %s.\n", INPUT_FILE);
		return E_NOT_OK;
	}
	process_input(&cave);	//ADD PARAM
	create_adjacency_matrix(&cave);


	printf("result_1 = %lu\n", result_1);
	printf("result_2 = %lu\n", result_2);

printf("***%d\n", cave.cnt);
    for (int i = 0; i < cave.cnt; i++) {
		printf("\t%s", cave.names[i]);
	}
    for (int i = 0; i < cave.cnt; i++) {
        printf(" \n%s", cave.names[i]);
	}


	getchar();
    return E_OK;
}

/*
 * biggest headaches:
 * 		- representing cave as a graph
*/
