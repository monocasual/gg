#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gg_window.hh"
#include "gg_element.hh"
#include "gg.hh"


namespace gg 
{
namespace
{
/* run
Whether the app is running or not. */

bool running_ = false;

/* windows
Array of pointers to windows. */

std::vector<Element*> elements_;

/* cleanup()
Cleans up the Window vector and quits the SDL app. */

void cleanup_()
{
	for (Element* e : elements_)
		delete e;
	elements_.clear();
	SDL_Quit();
	TTF_Quit();
}
} // {anonymous}


/* -------------------------------------------------------------------------- */


int init()
{
	running_ = false;

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
	running_ = true;
	return 1;
}


/* -------------------------------------------------------------------------- */


int run()
{
	SDL_Event ev;
	while (running_)
	{
		SDL_WaitEvent(&ev);
		if (ev.type == SDL_QUIT)
		{
			puts("[gg::run] SDL_QUIT event, stop event loop");
			running_ = false;
		}
		else
		{
			for (Element* el : elements_)
				el->handle(ev);
		}
	}
	cleanup_();
	return 1;
}


/* -------------------------------------------------------------------------- */


void add(Element* e)
{
	elements_.push_back(e);
}


/* -------------------------------------------------------------------------- */


void quit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}


} // gg::