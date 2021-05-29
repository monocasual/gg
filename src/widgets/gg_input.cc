#include "gg_input.hh"
#include "core/gg_events.hh"
#include "core/gg_renderer.hh"

namespace gg
{
Input::Input()
: Element()
, m_caret(0)
, m_editable(true)
{
}

/* -------------------------------------------------------------------------- */

void Input::draw(Renderer& ren)
{
	ren.setColor(gg::getStyle().inputBackgroundColor());
	ren.fillRect(m_bounds);

	if (!m_text.empty())
	{
		ren.setColor(gg::getStyle().inputTextColor());
		ren.drawText(m_text, m_bounds.reduced(5, 0), Renderer::TextAlign::LEFT);
	}

	if (m_focus && m_editable)
	{
		ren.setColor(gg::getStyle().inputFocusColor());
		ren.drawRect(m_bounds);
		ren.drawLine(m_bounds.reduced(5, 5).getHeightAsLine().withShiftedX(getCaretPx(ren)));
	}
}

/* -------------------------------------------------------------------------- */

void Input::keyPress(const KeyEvent& e)
{
	if (!m_editable)
		return;

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

void Input::setEditable(bool v) { m_editable = v; }
void Input::setText(const std::string& s) { m_text = s; }

/* -------------------------------------------------------------------------- */

int Input::getCaretPx(const Renderer& ren) const
{
	return ren.getTextBounds(m_text.substr(0, m_caret)).xw;
}
} // namespace gg