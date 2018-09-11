#ifndef GG_WINDOW_HH
#define GG_WINDOW_HH


#include <SDL2/SDL.h>
#include "gg_element.hh"


namespace gg 
{
class Window : public Element
{
	friend Element;

public:

	/* id
	Unique id of this window. */

	unsigned id;

	Window(const char* t, int x, int y, int w, int h);
	~Window();

	void handle(const SDL_Event& e) override;

	/* xywh()
	Sets and return coordinates. */

	int getX() const;
	int getY() const;
	int getW() const;
	int getH() const;

	/* clear()
	Deletes all widget from screen and cover it with the regular background. */

	void clear();

	/* render()
	Updates the screen after the children have been drawn. */

	void render();

protected:

	/* xywh
	Main coordinates. */

	int m_x, m_y, m_w, m_h;

	/* win
	Pointer to a SDL_Window structure. */

	SDL_Window* m_win;


	/* SLD_Renderer
	Each window contains a renderer. Any widget must refer to this pointer 
	in order to draw something. Also they can call other groups function to 
	refresh screen and such. Info on SDL renderer:
	http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer */

	SDL_Renderer* m_ren;
};
} // gg::


#endif
