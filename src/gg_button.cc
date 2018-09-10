#include "gg.hh"
#include "gg_window.hh"
#include "gg_button.hh"


namespace gg
{
Button::Button(const char* l)
: Widget  (),
  m_onDown(nullptr),
  m_onUp  (nullptr),
  m_down  (false),
  m_label (l)
{
}


/* -------------------------------------------------------------------------- */


void Button::draw(SDL_Renderer* ren)
{
	m_down ? drawDown(ren) : drawUp(ren);
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
				redraw();
			}
		}
		else
		if (e.type == SDL_MOUSEBUTTONUP && m_down)
		{
			m_down = false;
			if(m_onUp != nullptr) m_onUp();
			redraw();
		}
	}
}


/* -------------------------------------------------------------------------- */


void Button::onDown(std::function<void()> f) { m_onDown = f; }
void Button::onUp(std::function<void()> f)   { m_onUp   = f; }


/* -------------------------------------------------------------------------- */


void Button::drawUp(SDL_Renderer* ren)
{
	m_rect.x = m_x;
	m_rect.y = m_y;
	m_rect.w = m_w;
	m_rect.h = m_h;

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderFillRect(ren, &m_rect);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderDrawRect(ren, &m_rect);

	if (m_label != nullptr)
		gg::drawFont(ren, m_rect, m_label);
}


/* -------------------------------------------------------------------------- */


void Button::drawDown(SDL_Renderer* ren)
{
	SDL_SetRenderDrawColor(ren, 155, 155, 155, 255);
	SDL_RenderFillRect(ren, &m_rect);
}

} // gg::