#include "../core/gg_renderer.hh"
#include "gg_box.hh"


namespace gg
{
Box::Box(const char* l) : m_label(l)
{
}


/* -------------------------------------------------------------------------- */


void Box::draw(Renderer& ren)
{
	ren.setColor(255, 255, 255);
	ren.drawRect(m_x, m_y, m_w, m_h);

	if (m_label != nullptr)
		ren.drawText(m_label, m_x, m_y, m_w, m_h);
}
} // gg::