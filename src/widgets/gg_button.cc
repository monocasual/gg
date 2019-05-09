#include "../core/gg.hh"
#include "../core/gg_window.hh"
#include "gg_button.hh"


namespace gg
{
Button::Button(const char* l)
: Element (),
  onDown  (nullptr),
  onUp    (nullptr),
  m_down  (false),
  m_label (l)
{
}


/* -------------------------------------------------------------------------- */


void Button::draw(Renderer& ren)
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
				if (onDown != nullptr) onDown();
				redraw();
			}
		}
		else
		if (e.type == SDL_MOUSEBUTTONUP && m_down)
		{
			m_down = false;
			if (onUp != nullptr) onUp();
			redraw();
		}
	}
}


/* -------------------------------------------------------------------------- */


void Button::drawUp(Renderer& ren)
{
	ren.setColor(0, 0, 0);
	ren.fillRect(m_x, m_y, m_w, m_h);
	ren.setColor(255, 255, 255);
	ren.drawRect(m_x, m_y, m_w, m_h);

	if (m_label != nullptr)
		ren.drawText(m_label, m_x, m_y, m_w, m_h);
}


/* -------------------------------------------------------------------------- */


void Button::drawDown(Renderer& ren)
{
	ren.setColor(55, 155, 155);
	ren.fillRect(m_x, m_y, m_w, m_h);
}

} // gg::