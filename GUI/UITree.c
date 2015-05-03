#include "SDL.h"
#include "SDL_video.h"

#include "shared.h"
#include "Widget.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int drawUI(Widget *UI)	//returns 1 if there was an issue drawing, 0 otherwise
{
	int i;
	
	if(draw(UI))	//issue with drawing the widget
	{
		return DrawError;
	}
	
  if(UI->type == Game)
  {
    if(UI->focus != NULL)
    {
      if(drawUI(UI->focus))
      {
        return DrawError;
      }
    }
  }
  else
  {
  	if(UI->childrenNum == 0)
  	{
  		return !DrawError;
  	}
  	else
  	{
  		for(i = 0; i < UI->childrenNum; i++) //going over all of the head's children writing in DFS order
  		{
  			if(drawUI(UI->children[i]))
  			{
  				return DrawError;
  			}
  		}
  	}
  }
	return !DrawError;
}

void free_UI(Widget *UITree)
{
  Widget *temp1;
  Widget *temp2 = UITree->focus;
  if(temp2 != NULL)
  {
    temp1 = UITree->focus->next; 
  }
  else
  {
    freeWidget(UITree);
    return;
  }
  
	int i;
	for(i = 0; i < UITree->childrenNum; i++)
	{
    if(UITree->type == Game)
    {
      free_UI(temp2);
      temp2 = temp1;
      temp1 = temp1->next;
    }
    else
    {
		  free_UI(UITree->children[i]);
    }
	}
	freeWidget(UITree);
}