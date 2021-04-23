#include "gg_alert.hh"

namespace gg
{
Alert::Alert(const std::string& title, const std::string& text)
: Window(title, 0, 0, 400, 150)
, m_box(text)
{
	setResizable(false);
	setModal(getParentWindow());
	add(m_box);
}

/* -------------------------------------------------------------------------- */

void Alert::resized()
{
	m_box.setBounds(getBounds());
}

/* -------------------------------------------------------------------------- */

void Alert::closed()
{
	gg::removeWindow(this);
}
} // namespace gg