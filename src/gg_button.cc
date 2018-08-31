#include "gg.hh"
#include "gg_window.hh"
#include "gg_button.hh"


namespace gg
{
Button::Button(int x, int y, int w, int h, const char* l)
	: Widget(x, y, w, h, l)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = w;
	m_rect.h = h;
}


/* -------------------------------------------------------------------------- */


void Button::resize(int w, int h)
{
	Widget::resize(w, h);
	m_rect.w = w;
	m_rect.h = h;
}



/* -------------------------------------------------------------------------- */


void Button::draw()
{
	SDL_SetRenderDrawColor(m_window->ren, 0, 0, 0, 255);
	SDL_RenderFillRect(m_window->ren, &m_rect);
	SDL_SetRenderDrawColor(m_window->ren, 255, 255, 255, 255);
	SDL_RenderDrawRect(m_window->ren, &m_rect);

	if (m_label)
		gg::drawFont(m_window->ren, m_rect, m_label);

	m_window->damaged = true;
}


/* -------------------------------------------------------------------------- */


void Button::handle(const SDL_Event& e)
{
	if (e.type & (SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP))
	{
		int mx, my;
		SDL_GetMouseState(&mx, &my);

		if (mx < getXW() && mx > getX() && my < getYH() && my > getY())
		{
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				//doCallback();
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


/* -------------------------------------------------------------------------- */


void Button::drawDown()
{
	SDL_SetRenderDrawColor(m_window->ren, 255, 255, 255, 255);
	SDL_RenderFillRect(m_window->ren, &m_rect);
	m_window->damaged = true;
}

} // gg::