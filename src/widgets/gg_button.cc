#include "../core/gg_renderer.hh"
#include "../core/gg_events.hh"
#include "gg_button.hh"


namespace gg
{
Button::Button(std::string l)
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
	ren.setColor(Color{ 0, 0, 0 });
	ren.fillRect(m_x, m_y, m_w, m_h);
	ren.setColor(Color{ 255, 255, 255 });
	ren.drawRect(m_x, m_y, m_w, m_h);

	if (m_label != "")
		ren.drawText(m_label, m_x, m_y, m_w, m_h);
}


/* -------------------------------------------------------------------------- */


void Button::drawDown(Renderer& ren)
{
	ren.setColor(Color{ 55, 155, 155 });
	ren.fillRect(m_x, m_y, m_w, m_h);
}

} // gg::