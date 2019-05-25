#include "../core/gg_renderer.hh"
#include "gg_box.hh"


namespace gg
{
Box::Box(std::string t) : m_text(t)
{
}


/* -------------------------------------------------------------------------- */


void Box::draw(Renderer& ren)
{
    ren.setColor(Color{ 30, 30, 30 });
    ren.fillRect(m_bounds);
    
	ren.setColor(Color{ 255, 255, 255 });
	ren.drawRect(m_bounds);

	if (m_text != "")
		ren.drawText(m_text.c_str(), m_bounds);
}


/* -------------------------------------------------------------------------- */


void Box::setText(std::string t)
{
    m_text = t;
}
} // gg::