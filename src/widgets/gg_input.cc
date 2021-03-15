#include "core/gg_renderer.hh"
#include "core/gg_events.hh"
#include "gg_input.hh"


namespace gg
{
Input::Input() : Element()
{
}


/* -------------------------------------------------------------------------- */


void Input::draw(Renderer& ren)
{
	ren.setColor(Color{ 0, 0, 0 });
	ren.fillRect(m_bounds);

	if (m_text != "")
	{
		ren.setColor(Color{ 255, 255, 255 });
		ren.drawText(m_text, m_bounds);
	}

	if (m_focus)
	{
		ren.setColor(Color{ 150, 150, 150 });
		ren.drawRect(m_bounds);
	}
}


/* -------------------------------------------------------------------------- */


void Input::keyPress(const KeyEvent& e)
{
	m_text += e.ch;
    printf("%s\n", e.ch);
}
}