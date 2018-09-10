
/* BaseGroup -----------------------------------------------------------------
 *
 * A generic base for every group.
 *
 * -------------------------------------------------------------------------- */


#ifndef GG_BASEGROUP_HH
#define GG_BASEGROUP_HH


#include <vector>
#include <SDL2/SDL.h>


namespace gg 
{
class Widget;


class BaseGroup
{
protected:

	std::vector<Widget*> m_widgets;

	BaseGroup();

public:

	/* SLD_Renderer
	Each group contains a public renderer. Any widget must refer to this pointer 
	in order to draw something. Also they can call other groups function to 
	refresh screen and such. Info on SDL renderer:
	http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer */

	SDL_Renderer* ren;

	/* damaged
	A damaged group must be redrawn. Each subwidget must set this flag to true 
	when it needs to update the screen. */

	bool damaged;

	virtual ~BaseGroup();

	virtual void add(Widget* w);
	virtual void add(Widget& w);

	virtual void drawChildren();
};
} // gg::


#endif
