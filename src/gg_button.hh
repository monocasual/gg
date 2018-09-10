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

	std::function<void()> m_onDown;
	std::function<void()> m_onUp;

	bool m_down;

	const char* m_label;

	void drawDown();

public:

	Button(const char* l=nullptr);

	void draw() override;
	void handle(const SDL_Event& e) override;

	void onDown(std::function<void()> f);
	void onUp(std::function<void()> f);
};
} // gg::


#endif
