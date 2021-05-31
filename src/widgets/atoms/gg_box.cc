#include "gg_box.hh"
#include "core/gg_renderer.hh"

namespace gg
{
Box::Box(std::string t)
: m_text(t)
{
}

/* -------------------------------------------------------------------------- */

void Box::draw(Renderer& ren)
{
	ren.setColor(gg::getStyle().boxBackgroundColor());
	ren.fillRect(m_bounds);

	ren.setColor(gg::getStyle().boxBoundaryColor());
	ren.drawRect(m_bounds);

	if (m_text != "")
		ren.drawText(m_text.c_str(), m_bounds);
}

/* -------------------------------------------------------------------------- */

void Box::setText(std::string t)
{
	m_text = t;
}
} // namespace gg