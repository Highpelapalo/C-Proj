#ifndef ACTIONS_H_
#define ACTIONS_H_

/*Changes the button color when focused*/
void buttonFocus(Widget *);

/*Changes the to the widget's focused form*/
void onFocus(Widget *);

/*changes a focused item to an un-focused one*/
void noFocus(Widget *);

/*change the button color to the background's*/
void buttonNoFocus(Widget *);

/*helps avoid some stuff*/
void avoid(Widget *);

#endif /* ACTIONS_H_ */