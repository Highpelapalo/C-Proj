#ifndef LOAD_H_
#define LOAD_H_

/*Returns the colorKey of button border purple*/
Uint32 loadPurple(Widget *);

/*Returns the colorKey of background*/
Uint32 loadGrey(Widget *);

/*Returns a surface for the image in the specified location*/
SDL_Surface* loadImage(char *);

/*Load the first menu*/
Widget* loadMenu1(Widget *);

#endif /* LOAD_H_ */