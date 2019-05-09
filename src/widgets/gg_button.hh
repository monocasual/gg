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
	void handle(const SDL_Event& e) override;

	std::function<void()> onDown;
	std::function<void()> onUp;

private:

	bool m_down;

	const char* m_label;

	void drawDown(Renderer& ren);
	void drawUp(Renderer& ren);
};
} // gg::


#endif
