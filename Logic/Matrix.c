#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Matrix.h"

#define NumTile (7)
#define NumRow (7)

/*creating a new world with NumRow * NumTile space*/
char ** createWorld()
{
	int i;
	char ** matrix = (char **)malloc(NumRow * sizeof(char *));	//initializing the new matrix
	
	//if the malloc failed
	if(matrix == NULL)
	{
		return NULL;
	}

	for(i = 0; i < NumRow; i++)
	{
		matrix[i] = (char *)malloc(NumTile * sizeof(char)); //initializing each of the new rows
		//if any of the mallocs failed
		if(matrix[i] == NULL)
		{
			return NULL;
		}
		
	}
	return matrix;
}

/*insert char c to matrix in position (i,j)*/
char insert(char *** matrix, char c, int i, int j)
{
	(*matrix)[i][j] = c;
}


/* the method scans a row from the user the dimensions of the matrix
 	the first is the number of rows and the second is the number of columns  */
void getDimensions(int *dimensions)
{
	scanf("%d%d", &dimensions[0], &dimensions[1]); 
}


/* the method prints the row beginning at pointer <row> of <length> length  of long type numbers
	in the format - 1 3 2 -7 4 ... as requested in the question. */
void printRow(char *row, int length)
{
	int i;
	for(i = 0; i < length; i++)
	{
		if(i == length - 1)
			printf("%c\n", row[i]);
		else
			printf("%c ", row[i]);
	}
}

/*get is a function which prints the number of rows in the matrix,
  the number of columns of the matrix and each value in the matrix in the asked format */
void get(int *dimensions, char **matrix)
{
	int i;
	//this line prints the number of rows in matrix
	printf("Number of rows: %d\n", dimensions[0]);
	
	//this line prints the number of columns in matrix
	printf("Number of columns: %d\n", dimensions[1]);

	/*We go over all of the values in the matrix and print each one
	while each row is printed in a different line*/
	for(i = 0; i < dimensions[0]; i++) //going over the rows
		printRow(matrix[i], dimensions[1]);
}


/* the method frees all of the rows in the matrix 
 *  = frees all of the pointer in the pointer array.
 */
void free_rows(int *dimensions, char **matrix)
{
	int i;
	
	//going over all of the rows
	for(i = 0; i < dimensions[0]; i++)
	{
		if(matrix[i] != NULL)
		{	
			//free each of the rows
			free(matrix[i]);
		}
	}
}

/*Frees the entire matrix*/
void free_mat(int *dimensions, char ***matrix)
{
	free_rows(dimensions, *matrix);	//free all of the rows
	free(matrix);	//free the matrix itself
}


/*We assume that both of the positions exist in the matrix and we switch the values in them*/
void replace(char ***matrix, int i, int j, int k, int h)
{
	char temp = (*matrix)[i][j];
	(*matrix)[i][j] = (*matrix)[k][h];
	(*matrix)[k][h] = temp;
}

/*getting an empty initialized matrix and a src, then copying the contents of
the source to the destination*/
void copy_mat(char ***dest, char ***src)
{	
	int i;
	int j;
	//going over all of the rows
	for(i = 0; i < NumRow; i++)
	{
		//going over all of the columns
		for(j = 0; j < NumTile; j++)
		{
			(*dest)[i][j] = (*src)[i][j];	//copying the data from src in position (i,j) to dest in the same position
		}
	}	
}
