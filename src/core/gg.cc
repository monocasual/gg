#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gg_window.hh"
#include "gg.hh"


namespace gg 
{
namespace
{
/* run
Whether the app is running or not. */

bool running = false;

/* windows
Array of pointers to windows. */

std::vector<Window*> windows;

/* cleanup()
Cleans up the Window vector and quits the SDL app. */

void cleanup()
{
	for (Window* w : windows)
		delete w;
	windows.clear();
	SDL_Quit();
	TTF_Quit();
}
} // {anonymous}


/* -------------------------------------------------------------------------- */


int init()
{
	running = false;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("[gg::init] unable to initialize: %s\n", SDL_GetError());
		return 0;
	}
	if (TTF_Init() == -1)
	{
		printf("[gg::init] unable to initialize text rendering: %s\n", TTF_GetError());
		return 0;
	}
	running = true;
	return 1;
}


/* -------------------------------------------------------------------------- */


int run()
{
	SDL_Event e;
	while (running)
	{
		SDL_WaitEvent(&e);
		if (e.type == SDL_QUIT)
		{
			puts("[gg::run] SDL_QUIT event, stop event loop");
			running = false;
		}
		else
		{
			for (Window* w : windows)
				w->handle(e);
		}
	}
	cleanup();
	return 1;
}


/* -------------------------------------------------------------------------- */


void add(Window* w)
{
	windows.push_back(w);
	printf("[gg::add] add window %p, id=%d, windows size %zd\n",
		(void*)w, w->id, windows.size());
}


/* -------------------------------------------------------------------------- */


void quit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}


} // gg::