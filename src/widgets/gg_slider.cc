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
	ren.setColor(Color{0, 0, 0});
	ren.fillRect(m_bounds);

	ren.setColor(Color{255, 255, 255});
	ren.drawRect(m_bounds);

	if (m_type == Type::VERTICAL)
	{
		int y = utils::math::map<float, int>(m_value, 0.0f, 1.0f, getH(), 0);
		ren.fillRect(getX(), getY() + y, getW(), getH() - y);
	}
	else
	{
		int x = utils::math::map<float, int>(m_value, 0.0f, 1.0f, 0, getW());
		ren.fillRect(getX(), getY(), x, getH());
	}
}

/* -------------------------------------------------------------------------- */

void Slider::mouseDown(const MouseEvent& e)
{
	compute(e.position.x, e.position.y);
}

/* -------------------------------------------------------------------------- */

void Slider::mouseDrag(const MouseEvent& e)
{
	compute(e.position.x, e.position.y);
}

/* -------------------------------------------------------------------------- */

void Slider::compute(int x, int y)
{
	if (m_type == Type::VERTICAL)
		m_value = utils::math::map<int, float>(std::clamp(y - getY(), 0, getH()), 0, getH(), 1.0f, 0.0f);
	else
		m_value = utils::math::map<int, float>(std::clamp(x - getX(), 0, getW()), 0, getW(), 0.0f, 1.0f);

	if (onChange != nullptr)
		onChange();
}

/* -------------------------------------------------------------------------- */

float Slider::getValue() const { return m_value; }

/* -------------------------------------------------------------------------- */

void Slider::setValue(float v)
{
	m_value = std::clamp(v, 0.0f, 1.0f);
	if (onChange != nullptr)
		onChange();
}

} // namespace gg