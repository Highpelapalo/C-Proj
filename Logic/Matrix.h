#ifndef MATRIX_H_
#define MATRIX_H_



#define NumTile (7)
#define NumRow (7)


/*creating a new world with NumRow * NumTile space*/
char ** createWorld();



/*insert char c to matrix in position (i,j)*/
char insert(char***, char, int, int);



/* the method scans a row from the user the dimensions of the matrix
 	the first is the number of rows and the second is the number of columns  */
void getDimensions(int*);



/* the method prints the row beginning at pointer <row> of <length> length  of long type numbers
	in the format - 1 3 2 -7 4 ... as requested in the question. */
void printRow(char*, int);



/*get is a function which prints the number of rows in the matrix,
  the number of columns of the matrix and each value in the matrix in the asked format */
void get(int*, char**);



/* the method frees all of the rows in the matrix 
 *  = frees all of the pointer in the pointer array.
 */
void free_rows(int*, char**);



/*Frees the entire matrix*/
void free_mat(int*, char***);




/*We assume that both of the positions exist in the matrix and we switch the values in them*/
void replace(char***, int, int, int, int);



/*getting an empty initialized matrix and a src, then copying the contents of
the source to the destination*/
void copy_mat(char***, char***);



#endif /* MATRIX_H_ */