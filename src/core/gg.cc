#include "gg.hh"
#include "gg_const.hh"
#include "gg_element.hh"
#include "gg_utils.hh"
#include "gg_window.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

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
} // namespace

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

int init()
{
	running_ = false;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		GG_DEBUG("Unable to initialize: " << SDL_GetError());
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
			GG_DEBUG("SDL_QUIT event, stop event loop");
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

void removeWindow(Window* w)
{
	w->hide();
	utils::eraseIf(windows_, [w](const Window* o) { return o->id == w->id; });
}

/* -------------------------------------------------------------------------- */

void quit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}
} // namespace gg