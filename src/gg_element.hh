
/* Element ---------------------------------------------------------------------

A generic base for everything.

----------------------------------------------------------------------------- */


#ifndef GG_ELEMENT_HH
#define GG_ELEMENT_HH


#include <vector>
#include <SDL2/SDL.h>


namespace gg 
{
class Widget;


class Element
{
protected:

	std::vector<Widget*> m_widgets;

	Element();

public:

	/* SLD_Renderer
	Each group contains a public renderer. Any widget must refer to this pointer 
	in order to draw something. Also they can call other groups function to 
	refresh screen and such. Info on SDL renderer:
	http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer */

	SDL_Renderer* ren;

	virtual ~Element();

	/* handle() [virtual]
	Fired on events such as click, keypress, window show-hide and so on. */

	virtual void handle(const SDL_Event& e) {};

	/* resized() [virtuals]
	Fired when the element position and size change. */

	virtual void resized() {};

	/* add()
	Adds a child widget to this element. */

	virtual void add(Widget* w);
	virtual void add(Widget& w);

	virtual void drawChildren();

	void redraw(Widget* w);
};
} // gg::


#endif
