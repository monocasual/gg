/* Element ---------------------------------------------------------------------

A generic base for everything.

----------------------------------------------------------------------------- */


#ifndef GG_ELEMENT_HH
#define GG_ELEMENT_HH


#include <vector>
#include <SDL2/SDL.h>
#include "gg.hh"


namespace gg 
{
class Window;
class Renderer;
class MouseEvent;
class Element
{
public:

	virtual ~Element() {};

	/* handle() [virtual]
	Fired on events such as click, keypress, window show-hide and so on. */

	virtual void handle(const SDL_Event& e);

	/* resized() [virtuals]
	Fired when the element position and size change. */

	virtual void resized() {};

	/* draw() [virtual]
	Drawing routines. This method draws the initial graphical state of each 
	widget. */

	virtual void draw(Renderer& ren);

	virtual void mouseDown(const MouseEvent&) {};
	virtual void mouseUp(const MouseEvent&) {};
	virtual void mouseMove(const MouseEvent&) {};
	virtual void mouseDrag(const MouseEvent&) {};

	/* redraw() [virtual]
	Forces the redraw for this element and all its children. */

	virtual void redraw();

	/* add()
	Adds a child widget to this element. */

	void add(Element* w);
	void add(Element& w);

	int getX() const  { return m_bounds.x; }
	int getY() const  { return m_bounds.y; }
	int getW() const  { return m_bounds.w; }
	int getH() const  { return m_bounds.h; }
	int getXW() const { return m_bounds.xw; }
	int getYH() const { return m_bounds.yh; }
	Rect getBounds() const { return m_bounds; }

	void setBounds(int x, int y, int w, int h);
	void setBounds(Rect b);

protected:

	Element(Rect r=Rect());

	/* drawChildren [virtual]
	Draws all children of this element. */

	virtual void drawChildren(Renderer& ren);

	Window* getParentWindow();

	/* m_bounds
	Main coordinates. */

	Rect m_bounds;

	/* parent
	Widgets belong to a parent, that is a Window or another Element (groups). */

	Element* m_parent;

	/* elements
	Lists of children elements contained into this Element. */

	std::vector<Element*> m_elements;

	/* m_mouseDown
	Tells whether the mouse has been held down on this element. */
	
	bool m_mouseDown;
};
} // gg::


#endif
