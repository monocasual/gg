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
, m_value(0.0f)
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
		int y = utils::math::map(m_value, m_range.a, m_range.b, 0, getH() - MIN_HANDLE_SIZE);
		ren.fillRect(getX(), getY() + y, getW(), MIN_HANDLE_SIZE);
	}
	else
	{
		int x = utils::math::map(m_value, m_range.a, m_range.b, 0, getW() - MIN_HANDLE_SIZE);
		ren.fillRect(getX() + x, getY(), MIN_HANDLE_SIZE, getH());
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

void Scrollbar::setValue(float v, bool fireCallback)
{
	m_value = std::clamp(v, m_range.a, m_range.b);
	if (onChange != nullptr && fireCallback)
		onChange(m_value);
}

/* -------------------------------------------------------------------------- */

void Scrollbar::set(const MouseEvent& e)
{
	if (m_type == Type::VERTICAL)
		setValue(utils::math::map(e.position.y - getY(), 0, getH(), m_range.a, m_range.b));
	else
		setValue(utils::math::map(e.position.x - getX(), 0, getW(), m_range.a, m_range.b));
}
} // namespace gg