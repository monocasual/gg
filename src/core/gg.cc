#include "gg.hh"
#include "deps/mcl-utils/src/log.hpp"
#include "deps/mcl-utils/src/vector.hpp"
#include "gg_const.hh"
#include "gg_element.hh"
#include "gg_style.hh"
#include "gg_window.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

using namespace mcl;

namespace gg
{
namespace
{
/* run
Whether the app is running or not. */

bool running_ = false;

/* windows
Array of pointers to windows. */

std::vector<std::unique_ptr<Window>> windows_;

std::unique_ptr<Style> style_;

/* -------------------------------------------------------------------------- */

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
		ML_DEBUG("Unable to initialize: " << SDL_GetError());
		return 0;
	}

	/* Start accepting Unicode text input events. */
	SDL_StartTextInput();

	style_   = std::make_unique<Style>();
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
			ML_DEBUG("SDL_QUIT event, stop event loop");
			running_ = false;
		}
		else
		{
			for (std::unique_ptr<Window>& w : windows_)
				w->handle(ev);
		}
	}
	cleanup_();
}

/* -------------------------------------------------------------------------- */

void addWindow(std::unique_ptr<Window> w)
{
	w->show();
	windows_.push_back(std::move(w));
}

/* -------------------------------------------------------------------------- */

void removeWindow(Window& w)
{
	w.hide();
	utils::vector::removeIf(windows_, [id = w.id](const std::unique_ptr<Window>& o) { return o->id == id; });
}

/* -------------------------------------------------------------------------- */

const Style& getStyle()
{
	return *style_;
}

void setStyle(std::unique_ptr<Style> s)
{
	style_ = std::move(s);
	for (std::unique_ptr<Window>& w : windows_)
	{
		w->clear();
		w->redraw();
	}
}

/* -------------------------------------------------------------------------- */

void quit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}
} // namespace gg