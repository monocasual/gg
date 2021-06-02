#include "gg_slider.hh"
#include "core/gg_events.hh"
#include "core/gg_renderer.hh"
#include "deps/mcl-utils/src/math.hpp"
#include <algorithm>
#include <cassert>

using namespace mcl;

namespace gg
{
Slider::Slider(Type t)
: Element()
, onChange(nullptr)
, m_value(0.0f)
, m_type(t)
{
}

/* -------------------------------------------------------------------------- */

void Slider::draw(Renderer& ren)
{
	ren.setColor(gg::getStyle().sliderBackgroundColor());
	ren.fillRect(m_bounds);

	ren.setColor(gg::getStyle().sliderBodyColor());
	ren.drawRect(m_bounds);

	if (m_type == Type::VERTICAL)
	{
		int y = utils::math::map(m_value, 0.0f, 1.0f, getH(), 0);
		ren.fillRect(getX(), getY() + y, getW(), getH() - y);
	}
	else
	{
		int x = utils::math::map(m_value, 0.0f, 1.0f, 0, getW());
		ren.fillRect(getX(), getY(), x, getH());
	}
}

/* -------------------------------------------------------------------------- */

void Slider::mouseDown(const MouseEvent& e)
{
	set(e);
}

/* -------------------------------------------------------------------------- */

void Slider::mouseDrag(const MouseEvent& e)
{
	set(e);
}

/* -------------------------------------------------------------------------- */

float Slider::getValue() const { return m_value; }

/* -------------------------------------------------------------------------- */

void Slider::setValue(float v, bool fireCallback)
{
	m_value = std::clamp(v, 0.0f, 1.0f);
	if (onChange != nullptr && fireCallback)
		onChange();
}

/* -------------------------------------------------------------------------- */

void Slider::set(const MouseEvent& e)
{
	if (m_type == Type::VERTICAL)
		setValue(utils::math::map(e.position.y - getY(), 0, getH(), 1.0f, 0.0f));
	else
		setValue(utils::math::map(e.position.x - getX(), 0, getW(), 0.0f, 1.0f));
}
} // namespace gg