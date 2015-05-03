#ifndef WIDGET_H_
#define WIDGET_H_

typedef enum
{
	Button,
	Window,
	Image,
	Panel,
	Game
} WidgetType;

typedef struct Widget
{
	struct Widget *pre;	//the predecessor 

	SDL_Rect rect;	//the rectangle which represents the size of the widget, x & y are relative to the predecessor
	SDL_Surface *surface;	//the surface of the widget
	Uint32 colorKey;	//The color key of the widget;

	int clickable;	// 1 if the widget is clickable, 0 otherwise
	void (*onClick)(struct Widget *);	//what happens when we click on the widget;

	struct Widget **children;
	int childrenNum;
	int currChild;
 
  struct Widget *focus;  //The widget which is focused on the current screen
  struct Widget *next;  //The next widget to be focused after this one
                        //IMPORTANT NOTE: THOSE TO ARE DIFFERENT: 1 is for the focused widget on this widget, 2 is if this widget is on a widget with focus option
	
	WidgetType type;	//the type of the widget
	
} Widget;

/*initialize a widget*/
Widget* widgetInit(int);

/*initialize the game*/
Widget* gameInit(int, int, int);

/*initialize a window with sizes x, y*/
Widget* windowInit(Widget *, Uint32, int);

/*initialize a button*/
Widget* buttonInit(Widget *, void (*onClick)(Widget *), SDL_Rect, Uint32, int, int);

/*initialize an image*/
Widget* imageInit(Widget *, SDL_Surface *, SDL_Rect, int, int);

/*initialize a panel*/
Widget* panelInit(Widget *, SDL_Rect, int, int);

/*Links the second widget as the first's child*/
void linkChild(Widget *, Widget *);

/*we draw the widget on it's father in it's relative position 'pos', we return 0 if successful, 1 otherwise*/
int draw(Widget *);

/*decide if to responde to an event or not, return 1 if to responde, 0 otherwise*/
int decideEvent(Widget *, SDL_Event e);

/*Returns the surface thw widget is drawn on(since the surface of the widget for images is the image not the surface to draw on)*/
SDL_Surface* getSurface(Widget *);

/*Free the widget*/
void freeWidget(Widget *);

#endif /* WIDGET_H_ */
