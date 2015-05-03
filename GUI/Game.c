#include "SDL.h"
#include "SDL_video.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Widget.h"
#include "UITree.h"
#include "location.h"
#include "actions.h"
#include "shared.h"
#include "focus.h"
#include "load.h"

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)	//initiate the video
  {
    fprintf(stderr, "ERROR: unable to init SDL: %s\n", SDL_GetError());
		exit(1);
  }
  SDL_WM_SetCaption("Cat&Mouse", "Cat&Mouse");	//set the title 
  atexit(SDL_Quit);		//define what happens upon quiting
  
  SDL_Event e;

  Widget *game = gameInit(SCREENWIDTH, SCREENHEIGHT, 0);
  Widget *menu1 = loadMenu1(game);
  	
	drawUI(game);
	SDL_Flip(game->surface);
  
	while(1)
	{
		while(SDL_PollEvent(&e))
			{
				switch(e.type)
				{
					case SDL_QUIT:
						exit(0);
						break;
          				case SDL_KEYDOWN:
            					switch(e.key.keysym.sym)
            					{
              						case SDLK_TAB:
								changeFocus(menu1);
								drawUI(game);
								break;
							default:
								break;
						}
						break;
					default:
						break;
				}
			}
      			SDL_Flip(game->surface);
	}
 	free_UI(game);
	return 0;
}