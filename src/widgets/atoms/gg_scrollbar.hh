#ifndef GG_SCROLLBAR_HH
#define GG_SCROLLBAR_HH

#include "core/gg_element.hh"
#include "deps/geompp/src/range.hpp"
#include <functional>

namespace gg
{
class Renderer;
class Scrollbar : public Element
{
public:
	enum class Type
	{
		VERTICAL,
		HORIZONTAL
	};

	Scrollbar(Type t = Type::VERTICAL);

	void draw(Renderer& ren) override;
	void mouseDrag(const MouseEvent& e) override;
	void mouseDown(const MouseEvent& e) override;

	float getValue() const;

	void setValue(float v, bool fireCallback = true);
	void setRange(geompp::Range<float> r);

	std::function<void(float)> onChange;

private:
	static constexpr int   MIN_HANDLE_SIZE   = 20;
	static constexpr float MIN_DEFAULT_RANGE = 0.0f;
	static constexpr float MAX_DEFAULT_RANGE = 1.0f;

	void set(const MouseEvent& e);

	Type                 m_type;
	geompp::Range<float> m_range;
	float                m_value;
};
} // namespace gg

#endif
