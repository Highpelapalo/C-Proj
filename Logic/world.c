#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "Matrix.c"
#include "character.c"

#include "world.h"

#define Turns ("20")


/*getting an empty world and copies the data from src to it*/
void copy_world(world *dest, world *src)
{
	dest->cat = src->cat;
	dest->mouse = src->mouse;
	dest->cheese = src->cheese;
	dest->start = src->start;
	dest->turns = src->turns;
	copy_mat(&(dest->matrix), &(src->matrix));

}



/*Load a world from file, returns 1 on success and otherwise the error number*/
int loadWorld(world *worldRef, char* file)
{
	int i;
	int j;
	int c;
	char str[60];

	FILE *f;
	f = fopen(file, "r");
	
	//Failed to open the file
	if(f == NULL)
	{
		return errno;
	}	
	
	int dimensions[2] ={NumRow, NumTile};

	worldRef->cat = 0x00;
	worldRef->mouse = 0x00;
	worldRef->cheese = 0x00;

	//Creating the matrix
	char **matrix = createWorld();

	//if there was a previous matrix we want to free it
	if(worldRef->matrix != NULL)
	{	
		free_mat(dimensions, &(worldRef->matrix));
	}
	
	//CreateWorld faile to create a matrix
	if(matrix == NULL)
	{
		return errno;
	}
	
	//load the number of turns to the game
	if(!fscanf(f, "%d", &(worldRef->turns)))
	{
		return errno;
	}

	//skip the newline character
	if(fseek(f, 1, SEEK_CUR))
	{
		return errno;
	}
	
	//load the starting player
	if(fgets(str, 60, f) == NULL)
	{
		return errno;
	}

	//if the mouse starts
	if(!strcmp(str, "mouse\n"))
	{
		worldRef->start = 1;
	}
	else
	{
		worldRef->start = 0;
	}


	//going over all of the components of the world data
	for(i = 0; i < NumRow; i++)
	{
		for(j = 0; j < NumTile; j++)
		{
			//If we failed to load one of the characters
			if((c = fgetc(f)) == EOF)
			{
				return errno;
			}


			//when we found the mouse tile
			if(c == 'M')
			{
				worldRef->mouse = create_info(1, i, j);	
			}
			else if(c == 'C')	//cat tile
			{
				worldRef->cat = create_info(1, i, j);
			}

			else if(c == 'P')	//cheese tile
			{
				worldRef->cheese = create_info(1, i, j);
			}			

			//inserting the data to the matrix
			insert(&matrix, (char)c, i, j);
		}
		if(fseek(f, 1, SEEK_CUR) && !(i == NumRow - 1))
		{
			return errno;
		}
	}

	worldRef -> matrix = matrix; 

	//closing the file
	if(fclose(f))
	{
		return errno;
	}
	return 1;
}







/*Save matrix into file, return errno if an error occured, otherwise 1*/
int saveWorld(world *worldRef, char* file)
{
	int i;
	int j;
	FILE *f;
	f = fopen(file, "w");

	//Failed to open the file
	if(f == NULL)
	{
		return;
	}
	
	
	//We write the number of turns for the world, 20 is default
	if(fputs(Turns, f) == EOF)
	{
		return errno;
	}
	
	if(fputc('\n', f) == EOF)
	{
		return errno;
	}

	//if the mouse starts the game
	if(worldRef->start)
	{
		if(fputs("mouse\n", f) == EOF)
		{
			return errno;
		}
	}
	else //if the cat starts the game
	{
		if(fputs("cat\n", f) == EOF)
		{
			return errno;
		}
	}


	//going over all of the components of the world data
	for(i = 0; i < NumRow; i++)
	{
		for(j = 0; j < NumTile; j++)
		{
			//If we failed to store one of the tiles
			if(fputc((worldRef->matrix)[i][j], f) == EOF)
			{
				return errno;
			}
		}
		//Under the last row we want no new line
		if(i != NumRow - 1)
		{
			//If we failed to break a line after each row
			if(fputc('\n', f) == EOF)
			{
					return errno;
			}
		}

	}

	//closing the file
	if(fclose(f))
	{
		return errno;
	}

	return 1;
}






/*Change the [i,j] of matrix to c and return the previous character*/
char editWorld(char ***matrix, char c, int i, int j)
{	
	char res = (*matrix)[i][j];
	(*matrix)[i][j] = c;
	return res;
}


/*freeing a world*/
void free_world(world *worldRef)
{
	int dimensions[2] ={NumRow, NumTile};
	free_mat(dimensions, &(worldRef->matrix));	//free the matrix of the world
	free(worldRef);		//free the world itself
}




/*
int i;
	int j;
	char **matrix;
	matrix = (char **)malloc(7 * sizeof(char *));
	for(i = 0;i < 7;i++)
	{
		matrix[i] = (char *)malloc(7 * sizeof(char));
	}
	
	for(i = 0; i < 7; i++)
	{
		for(j = 0; j < 7; j++)
		{
			matrix[i][j] = 'a';
		}
	}
	saveWorld(matrix, "hello.world");
	return 0;
*/
int main()
{
	int i = 0;
	int j;
	world *new = (world*)malloc(sizeof(world));
	
	loadWorld(new, "hello.world");

	printf("%d\n", new->start);

	for(i = 0; i < 7; i++)
	{
		printRow((new->matrix)[i], NumTile);
	}
	
	printf("%d %d %d\n", exist(new->cat), row(new->cat), column(new->cat));	

}

