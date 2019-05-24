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
    ren.setColor(0, 0, 0);
    ren.fillRect(m_x, m_y, m_w, m_h);
    
	ren.setColor(255, 255, 255);
	ren.drawRect(m_x, m_y, m_w, m_h);

	if (m_text != "")
		ren.drawText(m_text.c_str(), m_x, m_y, m_w, m_h);
}


/* -------------------------------------------------------------------------- */


void Box::setText(std::string t)
{
    m_text = t;
    //redraw();
}
} // gg::