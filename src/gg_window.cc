#include <cstdio>
#include <cstdlib>
#include "gg_window.hh"


namespace gg 
{
Window::Window(const char* t, int x, int y, int w, int h)
	: Element(x, y, w, h),
		m_win  (nullptr)
{
	m_win = SDL_CreateWindow(t, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!m_win)
		printf("[Window] unable to create window: %s\n", SDL_GetError());

	m_ren = SDL_CreateRenderer(m_win, -1, SDL_RENDERER_ACCELERATED);
	id    = SDL_GetWindowID(m_win);
}


/* -------------------------------------------------------------------------- */


Window::~Window()
{
	SDL_DestroyWindow(m_win);
	puts("[~Window] destroyed");
}


/* -------------------------------------------------------------------------- */


void Window::clear()
{
	SDL_SetRenderDrawColor(m_ren, 30, 30, 30, 255);   // set color
	SDL_RenderClear(m_ren);                           // clear in memory
}


/* -------------------------------------------------------------------------- */


void Window::render()
{
	SDL_RenderPresent(m_ren);   // update render on screen
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
				clear();
				resized();  // Must be called on SDL_WINDOWEVENT_SHOWN as well
				drawChildren();
			}
		}
	}

	/* Handle events for each child widget. */

	for (Element* el : m_elements)
		el->handle(e);
	
	/* Then render everything on screen. */

	render();
}
} // gg::