#ifndef CHARACTER_H_
#define CHARACTER_H_


#define abs(a) (((a) < 0) ? (-(a)) : (a))


/*Return 1 if the component exists in the world, otherwise 0*/
int exist(char);


/*Returns the row the component is in if it exists*/
int row(char);


/*Returns the column the component is in if it exists*/
int column(char);


/*Creating the character with the appropriate info in it*/
char create_info(int , int, int);


/*Change the row that is saved in the char*/
char editRow(char, int);


/*Change the column that is saved in the char*/
char editColumn(char, int);


/*Return 1 if the two objects are adjacent, 0 otherwise*/
int adjacent(char, char);


#endif /* CHARACTER_H_ */