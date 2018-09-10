#ifndef GG_BUTTON_HH
#define GG_BUTTON_HH


#include <functional>
#include "gg_widget.hh"


namespace gg
{
class Button : public Widget
{
private:

	SDL_Rect m_rect;

	std::function<void()> m_onDown = nullptr;
	std::function<void()> m_onUp   = nullptr;

	bool m_down = false;

	void drawDown();

public:

	Button(int x, int y, int w, int h, const char* l=nullptr);

	void resize(int w, int h) override;
	void draw() override;
	void handle(const SDL_Event& e) override;

	void onDown(std::function<void()> f);
	void onUp(std::function<void()> f);
};
} // gg::


#endif
