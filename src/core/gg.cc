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

std::vector<Window*> windows_;

/* cleanup()
Cleans up the Window vector and quits the SDL app. */

void cleanup_()
{
	SDL_StopTextInput();
	SDL_Quit();
}
} // {anonymous}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */


Rect::Rect() : Rect(0, 0, 0, 0)
{
}


/* -------------------------------------------------------------------------- */


Rect::Rect(int x, int y, int w, int h)
: x(x), y(y), w(w), h(h), xw(x + w), yh(y + h)
{
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */


int init()
{
	running_ = false;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("[init] unable to initialize: %s\n", SDL_GetError());
		return 0;
	}

	/* Start accepting Unicode text input events. */
	SDL_StartTextInput();

	running_ = true;
	return 1;
}


/* -------------------------------------------------------------------------- */


void run()
{
	SDL_Event ev;
	while (running_)
	{
		SDL_WaitEvent(&ev);
		if (ev.type == SDL_QUIT)
		{
			puts("[run] SDL_QUIT event, stop event loop");
			running_ = false;
		}
		else
		{
			for (Window* w : windows_)
				w->handle(ev);
		}
	}
	cleanup_();
}


/* -------------------------------------------------------------------------- */


void addWindow(Window* w)
{
	w->show();
	windows_.push_back(w);
}


/* -------------------------------------------------------------------------- */


void quit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}


} // gg::