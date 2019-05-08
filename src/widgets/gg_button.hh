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

	void onDown(std::function<void()> f);
	void onUp(std::function<void()> f);

private:

	std::function<void()> m_onDown;
	std::function<void()> m_onUp;

	bool m_down;

	const char* m_label;

	void drawDown(Renderer& ren);
	void drawUp(Renderer& ren);
};
} // gg::


#endif
