#ifndef LOCATION_H_
#define LOCATION_H_



typedef struct
{
	int x;
	int y;
} Point;

/*Change the relative position of the widget*/
void changePos(Widget *, int, int);

/*Returns the real position of the widget in the screen*/
SDL_Rect getPos(Widget *);

/*Returns the relative position of the widget within its predecessor*/
SDL_Rect getRelPos(Widget *);

/*Return 1 if the point is within the boundry, 0 otherwise*/
int isBoundry(SDL_Rect, Point);

/*Returns if the point is within the boundry of the widget*/
int widgetBoundry(Widget *, Point);

/*Returns a rectangle with width and height as his parameters and pos as his center, if we can't we return NULL*/
SDL_Rect rectCenter(int, int, Point, SDL_Rect);

/*Returns the center point of the target rectangle*/
Point centerPoint(SDL_Rect);

/*Returns a rectangle with width and height as his parameters and at the center of target, if we can't we return NULL*/
SDL_Rect center(int, int, SDL_Rect);

/*Returns a rectangle with width and height as his parameters and at the center of the x axis, if we can't we return NULL
The y is relative to the target's location*/
SDL_Rect centerX(int, int, int, SDL_Rect);

/*Returns a rectangle with width and height as his parameters and at the center of the y axis, if we can't we return NULL
The x is relative to the target's location*/
SDL_Rect centerY(int, int, int, SDL_Rect);

/*From all of the numOf rectangles that the top of which is with marginTop from the top and each rectangle has a margin of
'margin' from all of the other rectangles we return the 'num'th one (all of which are horizontally centered and are of the same height)*/
SDL_Rect menu(int marginTop, int num, int margin, int width, int height, SDL_Rect rect);

#endif /* LOCATION_H_ */