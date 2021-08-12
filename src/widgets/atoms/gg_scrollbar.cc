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
, m_range(DEFAULT_RANGE)
, m_position(0)
, m_value(m_range.a)
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
		ren.fillRect(m_bounds.withShiftedY(m_position).withH(m_handleSize));
	else
		ren.fillRect(m_bounds.withShiftedX(m_position).withW(m_handleSize));
}

/* -------------------------------------------------------------------------- */
void Scrollbar::resized()
{
	// Make sure handle doesn't overflow in case it has been set manually.
	m_handleSize = std::min(m_handleSize, m_type == Type::HORIZONTAL ? getW() : getH());

	// Update position here, in case value has been set manually.
	m_position = utils::math::map(m_value, m_range.a, m_range.b, 0, getMaxPosition());
}

/* -------------------------------------------------------------------------- */

void Scrollbar::mouseDown(const MouseEvent& e)
{
	setPosition(getAxis(e.relativeTo(*this).position));
}

/* -------------------------------------------------------------------------- */

void Scrollbar::mouseDrag(const MouseEvent& e)
{
	setPosition(getAxis(e.relativeTo(*this).position));
}

/* -------------------------------------------------------------------------- */

float Scrollbar::getValue() const
{
	return utils::math::map(m_position, 0, getMaxPosition(), m_range.a, m_range.b);
}

/* -------------------------------------------------------------------------- */

void Scrollbar::setRange(geompp::Range<float> r) { m_range = r; }

/* -------------------------------------------------------------------------- */

void Scrollbar::setHandleSize(int s)
{
	m_handleSize = std::max(s, MIN_HANDLE_SIZE);
}

/* -------------------------------------------------------------------------- */

void Scrollbar::setValue(float v, bool fireCallback)
{
	m_value = std::clamp(v, m_range.a, m_range.b);

	if (onChange != nullptr && fireCallback)
		onChange(m_value);
}

/* -------------------------------------------------------------------------- */

int Scrollbar::getMaxPosition() const
{
	return (m_type == Type::HORIZONTAL ? getW() : getH()) - m_handleSize;
}

/* -------------------------------------------------------------------------- */

int Scrollbar::getAxis(geompp::Point<int> p) const
{
	return m_type == Type::HORIZONTAL ? p.x : p.y;
}

/* -------------------------------------------------------------------------- */

void Scrollbar::setPosition(int p, bool fireCallback)
{
	/* Don't set value if handle fits the scrollbar entirely. */

	if ((m_type == Type::HORIZONTAL && m_handleSize == getW()) ||
	    (m_type == Type::VERTICAL && m_handleSize == getH()))
		return;

	m_position = std::min(std::max(0, p), getMaxPosition());

	if (onChange != nullptr && fireCallback)
		onChange(getValue());
}
} // namespace gg