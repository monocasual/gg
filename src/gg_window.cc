#include <cstdio>
#include <cstdlib>
#include "gg_widget.hh"
#include "gg_window.hh"


namespace gg 
{
Window::Window(const char* t, int x, int y, int w, int h)
	: BaseGroup(),
		m_x      (x),
		m_y      (y),
		m_w      (w),
		m_h      (h),
		m_win    (nullptr),
		m_preW   (w),
		m_preH   (h),
		ren      (nullptr),
		damaged  (false)
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
void Window::setX(int x) { m_x = x; }
void Window::setY(int y) { m_y = y; }


/* -------------------------------------------------------------------------- */


void Window::resize(int w, int h)
{
	m_preW = m_w; m_w = w;
	m_preH = m_h; m_h = h;
}


/* -------------------------------------------------------------------------- */


void Window::show()
{
	clear();        // clear everything, aka set background color
	render();       // draw all widgets to screen
}


/* -------------------------------------------------------------------------- */


int Window::add(Widget* w)
{
	if (BaseGroup::add(w)) {
		w->addWindow(this);
		return 1;
	}
	return 0;
}


/* -------------------------------------------------------------------------- */


void Window::clear()
{
	SDL_SetRenderDrawColor(ren, 30, 30, 30, 255);   // set color
	SDL_RenderClear(ren);                           // clear in memory
}


/* -------------------------------------------------------------------------- */


void Window::render()
{
	if (damaged)
	{
		SDL_RenderPresent(ren);   // update render on screen
		damaged = false;
	}
}


/* -------------------------------------------------------------------------- */


void Window::drawChildren()
{
	int dw = m_w - m_preW;
	int dh = m_h - m_preH;
	BaseGroup::drawChildren(dw, dh);
}


/* -------------------------------------------------------------------------- */


void Window::handle(const SDL_Event& e)
{
	/* Handle window events such as shown, a resize, a popup and so on. */

	if (e.type == SDL_WINDOWEVENT)
	{
		if (e.window.event == SDL_WINDOWEVENT_SHOWN || e.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			if (e.window.windowID == id)
			{
				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
					resize(e.window.data1, e.window.data2);
				clear();
				drawChildren();
				render();
			}
		}
	}

	/* Then handle events for each child widget. */

	for (Widget* w : m_stack)
		w->handle(e);
	
	if (damaged)
		render();
}
} // gg::