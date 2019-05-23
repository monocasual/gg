#include "../core/gg_renderer.hh"
#include "../core/gg_events.hh"
#include "gg_button.hh"


namespace gg
{
Button::Button(const char* l)
: Element(),
  onClick(nullptr),
  m_label(l)
{
}


/* -------------------------------------------------------------------------- */


void Button::draw(Renderer& ren)
{
	m_mouseDown ? drawDown(ren) : drawUp(ren);
}


/* -------------------------------------------------------------------------- */


void Button::mouseUp(const MouseEvent& e)
{
	if (e.isOver(*this) && onClick != nullptr) onClick();
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