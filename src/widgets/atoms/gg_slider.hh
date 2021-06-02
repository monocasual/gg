#ifndef GG_SLIDER_HH
#define GG_SLIDER_HH

#include "core/gg_element.hh"
#include <functional>

namespace gg
{
class Renderer;
class Slider : public Element
{
public:
	enum class Type
	{
		VERTICAL,
		HORIZONTAL
	};

	Slider(Type t = Type::VERTICAL);

	void draw(Renderer& ren) override;
	void mouseDrag(const MouseEvent& e) override;
	void mouseDown(const MouseEvent& e) override;

	float getValue() const;

	void setValue(float v, bool fireCallback = true);

	std::function<void()> onChange;

private:
	void set(const MouseEvent& e);

	float m_value;
	Type  m_type;
};
} // namespace gg

#endif
