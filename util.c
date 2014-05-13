#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void nRowsCols(char *argv, int *rows, int *cols)//count rows and columns
{
	*rows=0;
	*cols=0;
	int len;
	FILE *file;
	file=fopen(argv,"r");
	char str,string[1000];
	{
		if (file) // count rows
		{
			while (!feof(file))
			{
				fscanf(file,"%c",&str);
				if(str=='\n')
					*rows+=1;
			}
		}
		fclose(file);
		*rows-=1;
	}
	file=fopen(argv,"r");
	{
		if(file) //count columns
		{
			fgets(string,1000,file);
			len=strlen(string);
			*cols=len-1;
		}
	}
	fclose(file);
}


int **createBoard(int columns, int rows)//creates a 2d array (dynamic allocation)
{
	int i=0, **backbone;
	backbone = (int**) malloc(sizeof(int *) * rows);
	for(i=0;i<rows;i++)
		backbone[i] = (int*) malloc(sizeof(int)*columns);
	return backbone;
}

/*void initializeBoard(int **table,int column,int rows,char *argv)//initializes table with values in the file
{
	FILE *input;
	input = fopen(argv, "r");
	int temp1, temp2;

	for (temp1 = 0; temp1< rows; temp1++)
	{
		temp2 =0;
		while (temp2 < column +1)
		{
			char temp_char;
			fscanf(input,"%c", &temp_char);
			if (temp_char == '\n')
				break;
			else
			{
				table[temp1][temp2] = temp_char;
				temp2 += 1;
			}
		}
	}
	fclose(input);
}*/
void **initializeBoard(int **newGen, int column, int rows, char *argv)//intilises board with values in file
{
	//	{
	//		int i=0,j=0;
	//		char value;
	//		FILE *fin;
	//		fin = fopen(argv,"r");
	//		for(i=0;i<rows;i++)
	//			{
	//			for(j=0;j<column;j++)
	//				{
	//				fscanf(fin,"%c",&value);
	//				newGen[i][j] = value;
	//				}
	//			fscanf(fin,"%c",&value);
	//			}
	//		fclose(fin);
	//		}
	FILE *file;
	file=fopen(argv,"r");
	char str;
	int i=0,j=0;
	while(i<rows)
	{
		for(j=0; j<=column; j++)
		{
			fscanf(file,"%c",&str);
			if(str=='\n')
				i++;
			else
				newGen[i][j]=str;
		}
	}
}

int **copyGen(int **newGen, int column, int rows) //copies value of one generation to other
{
	int **backbone,i,j;
	backbone=createBoard(column,rows);
	for(i=0;i<rows;i++)
		for(j=0;j<column;j++)
			backbone[i][j]=newGen[i][j];
	return backbone;
}

int **reset(int column, int rows) //resets value of array to 0
{
	int **backbone,i,j;
	backbone=createBoard(column, rows);
	for (i=0;i<rows;i++)
		for (j=0;j<column;j++)
			backbone[i][j]=0;
	return backbone;
}

void printBoard(int **newGen, int column, int rows)// prints the board
{
	int i,j;
	for (i=0;i<rows;i++)
	{
		for(j=0;j<column;j++)
			printf("%c",newGen[i][j]);
		printf("\n");
	}
}
void printTable(int **newGen, int column, int rows)// prints the table with integer values
{
	int i,j;
	for (i=0;i<rows;i++)
	{
		for(j=0;j<column;j++)
			printf("%d",newGen[i][j]);
		printf("\n");
	}
}

void neighbourVal(int **board, int **letters, int column, int rows)//tests for neighbour values, to find a live cell
{
	int i,j,count=0;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<column;j++)
		{
			if((i-1)>=0 && (i-1)<rows && (j-1)>=0 && (j-1)<column)
			{
				if(letters[i-1][j-1] != '.')
					count++;
			}
			if((j-1)>=0 && (j-1)<column)
			{
				if(letters[i][j-1] != '.')
					count++;
			}
			if((i-1)>=0 && (i-1)<rows)
			{
				if(letters[i-1][j] != '.')
					count++;
			}
			if((i+1)>=0 && (i+1)<rows && (j+1)>0 && (j+1)<column)
			{
				if(letters[i+1][j+1] != '.')
					count++;
			}
			if((i+1)>0 && (i+1)<rows)
			{
				if(letters[i+1][j] != '.')
					count++;
			}
			if((j+1)>0 && (j+1)<column)
			{
				if(letters[i][j+1] != '.')
					count++;
			}
			if((i-1)>=0 && (i-1)<rows && (j+1)>0 && (j+1)<column)
			{
				if(letters[i-1][j+1] != '.')
					count++;
			}
			if((i+1)>0 && (i+1)<rows && (j-1)>=0 && (j-1)<column)
			{
				if(letters[i+1][j-1] != '.')
					count++;
			}
			//printf("%d\n",count);
			board[i][j] = count;
			count = 0;
		}
	}
}


void deadCell (int **newGen, int **letters, int **board, int column, int rows)//checks for dead cell and live cell in same function
{
	int i,j;
	for(i=0; i<rows; i++)
	{
		for(j=0; j<column; j++)
		{
			if (letters[i][j]=='.')
			{
				if (board[i][j]<3 || board[i][j]>3)
					newGen[i][j] = '.';
				else
					newGen[i][j] = 'x';
			}
		}
	}
}
//void deadCell(int** newGen,int** letters,int** board,int cols,int rows)
//{
//	int i,j;
//	for(i=0;i<rows;i++)
//	{
//		for(j=0;j<cols;j++)
//		{
//			if(letters[i][j] != '.')
//			{
//				if((board[i][j] < 2) || (board[i][j] > 3))
//					newGen[i][j] = '.';   					}
//			else
//				newGen[i][j] = '.';
//		}
//	}
//}

void liveCell (int **newGen, int **letters, int **board, int column, int rows)//checks for new live cell
{
	int i,j;
	for(i=0; i<rows; i++)
	{
		for(j=0; j<column; j++)
		{
			if (letters[i][j]!='.')
			{
				if (board[i][j]<2 || board[i][j]>3)
					newGen[i][j] = '.';
				else
					if ((letters[i][j]-1)!='.')
						newGen[i][j] = letters[i][j]-1;
					else
						newGen[i][j] = letters[i][j]-2;
			}
		}
	}
}

void freeMatrix (int **newGen, int column, int rows)//frees up the memory in the matrix
{
	int i;
	for(i=0;i<rows;i++)
		free(newGen[i]);
	free(newGen);
	//printf("hello");
}

//int main(int argc, char *argv[])
//{
//	char str;
//	int rows, columns,j,i, **newGen, **backbone, **board, **letters;
//	FILE *in;
//	in=fopen(argv[1],"r");
//	nRowsCols(argv[1], &rows, &columns);
//	//printf("%d %d", rows,columns);
//	newGen=createBoard(columns,rows);
//	initializeBoard(newGen,columns,rows,argv[1]);
//	//for (i=0;i<rows;i++)
//	//for(j=0;j<columns;j++)
//	//printf("%c",newGen[i][j]);
//	backbone=copyGen(newGen,columns,rows);
//	//for (i=0;i<rows;i++)
//	//for(j=0;j<columns;j++)
//	//printf("%c",backbone[i][j]);
//
//	backbone=reset(columns,rows);
//	board = reset(columns,rows);
//	letters = copyGen(newGen, columns, rows);
//	printBoard(newGen, columns, rows);
//	//printBoard(backbone, columns, rows);
//	//for (i=0;i<rows;i++)
//	//for(j=0;j<columns;j++)
//	//printf("%c yo ",backbone[i][j]);
//	deadCell(newGen,letters,board,columns,rows);
//	neighbourVal(board,letters,columns,rows);
//	//printTable(board,columns, rows);
//	deadCell(newGen, letters, board, columns, rows);
//	liveCell(newGen, letters, board, columns, rows);
//	printBoard(newGen, columns, rows);
//	freeMatrix(newGen, columns, rows);
//	return 1;
//}
//
//#include<stdio.h>
