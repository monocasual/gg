#include <cassert>
#include "../core/gg_renderer.hh"
#include "../core/gg_events.hh"
#include "../core/gg_utils.hh"
#include "gg_slider.hh"


namespace gg
{
Slider::Slider()
: Element (),
  onChange(nullptr),
  m_value (0.0f),
  m_type  (Type::VERTICAL)
{
}


/* -------------------------------------------------------------------------- */


void Slider::draw(Renderer& ren)
{
	ren.setColor(0, 0, 0);
	ren.fillRect(m_x, m_y, m_w, m_h);

	ren.setColor(255, 255, 255);
	ren.drawRect(m_x, m_y, m_w, m_h);

	if (m_type == Type::VERTICAL)
	{
		int y = utils::map<float, int>(m_value, 0.0f, 1.0f, m_h, 0);
		ren.fillRect(m_x, m_y + y, m_w, m_h - y);
	}
	else
		assert(false); // TODO
}


/* -------------------------------------------------------------------------- */


void Slider::mouseDown(const MouseEvent& e)
{
	compute(e.x, e.y);
}


/* -------------------------------------------------------------------------- */


void Slider::mouseDrag(const MouseEvent& e)
{
	compute(e.x, e.y);
}


/* -------------------------------------------------------------------------- */


void Slider::compute(int x, int y)
{
	if (m_type == Type::VERTICAL)
	{
		m_value = utils::map<int, float>(utils::clamp(y - m_y, 0, m_h), 0, m_h, 1.0f, 0.0f);
	}
	else
	{
		assert(false); // TODO
	}
	if (onChange != nullptr) onChange();
}

/* -------------------------------------------------------------------------- */


float Slider::getValue() const { return m_value; }


/* -------------------------------------------------------------------------- */


void Slider::setValue(float v)
{ 
	m_value = utils::clamp(v, 0.0f, 1.0f);
	if (onChange != nullptr) onChange();
}

} // gg::