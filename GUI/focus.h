#ifndef FOCUS_H_
#define FOCUS_H_

/*links the second widget to be focused on the first widget*/
void linkFocus(Widget *, Widget *);	

/*send the focused signal*/
void changeFocus(Widget *);

/*clears the focuses of this widget*/
void clearFocus(Widget *);

#endif /* FOCUS_H_ */