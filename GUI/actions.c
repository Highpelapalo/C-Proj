#include "SDL.h"
#include "SDL_video.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Widget.h"
#include "actions.h"
#include "shared.h"
#include "load.h"

void buttonFocus(Widget *widget)
{
	widget->colorKey = loadPurple(widget);
}

void buttonNoFocus(Widget *widget)
{
  widget->colorKey = loadGrey(widget);
}

void onFocus(Widget *widget)
{
  switch(widget->type)
  {
    case Button:
      buttonFocus(widget);
      break;
    default:
      break;
  }
}

void noFocus(Widget *widget)
{
  switch(widget->type)
  {
    case Button:
      buttonNoFocus(widget);
      break;
    default:
      break;
  }
}

void avoid(Widget *widget)
{
  return;
}