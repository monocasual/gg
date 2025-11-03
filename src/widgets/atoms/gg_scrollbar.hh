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
	void resized() override;
	void mouseDrag(const MouseEvent& e) override;
	void mouseDown(const MouseEvent& e) override;

	float getValue() const;

	void setPosition(int p, bool fireCallback = true);
	void setValue(float v, bool fireCallback = true);
	void setRange(geompp::Range<float> r);
	void setHandleSize(int s);

	std::function<void(float)> onChange;

private:
	static constexpr int                  MIN_HANDLE_SIZE = 20;
	static constexpr geompp::Range<float> DEFAULT_RANGE   = {0.0f, 1.0f};

	int getMaxPosition() const;
	int getAxis(geompp::Point<int> p) const;

	Type                 m_type;
	geompp::Range<float> m_range;
	geompp::Range<int>   m_handle;
	float                m_value;
};
} // namespace gg

#endif
