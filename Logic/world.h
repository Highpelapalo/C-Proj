#ifndef WORLD_H_
#define WORLD_H_


#define Turns ("20")



typedef struct
{
	char ** matrix;	//the matrix grid of the world
	char cat; //Info on the cat, righest 3 bits are the column, 3 bits to the left is the row, 1 bit from there is wether
			//the component exists in the matrix
	char mouse;	//same for mouse
	char cheese;	//same for cheese
	int start;	//1 if the mouse starts, 0 otherwise
	int turns;	//number of turns remaining for the world
} world;



/*getting an empty world and copies the data from src to it*/
void copy_world(world*, world*);



/*Load a world from file, returns 1 on success and otherwise the error number*/
int loadWorld(world*, char*);



/*Save matrix into file, return errno if an error occured, otherwise 1*/
int saveWorld(world*, char*);



/*Change the [i,j] of matrix to c and return the previous character*/
char editWorld(char***, char, int, int);



/*freeing a world*/
void free_world(world*);




#endif /* WORLD_H_ */