/*
Name:APOORV VIKRAM SINGH
Rollnumber:IMT2013006
E-mail_ID:ApoorvVikram.Singh@iiitb.org
revision:15
date_of start:7/12/2013
Description:This assignment is to play game of life using dynamic memory allocation
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"util.h" // Contains function declarations 
// All the functions should be defined in util.c file
// If you use <util.h> then you will have to use -I . during the compilation
// For example gcc life.c util.c -o life -lm -I .
// Or else you can use the #include"util.h"


int main(int argc, char *argv[])
    {
    FILE *in;
    char token[512];
    int rows=0,column=0,**board,i,j,noGens,countGen=0,**letters, **newGen;

	// Finding rows and columns to create two-dimensional matrix
	nRowsCols(argv[1],&rows,&column);

	// Create two-dimensional matrix 
    newGen = createBoard(column,rows);

	// Initialize two-dimensional matrix 
    initializeBoard(newGen,column,rows,argv[1]);

    noGens = atoi(argv[2]);
    while(noGens > 0)
        {
        letters = copyGen(newGen,column,rows); // copy newGen matrix to letters matrix of same size: rows and columns
		board = reset(column,rows); 
        printf("Generation %d\n",countGen);
        printBoard(newGen,column,rows); // printing newGen matrix 
        neighbourVal(board,letters,column,rows); // board matrix will have value corresponding to the number of neighbours
        deadCell(newGen,letters,board,column,rows); // update the dead cells in newGen matrix 
        liveCell(newGen,letters,board,column,rows); // update live cells in newGen matrix
        // newLiveCell(newGen,letters,board,column,rows); // update new live cells in newGen matrix
        noGens--; countGen++; 
		freeMatrix(letters,column,rows); // deallocate the memory to the system
		freeMatrix(board,column,rows); 
        }

    printf("Generation %d\n",countGen);
    printBoard(newGen,column,rows); // printing the last generation
    
    freeMatrix(newGen,column,rows); // deallocate the memory to the system
    return 0;
    }
