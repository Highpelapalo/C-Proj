#include "SDL.h"
#include "SDL_video.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Widget.h"
#include "actions.h"

void linkFocus(Widget *dst, Widget *src)
{
  Widget *temp;
  
  if(dst->focus == NULL)  //if our focused list is empty
  {
    dst->focus = src;  //the current focused will be this one
    src->next = src;;  //the next focused will be this one
    onFocus(dst->focus);
  }
  
  temp = dst->focus;
  while(dst->focus != temp->next)  //if we still didn't finish the loop (focused list is a loop)
  {
    temp = temp->next;  //we go forward
  }
  temp->next = src;  //we change it so the "last" widget is 'src'
  src->next = dst->focus;  //we create a loop again 
  
}

void changeFocus(Widget *widget)
{
  if(widget->focus != NULL)  //if we have something to focus on
  {
    noFocus(widget->focus);
    widget->focus = widget->focus->next;
    onFocus(widget->focus);
  }
}

void clearFocus(Widget *widget)
{
	Widget *temp = widget->focus;	//save the focused
	widget->focus = NULL;	//delete the focused
	Widget *pre;
	while(temp != NULL)	//while we haven't cleared the loop
	{
		pre = temp;	//we save the current widget
		temp = temp->next;	//go to the next widget
		pre->next = NULL;	//remove the widget from the loop
	}
}