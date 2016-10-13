#include "gg.hh"
#include "gg_button.hh"
#include "gg_window.hh"


ggButton::ggButton(int x, int y, int w, int h, const char *l)
	: ggWidget(x, y, w, h, l)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}


/* ------------------------------------------------------------------ */


void ggButton::resize(int w, int h)
{
	ggWidget::resize(w, h);
	rect.w = w;
	rect.h = h;
}



/* ------------------------------------------------------------------ */


void ggButton::draw()
{
	SDL_SetRenderDrawColor(window->ren, 0, 0, 0, 255);
	SDL_RenderFillRect(window->ren, &rect);
	SDL_SetRenderDrawColor(window->ren, 255, 255, 255, 255);
	SDL_RenderDrawRect(window->ren, &rect);

	if (label)
		gg_drawFont(window->ren, rect, label);

	window->damaged = true;
}


/* ------------------------------------------------------------------ */


void ggButton::handle(SDL_Event &e)
{
	if (e.type & (SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP))
	{
		int mx, my;
		SDL_GetMouseState(&mx, &my);

		if (mx < _xw && mx > _x && my < _yh && my > _y)
		{
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				doCallback();
				drawDown();
			}
			else
			if (e.type == SDL_MOUSEBUTTONUP)
				draw();
		}
		else // when clicking and dragging outside button
			if (e.type == SDL_MOUSEBUTTONUP)
				draw();
	}
}


/* ------------------------------------------------------------------ */


void ggButton::drawDown()
{
	SDL_SetRenderDrawColor(window->ren, 255, 255, 255, 255);
	SDL_RenderFillRect(window->ren, &rect);
	window->damaged = true;
}
