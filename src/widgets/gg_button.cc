#include "gg_button.hh"
#include "core/gg_events.hh"
#include "core/gg_renderer.hh"

namespace gg
{
Button::Button(std::string l)
: Element()
, onClick(nullptr)
, m_label(l)
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
	if (e.isOver(m_bounds) && onClick != nullptr)
		onClick();
}

/* -------------------------------------------------------------------------- */

void Button::drawUp(Renderer& ren)
{
	ren.setColor(gg::getStyle().buttonBackgroundColorUp);
	ren.fillRect(m_bounds);
	ren.setColor(gg::getStyle().buttonBoundaryColor);
	ren.drawRect(m_bounds);

	if (m_label != "")
		ren.drawText(m_label, m_bounds);
}

/* -------------------------------------------------------------------------- */

void Button::drawDown(Renderer& ren)
{
	ren.setColor(gg::getStyle().buttonBackgroundColorDown);
	ren.fillRect(m_bounds);
}
} // namespace gg