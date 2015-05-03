#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#define NumTile (7)
#define NumRow (7)



typedef struct
{
	world* worldRef;	//pointer to the world of the game
	int isMaxPlayer;	//1 if it's mouse's turn, 0 otherwise
	int win;	//1 if tie, 2 if mouse wins, 3 if cat wins, 0 otherwise
	int pause;	//0 if not paused, 1 otherwise

} GameState;




/*Returns a new initialized GameState*/
GameState* init();




/*freeing the game*/
void free_gamestate(GameState*);




/*getting an empty GameState and copies the data from src to it*/
void copy_game(GameState*, GameState*);




/*Returns the row of the position of the current player*/
int getRow(GameState*);




/*Returns the column of the position of the current player*/
int getColumn(GameState*);




/*Returns a list of the possible GameStates one step from now*/
ListRef getChildren(GameState*);




/*moves the current player 1 tile up*/
void up(GameState*);




/*moves the current player 1 tile to the right*/
void right(GameState*);




/*moves the current player 1 tile down*/
void down(GameState*);




/*moves the current player 1 tile to the left*/
void left(GameState*);




/*Advancing the game 1 turn forward*/
void advance(GameState*, int);




/*Checking the status of the game, return 0 if nothing changed, 1 if we ran out of turns,
  2 if mouse won, 3 if cat won*/
int checkStatus(GameState*);




/*Returns the number of the action that was estimated to be the best from all of the available actions*/
int findChild(GameState*, int);



/*gives a numerical evaluation of the current game to the current player*/
int evaluate(GameState*);




#endif /* GAMESTATE_H_ */