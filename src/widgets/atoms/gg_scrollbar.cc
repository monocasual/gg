#include "gg_scrollbar.hh"
#include "core/gg_events.hh"
#include "core/gg_renderer.hh"
#include "deps/mcl-utils/src/math.hpp"

using namespace mcl;

namespace gg
{
Scrollbar::Scrollbar(Type t)
: Element()
, onChange(nullptr)
, m_type(t)
, m_range(MIN_DEFAULT_RANGE, MAX_DEFAULT_RANGE)
, m_value(MIN_DEFAULT_RANGE)
, m_handleSize(MIN_HANDLE_SIZE)
{
}

/* -------------------------------------------------------------------------- */

void Scrollbar::draw(Renderer& ren)
{
	ren.setColor(gg::getStyle().scrollbarBackgroundColor());
	ren.fillRect(m_bounds);

	ren.setColor(gg::getStyle().scrollbarBodyColor());
	ren.drawRect(m_bounds);

	if (m_type == Type::VERTICAL)
	{
		int y = utils::math::map(m_value, m_range.a, m_range.b, 0, getH() - m_handleSize);
		ren.fillRect(getX(), getY() + y, getW(), m_handleSize);
	}
	else
	{
		int x = utils::math::map(m_value, m_range.a, m_range.b, 0, getW() - m_handleSize);
		ren.fillRect(getX() + x, getY(), m_handleSize, getH());
	}
}

/* -------------------------------------------------------------------------- */

void Scrollbar::mouseDown(const MouseEvent& e) { set(e); }

/* -------------------------------------------------------------------------- */

void Scrollbar::mouseDrag(const MouseEvent& e) { set(e); }

/* -------------------------------------------------------------------------- */

float Scrollbar::getValue() const { return m_value; }

/* -------------------------------------------------------------------------- */

void Scrollbar::setRange(geompp::Range<float> r) { m_range = r; }

/* -------------------------------------------------------------------------- */

void Scrollbar::setHandleSize(int s)
{
	m_handleSize = std::min(std::max(s, MIN_HANDLE_SIZE), m_type == Type::HORIZONTAL ? getW() : getH());
}

/* -------------------------------------------------------------------------- */

void Scrollbar::setValue(float v, bool fireCallback)
{
	m_value = std::clamp(v, m_range.a, m_range.b);
	if (onChange != nullptr && fireCallback)
		onChange(m_value);
}

/* -------------------------------------------------------------------------- */

void Scrollbar::set(const MouseEvent& e)
{
	/* Don't set value if handle fits the scrollbar entirely. */

	if ((m_type == Type::HORIZONTAL && m_handleSize == getW()) ||
	    (m_type == Type::VERTICAL && m_handleSize == getH()))
		return;

	if (m_type == Type::VERTICAL)
		setValue(utils::math::map(e.position.y - getY(), 0, getH() - m_handleSize, m_range.a, m_range.b));
	else
		setValue(utils::math::map(e.position.x - getX(), 0, getW() - m_handleSize, m_range.a, m_range.b));
}
} // namespace gg