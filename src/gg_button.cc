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
	m_rect.w = m_w;
	m_rect.h = m_h;
}



/* -------------------------------------------------------------------------- */


void Button::draw()
{
	SDL_SetRenderDrawColor(m_parent->ren, 0, 0, 0, 255);
	SDL_RenderFillRect(m_parent->ren, &m_rect);
	SDL_SetRenderDrawColor(m_parent->ren, 255, 255, 255, 255);
	SDL_RenderDrawRect(m_parent->ren, &m_rect);

	if (m_label)
		gg::drawFont(m_parent->ren, m_rect, m_label);

	m_parent->damaged = true;
}


/* -------------------------------------------------------------------------- */


void Button::handle(const SDL_Event& e)
{
	if (e.type & (SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP))
	{
		int mx, my;
		SDL_GetMouseState(&mx, &my);

		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			if (mx < getXW() && mx > getX() && my < getYH() && my > getY())
			{
				m_down = true;
				if(m_onDown != nullptr) m_onDown();
				drawDown();
			}
		}
		else
		if (e.type == SDL_MOUSEBUTTONUP && m_down)
		{
			m_down = false;
			if(m_onUp != nullptr) m_onUp();
			draw();
		}
	}
}


/* -------------------------------------------------------------------------- */


void Button::onDown(std::function<void()> f) { m_onDown = f; }
void Button::onUp(std::function<void()> f)   { m_onUp   = f; }


/* -------------------------------------------------------------------------- */


void Button::drawDown()
{
	SDL_SetRenderDrawColor(m_parent->ren, 155, 155, 155, 255);
	SDL_RenderFillRect(m_parent->ren, &m_rect);
	m_parent->damaged = true;
}

} // gg::