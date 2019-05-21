#ifndef GG_BUTTON_HH
#define GG_BUTTON_HH


#include <functional>
#include "../core/gg_element.hh"


namespace gg
{
class Renderer;
class Button : public Element
{
public:

	Button(const char* l=nullptr);

	void draw(Renderer& ren) override;
    void mouseUp(const MouseEvent& e) override;

	std::function<void()> onClick;

private:

	void drawDown(Renderer& ren);
	void drawUp(Renderer& ren);

	const char* m_label;
};
} // gg::


#endif
