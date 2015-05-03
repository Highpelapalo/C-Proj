#ifndef SHARED_H_
#define SHARED_H_

#include "Widget.h"

/*Screen*/
#define SCREENWIDTH (800) //screen width
#define SCREENHEIGHT (800)  //screen height

/*Defined for Comfort*/
#define RECTZERO ((SDL_Rect){0, 0, 0, 0})  //a rectangle with all 0s
#define SDL_INIT (1)  //did we already initialize the SDL?
#define addToFocus (1)  //add to focus or not

/*First Screen buttons margin and border*/
#define BUTTONIMAGEWIDTH (275)  //Width dimension of button image
#define BUTTONIMAGEHEIGHT (64)  //Height dimension of button image
#define MARGINTOP (275)  //the margin of the first button from the top of the screen 
#define menuMARGIN (25)  //The margin between each button in the menu
#define buttonBorderHeight (10)  //The border above and below the button image
#define buttonBorderWidth (10)  //The border to the right and left of the button image
#define buttonRectWidth ((BUTTONIMAGEWIDTH) + (buttonBorderWidth))  //the total width of the button rectangle
#define buttonRectHeight ((BUTTONIMAGEHEIGHT) + (buttonBorderHeight))  //the total height of the button rectangle


/*Text sizes*/
#define titleWidth (350)  //The width of the title image
#define titleHeight (197)  //The height of the title image
#define newGameTextWidth (110)
#define newGameTextHeight (20)
#define loadGameTextWidth (116)
#define loadGameTextHeight (22)
#define createGameTextWidth (131)
#define createGameTextHeight (19)
#define editGameTextWidth (108)
#define editGameTextHeight (22)
#define exitGameTextWidth (42)
#define exitGameTextHeight (19)

/*Errors*/
#define DrawError (1)  //did we get an error while drawing
#define invalidRect ((SDL_Rect){-1, -1, -1, -1})  //if we got this rectangle we have an error

#endif /* SHARED_H_ */