#include <cstdio>
#include <cstdlib>
#include "gg_widget.hh"
#include "gg_window.hh"


namespace gg 
{
Window::Window(const char* t, int x, int y, int w, int h)
	: Element(),
		m_x    (x),
		m_y    (y),
		m_w    (w),
		m_h    (h),
		m_win  (nullptr)
{
	m_win = SDL_CreateWindow(t, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!m_win)
		printf("[Window] unable to create window: %s\n", SDL_GetError());

	ren = SDL_CreateRenderer(m_win, -1, SDL_RENDERER_ACCELERATED);
	id  = SDL_GetWindowID(m_win);
}


/* -------------------------------------------------------------------------- */


Window::~Window()
{
	SDL_DestroyWindow(m_win);
	puts("[~Window] destroyed");
}


/* -------------------------------------------------------------------------- */


int Window::getX() const { return m_x; }
int Window::getY() const { return m_y; }
int Window::getW() const { return m_w; }
int Window::getH() const { return m_h; }


/* -------------------------------------------------------------------------- */


void Window::clear()
{
	SDL_SetRenderDrawColor(ren, 30, 30, 30, 255);   // set color
	SDL_RenderClear(ren);                           // clear in memory
}


/* -------------------------------------------------------------------------- */


void Window::render()
{
	SDL_RenderPresent(ren);   // update render on screen
}


/* -------------------------------------------------------------------------- */


void Window::handle(const SDL_Event& e)
{
	if (e.type == SDL_WINDOWEVENT)
	{
		if (e.window.event == SDL_WINDOWEVENT_SHOWN || e.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			if (e.window.windowID == id)
			{
				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					m_w = e.window.data1;
					m_h = e.window.data2;
				}
				resized();  // Must be called on SDL_WINDOWEVENT_SHOWN as well
				clear();
				drawChildren();
			}
		}
	}

	/* Handle events for each child widget. */

	for (Widget* w : m_widgets)
		w->handle(e);
	
	/* Then render everything on screen. */

	render();
}
} // gg::