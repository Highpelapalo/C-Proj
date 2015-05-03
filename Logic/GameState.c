#include <stdio.h>

#include "world.c"
#include "ListUtils.c"
#include "MiniMax.c"

#include "GameState.h"

#define NumTile (7)
#define NumRow (7)




/*Returns a new initialized GameState*/
GameState* init()
{
	int i;
	
	GameState *game = (GameState*)malloc(sizeof(GameState));	//initializing the game
	game->isMaxPlayer = 1;	// IMPORTANT!!!!!!!!! ONLY IF THE MOUSE STARTS!!!!!!!!!!!!!!!
	game->win = 0;
	game->pause = 0;
	world* worldRef = (world*)malloc(sizeof(world));	//initializing the world
	worldRef->start = 1;
	worldRef->matrix = (char**)malloc(sizeof(char*) * NumRow);	//initializing the matrix
	
	for(i = 0; i < NumRow; i++)
	{
		(worldRef->matrix)[i] = (char*)malloc(sizeof(char) * NumTile);	//initializing all of the matrix rows
	}

	game->worldRef = worldRef;
	return game;	
}

/*freeing the game*/
void free_gamestate(GameState *game)
{
	free_world(game->worldRef);	//freeing the world of the game
	free(game);	//freeing the game itself
}


/*getting an empty GameState and copies the data from src to it*/
void copy_game(GameState *dest, GameState *src)
{
	dest->isMaxPlayer = src->isMaxPlayer;
	dest->win = src->win;
	dest->pause = src->pause;
	copy_world(dest->worldRef, src->worldRef);
}


/*Returns the row of the position of the current player*/
int getRow(GameState *game)
{
	int pos = row((game->worldRef)->mouse);
	if(!(game->isMaxPlayer))	//if the current isn't the mouse
	{
		pos = row((game->worldRef)->cat);
	}
	return pos;
}

/*Returns the column of the position of the current player*/
int getColumn(GameState *game)
{
	int pos = column((game->worldRef)->mouse);
	if(!(game->isMaxPlayer))	//if the current isn't the mouse
	{
		pos = column((game->worldRef)->cat);
	}
	return pos;

}



/*Returns a list of the possible GameStates one step from now*/
ListRef getChildren(GameState *game)
{
	ListRef children = newList(NULL);

	//The game after we moved up
	if(getRow(game) > 0)	//if we are not out of bounds
	{
		if(((game->worldRef)->matrix)[getRow(game) - 1][getColumn(game)] == '#')	//if there is no obstacle
		{
			GameState *gameup = init();	//initialize the new game

			copy_game(gameup, game);	//making the game look like the current one

			append(children, gameup);	//adding it to the children list
		}
	}

	//The game after we moved right
	if(getColumn(game) < 6)	//if we are not out of bounds
	{
		if(((game->worldRef)->matrix)[getRow(game)][getColumn(game) + 1] == '#')	//if there is no obstacle
		{
			GameState *gameright = init();	
			
			copy_game(gameright, game);

			append(children, gameright);
		}

	}

	//The game after we moved down
	if(getRow(game) < 6)	//if we are not out of bounds
	{
		if(((game->worldRef)->matrix)[getRow(game) + 1][getColumn(game)] == '#')	//if there is no obstacle
		{
			GameState *gamedown = init();	
			
			copy_game(gamedown, game);

			append(children, gamedown);
		}
	}

	//The game after we moved left
	if(getColumn(game) > 0)	//if we are not out of bounds
	{
		if(((game->worldRef)->matrix)[getRow(game)][getColumn(game) - 1] == '#')	//if there is no obstacle
		{
			GameState *gameleft = init();	
			
			copy_game(gameleft, game);

			append(children, gameleft);
		}

	}
	return children;
}



/*moves the current player 1 tile up*/
void up(GameState *game)
{
	replace(&((game->worldRef)->matrix), getRow(game), getColumn(game), getRow(game) - 1, getColumn(game));
}

/*moves the current player 1 tile to the right*/
void right(GameState *game)
{
	replace(&((game->worldRef)->matrix), getRow(game), getColumn(game), getRow(game) , getColumn(game) + 1);
}

/*moves the current player 1 tile down*/
void down(GameState *game)
{
	replace(&((game->worldRef)->matrix), getRow(game), getColumn(game), getRow(game) + 1 , getColumn(game));
}

/*moves the current player 1 tile to the left*/
void left(GameState *game)
{
	replace(&((game->worldRef)->matrix), getRow(game), getColumn(game), getRow(game) , getColumn(game) - 1);
}


/*Advancing the game 1 turn forward*/
void advance(GameState *game, int step)
{
	int i = 0;
	int j = 0;
	
	//moving accordingly
	if(step == 0)
	{
		up(game);
		i--;
	}
	else if(step == 1)
	{
		right(game);
		j++;
	}
	else if(step == 2)
	{
		down(game);
		i++;
	}
	else if(step == 3)
	{
		left(game);
		j--;
	}

	game->isMaxPlayer = 1 - game->isMaxPlayer;	//the next player's turn

	((game->worldRef)->turns)--;	//1 less turn left
	
	game->win = checkStatus(game);	//if the game ended
	

	if(game->isMaxPlayer)
	{
		(game->worldRef)->mouse = editRow((game->worldRef)->mouse, getRow(game) + i);
		(game->worldRef)->mouse = editColumn((game->worldRef)->mouse, getColumn(game) + j);
	}
	else
	{
		(game->worldRef)->cat = editRow((game->worldRef)->cat, getRow(game) + i);
		(game->worldRef)->cat = editColumn((game->worldRef)->cat, getColumn(game) + j);
	}
}


/*Checking the status of the game, return 0 if nothing changed, 1 if we ran out of turns,
  2 if mouse won, 3 if cat won*/
int checkStatus(GameState *game)
{
	if(adjacent((game->worldRef)->cat, (game->worldRef)->mouse))	//If the cat and the mouse are adjacent the cat wins
	{
		return 3;
	}
	else if(adjacent((game->worldRef)->cheese, (game->worldRef)->mouse))	//If the mouse is adjacent to the cheese and not 
	{									//to the cat then the mouse wins
		return 2;
	}
	else if((game->worldRef)->turns < 1)	//If no one won so far and there are no more turns left, then there is a tie
	{
		return 1;
	}
	else					//Else, the game isn't finished yet
	{
		return 0;
	}
}



/*Returns the number of the action that was estimated to be the best from all of the available actions*/
int findChild(GameState *game, int num)
{
	int counter = 0;
	
	//The game after we moved up
	if(getRow(game) > 0)	//if we are not out of bounds
	{
		if(((game->worldRef)->matrix)[getRow(game) - 1][getColumn(game)] == '#')	//if there is no obstacle
		{
			if(counter == num)	//if this is the child we got back from
			{
				return 0;
			}
			counter++;
		}
	}
	if(getColumn(game) < 6)	//if we are not out of bounds
	{
		if(((game->worldRef)->matrix)[getRow(game)][getColumn(game) + 1] == '#')	//if there is no obstacle
		{
			if(counter == num)	//if this is the child we got back from
			{
				return 1;
			}
			counter++;
		}
	}
	if(getRow(game) < 6)	//if we are not out of bounds
	{
		if(((game->worldRef)->matrix)[getRow(game)][getColumn(game) + 1] == '#')	//if there is no obstacle
		{
			if(counter == num)	//if this is the child we got back from
			{
				return 2;
			}
			counter++;
		}
	}
	if(getColumn(game) >0)	//if we are not out of bounds
	{
		if(((game->worldRef)->matrix)[getRow(game)][getColumn(game) + 1] == '#')	//if there is no obstacle
		{
			if(counter == num)	//if this is the child we got back from
			{
				return 3;
			}
			counter++;
		}
	}
}


/*gives a numerical evaluation of the current game to the current player*/
int evaluate(GameState *game)
{
	if(isMaxPlayer)
	{
		if(checkStatus(game) == 2)
		{
			return GAMEWIN;
		}
		else if(checkStatus(game) == 3)
		{
			return GAMELOSE;
		}
		else if(checkStatus(game) == 1)
		{
			return GAMELOSE / 2;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if(checkStatus(game) == 2)
		{
			return GAMELOSE;
		}
		else if(checkStatus(game) == 3)
		{
			return GAMEWIN;
		}
		else if(checkStatus(game) == 1)
		{
			return GAMELOSE / 2;
		}
		else
		{
			return 0;
		}
	}
}



