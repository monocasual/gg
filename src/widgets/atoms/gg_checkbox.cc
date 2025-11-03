#include "gg_checkbox.hh"
#include "core/gg_events.hh"
#include "core/gg_renderer.hh"

namespace gg
{
Checkbox::Checkbox(bool status, std::string t)
: m_status(status)
, m_text(t)
{
}

/* -------------------------------------------------------------------------- */

void Checkbox::draw(Renderer& ren)
{
	const Style& style      = gg::getStyle();
	const int    padding    = 10;
	const auto   boxBounds  = m_bounds.withW(m_bounds.h);
	const auto   textBounds = m_bounds.reduced({m_bounds.h + padding, 0});

	ren.setColor(m_status ? m_enabled ? style.checkboxBoundaryColor() : style.checkboxBoundaryColorDisabled()
	                      : style.checkboxBackgroundColor());
	ren.fillRect(boxBounds);

	ren.setColor(m_enabled ? style.checkboxBoundaryColor() : style.checkboxBoundaryColorDisabled());
	ren.drawRect(boxBounds);

	if (m_text != "")
		ren.drawText(m_text.c_str(), textBounds, Renderer::TextAlign::LEFT);
}

/* -------------------------------------------------------------------------- */

void Checkbox::mouseUp(const MouseEvent& e)
{
	if (e.isOver(m_bounds))
		m_status = !m_status;
	if (onChange != nullptr)
		onChange(m_status);
	redraw();
}

/* -------------------------------------------------------------------------- */

bool Checkbox::getStatus() const
{
	return m_status;
}

/* -------------------------------------------------------------------------- */

void Checkbox::setStatus(bool s)
{
	m_status = s;
	redraw();
}
} // namespace gg