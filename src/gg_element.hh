
/* Element ---------------------------------------------------------------------

A generic base for everything.

----------------------------------------------------------------------------- */


#ifndef GG_ELEMENT_HH
#define GG_ELEMENT_HH


#include <vector>
#include <SDL2/SDL.h>


namespace gg 
{
class Element
{
protected:

	/* xywh
	Main coordinates. */

	int m_x, m_y, m_w, m_h;

	/* parent
	Widgets belong to a parent, that is a Window or another Element (groups). */

	Element* m_parent;

	/* elements
	Lists of children elements contained into this Element. */

	std::vector<Element*> m_elements;

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

	/* draw() [virtual]
	Drawing routines. This method draws the initial graphical state of each 
	widget. */

	virtual void draw(SDL_Renderer* ren) {};

	/* add()
	Adds a child widget to this element. */

	virtual void add(Element* w);

	virtual void drawChildren();

	virtual void setBounds(int x, int y, int w, int h);

	virtual int getX() const  { return m_x; }
	virtual int getY() const  { return m_y; }
	virtual int getW() const  { return m_w; }
	virtual int getH() const  { return m_h; }
	virtual int getXW() const { return m_x + m_w; }
	virtual int getYH() const { return m_y + m_h; }

	virtual void redraw();
};
} // gg::


#endif
