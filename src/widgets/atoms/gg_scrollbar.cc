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
, m_handle(0, MIN_HANDLE_SIZE)
, m_value(m_range.getA())
, m_pinch(0)
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
		ren.fillRect(m_bounds.withShiftedY(m_handle.getA()).withH(m_handle.getLength()));
	else
		ren.fillRect(m_bounds.withShiftedX(m_handle.getA()).withW(m_handle.getLength()));
}

/* -------------------------------------------------------------------------- */

void Scrollbar::resized()
{
	// Update position here, in case value has been set manually.
	m_handle.move(utils::math::map(m_value, m_range.getA(), m_range.getB(), 0, getMaxPosition()));
}

/* -------------------------------------------------------------------------- */

void Scrollbar::mouseDown(const MouseEvent& e)
{
	const int mousePos = getAxis(e.relativeTo(*this).position);

	/* Update pinch point: the point where the cursor lies within the handle. */

	m_pinch = mousePos - m_handle.getA();

	/* Not much to do if the mouse is over the handle: no position change is necessary. */

	if (m_handle.contains(mousePos))
		return;

	/* If the mouse is NOT over the handle, just move the handle there so that
	the mouse cursor is right at the middle point. This requires the pinch point
	to be updated accordingly. */

	const int handleHalf = m_handle.getLength() / 2;
	const int handlePos  = mousePos - handleHalf;

	m_pinch = handleHalf;

	setPosition(handlePos);
}

/* -------------------------------------------------------------------------- */

void Scrollbar::mouseDrag(const MouseEvent& e)
{
	const int mousePos = getAxis(e.relativeTo(*this).position);
	const int position = mousePos - m_pinch;

	setPosition(position);
}

/* -------------------------------------------------------------------------- */

void Scrollbar::mouseUp(const MouseEvent&)
{
	m_pinch = 0;
}

/* -------------------------------------------------------------------------- */

float Scrollbar::getValue() const
{
	return utils::math::map(m_handle.getA(), 0, getMaxPosition(), m_range.getA(), m_range.getB());
}

/* -------------------------------------------------------------------------- */

void Scrollbar::setRange(geompp::Range<float> r) { m_range = r; }

/* -------------------------------------------------------------------------- */

void Scrollbar::setHandleSize(int s)
{
	m_handle.setLength(std::max(s, MIN_HANDLE_SIZE));
}

/* -------------------------------------------------------------------------- */

void Scrollbar::setValue(float v, bool fireCallback)
{
	m_value = std::clamp(v, m_range.getA(), m_range.getB());

	if (onChange != nullptr && fireCallback)
		onChange(m_value);
}

/* -------------------------------------------------------------------------- */

int Scrollbar::getMaxPosition() const
{
	return (m_type == Type::HORIZONTAL ? getW() : getH()) - m_handle.getLength();
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

	if ((m_type == Type::HORIZONTAL && m_handle.getLength() == getW()) ||
	    (m_type == Type::VERTICAL && m_handle.getLength() == getH()))
		return;

	m_handle.move(std::min(std::max(0, p), getMaxPosition()));
	m_value = getValue();

	if (onChange != nullptr && fireCallback)
		onChange(getValue());
}
} // namespace gg