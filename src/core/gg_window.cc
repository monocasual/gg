#include <cstdio>
#include <cstdlib>
#include "gg_window.hh"


namespace gg 
{
Window::Window(const char* t, int x, int y, int w, int h)
: Element(x, y, w, h),
  m_win  (SDL_CreateWindow(t, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)),
  m_ren  (*m_win)
{
	//if (!m_win)
	// TODO throw exception
	//	printf("[Window] unable to create window: %s\n", SDL_GetError());

	id = SDL_GetWindowID(m_win);
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
	m_ren.setColor(30, 30, 30, 255);
	m_ren.clear();
}


void Window::render()
{
	m_ren.render();
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
				render();
			}
		}
	}
	else
	{
		/* Handle remaining events for each child widget. They don't need Window 
		events. */

		for (Element* el : m_elements)
			el->handle(e);
	}
}
} // gg::