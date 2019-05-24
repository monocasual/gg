#ifndef GG_SLIDER_HH
#define GG_SLIDER_HH


#include <functional>
#include "../core/gg_element.hh"


namespace gg
{
class Renderer;
class Slider : public Element
{
public:

    enum class Type { VERTICAL, HORIZONTAL };

	Slider();

	void draw(Renderer& ren) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseDown(const MouseEvent& e) override;

    float getValue() const;

    void setValue(float v);

    std::function<void()> onChange;

private:

    float m_value;
    Type  m_type;

    void compute(int x, int y);
};
} // gg::


#endif
