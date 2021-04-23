#ifndef GG_WINDOW_HH
#define GG_WINDOW_HH

#include "gg_element.hh"
#include "gg_renderer.hh"
#include <SDL2/SDL.h>

namespace gg
{
class Window : public Element
{
	friend Element;

public:
	/* id
	Unique id of this window. */

	unsigned id;

	~Window();

	/* close [virtual]
	Invoked when the 'x' button is pressed. */

	virtual void closed(){};

	void handle(const SDL_Event& e) override;

	/* clear()
	Deletes all widget from screen and cover it with the regular background. */

	void clear();

	/* render()
	Render everything on this window. To be called by sub-elements when they
	are handling UI-changing events. */

	void render();

	/* setModal
	Creates a modal window. Call this before adding the window to the gg main
	loop. */

	void setModal(const Window* parent);

	void show();
	void hide();

	void setResizable(bool v);

protected:
	Window(const std::string& title, int x, int y, int w, int h);

	/* win
	Pointer to a SDL_Window structure. */

	SDL_Window* m_win;

	/* SLD_Renderer
	Each window contains a renderer. Any widget must refer to this pointer 
	in order to draw something. Also they can call other groups function to 
	refresh screen and such. */

	Renderer m_ren;
};
} // namespace gg

#endif
