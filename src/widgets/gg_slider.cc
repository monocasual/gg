#include <cassert>
#include "../core/gg_renderer.hh"
#include "../core/gg_events.hh"
#include "../core/gg_utils.hh"
#include "gg_slider.hh"


namespace gg
{
Slider::Slider(Type t)
: Element (),
  onChange(nullptr),
  m_value (0.0f),
  m_type  (t)
{
}


/* -------------------------------------------------------------------------- */


void Slider::draw(Renderer& ren)
{
	ren.setColor(Color{ 0, 0, 0 });
	ren.fillRect(m_x, m_y, m_w, m_h);

	ren.setColor(Color{ 255, 255, 255 });
	ren.drawRect(m_x, m_y, m_w, m_h);

	if (m_type == Type::VERTICAL)
	{
		int y = utils::map<float, int>(m_value, 0.0f, 1.0f, m_h, 0);
		ren.fillRect(m_x, m_y + y, m_w, m_h - y);
	}
	else
	{
		int x = utils::map<float, int>(m_value, 0.0f, 1.0f, 0, m_w);
		ren.fillRect(m_x, m_y, x, m_h);
	}
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
		m_value = utils::map<int, float>(utils::clamp(y - m_y, 0, m_h), 0, m_h, 1.0f, 0.0f);
	else
		m_value = utils::map<int, float>(utils::clamp(x - m_x, 0, m_w), 0, m_w, 0.0f, 1.0f);

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