#include "SDL.h"
#include "SDL_video.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Widget.h"
#include "actions.h"
#include "shared.h"
#include "location.h"

/*label definitions*/
#define imageButtonRect(rect) (center(BUTTONIMAGEWIDTH, BUTTONIMAGEHEIGHT, rect))
#define labelRect(rect, width, height) (center(width, height, rect))
#define labelRect1(rect) (center(newGameTextWidth, newGameTextHeight, rect))
#define labelRect2(rect) (center(loadGameTextWidth, loadGameTextHeight, rect))
#define labelRect3(rect) (center(createGameTextWidth, createGameTextHeight, rect))
#define labelRect4(rect) (center(editGameTextWidth, editGameTextHeight, rect))
#define labelRect5(rect) (center(exitGameTextWidth, exitGameTextHeight, rect))
#define titleRect(width) (SDL_Rect){(width-titleWidth) / 2, 0, titleWidth, titleHeight}

void click(Widget *wid)
{

}

Uint32 loadPurple(Widget *widget)
{
  return SDL_MapRGB(widget->surface->format, 89, 33, 60);
}

Uint32 loadGrey(Widget *widget)
{
  return SDL_MapRGB(widget->surface->format, 110, 117, 135);
}

SDL_Surface* loadImage(char *filename)
{
  return SDL_LoadBMP(filename);
}

Widget* loadMenu1(Widget *game)
{
  Widget *menu1 = windowInit(game, loadGrey(game), 6);
  
  SDL_Surface *buttonSurface = loadImage("images/button.bmp");
  
  SDL_Surface *newGameSurface = loadImage("images/new_game.bmp");
  SDL_Surface *loadGameSurface = loadImage("images/load_game.bmp");
  SDL_Surface *createGameSurface = loadImage("images/create_game.bmp");
  SDL_Surface *editGameSurface = loadImage("images/edit_game.bmp");
  SDL_Surface *exitGameSurface = loadImage("images/exit.bmp");
  
  SDL_Surface *catmouse = loadImage("images/catmouse.bmp");
  
  Widget *title = imageInit(menu1, catmouse, titleRect(menu1->rect.w), 0, !addToFocus);
  
  SDL_Rect menu1Rect1 = menu(MARGINTOP, 0, menuMARGIN, buttonRectWidth, buttonRectHeight, game->rect);
  SDL_Rect menu1Rect2 = menu(MARGINTOP, 1, menuMARGIN, buttonRectWidth, buttonRectHeight, game->rect);
  SDL_Rect menu1Rect3 = menu(MARGINTOP, 2, menuMARGIN, buttonRectWidth, buttonRectHeight, game->rect);
  SDL_Rect menu1Rect4 = menu(MARGINTOP, 3, menuMARGIN, buttonRectWidth, buttonRectHeight, game->rect);
  SDL_Rect menu1Rect5 = menu(MARGINTOP, 4, menuMARGIN, buttonRectWidth, buttonRectHeight, game->rect);
  
	Widget *newGButton = buttonInit(menu1, click, menu1Rect1, menu1->colorKey, 1, addToFocus);
  Widget *loadGButton = buttonInit(menu1, click, menu1Rect2, menu1->colorKey, 1, addToFocus);
  Widget *createGButton = buttonInit(menu1, click, menu1Rect3, menu1->colorKey, 1, addToFocus);
  Widget *editGButton = buttonInit(menu1, click, menu1Rect4, menu1->colorKey, 1, addToFocus);
  Widget *exitGButton = buttonInit(menu1, click, menu1Rect5, menu1->colorKey, 1, addToFocus);

  Widget *newGame = imageInit(newGButton, buttonSurface, imageButtonRect(newGButton->rect), 1, !addToFocus);
  Widget *loadGame = imageInit(loadGButton, buttonSurface, imageButtonRect(loadGButton->rect), 1, !addToFocus);
  Widget *createGame = imageInit(createGButton, buttonSurface, imageButtonRect(createGButton->rect), 1, !addToFocus);
  Widget *editGame = imageInit(editGButton, buttonSurface, imageButtonRect(editGButton->rect), 1, !addToFocus);
  Widget *exitGame = imageInit(exitGButton, buttonSurface, imageButtonRect(exitGButton->rect), 1, !addToFocus);
  
  Widget *newGameText = imageInit(newGame, newGameSurface, labelRect1(newGame->rect), 0, !addToFocus);
  Widget *loadGameText = imageInit(loadGame, loadGameSurface, labelRect2(loadGame->rect), 0, !addToFocus);
  Widget *createGameText = imageInit(createGame, createGameSurface, labelRect3(createGame->rect), 0, !addToFocus);
  Widget *editGameText = imageInit(editGame, editGameSurface, labelRect4(editGame->rect), 0, !addToFocus);
  Widget *exitGameText = imageInit(exitGame, exitGameSurface, labelRect5(exitGame->rect), 0, !addToFocus);
  
  avoid(title);
  avoid(newGameText);
  avoid(loadGameText);
  avoid(createGameText);
  avoid(editGameText);
  avoid(exitGameText);
  
  return menu1;
}