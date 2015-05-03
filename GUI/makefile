
CFlags = -Wall -std=c99 -pedantic-errors `sdl-config --cflags` `sdl-config --libs`
CO= gcc -o $@ $^ $(CFlags)
CC= gcc -c $*.c $(CFlags)
OFILES= Widget.o Game.o location.o UITree.o focus.o actions.o load.o
HFILES= location.h Widget.h shared.h focus.h actions.h load.h
UIHFILES = $(HFILES) UITree.h

all:  Game

clean: 
	-rm Game $(OFILES)
	
Game: $(OFILES)
	$(CO)

Widget.o: Widget.c $(HFILES)
	$(CC)

Game.o: Game.c $(HFILES)
	$(CC)

location.o: location.c $(HFILES)
	$(CC)

UITree.o: UITree.c $(UIHFILES)
	$(CC)

focus.o: focus.c $(HFILES)
	$(CC)
 
actions.o: actions.c $(HFILES)
	$(CC)
 
load.o: load.c $(HFILES)
	$(CC)