#include <stdio.h>
#include <stdlib.h>
#include "MiniMax.h"
#include "ListUtils.h"

#define GAMEWIN  (1000001)
#define GAMELOSE  (-1000001)

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))


/**
 * Returns the best child of the given state, resulting from the MiniMax computation up to maxDepth, given by its value and index.
 * The getChildren function will be used to get each state's children.
 * The freeState function will be used to deallocate any lists returned by GetChildren.
 * The evaluate function will be used to evaluate the state score.
 * The player who's turn it is to play at the given state is assumed to be the MAX player if and only if isMaxPlayer is non-zero,
 * otherwise, it is assumed to be the MIN player.
 *
 * Will NOT crash in case one of the given functions fails but result will be undefined.
 */
struct MiniMaxResult getBestChildB(  
		void* state,
		unsigned int maxDepth,
		ListRef (*getChildren) (void* state),
		FreeFunc freeState,
		int (*evaluate) (void* state),
		int isMaxPlayer,
		int alpha,
		int beta)
{
	struct MiniMaxResult result; /*We define the MiniMAxResult struct that the function will return*/
	if(maxDepth == 0 || evaluate(state) == GAMEWIN || evaluate(state) == GAMELOSE || (state->worldRef)->turns == 0)	/*If the maxDepth is 0 then we want to only look at the evaluation of the current state*/
	{
		result.value = evaluate(state);	/*we evaluate the current state*/
		result.index = 0;			/*We return a dummy index because the evaluation was not based on children*/
		return result;
	}
	
		
	ListRef children = getChildren(state);	/*If maxDepth > 0 then we want to evaluate based on the children*/
	
	ListRef temp = children;			/*temp will be the list we will iterate over so we can look at the data of the children list*/
	
	int extremum = GAMELOSE - 1;					/*This point will be the maximum if isMaxPlayer != 0 and the minimum if isMaxPlayer = 1*/
	int iextremum = 0;					/*The index of the extremum point*/
	int i = 0;							/*The index of the current child we are looking at*/
	int local;							/*The evaluation of the current child*/
	
	
	int play = 0;            				/*The type of player the children of this state will be (Min if the current is Max and Max otherwise)*/
	if(isMaxPlayer == 0)
	{
		play = 1;
		extremum = GAMEWIN + 1;				/*if the player is min player we want to minimize so we give it "infinity"*/
	}
	
	if(isEmpty(temp) == 1)					/*In the case the current state has no children left we want to return the evaluation of the state by*/
	{										/*the evaluation function we received*/
		extremum = evaluate(state);
		iextremum = 0;
	}

	while(isEmpty(temp) == 0 && i < 4) 				/*while the there is still a child to iterate over*/
	{ 	
		local = getBestChildB(headData(temp) ,maxDepth - 1, getChildren, freeState, evaluate, play, alpha, beta).value;	/*this is the value of the best result of the child*/
		
		/*
		if(i == 0)			if the player is min player we want to minimize so we give it "infinity"
		{
			extremum = local;
		}
		*/
		//else				/*When everything is defined*/
		//{
			if(isMaxPlayer != 0)		/*If we are the MaxPlayer*/
			{
				if(local > extremum)	/*we want to find the maximum*/
				{
					iextremum = i;
					extremum = local;
				}
				
				alpha = max(alpha,local);
				
				if(beta <= alpha)
				{
					break;				/*beta cut off*/
				}
				
			}
			else						/*If we are the MinPlayer*/
			{
				if(local < extremum)	/*we want to find the minimum*/
				{
					iextremum = i;
					extremum = local;
				}
				
				beta = min(beta,local);
				
				if(beta <= alpha)
				{
					break;				/*alpha cut off*/
				}
			}
		//}
		
		temp = tail(temp);			/*we go to the next child*/
		i++;
	}
	
	destroyList(children, freeState);	/*we destroy the list of children because we will never use it again*/
	result.value = extremum;			/*the value of the best result*/
	result.index = iextremum;			/*the index of the child that give the value of the best result*/
	return result;

}

struct MiniMaxResult getBestChild(  
		void* state,
		unsigned int maxDepth,
		ListRef (*getChildren) (void* state),
		FreeFunc freeState,
		int (*evaluate) (void* state),
		int isMaxPlayer)
{
	if(isMaxPlayer)
	{
		return getBestChildB(state, maxDepth, getChildren, freeState, evaluate, isMaxPlayer, GAMEWIN, GAMELOSE);
	}
	else
	{
		return getBestChildB(state, maxDepth, getChildren, freeState, evaluate, isMaxPlayer, GAMELOSE, GAMEWIN);
	}
}



