#include <cstdio>
#include <cstdlib>
#include "gg_window.hh"


ggWindow::ggWindow(const char *t, int x, int y, int w, int h)
	: ggBaseGroup(),
		_x(x),
		_y(y),
		_w(w),
		_h(h),
		win(nullptr),
		ren(nullptr),
		damaged(false),
		preW(w),
		preH(h)
{
	win = SDL_CreateWindow(t, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!win)
		printf("[ggWindow] unable to create window: %s\n", SDL_GetError());

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	id  = SDL_GetWindowID(win);
}


/* ------------------------------------------------------------------ */


ggWindow::~ggWindow()
{
	SDL_DestroyWindow(win);
	puts("[~ggWindow] destroyed");
}


/* ------------------------------------------------------------------ */


void ggWindow::resize(int w, int h)
{
	preW = _w; _w = w;
	preH = _h; _h = h;
}


/* ------------------------------------------------------------------ */


void ggWindow::show()
{
	clear();        // clear everything, aka set background color
	render();       // draw all widgets to screen
}


/* ------------------------------------------------------------------ */


int ggWindow::add(ggWidget *w)
{
	if (ggBaseGroup::add(w)) {
		w->addWindow(this);
		return 1;
	}
	return 0;
}


/* ------------------------------------------------------------------ */


void ggWindow::clear()
{
	SDL_SetRenderDrawColor(ren, 30, 30, 30, 255);   // set color
	SDL_RenderClear(ren);                           // clear in memory
}


/* ------------------------------------------------------------------ */


void ggWindow::render()
{
	if (damaged)
	{
		SDL_RenderPresent(ren);   // update render on screen
		damaged = false;
	}
}


/* ------------------------------------------------------------------ */


void ggWindow::drawChildren()
{
	int dw = _w - preW;
	int dh = _h - preH;
	ggBaseGroup::drawChildren(dw, dh);
}


/* ------------------------------------------------------------------ */


void ggWindow::handle(SDL_Event &e)
{
	/* first handle window events such as shown, a resize, a popup and
	 * so on. */

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

	/* then handle events for each child widget. */

	for (unsigned i=0; i<stack.size(); i++)
		stack[i]->handle(e);
	if (damaged)
	{
		//puts("[ggWindow::handle] damaged, redrawing required");
		render();
	}
}
