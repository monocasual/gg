#include <cstdio>
#include <cstdlib>
#include "gg_const.hh"
#include "gg_window.hh"


namespace gg 
{
Window::Window(const std::string& t, int x, int y, int w, int h)
: Element(geompp::Rect<int>(x, y, w, h)),
  m_win  (SDL_CreateWindow(t.c_str(), x, y, w, h, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE)),
  m_ren  (*m_win)
{
	if (m_win == nullptr)
		throw std::bad_alloc();

	id = SDL_GetWindowID(m_win);
}


/* -------------------------------------------------------------------------- */


Window::~Window()
{
	SDL_DestroyWindow(m_win);
	GG_DEBUG("Window destroyed");
}


/* -------------------------------------------------------------------------- */


void Window::clear()
{
	m_ren.setColor(Color{ 30, 30, 30 });
	m_ren.clear();
}


void Window::render()
{
	m_ren.render();
}


/* -------------------------------------------------------------------------- */


void Window::show()
{
	SDL_ShowWindow(m_win);
}


void Window::hide()
{
	SDL_HideWindow(m_win);
}


/* -------------------------------------------------------------------------- */


void Window::setResizable(bool v)
{
	SDL_SetWindowResizable(m_win, static_cast<SDL_bool>(v));
}


/* -------------------------------------------------------------------------- */


void Window::setModal(const Window* parent)
{
	SDL_SetWindowModalFor(m_win, parent->m_win);
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
					m_bounds.w = e.window.data1;
					m_bounds.h = e.window.data2;
				}
				resized();  // Must be called on SDL_WINDOWEVENT_SHOWN as well
				clear();
				drawChildren(m_ren);
				render();
			}
		}
		else
		if (e.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			if (e.window.windowID == id)
				closed();
		}
	}
	else
	{
		/* Handle remaining events as default. They don't need Window events. */
		Element::handle(e);
	}
}
} // gg::