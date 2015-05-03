#include "SDL.h"
#include "SDL_video.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Widget.h"
#include "shared.h"
#include "focus.h"

int is_sdl_init;

Widget* widgetInit(int n)
{
	Widget *widget = (Widget *)malloc(sizeof(Widget));

	widget->clickable = 0;

	widget->pre = NULL;

	widget->rect = RECTZERO;
 
	widget->childrenNum = n;	
	widget->currChild = 0;
 
  widget->children = NULL;
  widget->focus = NULL;
  widget->next = NULL;

	return widget;
}

Widget* gameInit(int x, int y, int n)
{
	Widget *game = widgetInit(n);

	game->surface = SDL_SetVideoMode(x, y, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);	//init the surface

	game->rect = (SDL_Rect){0, 0, x, y};

	game->type = Game;

	return game;
}

Widget* windowInit(Widget *pre, Uint32 colorkey, int n)
{
	Widget *window = widgetInit(n);

	window->surface = pre->surface;

	window->rect = pre->rect;
 
  window->colorKey = colorkey;
  
  window->type = Window;
  
  if(pre->focus == NULL)
  {
    linkFocus(pre, window);  //Window is only connected to Game and Game doesn't have children, he has focused...
  }
  else
  {
    window->next = pre->focus;
    pre->focus = window;
  }

	return window;
}

Widget* buttonInit(Widget *pre, void (*onClick)(Widget *), SDL_Rect rect, Uint32 colorKey, int n, int focus) //buttons have no surface
{
	Widget *button = widgetInit(n);

	button->clickable = 1;

	button->pre = pre;

	button->onClick = onClick;

	button->surface = pre->surface;
	button->rect = rect;
	
	button->colorKey = colorKey;

	button->type = Button;
 
  linkChild(pre, button);  //add this widget to it's child list
  
  if(focus)
  {
    linkFocus(pre, button);
  }
  
	return button;
}

Widget* imageInit(Widget *pre, SDL_Surface *im, SDL_Rect rect, int n, int focus)
{
	Widget *image = widgetInit(n);

	image->pre = pre;

	image->surface = im;

	image->rect = rect;

	image->type = Image;
 
  linkChild(pre, image);  //add this widget to it's child list
  
  if(focus)
  {
    linkFocus(pre, image);
  }

	return image;
}

Widget* panelInit(Widget *pre, SDL_Rect rect, int n, int focus)
{
	Widget *panel = widgetInit(n);

	panel->pre = pre;

	panel->rect = rect;

	panel->type = Panel;
 
  linkChild(pre, panel);  //add this widget to it's child list
  
  if(focus)
  {
    linkFocus(pre, panel);
  }
  
	return panel;
}

void linkChild(Widget *pre, Widget* child)
{
  if(pre->currChild == 0)
  {
    if(pre->childrenNum > 0)
    {
		  pre->children = (Widget **)malloc(sizeof(Widget *) * pre->childrenNum);	//we are going to have n children
    }
  }
	if(pre->currChild < pre->childrenNum)  //if we still have room for children
	{
		pre->children[pre->currChild++] = child;  //wrtie to the current child location and advance the currChild number
	}
}

int draw(Widget *widget)
{
	switch(widget->type)
	{
		case Game:
			break;
		case Window:	//if the widget is a window
			if(SDL_FillRect(widget->surface, &widget->rect, widget->colorKey))
      {
        return DrawError;
      }
			break;

		case Button:	//if the widget is a button
			if(SDL_FillRect(widget->pre->surface, &widget->rect, widget->colorKey))
      {
        return DrawError;
      }
			break;

		case Image:
			if(SDL_BlitSurface(widget->surface, &(SDL_Rect){0, 0, widget->rect.w, widget->rect.h}, getSurface(widget), &(SDL_Rect){widget->rect.x, widget->rect.y, 0, 0}))
      {
        return DrawError;
      }							
			break;

		case Panel:
			
			break;
	}
	return !DrawError;
}

SDL_Surface* getSurface(Widget *widget)
{
  if(widget->type == Image)
  {
    return getSurface(widget->pre);
  }
  else
  {
    return widget->surface;
  }
}

/*Free the widget*/
void freeWidget(Widget *widget)
{
	//SDL_FreeSurface(widget->surface);	//Free the surface of the widget
	free(widget->children);				//Free the children array
  if(widget->surface != NULL)
  {
    SDL_FreeSurface(widget->surface);
  }
	free(widget);				//Free the widget itself
}
