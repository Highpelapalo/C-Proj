#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "character.h"

#define abs(a) (((a) < 0) ? (-(a)) : (a))


/*Return 1 if the component exists in the world, otherwise 0*/
int exist(char info)
{
	char mask = 1 << 6;
	return (info & mask) >> 6 ;
}

/*Returns the row the component is in if it exists*/
int row(char info)
{
	char mask = ((((1 << 1) | 1) << 1) | 1) << 3;
	return (info & mask) >> 3;
}

/*Returns the column the component is in if it exists*/
int column(char info)
{
	char mask = (((1 << 1) | 1) << 1) | 1;
	return info & mask;
}


/*Creating the character with the appropriate info in it*/
char create_info(int exists, int i, int j)
{
	char res = 0x00;
	
	res |= exists; 
	res <<= 3;
	res |= i;	//row
	res <<= 3;
	res |= j;	//column

	return res;
}


/*Change the row that is saved in the char*/
char editRow(char c, int i)
{
	c &= (~56);		//clearing the second set of 3 bits of info (56 = 00111000)
	c |= (i << 3);		//giving the new row
	
	return c;
}

/*Change the column that is saved in the char*/
char editColumn(char c, int j)
{
	c &= (~7);	//clearing the 3 first bits of info (7 = 00000111)
	c |= j;		//giving the new column
	
	return c;
}


/*Return 1 if the two objects are adjacent, 0 otherwise*/
int adjacent(char obj1, char obj2)
{
	int sum = 0;
	sum += abs(row(obj1) - row(obj2));		//The distance diagonally
	sum += abs(column(obj1) - column(obj2));	//The distance horizontally
	
	return (sum > 1 ? 0 : 1);			//Overall the distance needs to be 1 or less for them to be adjacent
}