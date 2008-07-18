/*
 * This file tests the entity manager
 */

#include <iostream>
using namespace std;


#include <SDL/SDL.h>
#include <stdlib.h>
#include "text.h"
#include "entityset.h"

inline double now()
{
//    struct timeval tv;
//    gettimeofday(&tv, NULL);
//	  return tv.tv_sec + tv.tv_usec/1000000.0;
	return SDL_GetTicks()/1000.0;
}


int main()
{
	if ( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Unable to initialize sdl: " << SDL_GetError() << "\n";
		return 1;
	}
	atexit(SDL_Quit);
	SDL_Surface * screen;
	if (!(screen = SDL_SetVideoMode(512,512,32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE)))
	{
		cout << "Unable to get a hardware surface, falling back on software\n";
		screen = SDL_SetVideoMode(512,512,32, SDL_SWSURFACE|SDL_RESIZABLE);
	}
	if (!screen) 
	{
		cout << "Unable to set display: " << SDL_GetError() << "\n";
		return 2;
	}

	entityset entities;
	entities.add(string("h1"));
	entities.add(string("h2"));
	char estr[] = "A";	
	bool run=true;
	double ti = now();
	while(run)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: 
				run = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					run = false;
				else if (event.key.keysym.sym == SDLK_SPACE)
					entities.add(string(estr));
					estr[0]++;
				break;
			}
		}
		double dt = now() - ti;
		ti = now();
		entities.process(dt);
		SDL_FillRect(screen, NULL, 0);
		entities.draw(screen);
		SDL_Flip(screen);

	}

	return 0;
}
