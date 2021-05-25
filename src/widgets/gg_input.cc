#include "gg_input.hh"
#include "core/gg_events.hh"
#include "core/gg_renderer.hh"

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
	ren.setColor(Color{0, 0, 0});
	ren.fillRect(m_bounds);

	if (!m_text.empty())
	{
		ren.setColor(Color{255, 255, 255});
		ren.drawText(m_text, m_bounds, Renderer::TextAlign::LEFT);
	}

	if (m_focus)
	{
		ren.setColor(Color{150, 150, 150});
		ren.drawRect(m_bounds);
		ren.drawLine(m_bounds.getHeightAsLine().withShiftedX(getCaretPx(ren)));
	}
}

/* -------------------------------------------------------------------------- */

void Input::keyPress(const KeyEvent& e)
{
	switch (e.type)
	{
	case KeyEvent::Type::TEXT:
		m_text.insert(m_caret++, e.ch);
		break;

	case KeyEvent::Type::BACKSPACE:
		if (m_caret > 0)
			m_text.erase(--m_caret);
		break;

	case KeyEvent::Type::DELETE:
		//if (m_caret > 0)
		m_text.erase(m_caret);
		break;

	case KeyEvent::Type::ARROW_LEFT:
		if (m_caret > 0)
			m_caret--;
		break;

	case KeyEvent::Type::ARROW_RIGHT:
		if (m_caret < m_text.length())
			m_caret++;
		break;

	default:
		break;
	}
}

/* -------------------------------------------------------------------------- */

void Input::mouseDown(const MouseEvent& e)
{ /*
	switch (e.type)
	{

	default:
		break;
	}*/
}

/* -------------------------------------------------------------------------- */

int Input::getCaretPx(const Renderer& ren) const
{
	return ren.getTextBounds(m_text.substr(0, m_caret)).xw;
}
} // namespace gg