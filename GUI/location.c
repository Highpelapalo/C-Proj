#include "SDL.h"
#include "SDL_video.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Widget.h"
#include "location.h"
#include "shared.h"

/*Attention! The methods return the center and point relatively to the rectangles unless stated otherwise*/

/*Change the relative position of the widget*/
void changePos(Widget *widget, int x, int y)
{
	widget->rect.x = x;
	widget->rect.y = y;
}

/*Returns the real position of the widget in the screen*/
SDL_Rect getPos(Widget *widget)
{
	SDL_Rect rect;

	if(widget->pre == NULL)	//If the widget has no predecessor then we want to stop
	{
		rect.x = widget->rect.x;	
		rect.y = widget->rect.y;
		return rect;		//we return the position of the widget
	}
	else
	{
		rect = getPos(widget->pre);	//we check to see the real position of the predecessor
		rect.x += widget->rect.x;		//and we add to it the relative position of the widget
		rect.y += widget->rect.y;
		return rect;
	}
}

/*Returns the relative position of the widget within its predecessor*/
SDL_Rect getRelPos(Widget *widget)
{
	if(widget == NULL)
	{
		return RECTZERO;
	}
	return widget->rect;	
}

/*Return 1 if the point is within the boundry, 0 otherwise*/
int isBoundry(SDL_Rect rect, Point pos)
{
	if(pos.x >= rect.x && pos.y >= rect.y)
	{
		if(pos.x < rect.x + rect.w && pos.y < rect.y + rect.h)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

/*Returns if the point is within the boundry of the widget, both aren't measured relatively*/
int widgetBoundry(Widget *widget, Point pos)
{
	return isBoundry(getPos(widget), pos);
}

/*Returns a rectangle with width and height as his parameters and pos as his center, if we can't we return invalidRect*/
SDL_Rect rectCenter(int width, int height, Point pos, SDL_Rect target)
{
	SDL_Rect rect = {0, 0, width, height};
	
	rect.x = pos.x - width / 2;	//calculating the upper left x coordinate of the rectangle
	rect.y = pos.y - height /2;	//calculating the upper left y coordinate of the rectangle
	
	if(rect.x >= target.x && rect.y >= target.y)
	{
		if(rect.x < target.x + target.w && rect.y < target.y + target.h)
		{
			return rect;	//rect is in the screen
		}
		else
		{
			return invalidRect;		//rect goes out of screen boundries
		}
	}
	else
	{
		return invalidRect;		//rect goes out of screen boundries
	}
}

/*Returns the center point of the target rectangle*/
Point centerPoint(SDL_Rect target)
{
	Point pos;
	pos.x = target.x + target.w / 2;
	pos.y = target.y + target.h / 2;
	return pos;
}

/*Returns a rectangle with width and height as his parameters and at the center of target, if we can't we return invalidRect*/
SDL_Rect center(int width, int height, SDL_Rect target)
{
	return rectCenter(width, height, centerPoint(target), target);
}

/*Returns a rectangle with width and height as his parameters and at the center of the x axis, if we can't we return invalidRect
The y is relative to the target's location*/
SDL_Rect centerX(int width, int height, int y, SDL_Rect target)
{
	Point pos = centerPoint(target);
	if(y < target.h)	//If our desired y isn't out of bounds
	{
		pos.y = target.y + y;	//change to our desired y
		return rectCenter(width, height, pos, target);
	}
	else
	{
		return invalidRect;
	}
}

/*Returns a rectangle with width and height as his parameters and at the center of the y axis, if we can't we return invalidRect
The x is relative to the target's location*/
SDL_Rect centerY(int width, int height, int x, SDL_Rect target)
{
	Point pos = centerPoint(target);
	if(x < target.w)	//If our desired x isn't out of bounds
	{
		pos.x = target.x + x;	//change to our desired x
		return rectCenter(width, height, pos, target);
	}
	else
	{
		return invalidRect;
	}
}

SDL_Rect menu(int marginTop, int num, int margin, int width, int height, SDL_Rect rect)
{
  int y = marginTop;
  y += num * height;
  y += num * margin;
  
  return centerX(width, height, y, rect);
}