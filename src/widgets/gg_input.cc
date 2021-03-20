#include "core/gg_renderer.hh"
#include "core/gg_events.hh"
#include "gg_input.hh"


namespace gg
{
Input::Input() 
: Element()
, m_caret(0)
{
}


/* -------------------------------------------------------------------------- */


void Input::draw(Renderer& ren)
{
	ren.setColor(Color{ 0, 0, 0 });
	ren.fillRect(m_bounds);

	if (!m_text.empty())
	{
		ren.setColor(Color{ 255, 255, 255 });
		ren.drawText(m_text, m_bounds, Renderer::TextAlign::LEFT);
	}

	if (m_focus)
	{
		ren.setColor(Color{ 150, 150, 150 });
		ren.drawRect(m_bounds);

		int caret_x  = m_bounds.x + getCaretPx(ren);
		int caret_y1 = m_bounds.y;
		int caret_y2 = m_bounds.yh;
		ren.drawLine(caret_x, caret_y1, caret_x, caret_y2);
	}
}


/* -------------------------------------------------------------------------- */


void Input::keyPress(const KeyEvent& e)
{
	switch (e.type)
	{
	case KeyEvent::Type::TEXT:
		m_text += e.ch;
		m_caret = m_text.length();
		break;
	
	case KeyEvent::Type::BACKSPACE:
		if (!m_text.empty())
			m_text.pop_back();
		break;
	}
}


/* -------------------------------------------------------------------------- */


int Input::getCaretPx(const Renderer& ren) const
{
	return ren.getTextBounds(m_text.substr(0, m_caret)).xw;
}
}