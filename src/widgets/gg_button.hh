#ifndef GG_BUTTON_HH
#define GG_BUTTON_HH

#include "core/gg_element.hh"
#include <functional>

namespace gg
{
class Renderer;
class Button : public Element
{
public:
	Button(std::string l = "");

	void draw(Renderer& ren) override;
	void mouseUp(const MouseEvent& e) override;

	std::function<void()> onClick;

private:
	void drawDown(Renderer& ren);
	void drawUp(Renderer& ren);

	std::string m_label;
};
} // namespace gg

#endif
